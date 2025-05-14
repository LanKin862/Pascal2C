#include "../include/PascalToCTranslator.h"

#include <antlr4-runtime.h>

#include <fstream>
#include <regex>

#include "../antlr/PascalSLexer.h"
#include "../antlr/PascalSParser.h"
#include "../include/TranslatorUtils.h"

/**
 * Pascal到C翻译器的构造函数
 * 初始化符号表、类型转换器和其他状态变量
 */
PascalToCTranslator::PascalToCTranslator()
        : symbolTable(new SymbolTable()),  // 直接使用 new 构造 unique_ptr
          typeConverter(new TypeConverter()),
          indentation(""),
          isInGlobalScope(true),
          tempVarCounter(0) {
}

/**
 * 将Pascal代码转换为C代码的主翻译方法
 * @param inputFile Pascal源文件的路径
 * @return 包含翻译后C代码的字符串
 */
std::string PascalToCTranslator::translate(const std::string &inputFile) {
    // 清除状态进行全新翻译
    output.str("");
    indentation = "";
    isInGlobalScope = true;
    tempVarCounter = 0;

    // 设置ANTLR解析器组件
    std::ifstream stream;
    stream.open(inputFile);
    antlr4::ANTLRInputStream input(stream);
    PascalSLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    PascalSParser parser(&tokens);

    // 解析输入文件生成AST
    PascalSParser::ProgramContext *tree = parser.program();

    // 访问解析树并生成C代码
    try {
        visitProgram(tree);
    } catch (const TranslatorException &e) {
        TranslatorUtils::logError(e.what());
        return "";
    }

    // 返回生成的C代码
    return output.str();
}

/**
 * 增加一个单位的缩进级别（4个空格）
 */
void PascalToCTranslator::increaseIndentation() {
    indentation += "    ";
}

/**
 * 减少一个单位的缩进级别（4个空格）
 * 确保缩进不会变为负值
 */
void PascalToCTranslator::decreaseIndentation() {
    if (!indentation.empty()) {
        indentation.resize(indentation.size() - 4);
    }
}

/**
 * 返回当前缩进字符串
 * @return 当前缩进，表示为空格字符串
 */
std::string PascalToCTranslator::getCurrentIndentation() const {
    return indentation;
}

/**
 * 生成唯一的临时变量名
 * @return 表示新临时变量的字符串
 */
std::string PascalToCTranslator::getNextTempVar() {
    return "temp_" + std::to_string(tempVarCounter++);
}

/**
 * 处理程序节点，这是解析树的根
 * 生成Pascal程序所需的标准包含和辅助函数
 * @param context 解析器中的程序上下文
 * @return 访问者模式的标准占位符
 */
antlrcpp::Any PascalToCTranslator::visitProgram(PascalSParser::ProgramContext *context) {
    // 生成Pascal功能所需的标准C包含
    output << "#include <stdio.h>\n";
    output << "#include <stdlib.h>\n";
    output << "#include <stdbool.h>\n";
    output << "#include <string.h>\n";
    output << "#include <stdarg.h>\n\n";

    // 定义Pascal特定类型和辅助函数
    output << "// Pascal特定函数和类型\n";
    output << "typedef int boolean;\n";
    output << "typedef char *string;\n\n";

    // 访问程序结构节点
    return visit(context->programStruct());
}

/**
 * 处理由头部和主体组成的程序结构
 * @param context 解析器中的程序结构上下文
 * @return 访问者模式的标准占位符
 */
antlrcpp::Any PascalToCTranslator::visitProgramStruct(PascalSParser::ProgramStructContext *context) {
    // 访问程序头部（名称和参数）
    visit(context->programHead());

    // 访问程序主体（声明和语句）
    visit(context->programBody());

    return antlrcpp::Any();
}

/**
 * 处理包含程序名称的程序头部
 * @param context 解析器中的程序头部上下文
 * @return 访问者模式的标准占位符
 */
antlrcpp::Any PascalToCTranslator::visitProgramHead(PascalSParser::ProgramHeadContext *context) {
    // 提取程序名称
    std::string programName = context->ID()->getText();

    // 在C代码中添加程序名称作为注释
    output << "// 程序: " << programName << "\n\n";

    return antlrcpp::Any();
}

/**
 * 处理包含声明和复合语句的程序主体
 * @param context 解析器中的程序主体上下文
 * @return 访问者模式的标准占位符
 */
antlrcpp::Any PascalToCTranslator::visitProgramBody(PascalSParser::ProgramBodyContext *context) {
    // 如果存在常量声明则处理
    if (context->constDeclarations()) {
        visit(context->constDeclarations());
    }

    // 如果存在变量声明则处理
    if (context->varDeclarations()) {
        visit(context->varDeclarations());
    }

    // 首先为所有子程序创建前向声明以处理函数引用
    if (context->subprogramDeclarations()) {
        // 创建临时字符串流来收集前向声明
        std::stringstream forwardDeclsStream;
        std::stringstream tempOutput = std::move(output);
        output = std::move(forwardDeclsStream);

        output << "// 前向声明\n";
        generateForwardDeclarations(context->subprogramDeclarations());
        output << "\n";

        // 恢复原始输出并添加前向声明
        std::string forwardDecls = output.str();
        output = std::move(tempOutput);
        output << forwardDecls;
    }

    // 如果存在子程序（函数/过程）声明则处理
    if (context->subprogramDeclarations()) {
        visit(context->subprogramDeclarations());
    }

    // 生成main函数
    output << "int main() {\n";
    increaseIndentation();

    // 访问主程序的复合语句
    if (context->compoundStatement()) {
        visit(context->compoundStatement());
    }

    // 向main添加return语句
    output << getCurrentIndentation() << "return 0;\n";

    decreaseIndentation();
    output << "}\n";

    return antlrcpp::Any();
}

/**
 * Helper method to generate forward declarations for all functions and procedures
 * This is needed to handle function references and maintain proper parameter types
 * @param context The subprogram declarations context
 */
void PascalToCTranslator::generateForwardDeclarations(PascalSParser::SubprogramDeclarationsContext *context) {
    if (!context) return;

    // Then process any nested declarations first (earlier in source)
    if (context->subprogramDeclarations()) {
        generateForwardDeclarations(context->subprogramDeclarations());
    }
    // Process the current subprogram (later in source)
    if (context->subprogram()) {
        PascalSParser::SubprogramHeadContext *headContext = context->subprogram()->subprogramHead();
        if (headContext) {
            std::string name = TranslatorUtils::toCIdentifier(headContext->ID()->getText());
            bool isFunction = headContext->FUNCTION() != nullptr;

            // Get return type for functions
            std::string returnType = "void";
            if (isFunction && headContext->basicType()) {
                auto result = visit(headContext->basicType());
                PascalType pascalReturnType = result.as<PascalType>();
                returnType = typeConverter->convertType(pascalReturnType);
            }

            // Get parameters
            std::string params = "()";
            if (headContext->formalParameter()) {
                auto paramsResult = visit(headContext->formalParameter());
                params = paramsResult.as<std::string>();
            }

            // Output forward declaration
            output << returnType << " " << name << params << ";\n";
            std::cout << "为 " << name << " 生成前向声明\n";
        }
    }
}

/**
 * Processes an identifier list, used for variable and parameter declarations
 * @param context The identifier list context from the parser
 * @return Vector of C-compatible identifier strings
 */
antlrcpp::Any PascalToCTranslator::visitIdList(PascalSParser::IdListContext *context) {
    std::vector<std::string> ids;

    // Collect all identifiers and convert them to C-compatible names
    for (auto id: context->ID()) {
        ids.push_back(TranslatorUtils::toCIdentifier(id->getText()));
    }

    return ids;
}

/**
 * Processes constant declarations section
 * @param context The constant declarations context
 * @return Standard placeholder for visitor pattern
 */
antlrcpp::Any PascalToCTranslator::visitConstDeclarations(PascalSParser::ConstDeclarationsContext *context) {
    // Check if there are any constant declarations
    if (!context->constDeclaration()) {
        return antlrcpp::Any();
    }

    output << "// Constants\n";

    // Visit constant declaration nodes
    visit(context->constDeclaration());

    output << "\n";

    return antlrcpp::Any();
}

/**
 * Processes individual constant declarations
 * Converts Pascal constants to C #define statements
 * @param context The constant declaration context
 * @return Standard placeholder for visitor pattern
 */
antlrcpp::Any PascalToCTranslator::visitConstDeclaration(PascalSParser::ConstDeclarationContext *context) {
    std::string id = TranslatorUtils::toCIdentifier(context->ID()->getText());

    // Get constant value
    std::string value = visit(context->constValue()).as<std::string>();

    // Add constant to symbol table
    SymbolEntry entry;
    entry.name = id;
    entry.symbolType = SymbolType::CONSTANT;
    entry.value = value;

    // Try to infer the type from the value's format
    if (value.find('.') != std::string::npos) {
        entry.dataType = PascalType::REAL;
    } else if (TranslatorUtils::toCIdentifier(value) == "true" || TranslatorUtils::toCIdentifier(value) == "false") {
        entry.dataType = PascalType::INTEGER;
        entry.value = TranslatorUtils::toCIdentifier(value) == "true" ? "1" : "0";
    } else if (value.length() >= 2 && value[0] == '\'' && value.back() == '\'') {
        entry.dataType = PascalType::STRING;
        entry.value[0] = entry.value.back() = '\"';
    } else {
        entry.dataType = PascalType::INTEGER;
    }

    symbolTable->addSymbol(entry);

    // Output as a C preprocessor define
    output << "#define " << entry.name << " " << entry.value << "\n";

    // Process additional constant declarations if any (recursively)
    if (context->constDeclaration()) {
        visit(context->constDeclaration());
    }

    return antlrcpp::Any();
}

/**
 * Processes constant values including numbers, letters, and strings
 * @param context The constant value context
 * @return String representation of the constant value
 */
antlrcpp::Any PascalToCTranslator::visitConstValue(PascalSParser::ConstValueContext *context) {
    if (context->num()) {
        // Handle numeric constants, preserving sign
        if (context->PLUS()) {
            return "+" + context->num()->getText();
        } else if (context->MINUS()) {
            return "-" + context->num()->getText();
        } else {
            return context->num()->getText();
        }
    } else if (context->LETTER()) {
        // Handle character constants
        return context->LETTER()->getText();
    } else if (context->STRING()) {
        // Handle string constants
        return context->STRING()->getText();
    }

    return antlrcpp::Any(std::string(""));
}

/**
 * Processes variable declarations section
 * @param context The variable declarations context
 * @return Standard placeholder for visitor pattern
 */
antlrcpp::Any PascalToCTranslator::visitVarDeclarations(PascalSParser::VarDeclarationsContext *context) {
    // Check if there are any variable declarations
    if (!context->varDeclaration()) {
        return antlrcpp::Any();
    }

    output << "// Variables\n";

    // Visit variable declaration nodes
    visit(context->varDeclaration());

    output << "\n";

    return antlrcpp::Any();
}

/**
 * Processes individual variable declarations
 * Converts Pascal variable declarations to C variable declarations with initialization
 * @param context The variable declaration context
 * @return Standard placeholder for visitor pattern
 */
antlrcpp::Any PascalToCTranslator::visitVarDeclaration(PascalSParser::VarDeclarationContext *context) {
    // Get list of variable identifiers
    std::vector<std::string> ids = visit(context->idList()).as<std::vector<std::string>>();

    // Get type information
    auto typeResult = visit(context->type());

    // Initialize variables for type information
    std::string typeStr;
    PascalType pascalType;
    PascalType elementType = PascalType::INTEGER; // Default element type for arrays
    std::vector<ArrayBounds> dimensions;

    // Extract type information based on whether it's an array or basic type
    try {
        // Try to extract as a basic type first
        auto typePair = typeResult.as<std::pair<std::string, PascalType>>();
        typeStr = typePair.first;
        pascalType = typePair.second;
    } catch (const std::bad_cast &) {
        // If not a basic type, it's an array type
        try {
            auto arrayTypeInfo = typeResult.as<std::tuple<std::string, PascalType, PascalType, std::vector<ArrayBounds>>>();
            typeStr = std::get<0>(arrayTypeInfo);
            pascalType = std::get<1>(arrayTypeInfo);
            elementType = std::get<2>(arrayTypeInfo);
            dimensions = std::get<3>(arrayTypeInfo);

            for (auto &bounds: dimensions) {
                bounds.lowerBound--;
            }
        } catch (const std::bad_cast &e) {
            throw TranslatorException("Failed to extract type information: " + std::string(e.what()));
        }
    }

    // Output variable declarations for each identifier
    for (auto &id: ids) {
        // Handle array types with array dimensions in the type string
        std::regex pattern("\\[.*\\]");
        std::smatch matches;
        if (std::regex_search(typeStr, matches, pattern)) {
            // For array types, put the dimensions after the identifier
            std::string tmpId = id + std::string(matches[0]);
            std::string tmpTypeStr = std::regex_replace(typeStr, pattern, "");
            output << tmpTypeStr << " " << tmpId;

            // For multidimensional arrays, add initialization code to zero out all elements
            if (pascalType == PascalType::ARRAY && dimensions.size() > 1) {
                output << " = {0}";  // C99 and later support this syntax for zero initialization
            }
        } else {
            // For basic types, standard format
            output << typeStr << " " << id;
        }

        // Only add initialization for non-array types (arrays are more complex to initialize)
        if (pascalType != PascalType::ARRAY) {
            // Initialize with default values based on type
            if (pascalType == PascalType::INTEGER) {
                output << " = 0";
            } else if (pascalType == PascalType::REAL) {
                output << " = 0.0";
            } else if (pascalType == PascalType::BOOLEAN) {
                output << " = 0";  // false in C
            } else if (pascalType == PascalType::CHAR) {
                output << " = '\\0'";
            }
        } else if (dimensions.size() == 1) {
            // For single dimension arrays, add simple zero initialization
            output << " = {0}";  // C99 and later support this syntax for zero initialization
        }
        output << ";\n";

        // Add variable to symbol table for type checking and reference
        SymbolEntry entry;
        entry.name = id;
        entry.symbolType = SymbolType::VARIABLE;
        entry.dataType = pascalType;

        // Store array-specific information if needed
        if (pascalType == PascalType::ARRAY) {
            entry.arrayElementType = elementType;
            entry.arrayDimensions = dimensions;
        }

        symbolTable->addSymbol(entry);
    }

    // Process additional variable declarations if any (recursively)
    if (context->varDeclaration()) {
        visit(context->varDeclaration());
    }

    return antlrcpp::Any();
}

/**
 * Processes type declarations, handling both basic types and arrays
 * @param context The type context
 * @return Type information as either a pair (for basic types) or tuple (for array types)
 */
antlrcpp::Any PascalToCTranslator::visitType(PascalSParser::TypeContext *context) {
    if (context->basicType() && context->ARRAY() == nullptr) {
        // Basic type (integer, real, boolean, char)
        auto result = visit(context->basicType());
        PascalType type = result.as<PascalType>();
        std::string typeStr = typeConverter->convertType(type);
        return std::make_pair(typeStr, type);
    } else if (context->ARRAY()) {
        // Array type with dimensions
        auto basicTypeResult = visit(context->basicType());
        PascalType elementType = basicTypeResult.as<PascalType>();

        // Get array dimensions (bounds)
        auto periodResult = visit(context->period());
        std::vector<ArrayBounds> dimensions = periodResult.as<std::vector<ArrayBounds>>();

        // Convert to C array type using the type converter
        std::string arrayTypeStr = typeConverter->convertArrayType(elementType, dimensions);

        // Return array type, element type, and dimensions as a tuple
        return std::make_tuple(arrayTypeStr, PascalType::ARRAY, elementType, dimensions);
    }

    throw TranslatorException("Unknown type");
}

/**
 * Processes basic type keywords (INTEGER, REAL, BOOLEAN, CHAR)
 * @param context The basic type context
 * @return PascalType enum value representing the type
 */
antlrcpp::Any PascalToCTranslator::visitBasicType(PascalSParser::BasicTypeContext *context) {
    if (context->INTEGER()) {
        return PascalType::INTEGER;
    } else if (context->REAL()) {
        return PascalType::REAL;
    } else if (context->BOOLEAN()) {
        return PascalType::BOOLEAN;
    } else if (context->CHAR()) {
        return PascalType::CHAR;
    }

    throw TranslatorException("Unknown basic type");
}

/**
 * Processes array index range declarations (e.g., 1..10, 0..9)
 * @param context The period context containing range bounds
 * @return Vector of ArrayBounds structures with lower and upper bounds
 */
antlrcpp::Any PascalToCTranslator::visitPeriod(PascalSParser::PeriodContext *context) {
    std::vector<ArrayBounds> dimensions;
    std::vector<std::string> numStrings;
    std::string periodStr = context->getText();

    // Extract all pairs of numbers separated by DOTDOT (..)
    std::regex pattern(R"((\d+)\.\.(\d+))");  // 匹配 "数字..数字"
    std::smatch matches;

    auto begin = periodStr.cbegin();
    auto end = periodStr.cend();

    while (std::regex_search(begin, end, matches, pattern)) {
        numStrings.push_back(matches[1].str());  // 下界（如 "1"）
        numStrings.push_back(matches[2].str());  // 上界（如 "4"）
        begin = matches[0].second;           // 继续匹配剩余部分
    }
    // Convert bounds to integers and store in ArrayBounds structures
    for (int i = 0; i < numStrings.size(); i += 2) {
        if (i + 1 < numStrings.size()) {
            ArrayBounds bounds;
            bounds.lowerBound = std::stoi(numStrings[i]);
            bounds.upperBound = std::stoi(numStrings[i + 1]);
            dimensions.push_back(bounds);
        }
    }
    return dimensions;
}

/**
 * Processes subprogram (function/procedure) declarations
 * @param context The subprogram declarations context
 * @return Standard placeholder for visitor pattern
 */
antlrcpp::Any PascalToCTranslator::visitSubprogramDeclarations(PascalSParser::SubprogramDeclarationsContext *context) {
    // Check if there are any subprogram declarations
    if (!context->subprogramDeclarations() && !context->subprogram()) {
        return antlrcpp::Any();
    }

    // First process the current subprogram declarations, which comes earlier in the source
    if (context->subprogramDeclarations()) {
        visit(context->subprogramDeclarations());
    }

    // Then process additional subprogram that come later in the source
    if (context->subprogram()) {
        visit(context->subprogram());
    }
    return antlrcpp::Any();
}

/**
 * Processes a single subprogram (function or procedure)
 * @param context The subprogram context
 * @return Standard placeholder for visitor pattern
 */
antlrcpp::Any PascalToCTranslator::visitSubprogram(PascalSParser::SubprogramContext *context) {
    // Visit subprogram head to generate function signature
    visit(context->subprogramHead());

    // Add opening brace for function body
    output << " {\n";
    increaseIndentation();

    // For functions, add a return value variable with the same name as the function
    if (context->subprogramHead()->FUNCTION()) {
        std::string funcName = TranslatorUtils::toCIdentifier(context->subprogramHead()->ID()->getText());
        std::string funcNameTmp = funcName + "tmp";
        auto typeResult = visit(context->subprogramHead()->basicType());
        PascalType returnType = typeResult.as<PascalType>();
        std::string cType = typeConverter->convertType(returnType);

        // Initialize the return value variable based on type
        output << getCurrentIndentation() << cType << " " << funcNameTmp << " = ";
        if (returnType == PascalType::INTEGER) {
            output << "0";
        } else if (returnType == PascalType::REAL) {
            output << "0.0";
        } else if (returnType == PascalType::BOOLEAN) {
            output << "0";
        } else if (returnType == PascalType::CHAR) {
            output << "'\\0'";
        } else if (returnType == PascalType::STRING) {
            output << "\"\"";
        } else if (returnType == PascalType::ARRAY) {
            // Arrays are initialized to zero by default in C
            output << "{0}";
        }
        output << ";\n";

        // Also store the temporary variable name in the symbol table so we can reference it correctly
        SymbolEntry tmpEntry;
        tmpEntry.name = funcNameTmp;
        tmpEntry.symbolType = SymbolType::VARIABLE;
        tmpEntry.dataType = returnType;
        symbolTable->addSymbol(tmpEntry);
    }

    // Visit subprogram body to generate function implementation
    visit(context->subprogramBody());

    // For functions, add a return statement at the end if there isn't one
    if (context->subprogramHead()->FUNCTION()) {
        std::string funcName = TranslatorUtils::toCIdentifier(context->subprogramHead()->ID()->getText());
        std::string funcNameTmp = funcName + "tmp";
        output << getCurrentIndentation() << "return " << funcNameTmp << ";\n";
    }

    // Add closing brace and extra newline
    decreaseIndentation();
    output << "}\n\n";

    return antlrcpp::Any();
}

/**
 * Processes a subprogram header (function or procedure declaration)
 * @param context The subprogram header context
 * @return Standard placeholder for visitor pattern
 */
antlrcpp::Any PascalToCTranslator::visitSubprogramHead(PascalSParser::SubprogramHeadContext *context) {
    // Get function/procedure name and convert to C identifier
    std::string name = TranslatorUtils::toCIdentifier(context->ID()->getText());

    // Determine if this is a function or procedure
    bool isFunction = context->FUNCTION() != nullptr;

    // Get return type for functions (procedures default to void)
    std::string returnType = "void";
    PascalType pascalReturnType = PascalType::INTEGER;  // Default

    if (isFunction) {
        auto result = visit(context->basicType());
        pascalReturnType = result.as<PascalType>();
        returnType = typeConverter->convertType(pascalReturnType);
    }

    // Add function/procedure to the symbol table before entering its scope
    SymbolEntry entry;
    entry.name = name;
    entry.symbolType = isFunction ? SymbolType::FUNCTION : SymbolType::PROCEDURE;
    entry.dataType = pascalReturnType;
    symbolTable->addSymbol(entry);

    // Create a new scope for the function/procedure
    symbolTable->enterScope(name);

    // Output function/procedure declaration with return type and name
    output << returnType << " " << name;

    // Visit formal parameters section
    auto paramsResult = visit(context->formalParameter());
    std::string params = paramsResult.as<std::string>();

    // In C, array parameters need proper pointer notation
    // For array dimensions, first dimension is always empty in function parameters
    std::regex arrayPattern("\\[(\\d+)\\]");
    std::regex multiDimPattern("\\[(\\d+)\\](\\[\\d+\\])+");

    // First find all multidimensional arrays and convert them properly
    std::smatch matches;
    std::string processedParams = params;
    std::string temp = processedParams;

    while (std::regex_search(temp, matches, multiDimPattern)) {
        std::string fullMatch = matches[0];

        // Extract the position and replace with proper C array notation
        // In C function parameters, first dimension is always empty: int[][10]
        size_t pos = processedParams.find(fullMatch);
        if (pos != std::string::npos) {
            std::string replacement = "[]" + fullMatch.substr(fullMatch.find("]") + 1);
            processedParams.replace(pos, fullMatch.length(), replacement);
        }

        // Continue search from after the current match
        temp = matches.suffix().str();
    }

    // Then handle single dimension arrays
//    processedParams = std::regex_replace(processedParams, arrayPattern, "[]");

    output << processedParams;

    return antlrcpp::Any();
}

/**
 * Processes formal parameter declarations for functions and procedures
 * @param context The formal parameter context
 * @return String representation of parameter list in C syntax
 */
antlrcpp::Any PascalToCTranslator::visitFormalParameter(PascalSParser::FormalParameterContext *context) {
    // Default empty parameter list
    if (!context->parameterList()) {
        return antlrcpp::Any(std::string("()"));
    }

    // Visit parameter list to generate parameter declarations
    auto result = visit(context->parameterList());
    std::string params = result.as<std::string>();

    return antlrcpp::Any(std::string("(") + params + ")");
}

/**
 * Processes a list of parameters
 * @param context The parameter list context
 * @return String representation of all parameters, comma-separated
 */
antlrcpp::Any PascalToCTranslator::visitParameterList(PascalSParser::ParameterListContext *context) {
    std::string paramList = "";

    // First process the current parameter
    auto result = visit(context->parameter());
    std::string param = result.as<std::string>();

    TranslatorUtils::logDebug("Processing parameter: " + param);

    // Check if there are any nested parameters (which come earlier in the Pascal code)
    if (context->parameterList()) {
        auto moreParamsResult = visit(context->parameterList());
        std::string moreParamsStr = moreParamsResult.as<std::string>();

        TranslatorUtils::logDebug("Earlier parameters: " + moreParamsStr);

        // Put the earlier parameters first in the list
        if (!moreParamsStr.empty()) {
            if (param.empty()) paramList = moreParamsStr;
            else paramList = moreParamsStr + ", " + param;
            TranslatorUtils::logDebug("Combined parameters: " + paramList);
        } else {
            paramList = param;
        }
    } else {
        // No nested parameters, just return the current one
        paramList = param;
    }

    return paramList;
}

/**
 * Processes a single parameter, which can be either by value or by reference (VAR)
 * @param context The parameter context
 * @return String representation of the parameter in C syntax
 */
antlrcpp::Any PascalToCTranslator::visitParameter(PascalSParser::ParameterContext *context) {
    if (context->varParameter()) {
        TranslatorUtils::logDebug("Processing VAR parameter");
        return visit(context->varParameter());
    } else if (context->valueParameter()) {
        TranslatorUtils::logDebug("Processing value parameter");
        return visit(context->valueParameter());
    }

    return antlrcpp::Any(std::string(""));
}

/**
 * Processes a VAR parameter (by reference)
 * In Pascal, VAR parameters are passed by reference
 * In C, this is implemented using pointers
 * @param context The VAR parameter context
 * @return String representation of the parameter in C syntax with pointer notation
 */
antlrcpp::Any PascalToCTranslator::visitVarParameter(PascalSParser::VarParameterContext *context) {
    // Get value parameter string representation
    auto result = visit(context->valueParameter());
    std::string params = result.as<std::string>();

    // Get identifiers from the context to mark them as reference parameters in the symbol table
    auto idListResult = visit(context->valueParameter()->idList());
    std::vector<std::string> ids = idListResult.as<std::vector<std::string>>();

    // Debug output to verify parameter identifiers
    std::string idListStr;
    for (const auto &id: ids) {
        if (!idListStr.empty()) idListStr += ", ";
        idListStr += id;
    }
    TranslatorUtils::logDebug("VAR parameter identifiers: " + idListStr);

    // Also get type information to check for array types
    auto typeResult = visit(context->valueParameter()->type());

    // Initialize variables for type information
    std::string typeStr;
    PascalType pascalType;
    PascalType elementType = PascalType::INTEGER; // Default for arrays
    std::vector<ArrayBounds> dimensions;
    bool isArray = false;
    bool isMultidimensionalArray = false;

    // Extract type information based on whether it's an array or basic type
    try {
        // Try to extract as a basic type first
        auto typePair = typeResult.as<std::pair<std::string, PascalType>>();
        typeStr = typePair.first;
        pascalType = typePair.second;
        isArray = (pascalType == PascalType::ARRAY);
    } catch (const std::bad_cast &) {
        // If it fails, it's an array type
        try {
            auto arrayTypeInfo = typeResult.as<std::tuple<std::string, PascalType, PascalType, std::vector<ArrayBounds>>>();
            typeStr = std::get<0>(arrayTypeInfo);
            pascalType = std::get<1>(arrayTypeInfo);
            elementType = std::get<2>(arrayTypeInfo);
            dimensions = std::get<3>(arrayTypeInfo);
            isArray = true;
            isMultidimensionalArray = (dimensions.size() > 1);
        } catch (const std::bad_cast &e) {
            throw TranslatorException("Failed to extract type information: " + std::string(e.what()));
        }
    }

    // Mark all parameters as reference parameters in symbol table
    for (const auto &id: ids) {
        if (symbolTable->hasSymbolInCurrentScope(id)) {
            // Update the symbol in the symbol table
            SymbolEntry &entry = symbolTable->getSymbol(id);
            entry.isReference = true;

            // Check if the parameter is an array
            bool isArray = (entry.dataType == PascalType::ARRAY);
            bool isMultidim = (isArray && entry.arrayDimensions.size() > 1);
            TranslatorUtils::logDebug("  Marking " + id + " as reference parameter, isArray: " +
                                      (isArray ? "true" : "false") +
                                      ", isMultidimensional: " + (isMultidim ? "true" : "false"));

            // Since we already have addSymbol automatically adding parameters,
            // we need to update the existing parameters in the scope's parameters list
            std::vector<SymbolEntry> &parameters = symbolTable->getCurrentScope().getParameters();
            for (auto &param: parameters) {
                if (param.name == id) {
                    param.isReference = true;
                    break;
                }
            }
        }
    }

    // Add pointer (*) for reference parameters to the type part of the declaration
    // We need to handle multiple parameters in the chain
    std::stringstream ss;
    std::string baseTypeStr;
    size_t pos = params.find_first_of(" ");
    if (pos != std::string::npos) {
        baseTypeStr = params.substr(0, pos);
        std::string rest = params.substr(pos);

        // Split the rest into individual parameter declarations
        std::vector<std::string> paramDecls;
        size_t start = 0;
        size_t commaPos;
        while ((commaPos = rest.find(",", start)) != std::string::npos) {
            paramDecls.push_back(rest.substr(start, commaPos - start));
            start = commaPos + 2; // Skip ", "
        }
        paramDecls.push_back(rest.substr(start));

        // Extract the base type without array dimensions
        std::string baseType = baseTypeStr;
        size_t bracketPos = baseType.find('[');
        if (bracketPos != std::string::npos) {
            baseType = baseType.substr(0, bracketPos);
        }

        // Check if we're dealing with a multidimensional array
        std::vector<std::string> dimensionSizes;
        if (isMultidimensionalArray) {
            // Extract all dimension sizes for proper C array parameter declaration
            for (const auto &dim: dimensions) {
                int size = dim.upperBound - dim.lowerBound + 1 + 1;
                dimensionSizes.push_back(std::to_string(size));
            }
        }

        // Add pointer type to each parameter
        for (size_t i = 0; i < paramDecls.size(); ++i) {
            if (i > 0) ss << ", ";

            // Get the parameter's variable name
            size_t last_space_pos = paramDecls[i].rfind(' ');
            std::string paramName;
            if (last_space_pos != std::string::npos) {
                paramName = paramDecls[i].substr(last_space_pos + 1);
            } else {
                paramName = paramDecls[i];
            }

            // Handle based on whether it's an array parameter or not
            if (isArray) {
                if (isMultidimensionalArray) {
                    // For multidimensional arrays as parameters, use proper C syntax:
                    // For a 2D array: type (*param)[dim2]
                    // For a 3D array: type (*param)[dim2][dim3]
                    ss << baseType << " (*" << paramName << ")";

                    // Add all dimensions except the first, which is omitted in C array parameters
                    for (size_t j = 1; j < dimensionSizes.size(); ++j) {
                        ss << "[" << dimensionSizes[j] << "]";
                    }
                } else {
                    // For single dimension arrays, we can use the simpler notation
                    ss << baseType << " *" << paramName;
                }
            } else {
                // Non-array parameter - regular pointer
                ss << baseType << "* " << paramName;
            }
        }
    } else {
        // If we can't find a space, just add the pointer to the whole string
        ss << params << "*";
    }

    return ss.str();
}

/**
 * Processes a value parameter (by value)
 * In Pascal, regular parameters are passed by value
 * @param context The value parameter context
 * @return String representation of the parameter in C syntax
 */
antlrcpp::Any PascalToCTranslator::visitValueParameter(PascalSParser::ValueParameterContext *context) {
    // Get identifiers
    std::vector<std::string> ids = visit(context->idList()).as<std::vector<std::string>>();

    // Debug output for parameter identifiers
    std::string idListStr;
    for (const auto &id: ids) {
        if (!idListStr.empty()) idListStr += ", ";
        idListStr += id;
    }
    TranslatorUtils::logDebug("Value parameter identifiers: " + idListStr);

    // Get type information
    auto typeResult = visit(context->type());

    // Initialize variables for type information
    std::string typeStr;
    PascalType pascalType;
    PascalType elementType = PascalType::INTEGER; // Default for arrays
    std::vector<ArrayBounds> dimensions;

    // Extract type information based on whether it's an array or basic type
    try {
        // Try to extract as a basic type first
        auto typePair = typeResult.as<std::pair<std::string, PascalType>>();
        typeStr = typePair.first;
        pascalType = typePair.second;
    } catch (const std::bad_cast &) {
        // If it fails, it's an array type
        try {
            auto arrayTypeInfo = typeResult.as<std::tuple<std::string, PascalType, PascalType, std::vector<ArrayBounds>>>();
            typeStr = std::get<0>(arrayTypeInfo);
            pascalType = std::get<1>(arrayTypeInfo);
            elementType = std::get<2>(arrayTypeInfo);
            dimensions = std::get<3>(arrayTypeInfo);
        } catch (const std::bad_cast &e) {
            throw TranslatorException("Failed to extract type information: " + std::string(e.what()));
        }
    }

    // Format parameters
    std::stringstream ss;
    for (size_t i = 0; i < ids.size(); ++i) {
        if (i > 0) {
            ss << ", ";
        }

        ss << typeStr << " " << ids[i];
        TranslatorUtils::logDebug("  Adding parameter: " + typeStr + " " + ids[i] +
                                  ", type: " + (pascalType == PascalType::ARRAY ? "ARRAY" :
                                                (pascalType == PascalType::INTEGER ? "INTEGER" :
                                                 (pascalType == PascalType::REAL ? "REAL" :
                                                  (pascalType == PascalType::BOOLEAN ? "BOOLEAN" :
                                                   (pascalType == PascalType::CHAR ? "CHAR" : "UNKNOWN"))))));

        // Add parameter to symbol table
        SymbolEntry entry;
        entry.name = ids[i];
        entry.symbolType = SymbolType::PARAMETER;
        entry.dataType = pascalType;
        entry.isReference = false;  // Default is by value, will be updated if VAR parameter

        // Store array-specific information if needed
        if (pascalType == PascalType::ARRAY) {
            entry.arrayElementType = elementType;
            entry.arrayDimensions = dimensions;
            TranslatorUtils::logDebug(
                    (elementType == PascalType::INTEGER ? "INTEGER" :
                     (elementType == PascalType::REAL ? "REAL" :
                      (elementType == PascalType::BOOLEAN ? "BOOLEAN" :
                       (elementType == PascalType::CHAR ? "CHAR" : "UNKNOWN")))));
        }

        symbolTable->addSymbol(entry);
    }

    return ss.str();
}

/**
 * Processes a subprogram body which contains declarations and statements
 * @param context The subprogram body context
 * @return Standard placeholder for visitor pattern
 */
antlrcpp::Any PascalToCTranslator::visitSubprogramBody(PascalSParser::SubprogramBodyContext *context) {
    // Process constant declarations if present
    if (context->constDeclarations()) {
        visit(context->constDeclarations());
    }

    // Process variable declarations if present
    if (context->varDeclarations()) {
        visit(context->varDeclarations());
    }

    // Process compound statement (main body of the function/procedure)
    if (context->compoundStatement()) {
        visit(context->compoundStatement());
    }

    // Exit the scope at the end of the subprogram
    symbolTable->exitScope();

    return antlrcpp::Any();
}

/**
 * Processes a compound statement (BEGIN ... END block)
 * @param context The compound statement context
 * @return Standard placeholder for visitor pattern
 */
antlrcpp::Any PascalToCTranslator::visitCompoundStatement(PascalSParser::CompoundStatementContext *context) {
    // Skip BEGIN and END tokens, just visit the statement list inside
    visit(context->statementList());

    return antlrcpp::Any();
}

/**
 * Processes a list of statements
 * @param context The statement list context
 * @return Standard placeholder for visitor pattern
 */
antlrcpp::Any PascalToCTranslator::visitStatementList(PascalSParser::StatementListContext *context) {
    // Visit additional statements first if any (earlier in source)
    if (context->statementList()) {
        visit(context->statementList());
    }

    // Visit the current statement (later in source)
    visit(context->statement());

    return antlrcpp::Any();
}

/**
 * Processes individual statements (assignment, procedure call, if, for, etc.)
 * @param context The statement context
 * @return Standard placeholder for visitor pattern
 */
antlrcpp::Any PascalToCTranslator::visitStatement(PascalSParser::StatementContext *context) {
    // Empty statement
    if (!context->variable() && !context->ID() && !context->procedureCall() && !context->compoundStatement() &&
        !context->ifStatement() && !context->forStatement() && !context->readStatement() &&
        !context->whileStatement() && !context->writeStatement() && !context->breakStatement()) {
        return antlrcpp::Any();
    }

    // Assignment to identifier (procedure or function result)
    if (context->ID() && context->ASSIGNOP()) {
        std::string id = TranslatorUtils::toCIdentifier(context->ID()->getText());
        if (!symbolTable->hasSymbol(id)) {
            std::cout << "----------------------------------------------------------" << std::endl;
            std::cout << "Error: Undefined variable " << id << " in " << symbolTable->getCurrentScope().getScopeName()
                      << ", line :" << context->start->getLine() << std::endl;
            std::cout << "----------------------------------------------------------" << std::endl;
        }

        auto exprResult = visit(context->expression());
        std::string expr = exprResult.as<std::string>();

        // Get current scope name - if we're assigning to a function with the same name, it's a return value assignment
        std::string currentScopeName = symbolTable->getCurrentScope().getScopeName();

        if (currentScopeName == id) {
            // This is a function result assignment (Pascal function:=value)
            // Assign to the function's tmp variable instead of the function name directly
            output << getCurrentIndentation() << id << "tmp = " << expr << ";\n";
        } else {
            // Regular assignment to an identifier
            output << getCurrentIndentation() << id << " = " << expr << ";\n";
        }
    }
        // Assignment to variable (can be array element or another complex variable)
    else if (context->variable() && context->ASSIGNOP()) {
        auto varResult = visit(context->variable());

        // Check if this is a function result assignment
        try {
            if (varResult.is<std::pair<std::string, std::string>>()) {
                auto pair = varResult.as<std::pair<std::string, std::string>>();
                if (pair.first == "FUNCTION_RESULT") {
                    // This is a function result assignment (Pascal function:=value)
                    auto exprResult = visit(context->expression());
                    std::string expr = exprResult.as<std::string>();

                    // Assign to the function's tmp variable instead of returning directly
                    output << getCurrentIndentation() << pair.second << "tmp = " << expr << ";\n";
                    return antlrcpp::Any();
                }
            }
        } catch (const std::bad_cast &e) {
            // If there's a cast error, assume it's a regular variable assignment
            TranslatorUtils::logError(
                    "Warning: Type conversion issue in variable assignment: " + std::string(e.what()));
        }

        // Regular variable assignment - try with explicit string cast
        try {
            std::string var = varResult.as<std::string>();
            auto exprResult = visit(context->expression());
            std::string expr = exprResult.as<std::string>();

            output << getCurrentIndentation() << var << " = " << expr << ";\n";
        } catch (const std::bad_cast &e) {
            // If cast fails again, add error handling
            TranslatorUtils::logError("Error in variable assignment: " + std::string(e.what()));
        }
    }
        // Procedure call
    else if (context->procedureCall()) {
        auto result = visit(context->procedureCall());
        std::string call = result.as<std::string>();

        output << getCurrentIndentation() << call << ";\n";
    }
        // Compound statement (BEGIN ... END block)
    else if (context->compoundStatement()) {
        visit(context->compoundStatement());
    }
        // If statement
    else if (context->ifStatement()) {
        visit(context->ifStatement());
    }
        // For statement
    else if (context->forStatement()) {
        visit(context->forStatement());
    }
        // Read statement
    else if (context->readStatement()) {
        visit(context->readStatement());
    }
        // While statement
    else if (context->whileStatement()) {
        visit(context->whileStatement());
    }
        // Write statement
    else if (context->writeStatement()) {
        visit(context->writeStatement());
    }
        // Break statement
    else if (context->breakStatement()) {
        visit(context->breakStatement());
    }

    return antlrcpp::Any();
}

/**
 * Processes an if statement and optional else part
 * @param context The if statement context
 * @return Standard placeholder for visitor pattern
 */
antlrcpp::Any PascalToCTranslator::visitIfStatement(PascalSParser::IfStatementContext *context) {
    // Get the condition expression
    auto condResult = visit(context->expression());
    std::string cond = condResult.as<std::string>();

    // Output if statement with condition
    output << getCurrentIndentation() << "if (" << cond << ") {\n";
    increaseIndentation();

    // Visit the if-branch statement
    visit(context->statement());

    decreaseIndentation();
    output << getCurrentIndentation() << "}";

    // Visit else part if present
    if (context->elsePart()) {
        output << " else {\n";
        increaseIndentation();

        visit(context->elsePart());

        decreaseIndentation();
        output << getCurrentIndentation() << "}";
    }

    output << "\n";

    return antlrcpp::Any();
}

/**
 * Processes a for statement (loop with counter)
 * @param context The for statement context
 * @return Standard placeholder for visitor pattern
 */
antlrcpp::Any PascalToCTranslator::visitForStatement(PascalSParser::ForStatementContext *context) {
    // Get loop counter variable
    std::string id = TranslatorUtils::toCIdentifier(context->ID()->getText());

    // Get initial value
    auto initResult = visit(context->expression(0));
    std::string init = initResult.as<std::string>();

    // Get final value
    auto finalResult = visit(context->expression(1));
    std::string final = finalResult.as<std::string>();

    // Output C-style for loop (Pascal for-loops are always incrementing by 1)
    output << getCurrentIndentation() << "for (" << id << " = " << init << "; " << id << " <= " << final << "; ++" << id
           << ") {\n";
    increaseIndentation();

    // Visit loop body statement
    visit(context->statement());

    decreaseIndentation();
    output << getCurrentIndentation() << "}\n";

    return antlrcpp::Any();
}

/**
 * Processes a read statement (input)
 * Translates to scanf calls in C
 * @param context The read statement context
 * @return Standard placeholder for visitor pattern
 */
antlrcpp::Any PascalToCTranslator::visitReadStatement(PascalSParser::ReadStatementContext *context) {
    try {
        // Get list of variables to read into
        auto result = visit(context->variableList());
        std::vector<std::string> vars = result.as<std::vector<std::string>>();

        // Output read statements for each variable
        for (const auto &var: vars) {
            // Check if it's an array access
            std::string baseVar = var;
            size_t bracketPos = var.find('[');
            bool isArrayAccess = false;

            if (bracketPos != std::string::npos) {
                baseVar = var.substr(0, bracketPos);
                isArrayAccess = true;
            }

            // Look up the variable's type in the symbol table
            if (symbolTable->hasSymbol(baseVar)) {
                const SymbolEntry &entry = symbolTable->getSymbol(baseVar);
                std::string format;

                if (isArrayAccess && entry.dataType == PascalType::ARRAY) {
                    // Use the array element type for the format specifier
                    switch (entry.arrayElementType) {
                        case PascalType::INTEGER:
                            format = "\"%d\"";
                            break;
                        case PascalType::REAL:
                            format = "\"%f\"";
                            break;
                        case PascalType::CHAR:
                            format = "\" %c\"";
                            break;
                        case PascalType::BOOLEAN:
                            format = "\"%d\"";
                            break;
                        default:
                            format = "\"%d\"";
                            break;
                    }
                } else {
                    // Use the variable's own type for the format specifier
                    switch (entry.dataType) {
                        case PascalType::INTEGER:
                            format = "\"%d\"";
                            break;
                        case PascalType::REAL:
                            format = "\"%f\"";
                            break;
                        case PascalType::CHAR:
                            format = "\" %c\"";
                            break;
                        case PascalType::BOOLEAN:
                            format = "\"%d\"";
                            break;
                        default:
                            format = "\"%s\"";
                            break;
                    }
                }

                // For reference parameters that are not arrays, in the current scope, we don't need to use &
                // because they are already pointers in C
                if (entry.isReference && entry.symbolType == SymbolType::PARAMETER &&
                    !isArrayAccess && entry.dataType != PascalType::ARRAY &&
                    symbolTable->hasSymbolInCurrentScope(baseVar)) {
                    output << getCurrentIndentation() << "scanf(" << format << ", " << var << ");\n";
                } else {
                    // Regular variables need & to get their address for scanf
                    output << getCurrentIndentation() << "scanf(" << format << ", &" << var << ");\n";
                }
            } else {
                // Default to integer if type is unknown
                output << getCurrentIndentation() << "scanf(\"%d\", &" << var << ");\n";
            }
        }
    } catch (const std::bad_cast &e) {
        TranslatorUtils::logError("Type conversion error in read statement: " + std::string(e.what()));
    }

    return antlrcpp::Any();
}

/**
 * Processes a while statement (loop with condition)
 * @param context The while statement context
 * @return Standard placeholder for visitor pattern
 */
antlrcpp::Any PascalToCTranslator::visitWhileStatement(PascalSParser::WhileStatementContext *context) {
    // Get the loop condition
    auto condResult = visit(context->expression());
    std::string cond = condResult.as<std::string>();

    // Output while loop with condition
    output << getCurrentIndentation() << "while (" << cond << ") {\n";
    increaseIndentation();

    // Visit loop body statement
    visit(context->statement());

    decreaseIndentation();
    output << getCurrentIndentation() << "}\n";

    return antlrcpp::Any();
}

/**
 * Processes a write statement (output)
 * Translates to printf calls in C
 * @param context The write statement context
 * @return Standard placeholder for visitor pattern
 */
antlrcpp::Any PascalToCTranslator::visitWriteStatement(PascalSParser::WriteStatementContext *context) {
    auto result = visit(context->expressionList());
    std::vector<std::string> exprs = result.as<std::vector<std::string>>();

    output << getCurrentIndentation() << "printf(";

    // Format string part of printf
    std::string formatStr = "\"";
    std::vector<std::string> formattedArgs;

    // Process expressions in the original Pascal order (already handled in visitExpressionList)
    for (size_t i = 0; i < exprs.size(); ++i) {
        std::string expr = exprs[i];
        std::string formatSpecifier;
        std::string formattedArg = expr;

        // Check if it's an array access (contains square brackets)
        std::string baseVar = expr;
        size_t bracketPos = expr.find('[');
        if (bracketPos != std::string::npos) {
            baseVar = expr.substr(0, bracketPos);
        }

        // Check for function call
        size_t parenPos = baseVar.find('(');
        if (parenPos != std::string::npos) {
            baseVar = baseVar.substr(0, parenPos);
        }

        // Try to look up the type in the symbol table
        bool found = false;
        // Check if it's a string literal
        if (expr.size() >= 2 && expr[0] == '\'' && expr.back() == '\'') {
            formatSpecifier = "%s";
            // Remove the single quotes from the expression and add double quotes for C string
            formattedArg = "\"" + expr.substr(1, expr.size() - 2) + "\"";
            found = true;
        } else if (expr.find('.') != std::string::npos) {
            // Floating point values use %f
            formatSpecifier = "%f";
            found = true;
        } else if (expr == "0" || expr == "1" || TranslatorUtils::toCIdentifier(expr) == "true" ||
                   TranslatorUtils::toCIdentifier(expr) == "false") {
            // Boolean values use %d (0/1 in C)
            formatSpecifier = "%d";
            found = true;
            formattedArg = expr.length() == 1 ? expr : (TranslatorUtils::toCIdentifier(expr) == "true" ? "1" : "0");
        } else {
            // Look up variable type in symbol table
            if (symbolTable->hasSymbol(baseVar)) {
                const SymbolEntry &entry = symbolTable->getSymbol(baseVar);
                const std::string value = entry.value;
                // Determine the format specifier based on the variable type
                if (entry.dataType == PascalType::ARRAY && bracketPos != std::string::npos) {
                    // Use the array element type for array accesses
                    switch (entry.arrayElementType) {
                        case PascalType::INTEGER:
                            formatSpecifier = "%d";
                            found = true;
                            break;
                        case PascalType::REAL:
                            formatSpecifier = "%f";
                            found = true;
                            break;
                        case PascalType::BOOLEAN:
                            formatSpecifier = "%d";
                            found = true;
                            break;
                        case PascalType::CHAR:
                            formatSpecifier = "%c";
                            found = true;
                            break;
                        case PascalType::STRING:
                            formatSpecifier = "%s";
                            found = true;
                            break;
                        default:
                            break;
                    }
                } else {
                    // Use the variable's own type
                    switch (entry.dataType) {
                        case PascalType::INTEGER:
                            formatSpecifier = "%d";
                            found = true;
                            break;
                        case PascalType::REAL:
                            formatSpecifier = "%f";
                            found = true;
                            break;
                        case PascalType::BOOLEAN:
                            formatSpecifier = "%d";
                            found = true;
                            break;
                        case PascalType::CHAR:
                            formatSpecifier = "%c";
                            found = true;
                            break;
                        case PascalType::STRING:
                            formatSpecifier = "%s";
                            found = true;
                            break;
                        default:
                            break;
                    }
                }
            } else {
                std::cout << "----------------------------------------------------------" << std::endl;
                std::cout << "Error: Undefined variable " << baseVar << " in "
                          << symbolTable->getCurrentScope().getScopeName()
                          << ", line :" << context->start->getLine() << std::endl;
                std::cout << "----------------------------------------------------------" << std::endl;
            }
        }
        if (!found) formatSpecifier = "%d";  // Default to integer format

        formatStr += formatSpecifier;
        formattedArgs.push_back(formattedArg);
    }

    formatStr += "\"";
    output << formatStr;

    // Arguments - keep them in the same order as they appear in the format string
    for (const auto &arg: formattedArgs) {
        output << ", " << arg;
    }

    output << ");\n";

    return antlrcpp::Any();
}

antlrcpp::Any PascalToCTranslator::visitBreakStatement(PascalSParser::BreakStatementContext *context) {
    output << getCurrentIndentation() << "break;\n";
    return antlrcpp::Any();
}


/**
 * Processes a list of variables for input/output or other operations
 * @param context The variable list context
 * @return Vector of string representations of variables in C syntax
 */
antlrcpp::Any PascalToCTranslator::visitVariableList(PascalSParser::VariableListContext *context) {
    std::vector<std::string> vars;

    // In Pascal, variables in a list appear from left to right in the source code,
    // but the ANTLR parser processes them in a way that the rightmost variable becomes
    // the current node and earlier variables are in the nested variableList.

    // First, process any earlier variables in the nested variableList
    if (context->variableList()) {
        auto earlierVars = visit(context->variableList());
        vars = earlierVars.as<std::vector<std::string>>();
    }

    // Then add the current variable, which comes later in the source
    auto result = visit(context->variable());

    // Handle potential function return value marker
    if (result.is<std::pair<std::string, std::string>>()) {
        auto pair = result.as<std::pair<std::string, std::string>>();
        // Use the function name with tmp suffix
        vars.push_back(pair.second + "tmp");
    } else {
        // Regular variable
        vars.push_back(result.as<std::string>());
    }

    return vars;
}

/**
 * Processes a variable identifier, which could be a simple variable or array element
 * Handles special cases like function result variables and reference parameters
 * @param context The variable context
 * @return String representation of the variable in C syntax or a special marker for function results
 */
antlrcpp::Any PascalToCTranslator::visitVariable(PascalSParser::VariableContext *context) {
    std::string id = TranslatorUtils::toCIdentifier(context->ID()->getText());

    // Check if the variable is a function name in the current scope
    std::string currentScopeName = symbolTable->getCurrentScope().getScopeName();

    // Check if we're in a function and the variable name matches the function name
    if (id == currentScopeName) {
        // For a function return value, return a special pair to indicate this
        // We'll handle this in visitStatement
        std::pair<std::string, std::string> resultPair("FUNCTION_RESULT", id);
        return resultPair;
    }

    // Check if the variable is a reference parameter (not a local variable)
    bool isReferenceParam = false;
    bool isArray = false;

    if (symbolTable->hasSymbol(id)) {
        const SymbolEntry &entry = symbolTable->getSymbol(id);
        // Only consider as reference parameter if it's actually a parameter and marked as reference
        isReferenceParam = entry.isReference && entry.symbolType == SymbolType::PARAMETER;
        isArray = (entry.dataType == PascalType::ARRAY);
    } else {
        std::cout << "----------------------------------------------------------" << std::endl;
        std::cout << "Error: Undefined variable " << id << " in " << symbolTable->getCurrentScope().getScopeName()
                  << ", line :" << context->start->getLine() << std::endl;
        std::cout << "----------------------------------------------------------" << std::endl;
    }

    // Check if it's an array access
    std::string result;
    if (context->idVarPart()) {
        auto partResult = visit(context->idVarPart());
        std::string indices = partResult.as<std::string>();

        // Only dereference reference parameters (not local variables) when they're used within the function they were passed to
        if (isReferenceParam && !isArray && symbolTable->hasSymbolInCurrentScope(id)) {
            // For non-array reference parameters, we need to dereference when accessing
            result = "(*" + id + ")" + indices;
        } else {
            result = id + indices;
        }
    } else {
        // Not an array access
        if (isReferenceParam && !isArray && symbolTable->hasSymbolInCurrentScope(id)) {
            // For non-array reference parameters, we need to dereference
            result = "(*" + id + ")";
        } else {
            result = id;
        }
    }

    return result;
}

/**
 * Processes array indexing expressions for a variable
 * @param context The ID variable part context (array indexing)
 * @return String representation of the array indices in C syntax
 */
antlrcpp::Any PascalToCTranslator::visitIdVarPart(PascalSParser::IdVarPartContext *context) {
    // Empty array access
    if (!context->expressionList()) {
        return antlrcpp::Any(std::string(""));
    }

    // Get array indices from expression list
    auto result = visit(context->expressionList());
    std::vector<std::string> indices = result.as<std::vector<std::string>>();

    // Format array access with C-style indexing
    std::stringstream ss;
    for (const auto &index: indices) {
        ss << "[" << index << "]";
    }

    return ss.str();
}

/**
 * Processes a procedure call statement
 * @param context The procedure call context
 * @return String representation of the procedure call in C syntax
 */
antlrcpp::Any PascalToCTranslator::visitProcedureCall(PascalSParser::ProcedureCallContext *context) {
    std::string id = TranslatorUtils::toCIdentifier(context->ID()->getText());

    // Check if it's a procedure call with arguments
    if (context->expressionList()) {
        auto result = visit(context->expressionList());
        std::vector<std::string> args = result.as<std::vector<std::string>>();

        // Format procedure call with arguments
        std::stringstream ss;
        ss << id << "(";

        // Get procedure definition if available to check for reference parameters
        bool hasProcedureSymbol = symbolTable->hasSymbol(id);
        std::vector<SymbolEntry> parameters;

        if (hasProcedureSymbol) {
            // Get the parameters for this procedure
            if (symbolTable->hasScope(id)) {
                const ScopeEntry &scope = symbolTable->getScope(id);
                parameters = scope.getParameters();

                // Debug output to verify parameters
                TranslatorUtils::logDebug("Procedure " + id + " parameters:");
                for (size_t i = 0; i < parameters.size(); ++i) {
                    TranslatorUtils::logDebug("  Param " + std::to_string(i) + ": " + parameters[i].name +
                                              ", isRef: " + (parameters[i].isReference ? "true" : "false"));
                }
            }
        }

        for (size_t i = 0; i < args.size(); ++i) {
            if (i > 0) {
                ss << ", ";
            }

            // Check if this parameter should be passed by reference
            bool isReferenceParam = false;
            bool isArrayType = false;
            bool isMultidimensionalArray = false;

            // Fix parameter ordering issue: The parameters in the scope's parameters list are
            // stored in reverse order compared to how they appear in Pascal source.
            // So need to reverse the index to match the correct parameter.
            if (parameters.size() == args.size()) {
                // Calculate the correct parameter index (parameters are in reverse order)
                size_t paramIndex = parameters.size() - 1 - i;

                isReferenceParam = parameters[paramIndex].isReference;

                // Debug output to verify reference parameter detection
                TranslatorUtils::logDebug("  Checking arg " + std::to_string(i) + ": " + args[i] +
                                          ", isRef: " + (isReferenceParam ? "true" : "false") +
                                          ", paramIndex: " + std::to_string(paramIndex));

                // Check if the argument is an array
                std::string argBase = args[i];
                size_t bracketPos = argBase.find('[');
                size_t parenPos = argBase.find('(');

                // Extract base variable name if it has array indexing or function call
                if (bracketPos != std::string::npos) {
                    argBase = argBase.substr(0, bracketPos);
                } else if (parenPos != std::string::npos) {
                    argBase = argBase.substr(0, parenPos);
                }

                // Check if the argument is an array and if it's multidimensional
                if (symbolTable->hasSymbol(argBase)) {
                    const SymbolEntry &argEntry = symbolTable->getSymbol(argBase);
                    isArrayType = (argEntry.dataType == PascalType::ARRAY);
                    isMultidimensionalArray = (isArrayType && argEntry.arrayDimensions.size() > 1);

                    TranslatorUtils::logDebug("    Arg " + argBase + " is array: " + (isArrayType ? "true" : "false") +
                                              ", is multidimensional: " + (isMultidimensionalArray ? "true" : "false") +
                                              ", dimensions: " + std::to_string(argEntry.arrayDimensions.size()));
                }

                // Handle regular arrays and multidimensional arrays differently
                if (isArrayType) {
                    // If it's an array indexing operation, we need to check if we're passing a slice of the array
                    if (args[i].find('[') != std::string::npos) {
                        // Count the number of dimensions in the original array vs. the array access
                        int accessedDimensions = 0;
                        size_t pos = 0;
                        while ((pos = args[i].find('[', pos)) != std::string::npos) {
                            accessedDimensions++;
                            pos++;
                        }

                        // If using the parameter as an array, check dimensions
                        bool isFullyIndexed = false;
                        if (symbolTable->hasSymbol(argBase)) {
                            const SymbolEntry &argEntry = symbolTable->getSymbol(argBase);
                            isFullyIndexed = (accessedDimensions >= argEntry.arrayDimensions.size());
                        }

                        // If we're passing a slice or the parameter expects an array
                        if (!isFullyIndexed) {
                            // Pass the array element directly (it's a slice of the multidimensional array)
                            ss << args[i];
                        } else {
                            // Pass the fully indexed element (might need & if it's a VAR parameter)
                            if (isReferenceParam) {
                                ss << "(&(" << args[i] << "))";
                            } else {
                                ss << args[i];
                            }
                        }
                    } else {
                        // Passing the whole array - no & needed as arrays are passed by reference by default
                        ss << args[i];
                    }
                }
                    // For non-array parameters that are passed by reference
                else if (isReferenceParam) {
                    ss << "(&(" << args[i] << "))";
                    TranslatorUtils::logDebug("  Adding & to " + args[i]);
                } else {
                    // Regular value parameter
                    ss << args[i];
                }
                std::cout << "arg :" << args[i] << std::endl;
            } else {
                // If we can't match parameters, just pass the argument as-is
                ss << args[i];
                std::cout << "can't match parameters, arg :" << args[i] << std::endl;
            }
        }

        ss << ")";

        return ss.str();
    }

    // Procedure call without arguments
    return id + "()";
}

/**
 * Processes the else part of an if statement
 * @param context The else part context
 * @return String representation of "else" (for consistency in visitor pattern)
 */
antlrcpp::Any PascalToCTranslator::visitElsePart(PascalSParser::ElsePartContext *context) {
    // Empty else part
    if (!context->statement()) {
        return antlrcpp::Any(std::string(""));
    }

    // Visit else statement
    visit(context->statement());

    return antlrcpp::Any(std::string("else"));
}

/**
 * Processes a list of expressions for function/procedure arguments or array indices
 * @param context The expression list context
 * @return Vector of string representations of expressions in C syntax
 */
antlrcpp::Any PascalToCTranslator::visitExpressionList(PascalSParser::ExpressionListContext *context) {
    std::vector<std::string> exprs;

    try {
        // In Pascal, expressions in a list appear from left to right in the source code,
        // but the ANTLR parser processes them in a way that the rightmost expression becomes
        // the current node and earlier expressions are in the nested expressionList.

        // First, process any earlier expressions in the nested expressionList
        if (context->expressionList()) {
            auto earlierExprs = visit(context->expressionList());
            exprs = earlierExprs.as<std::vector<std::string>>();
        }

        // Then add the current expression, which comes later in the source
        auto result = visit(context->expression());
        exprs.push_back(result.as<std::string>());
    } catch (const std::bad_cast &e) {
        TranslatorUtils::logError("Type conversion error in expression list: " + std::string(e.what()));
    }

    return exprs;
}

/**
 * Processes an expression which can be a simple expression or a relational expression
 * @param context The expression context
 * @return String representation of the expression in C syntax
 */
antlrcpp::Any PascalToCTranslator::visitExpression(PascalSParser::ExpressionContext *context) {
    // Simple expression (no relational operator)
    if (!context->relop()) {
        return visit(context->simpleExpression(0));
    }

    // Relational expression (with comparison operator)
    auto leftResult = visit(context->simpleExpression(0));
    std::string left = leftResult.as<std::string>();

    auto relopResult = visit(context->relop());
    std::string op = relopResult.as<std::string>();

    auto rightResult = visit(context->simpleExpression(1));
    std::string right = rightResult.as<std::string>();

    // Check if the left or right operands are function names that should use their tmp variables
    std::string currentScopeName = symbolTable->getCurrentScope().getScopeName();
    if (left == currentScopeName) {
        left = left + "tmp";
    }
    if (right == currentScopeName) {
        right = right + "tmp";
    }

    // Parenthesize the comparison for safety
    std::string result = "(" + left + " " + op + " " + right + ")";
    return antlrcpp::Any(result);
}

/**
 * Processes a simple expression which can be a term or additive expressions
 * @param context The simple expression context
 * @return String representation of the simple expression in C syntax
 */
antlrcpp::Any PascalToCTranslator::visitSimpleExpression(PascalSParser::SimpleExpressionContext *context) {
    // Single term (no additive operator)
    if (!context->addop()) {
        return visit(context->term());
    }

    // Expression with additive operator (+ - OR)
    auto leftResult = visit(context->simpleExpression());
    std::string left = leftResult.as<std::string>();

    auto addopResult = visit(context->addop());
    std::string op = addopResult.as<std::string>();

    auto rightResult = visit(context->term());
    std::string right = rightResult.as<std::string>();

    // Check if the left or right operands are function names that should use their tmp variables
    std::string currentScopeName = symbolTable->getCurrentScope().getScopeName();
    if (left == currentScopeName) {
        left = left + "tmp";
    }
    if (right == currentScopeName) {
        right = right + "tmp";
    }

    // Parenthesize the expression for correct precedence
    return antlrcpp::Any(std::string("(") + left + " " + op + " " + right + ")");
}

/**
 * Processes a term which can be a factor or multiplicative expressions
 * @param context The term context
 * @return String representation of the term in C syntax
 */
antlrcpp::Any PascalToCTranslator::visitTerm(PascalSParser::TermContext *context) {
    // Single factor (no multiplicative operator)
    if (!context->mulop()) {
        return visit(context->factor());
    }

    // Term with multiplicative operator (* / DIV MOD AND)
    auto leftResult = visit(context->term());
    std::string left = leftResult.as<std::string>();

    auto mulopResult = visit(context->mulop());
    std::string op = mulopResult.as<std::string>();

    auto rightResult = visit(context->factor());
    std::string right = rightResult.as<std::string>();

    // Check if the left or right operands are function names that should use their tmp variables
    std::string currentScopeName = symbolTable->getCurrentScope().getScopeName();
    if (left == currentScopeName) {
        left = left + "tmp";
    }
    if (right == currentScopeName) {
        right = right + "tmp";
    }

    // Parenthesize the expression for correct precedence
    return antlrcpp::Any(std::string("(") + left + " " + op + " " + right + ")");
}

/**
 * Processes a factor, which can be a constant, variable, expression, function call, or unary operation
 * @param context The factor context
 * @return String representation of the factor in C syntax
 */
antlrcpp::Any PascalToCTranslator::visitFactor(PascalSParser::FactorContext *context) {
    // Number literal
    if (context->num()) {
        return visit(context->num());
    }
        // Variable (can be simple variable or array element)
    else if (context->variable()) {
        return visit(context->variable());
    }
        // Parenthesized expression
    else if (context->LPAREN() && context->expression()) {
        auto result = visit(context->expression());
        std::string expr = result.as<std::string>();

        return antlrcpp::Any(std::string("(") + expr + ")");
    }
        // Function call
    else if (context->ID() && context->expressionList()) {
        std::string id = TranslatorUtils::toCIdentifier(context->ID()->getText());

        if (!symbolTable->hasSymbol(id)) {
            std::cout << "----------------------------------------------------------" << std::endl;
            std::cout << "Error: Undefined variable " << id << " in "
                      << symbolTable->getCurrentScope().getScopeName() << ", line :" << context->start->getLine()
                      << std::endl;
            std::cout << "----------------------------------------------------------" << std::endl;
        }

        auto result = visit(context->expressionList());
        std::vector<std::string> args = result.as<std::vector<std::string>>();

        // Format function call
        std::stringstream ss;
        ss << id << "(";

        // Get function definition if available to check for reference parameters
        bool hasFunctionSymbol = symbolTable->hasSymbol(id);
        std::vector<SymbolEntry> parameters;

        if (hasFunctionSymbol) {
            // Get the parameters for this function
            if (symbolTable->hasScope(id)) {
                const ScopeEntry &scope = symbolTable->getScope(id);
                parameters = scope.getParameters();

                // Debug output to verify parameters
                TranslatorUtils::logDebug("Function " + id + " parameters:");
                for (size_t i = 0; i < parameters.size(); ++i) {
                    TranslatorUtils::logDebug("  Param " + std::to_string(i) + ": " + parameters[i].name +
                                              ", isRef: " + (parameters[i].isReference ? "true" : "false"));
                }
            }
        }

        for (size_t i = 0; i < args.size(); ++i) {
            if (i > 0) {
                ss << ", ";
            }

            // Check if this parameter should be passed by reference
            bool isReferenceParam = false;
            bool isArrayType = false;
            bool isMultidimensionalArray = false;

            // Fix parameter ordering issue: The parameters in the scope's parameters list are
            // stored in reverse order compared to how they appear in Pascal source.
            // We need to reverse the index to match the correct parameter.
            if (parameters.size() == args.size()) {
                // Calculate the correct parameter index (parameters are in reverse order)
                size_t paramIndex = parameters.size() - 1 - i;

                isReferenceParam = parameters[paramIndex].isReference;

                // Debug output to verify reference parameter detection
                TranslatorUtils::logDebug("  Checking arg " + std::to_string(i) + ": " + args[i] +
                                          ", isRef: " + (isReferenceParam ? "true" : "false") +
                                          ", paramIndex: " + std::to_string(paramIndex));

                // Check if the argument is an array
                std::string argBase = args[i];
                size_t bracketPos = argBase.find('[');
                size_t parenPos = argBase.find('(');

                // Extract base variable name if it has array indexing or function call
                if (bracketPos != std::string::npos) {
                    argBase = argBase.substr(0, bracketPos);
                } else if (parenPos != std::string::npos) {
                    argBase = argBase.substr(0, parenPos);
                }

                // Check if the argument is an array and if it's multidimensional
                if (symbolTable->hasSymbol(argBase)) {
                    const SymbolEntry &argEntry = symbolTable->getSymbol(argBase);
                    isArrayType = (argEntry.dataType == PascalType::ARRAY);
                    isMultidimensionalArray = (isArrayType && argEntry.arrayDimensions.size() > 1);

                    TranslatorUtils::logDebug("    Arg " + argBase + " is array: " + (isArrayType ? "true" : "false") +
                                              ", is multidimensional: " + (isMultidimensionalArray ? "true" : "false") +
                                              ", dimensions: " + std::to_string(argEntry.arrayDimensions.size()));
                }

                // Handle regular arrays and multidimensional arrays differently
                if (isArrayType) {
                    // If it's an array indexing operation, we need to check if we're passing a slice of the array
                    if (args[i].find('[') != std::string::npos) {
                        // Count the number of dimensions in the original array vs. the array access
                        int accessedDimensions = 0;
                        size_t pos = 0;
                        while ((pos = args[i].find('[', pos)) != std::string::npos) {
                            accessedDimensions++;
                            pos++;
                        }

                        // If using the parameter as an array, check dimensions
                        bool isFullyIndexed = false;
                        if (symbolTable->hasSymbol(argBase)) {
                            const SymbolEntry &argEntry = symbolTable->getSymbol(argBase);
                            isFullyIndexed = (accessedDimensions >= argEntry.arrayDimensions.size());
                        }

                        // If we're passing a slice or the parameter expects an array
                        if (!isFullyIndexed) {
                            // Pass the array element directly (it's a slice of the multidimensional array)
                            ss << args[i];
                        } else {
                            // Pass the fully indexed element (might need & if it's a VAR parameter)
                            if (isReferenceParam) {
                                ss << "(&(" << args[i] << "))";
                            } else {
                                ss << args[i];
                            }
                        }
                    } else {
                        // Passing the whole array - no & needed as arrays are passed by reference by default
                        ss << args[i];
                    }
                }
                    // For non-array parameters that are passed by reference
                else if (isReferenceParam) {
                    ss << "(&(" << args[i] << "))";
                    TranslatorUtils::logDebug("  Adding & to " + args[i]);
                } else {
                    // Regular value parameter
                    ss << args[i];
                }
            } else {
                // If we can't match parameters, just pass the argument as-is
                ss << args[i];
            }
        }

        ss << ")";
        std::cout << "function call :" << ss.str() << std::endl;

        return ss.str();
    }
        // Function call without parentheses (for Pascal functions with no parameters)
    else if (context->ID() && !context->expressionList()) {
        std::string id = TranslatorUtils::toCIdentifier(context->ID()->getText());

        if (!symbolTable->hasSymbol(id)) {
            std::cout << "----------------------------------------------------------" << std::endl;
            std::cout << "Error: Undefined variable " << id << " in "
                      << symbolTable->getCurrentScope().getScopeName() << ", line :" << context->start->getLine()
                      << std::endl;
            std::cout << "----------------------------------------------------------" << std::endl;
        }

        // Check if this ID is a function in the symbol table
        if (symbolTable->hasSymbol(id)) {
            const SymbolEntry &entry = symbolTable->getSymbol(id);

            // If it's a function and it has a scope (meaning it's a function declaration, not a variable)
            if (entry.symbolType == SymbolType::FUNCTION && symbolTable->hasScope(id)) {
                const ScopeEntry &scope = symbolTable->getScope(id);
                // Check if the function has no parameters
                if (scope.getParameters().empty()) {
                    // This is a parameter-less function call without parentheses
                    // In C, we need to add the parentheses
                    return id + "()";
                }
            } else if (entry.symbolType == SymbolType::PARAMETER) {
                if (entry.isReference && symbolTable->hasSymbolInCurrentScope(id)) {
                    // For non-array reference parameters, we need to dereference when accessing
                    return "(*" + id + ")";
                }
            }

            // Special case: if we're in a function and we're referencing the function's name
            // as a variable (typical for recursive functions in Pascal)
            if (id == symbolTable->getCurrentScope().getScopeName()) {
                // This is accessing our own function's return value
                return id + "tmp";
            }
        }

        // If not recognized as a function with no parameters, treat as a regular variable
        return id;
    }
        // Logical NOT operation
    else if (context->NOT()) {
        auto result = visit(context->factor());
        std::string factor = result.as<std::string>();
        if (!((factor[0] >= '0' && factor[0] <= '9') || factor[0] == '(' || factor[0] == '-' || factor[0] == '~' ||
              factor[0] == '+') && (!symbolTable->hasSymbol(factor))) {
            std::cout << "----------------------------------------------------------" << std::endl;
            std::cout << "Error: Undefined variable " << factor << " in "
                      << symbolTable->getCurrentScope().getScopeName() << ", line :" << context->start->getLine()
                      << std::endl;
            std::cout << "----------------------------------------------------------" << std::endl;
        }
        return antlrcpp::Any(std::string("~(") + factor + ")");
    }
        // Unary minus operation
    else if (context->MINUS()) {
        auto result = visit(context->factor());
        std::string factor = result.as<std::string>();
        if (!((factor[0] >= '0' && factor[0] <= '9') || factor[0] == '(' || factor[0] == '-' || factor[0] == '~' ||
              factor[0] == '+') && (!symbolTable->hasSymbol(factor))) {
            std::cout << "----------------------------------------------------------" << std::endl;
            std::cout << "Error: Undefined variable " << factor << " in "
                      << symbolTable->getCurrentScope().getScopeName() << ", line :" << context->start->getLine()
                      << std::endl;
            std::cout << "----------------------------------------------------------" << std::endl;
        }

        return antlrcpp::Any(std::string("-(") + factor + ")");
    }
        // Unary plus operation
    else if (context->PLUS()) {
        auto result = visit(context->factor());
        std::string factor = result.as<std::string>();
        if (!((factor[0] >= '0' && factor[0] <= '9') || factor[0] == '(' || factor[0] == '-' || factor[0] == '~' ||
              factor[0] == '+') && (!symbolTable->hasSymbol(factor))) {
            std::cout << "----------------------------------------------------------" << std::endl;
            std::cout << "Error: Undefined variable " << factor << " in "
                      << symbolTable->getCurrentScope().getScopeName() << ", line :" << context->start->getLine()
                      << std::endl;
            std::cout << "----------------------------------------------------------" << std::endl;
        }

        return antlrcpp::Any(std::string("+(") + factor + ")");
    }
        // String literal
    else if (context->STRING()) {
        return context->STRING()->getText();
    }
        // Character literal
    else if (context->LETTER()) {
        return antlrcpp::Any(
                std::string((TranslatorUtils::toCIdentifier(context->LETTER()->getText()) == "true") ? "1" : "0"));
    }

    return antlrcpp::Any(std::string(""));
}

/**
 * Processes a numeric literal
 * @param context The num context
 * @return String representation of the number
 */
antlrcpp::Any PascalToCTranslator::visitNum(PascalSParser::NumContext *context) {
    return context->NUM()->getText();
}

/**
 * Processes a relational operator (==, !=, <, <=, >, >=)
 * @param context The relop context
 * @return String representation of the operator in C syntax
 */
antlrcpp::Any PascalToCTranslator::visitRelop(PascalSParser::RelopContext *context) {
    if (context->EQUAL()) {
        return antlrcpp::Any(std::string("=="));  // Pascal = becomes == in C
    } else if (context->NOTEQUAL()) {
        return antlrcpp::Any(std::string("!="));  // Pascal <> becomes != in C
    } else if (context->LT()) {
        return antlrcpp::Any(std::string("<"));   // Pascal < same in C
    } else if (context->LE()) {
        return antlrcpp::Any(std::string("<="));  // Pascal <= same in C
    } else if (context->GT()) {
        return antlrcpp::Any(std::string(">"));   // Pascal > same in C
    } else if (context->GE()) {
        return antlrcpp::Any(std::string(">="));  // Pascal >= same in C
    }

    return antlrcpp::Any(std::string(""));
}

/**
 * Processes an additive operator (+, -, OR)
 * @param context The addop context
 * @return String representation of the operator in C syntax
 */
antlrcpp::Any PascalToCTranslator::visitAddop(PascalSParser::AddopContext *context) {
    if (context->PLUS()) {
        return antlrcpp::Any(std::string("+"));   // Pascal + same in C
    } else if (context->MINUS()) {
        return antlrcpp::Any(std::string("-"));   // Pascal - same in C
    } else if (context->OR()) {
        return antlrcpp::Any(std::string("||"));  // Pascal OR becomes || in C
    }

    return antlrcpp::Any(std::string(""));
}

/**
 * Processes a multiplicative operator (*, /, DIV, MOD, AND)
 * @param context The mulop context
 * @return String representation of the operator in C syntax
 */
antlrcpp::Any PascalToCTranslator::visitMulop(PascalSParser::MulopContext *context) {
    if (context->STAR()) {
        return antlrcpp::Any(std::string("*"));   // Pascal * same in C
    } else if (context->SLASH()) {
        return antlrcpp::Any(std::string("/"));   // Pascal / same in C (float division)
    } else if (context->DIV()) {
        return antlrcpp::Any(std::string("/"));   // Pascal DIV becomes / in C (integer division)
    } else if (context->MOD()) {
        return antlrcpp::Any(std::string("%"));   // Pascal MOD becomes % in C
    } else if (context->AND()) {
        return antlrcpp::Any(std::string("&&"));  // Pascal AND becomes && in C
    }

    return antlrcpp::Any(std::string(""));
}