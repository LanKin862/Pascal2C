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
 * 主翻译方法，将Pascal代码转换为C代码
 * @param inputFile Pascal源文件的路径
 * @return 包含翻译后的C代码的字符串
 */
std::string PascalToCTranslator::translate(const std::string &inputFile) {
    // 为新的翻译清除状态
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
 * 增加缩进级别一个单位（4个空格）
 */
void PascalToCTranslator::increaseIndentation() {
    indentation += "    ";
}

/**
 * 减少缩进级别一个单位（4个空格）
 * 确保缩进不会变为负值
 */
void PascalToCTranslator::decreaseIndentation() {
    if (!indentation.empty()) {
        indentation.resize(indentation.size() - 4);
    }
}

/**
 * 返回当前缩进字符串
 * @return 当前缩进，表示为一串空格
 */
std::string PascalToCTranslator::getCurrentIndentation() const {
    return indentation;
}

/**
 * 生成一个唯一的临时变量名
 * @return 表示新临时变量的字符串
 */
std::string PascalToCTranslator::getNextTempVar() {
    return "temp_" + std::to_string(tempVarCounter++);
}

/**
 * 处理程序节点，它是解析树的根
 * 生成Pascal程序需要的标准包含文件和辅助函数
 * @param context 来自解析器的程序上下文
 * @return 访问者模式的标准占位符
 */
antlrcpp::Any PascalToCTranslator::visitProgram(PascalSParser::ProgramContext *context) {
    // 为Pascal功能生成标准C包含文件
    output << "#include <stdio.h>\n";
    output << "#include <stdlib.h>\n";
    output << "#include <stdbool.h>\n";
    output << "#include <string.h>\n";
    output << "#include <stdarg.h>\n\n";

    // 定义Pascal特定的类型和辅助函数
    output << "// Pascal-specific functions and types\n";
    output << "typedef int boolean;\n";
    output << "typedef char *string;\n\n";

    // 访问程序结构节点
    return visit(context->programStruct());
}

/**
 * 处理由头部和主体组成的程序结构
 * @param context 来自解析器的程序结构上下文
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
 * @param context 来自解析器的程序头部上下文
 * @return 访问者模式的标准占位符
 */
antlrcpp::Any PascalToCTranslator::visitProgramHead(PascalSParser::ProgramHeadContext *context) {
    // 提取程序名称
    std::string programName = context->ID()->getText();

    // 在C代码中添加程序名称作为注释
    output << "// Program: " << programName << "\n\n";

    return antlrcpp::Any();
}

/**
 * 处理包含声明和复合语句的程序主体
 * @param context 来自解析器的程序主体上下文
 * @return 访问者模式的标准占位符
 */
antlrcpp::Any PascalToCTranslator::visitProgramBody(PascalSParser::ProgramBodyContext *context) {
    // 如果存在，处理常量声明
    if (context->constDeclarations()) {
        visit(context->constDeclarations());
    }

    // 如果存在，处理变量声明
    if (context->varDeclarations()) {
        visit(context->varDeclarations());
    }

    // 首先为所有子程序创建前向声明以处理函数引用
    if (context->subprogramDeclarations()) {
        // 创建临时字符串流来收集前向声明
        std::stringstream forwardDeclsStream;
        std::stringstream tempOutput = std::move(output);
        output = std::move(forwardDeclsStream);

        output << "// Forward declarations\n";
        generateForwardDeclarations(context->subprogramDeclarations());
        output << "\n";

        // 恢复原始输出并添加前向声明
        std::string forwardDecls = output.str();
        output = std::move(tempOutput);
        output << forwardDecls;
    }

    // 如果存在，处理子程序（函数/过程）声明
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
 * 用于生成所有函数和过程的前向声明的辅助方法
 * 这对于处理函数引用和维护正确的参数类型是必要的
 * @param context 子程序声明上下文
 */
void PascalToCTranslator::generateForwardDeclarations(PascalSParser::SubprogramDeclarationsContext *context) {
    if (!context) return;

    // 首先处理任何嵌套声明（在源码中较早出现）
    if (context->subprogramDeclarations()) {
        generateForwardDeclarations(context->subprogramDeclarations());
    }
    // 处理当前子程序（在源码中较晚出现）
    if (context->subprogram()) {
        PascalSParser::SubprogramHeadContext *headContext = context->subprogram()->subprogramHead();
        if (headContext) {
            std::string name = TranslatorUtils::toCIdentifier(headContext->ID()->getText());
            bool isFunction = headContext->FUNCTION() != nullptr;

            // 获取函数的返回类型
            std::string returnType = "void";
            if (isFunction && headContext->basicType()) {
                auto result = visit(headContext->basicType());
                PascalType pascalReturnType = result.as<PascalType>();
                returnType = typeConverter->convertType(pascalReturnType);
            }

            // 获取参数
            std::string params = "()";
            if (headContext->formalParameter()) {
                auto paramsResult = visit(headContext->formalParameter());
                params = paramsResult.as<std::string>();
            }

            // 输出前向声明
            output << returnType << " " << name << params << ";\n";
            std::cout << "Forward declaration for " << name << " generated\n";
        }
    }
}

/**
 * 处理标识符列表，用于变量和参数声明
 * @param context 来自解析器的标识符列表上下文
 * @return C兼容标识符字符串的向量
 */
antlrcpp::Any PascalToCTranslator::visitIdList(PascalSParser::IdListContext *context) {
    std::vector<std::string> ids;

    // 收集所有标识符并将它们转换为C兼容的名称
    for (auto id: context->ID()) {
        ids.push_back(TranslatorUtils::toCIdentifier(id->getText()));
    }

    return ids;
}

/**
 * 处理常量声明部分
 * @param context 常量声明上下文
 * @return 访问者模式的标准占位符
 */
antlrcpp::Any PascalToCTranslator::visitConstDeclarations(PascalSParser::ConstDeclarationsContext *context) {
    // 检查是否有任何常量声明
    if (!context->constDeclaration()) {
        return antlrcpp::Any();
    }

    output << "// Constants\n";

    // 访问常量声明节点
    visit(context->constDeclaration());

    output << "\n";

    return antlrcpp::Any();
}

/**
 * 处理单个常量声明
 * 将Pascal常量转换为C的#define语句
 * @param context 常量声明上下文
 * @return 访问者模式的标准占位符
 */
antlrcpp::Any PascalToCTranslator::visitConstDeclaration(PascalSParser::ConstDeclarationContext *context) {
    std::string id = TranslatorUtils::toCIdentifier(context->ID()->getText());

    // 获取常量值
    std::string value = visit(context->constValue()).as<std::string>();

    // 添加常量到符号表
    SymbolEntry entry;
    entry.name = id;
    entry.symbolType = SymbolType::CONSTANT;
    entry.value = value;

    // 尝试从值的格式推断类型
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

    // 输出为C预处理器定义
    output << "#define " << entry.name << " " << entry.value << "\n";

    // 如果有其他常量声明，则递归处理
    if (context->constDeclaration()) {
        visit(context->constDeclaration());
    }

    return antlrcpp::Any();
}

/**
 * 处理常量值，包括数字、字母和字符串
 * @param context 常量值上下文
 * @return 常量值的字符串表示
 */
antlrcpp::Any PascalToCTranslator::visitConstValue(PascalSParser::ConstValueContext *context) {
    if (context->num()) {
        // 处理数字常量，保留符号
        if (context->PLUS()) {
            return "+" + context->num()->getText();
        } else if (context->MINUS()) {
            return "-" + context->num()->getText();
        } else {
            return context->num()->getText();
        }
    } else if (context->LETTER()) {
        // 处理字符常量
        return context->LETTER()->getText();
    } else if (context->STRING()) {
        // 处理字符串常量
        return context->STRING()->getText();
    }

    return antlrcpp::Any(std::string(""));
}

/**
 * 处理变量声明部分
 * @param context 变量声明上下文
 * @return 访问者模式的标准占位符
 */
antlrcpp::Any PascalToCTranslator::visitVarDeclarations(PascalSParser::VarDeclarationsContext *context) {
    // 检查是否有任何变量声明
    if (!context->varDeclaration()) {
        return antlrcpp::Any();
    }

    output << "// Variables\n";

    // 访问变量声明节点
    visit(context->varDeclaration());

    output << "\n";

    return antlrcpp::Any();
}

/**
 * 处理单个变量声明
 * 将Pascal变量声明转换为带初始化的C变量声明
 * @param context 变量声明上下文
 * @return 访问者模式的标准占位符
 */
antlrcpp::Any PascalToCTranslator::visitVarDeclaration(PascalSParser::VarDeclarationContext *context) {
    // 获取变量标识符列表
    std::vector<std::string> ids = visit(context->idList()).as<std::vector<std::string>>();

    // 获取类型信息
    auto typeResult = visit(context->type());

    // 初始化类型信息变量
    std::string typeStr;
    PascalType pascalType;
    PascalType elementType = PascalType::INTEGER; // 数组的默认元素类型
    std::vector<ArrayBounds> dimensions;

    // 基于是基本类型还是数组类型提取类型信息
    try {
        // 首先尝试提取为基本类型
        auto typePair = typeResult.as<std::pair<std::string, PascalType>>();
        typeStr = typePair.first;
        pascalType = typePair.second;
    } catch (const std::bad_cast &) {
        // 如果不是基本类型，就是数组类型
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

    // 为每个标识符输出变量声明
    for (auto &id: ids) {
        // 处理类型字符串中带有数组维度的数组类型
        std::regex pattern("\\[.*\\]");
        std::smatch matches;
        if (std::regex_search(typeStr, matches, pattern)) {
            // 对于数组类型，在标识符后放置维度
            std::string tmpId = id + std::string(matches[0]);
            std::string tmpTypeStr = std::regex_replace(typeStr, pattern, "");
            output << tmpTypeStr << " " << tmpId;

            // 对于多维数组，添加初始化代码将所有元素置零
            if (pascalType == PascalType::ARRAY && dimensions.size() > 1) {
                output << " = {0}";  // C99及以后支持这种零初始化语法
            }
        } else {
            // 对于基本类型，使用标准格式
            output << typeStr << " " << id;
        }

        // 只为非数组类型添加初始化（数组的初始化更复杂）
        if (pascalType != PascalType::ARRAY) {
            // 根据类型用默认值初始化
            if (pascalType == PascalType::INTEGER) {
                output << " = 0";
            } else if (pascalType == PascalType::REAL) {
                output << " = 0.0";
            } else if (pascalType == PascalType::BOOLEAN) {
                output << " = 0";  // C中的false
            } else if (pascalType == PascalType::CHAR) {
                output << " = '\\0'";
            }
        } else if (dimensions.size() == 1) {
            // 对于单维数组，添加简单的零初始化
            output << " = {0}";  // C99及以后支持这种零初始化语法
        }
        output << ";\n";

        // 将变量添加到符号表进行类型检查和引用
        SymbolEntry entry;
        entry.name = id;
        entry.symbolType = SymbolType::VARIABLE;
        entry.dataType = pascalType;

        // 如果需要，存储数组特定信息
        if (pascalType == PascalType::ARRAY) {
            entry.arrayElementType = elementType;
            entry.arrayDimensions = dimensions;
        }

        symbolTable->addSymbol(entry);
    }

    // 如果有其他变量声明，则递归处理
    if (context->varDeclaration()) {
        visit(context->varDeclaration());
    }

    return antlrcpp::Any();
}

/**
 * 处理类型声明，处理基本类型和数组
 * @param context 类型上下文
 * @return 类型信息，基本类型为对（pair），数组类型为元组（tuple）
 */
antlrcpp::Any PascalToCTranslator::visitType(PascalSParser::TypeContext *context) {
    if (context->basicType() && context->ARRAY() == nullptr) {
        // 基本类型（整数、实数、布尔、字符）
        auto result = visit(context->basicType());
        PascalType type = result.as<PascalType>();
        std::string typeStr = typeConverter->convertType(type);
        return std::make_pair(typeStr, type);
    } else if (context->ARRAY()) {
        // 带维度的数组类型
        auto basicTypeResult = visit(context->basicType());
        PascalType elementType = basicTypeResult.as<PascalType>();

        // 获取数组维度（边界）
        auto periodResult = visit(context->period());
        std::vector<ArrayBounds> dimensions = periodResult.as<std::vector<ArrayBounds>>();

        // 使用类型转换器转换为C数组类型
        std::string arrayTypeStr = typeConverter->convertArrayType(elementType, dimensions);

        // 返回数组类型、元素类型和维度作为元组
        return std::make_tuple(arrayTypeStr, PascalType::ARRAY, elementType, dimensions);
    }

    throw TranslatorException("Unknown type");
}

/**
 * 处理基本类型关键字（INTEGER、REAL、BOOLEAN、CHAR）
 * @param context 基本类型上下文
 * @return 表示类型的PascalType枚举值
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
 * 处理数组索引范围声明（如1..10、0..9）
 * @param context 包含范围边界的周期上下文
 * @return 包含上下边界的ArrayBounds结构向量
 */
antlrcpp::Any PascalToCTranslator::visitPeriod(PascalSParser::PeriodContext *context) {
    std::vector<ArrayBounds> dimensions;
    std::vector<std::string> numStrings;
    std::string periodStr = context->getText();

    // 提取所有由DOTDOT（..）分隔的数字对
    std::regex pattern(R"((\d+)\.\.(\d+))");  // 匹配 "数字..数字"
    std::smatch matches;

    auto begin = periodStr.cbegin();
    auto end = periodStr.cend();

    while (std::regex_search(begin, end, matches, pattern)) {
        numStrings.push_back(matches[1].str());  // 下界（如 "1"）
        numStrings.push_back(matches[2].str());  // 上界（如 "4"）
        begin = matches[0].second;           // 继续匹配剩余部分
    }
    // 将边界转换为整数并存储在ArrayBounds结构中
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
 * 处理子程序（函数/过程）声明
 * @param context 子程序声明上下文
 * @return 访问者模式的标准占位符
 */
antlrcpp::Any PascalToCTranslator::visitSubprogramDeclarations(PascalSParser::SubprogramDeclarationsContext *context) {
    // 检查是否有任何子程序声明
    if (!context->subprogramDeclarations() && !context->subprogram()) {
        return antlrcpp::Any();
    }

    // 首先处理当前子程序声明，这在源代码中较早出现
    if (context->subprogramDeclarations()) {
        visit(context->subprogramDeclarations());
    }

    // 然后处理在源代码中较晚出现的其他子程序
    if (context->subprogram()) {
        visit(context->subprogram());
    }
    return antlrcpp::Any();
}

/**
 * 处理单个子程序（函数或过程）
 * @param context 子程序上下文
 * @return 访问者模式的标准占位符
 */
antlrcpp::Any PascalToCTranslator::visitSubprogram(PascalSParser::SubprogramContext *context) {
    // 访问子程序头部以生成函数签名
    visit(context->subprogramHead());

    // 为函数体添加开括号
    output << " {\n";
    increaseIndentation();

    // 对于函数，添加一个与函数同名的返回值变量
    if (context->subprogramHead()->FUNCTION()) {
        std::string funcName = TranslatorUtils::toCIdentifier(context->subprogramHead()->ID()->getText());
        std::string funcNameTmp = funcName + "tmp";
        auto typeResult = visit(context->subprogramHead()->basicType());
        PascalType returnType = typeResult.as<PascalType>();
        std::string cType = typeConverter->convertType(returnType);

        // 根据类型初始化返回值变量
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
            // 数组在C中默认初始化为零
            output << "{0}";
        }
        output << ";\n";

        // 同时将临时变量名存储在符号表中，以便我们能正确引用
        SymbolEntry tmpEntry;
        tmpEntry.name = funcNameTmp;
        tmpEntry.symbolType = SymbolType::VARIABLE;
        tmpEntry.dataType = returnType;
        symbolTable->addSymbol(tmpEntry);
    }

    // 访问子程序主体以生成函数实现
    visit(context->subprogramBody());

    // 对于函数，如果没有返回语句，在末尾添加一个
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
 * 处理子程序头部（函数或过程声明）
 * @param context 子程序头部上下文
 * @return 访问者模式的标准占位符
 */
antlrcpp::Any PascalToCTranslator::visitSubprogramHead(PascalSParser::SubprogramHeadContext *context) {
    // 获取函数/过程名称并转换为C标识符
    std::string name = TranslatorUtils::toCIdentifier(context->ID()->getText());

    // 确定这是函数还是过程
    bool isFunction = context->FUNCTION() != nullptr;

    // 获取函数的返回类型（过程默认为void）
    std::string returnType = "void";
    PascalType pascalReturnType = PascalType::INTEGER;  // 默认

    if (isFunction) {
        auto result = visit(context->basicType());
        pascalReturnType = result.as<PascalType>();
        returnType = typeConverter->convertType(pascalReturnType);
    }

    // 在进入其作用域之前将函数/过程添加到符号表
    SymbolEntry entry;
    entry.name = name;
    entry.symbolType = isFunction ? SymbolType::FUNCTION : SymbolType::PROCEDURE;
    entry.dataType = pascalReturnType;
    symbolTable->addSymbol(entry);

    // 为函数/过程创建新的作用域
    symbolTable->enterScope(name);

    // 输出带有返回类型和名称的函数/过程声明
    output << returnType << " " << name;

    // 访问形式参数部分
    auto paramsResult = visit(context->formalParameter());
    std::string params = paramsResult.as<std::string>();

    // 在C中，数组参数需要适当的指针表示法
    // 对于数组维度，在函数参数中第一维总是空的
    std::regex arrayPattern("\\[(\\d+)\\]");
    std::regex multiDimPattern("\\[(\\d+)\\](\\[\\d+\\])+");

    // 首先找到所有多维数组并正确转换
    std::smatch matches;
    std::string processedParams = params;
    std::string temp = processedParams;

    while (std::regex_search(temp, matches, multiDimPattern)) {
        std::string fullMatch = matches[0];

        // 提取位置并替换为适当的C数组表示法
        // 在C函数参数中，第一维总是空的：int[][10]
        size_t pos = processedParams.find(fullMatch);
        if (pos != std::string::npos) {
            std::string replacement = "[]" + fullMatch.substr(fullMatch.find("]") + 1);
            processedParams.replace(pos, fullMatch.length(), replacement);
        }

        // 从当前匹配之后继续搜索
        temp = matches.suffix().str();
    }

    // 然后处理单维数组
//    processedParams = std::regex_replace(processedParams, arrayPattern, "[]");

    output << processedParams;

    return antlrcpp::Any();
}

/**
 * 处理函数和过程的形式参数声明
 * @param context 形式参数上下文
 * @return C语法中参数列表的字符串表示
 */
antlrcpp::Any PascalToCTranslator::visitFormalParameter(PascalSParser::FormalParameterContext *context) {
    // 默认空参数列表
    if (!context->parameterList()) {
        return antlrcpp::Any(std::string("()"));
    }

    // 访问参数列表以生成参数声明
    auto result = visit(context->parameterList());
    std::string params = result.as<std::string>();

    return antlrcpp::Any(std::string("(") + params + ")");
}

/**
 * 处理参数列表
 * @param context 参数列表上下文
 * @return 所有参数的字符串表示，以逗号分隔
 */
antlrcpp::Any PascalToCTranslator::visitParameterList(PascalSParser::ParameterListContext *context) {
    std::string paramList = "";

    // 首先处理当前参数
    auto result = visit(context->parameter());
    std::string param = result.as<std::string>();

    TranslatorUtils::logDebug("Processing parameter: " + param);

    // 检查是否有任何嵌套参数（在Pascal代码中较早出现）
    if (context->parameterList()) {
        auto moreParamsResult = visit(context->parameterList());
        std::string moreParamsStr = moreParamsResult.as<std::string>();

        TranslatorUtils::logDebug("Earlier parameters: " + moreParamsStr);

        // 将早期参数放在列表的前面
        if (!moreParamsStr.empty()) {
            if (param.empty()) paramList = moreParamsStr;
            else paramList = moreParamsStr + ", " + param;
            TranslatorUtils::logDebug("Combined parameters: " + paramList);
        } else {
            paramList = param;
        }
    } else {
        // 没有嵌套参数，只返回当前参数
        paramList = param;
    }

    return paramList;
}

/**
 * 处理单个参数，可以是值参数或引用参数（VAR）
 * @param context 参数上下文
 * @return C语法中参数的字符串表示
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
 * 处理VAR参数（通过引用）
 * 在Pascal中，VAR参数通过引用传递
 * 在C中，这通过指针实现
 * @param context VAR参数上下文
 * @return C语法中带指针表示法的参数的字符串表示
 */
antlrcpp::Any PascalToCTranslator::visitVarParameter(PascalSParser::VarParameterContext *context) {
    // 获取值参数的字符串表示
    auto result = visit(context->valueParameter());
    std::string params = result.as<std::string>();

    // 从上下文中获取标识符，将它们标记为符号表中的引用参数
    auto idListResult = visit(context->valueParameter()->idList());
    std::vector<std::string> ids = idListResult.as<std::vector<std::string>>();

    // 调试输出以验证参数标识符
    std::string idListStr;
    for (const auto &id: ids) {
        if (!idListStr.empty()) idListStr += ", ";
        idListStr += id;
    }
    TranslatorUtils::logDebug("VAR parameter identifiers: " + idListStr);

    // 同时获取类型信息以检查数组类型
    auto typeResult = visit(context->valueParameter()->type());

    // 初始化类型信息变量
    std::string typeStr;
    PascalType pascalType;
    PascalType elementType = PascalType::INTEGER; // 数组的默认类型
    std::vector<ArrayBounds> dimensions;
    bool isArray = false;
    bool isMultidimensionalArray = false;

    // 基于是基本类型还是数组类型提取类型信息
    try {
        // 首先尝试提取为基本类型
        auto typePair = typeResult.as<std::pair<std::string, PascalType>>();
        typeStr = typePair.first;
        pascalType = typePair.second;
        isArray = (pascalType == PascalType::ARRAY);
    } catch (const std::bad_cast &) {
        // 如果失败，就是数组类型
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

    // 在符号表中将所有参数标记为引用参数
    for (const auto &id: ids) {
        if (symbolTable->hasSymbolInCurrentScope(id)) {
            // 更新符号表中的符号
            SymbolEntry &entry = symbolTable->getSymbol(id);
            entry.isReference = true;

            // 检查参数是否为数组
            bool isArray = (entry.dataType == PascalType::ARRAY);
            bool isMultidim = (isArray && entry.arrayDimensions.size() > 1);
            TranslatorUtils::logDebug("  Marking " + id + " as reference parameter, isArray: " +
                                      (isArray ? "true" : "false") +
                                      ", isMultidimensional: " + (isMultidim ? "true" : "false"));

            // 由于我们已经有自动添加参数的addSymbol，
            // 我们需要更新作用域的参数列表中的现有参数
            std::vector<SymbolEntry> &parameters = symbolTable->getCurrentScope().getParameters();
            for (auto &param: parameters) {
                if (param.name == id) {
                    param.isReference = true;
                    break;
                }
            }
        }
    }

    // 为引用参数在声明的类型部分添加指针(*)
    // 我们需要处理链中的多个参数
    std::stringstream ss;
    std::string baseTypeStr;
    size_t pos = params.find_first_of(" ");
    if (pos != std::string::npos) {
        baseTypeStr = params.substr(0, pos);
        std::string rest = params.substr(pos);

        // 将剩余部分分割成单独的参数声明
        std::vector<std::string> paramDecls;
        size_t start = 0;
        size_t commaPos;
        while ((commaPos = rest.find(",", start)) != std::string::npos) {
            paramDecls.push_back(rest.substr(start, commaPos - start));
            start = commaPos + 2; // 跳过", "
        }
        paramDecls.push_back(rest.substr(start));

        // 提取不带数组维度的基本类型
        std::string baseType = baseTypeStr;
        size_t bracketPos = baseType.find('[');
        if (bracketPos != std::string::npos) {
            baseType = baseType.substr(0, bracketPos);
        }

        // 检查我们是否在处理多维数组
        std::vector<std::string> dimensionSizes;
        if (isMultidimensionalArray) {
            // 提取所有维度大小，以便正确声明C数组参数
            for (const auto &dim: dimensions) {
                int size = dim.upperBound - dim.lowerBound + 1 + 1;
                dimensionSizes.push_back(std::to_string(size));
            }
        }

        // 为每个参数添加指针类型
        for (size_t i = 0; i < paramDecls.size(); ++i) {
            if (i > 0) ss << ", ";

            // 获取参数的变量名
            size_t last_space_pos = paramDecls[i].rfind(' ');
            std::string paramName;
            if (last_space_pos != std::string::npos) {
                paramName = paramDecls[i].substr(last_space_pos + 1);
            } else {
                paramName = paramDecls[i];
            }

            // 根据是否为数组参数进行处理
            if (isArray) {
                if (isMultidimensionalArray) {
                    // 对于多维数组作为参数，使用正确的C语法：
                    // 对于2D数组：type (*param)[dim2]
                    // 对于3D数组：type (*param)[dim2][dim3]
                    ss << baseType << " (*" << paramName << ")";

                    // 添加除第一维外的所有维度，在C数组参数中第一维总是省略的
                    for (size_t j = 1; j < dimensionSizes.size(); ++j) {
                        ss << "[" << dimensionSizes[j] << "]";
                    }
                } else {
                    // 对于单维数组，我们可以使用更简单的表示法
                    ss << baseType << " *" << paramName;
                }
            } else {
                // 非数组参数 - 常规指针
                ss << baseType << "* " << paramName;
            }
        }
    } else {
        // 如果找不到空格，只需将指针添加到整个字符串
        ss << params << "*";
    }

    return ss.str();
}

/**
 * 处理值参数（按值传递）
 * 在Pascal中，常规参数按值传递
 * @param context 值参数上下文
 * @return C语法中参数的字符串表示
 */
antlrcpp::Any PascalToCTranslator::visitValueParameter(PascalSParser::ValueParameterContext *context) {
    // 获取标识符
    std::vector<std::string> ids = visit(context->idList()).as<std::vector<std::string>>();

    // 参数标识符的调试输出
    std::string idListStr;
    for (const auto &id: ids) {
        if (!idListStr.empty()) idListStr += ", ";
        idListStr += id;
    }
    TranslatorUtils::logDebug("Value parameter identifiers: " + idListStr);

    // 获取类型信息
    auto typeResult = visit(context->type());

    // 初始化类型信息变量
    std::string typeStr;
    PascalType pascalType;
    PascalType elementType = PascalType::INTEGER; // 数组的默认类型
    std::vector<ArrayBounds> dimensions;

    // 基于是基本类型还是数组类型提取类型信息
    try {
        // 首先尝试提取为基本类型
        auto typePair = typeResult.as<std::pair<std::string, PascalType>>();
        typeStr = typePair.first;
        pascalType = typePair.second;
    } catch (const std::bad_cast &) {
        // 如果失败，就是数组类型
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

    // 格式化参数
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

        // 添加参数到符号表
        SymbolEntry entry;
        entry.name = ids[i];
        entry.symbolType = SymbolType::PARAMETER;
        entry.dataType = pascalType;
        entry.isReference = false;  // 默认按值传递，如果是VAR参数将被更新

        // 如果需要，存储数组特定信息
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
 * 处理子程序主体，包含声明和语句
 * @param context 子程序主体上下文
 * @return 访问者模式的标准占位符
 */
antlrcpp::Any PascalToCTranslator::visitSubprogramBody(PascalSParser::SubprogramBodyContext *context) {
    // 如果存在，处理常量声明
    if (context->constDeclarations()) {
        visit(context->constDeclarations());
    }

    // 如果存在，处理变量声明
    if (context->varDeclarations()) {
        visit(context->varDeclarations());
    }

    // 处理复合语句（函数/过程的主体）
    if (context->compoundStatement()) {
        visit(context->compoundStatement());
    }

    // 在子程序结束时退出作用域
    symbolTable->exitScope();

    return antlrcpp::Any();
}

/**
 * 处理复合语句（BEGIN ... END块）
 * @param context 复合语句上下文
 * @return 访问者模式的标准占位符
 */
antlrcpp::Any PascalToCTranslator::visitCompoundStatement(PascalSParser::CompoundStatementContext *context) {
    // 跳过BEGIN和END标记，只访问内部的语句列表
    visit(context->statementList());

    return antlrcpp::Any();
}

/**
 * 处理语句列表
 * @param context 语句列表上下文
 * @return 访问者模式的标准占位符
 */
antlrcpp::Any PascalToCTranslator::visitStatementList(PascalSParser::StatementListContext *context) {
    // 如果有任何早期语句，首先访问它们（在源码中较早出现）
    if (context->statementList()) {
        visit(context->statementList());
    }

    // 访问当前语句（在源码中较晚出现）
    visit(context->statement());

    return antlrcpp::Any();
}

/**
 * 处理单个语句（赋值、过程调用、if、for等）
 * @param context 语句上下文
 * @return 访问者模式的标准占位符
 */
antlrcpp::Any PascalToCTranslator::visitStatement(PascalSParser::StatementContext *context) {
    // 空语句
    if (!context->variable() && !context->ID() && !context->procedureCall() && !context->compoundStatement() &&
        !context->ifStatement() && !context->forStatement() && !context->readStatement() &&
        !context->whileStatement() && !context->writeStatement() && !context->breakStatement()) {
        return antlrcpp::Any();
    }

    // 向标识符赋值（过程或函数结果）
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

        // 获取当前作用域名称 - 如果我们向与当前函数同名的标识符赋值，那是一个返回值赋值
        std::string currentScopeName = symbolTable->getCurrentScope().getScopeName();

        if (currentScopeName == id) {
            // 这是一个函数结果赋值（Pascal function:=value）
            // 赋值给函数的tmp变量而不是直接使用函数名
            output << getCurrentIndentation() << id << "tmp = " << expr << ";\n";
        } else {
            // 向普通标识符赋值
            output << getCurrentIndentation() << id << " = " << expr << ";\n";
        }
    }
        // 向变量赋值（可以是数组元素或其他复杂变量）
    else if (context->variable() && context->ASSIGNOP()) {
        auto varResult = visit(context->variable());

        // 检查这是否是函数结果赋值
        try {
            if (varResult.is<std::pair<std::string, std::string>>()) {
                auto pair = varResult.as<std::pair<std::string, std::string>>();
                if (pair.first == "FUNCTION_RESULT") {
                    // 这是一个函数结果赋值（Pascal function:=value）
                    auto exprResult = visit(context->expression());
                    std::string expr = exprResult.as<std::string>();

                    // 赋值给函数的tmp变量而不是直接返回
                    output << getCurrentIndentation() << pair.second << "tmp = " << expr << ";\n";
                    return antlrcpp::Any();
                }
            }
        } catch (const std::bad_cast &e) {
            // 如果有类型转换错误，假设它是常规变量赋值
            TranslatorUtils::logError(
                    "Warning: Type conversion issue in variable assignment: " + std::string(e.what()));
        }

        // 常规变量赋值 - 尝试使用显式字符串转换
        try {
            std::string var = varResult.as<std::string>();
            auto exprResult = visit(context->expression());
            std::string expr = exprResult.as<std::string>();

            output << getCurrentIndentation() << var << " = " << expr << ";\n";
        } catch (const std::bad_cast &e) {
            // 如果转换再次失败，添加错误处理
            TranslatorUtils::logError("Error in variable assignment: " + std::string(e.what()));
        }
    }
        // 过程调用
    else if (context->procedureCall()) {
        auto result = visit(context->procedureCall());
        std::string call = result.as<std::string>();

        output << getCurrentIndentation() << call << ";\n";
    }
        // 复合语句（BEGIN ... END块）
    else if (context->compoundStatement()) {
        visit(context->compoundStatement());
    }
        // If语句
    else if (context->ifStatement()) {
        visit(context->ifStatement());
    }
        // For语句
    else if (context->forStatement()) {
        visit(context->forStatement());
    }
        // Read语句
    else if (context->readStatement()) {
        visit(context->readStatement());
    }
        // While语句
    else if (context->whileStatement()) {
        visit(context->whileStatement());
    }
        // Write语句
    else if (context->writeStatement()) {
        visit(context->writeStatement());
    }
        // Break语句
    else if (context->breakStatement()) {
        visit(context->breakStatement());
    }

    return antlrcpp::Any();
}

/**
 * 处理if语句和可选的else部分
 * @param context if语句上下文
 * @return 访问者模式的标准占位符
 */
antlrcpp::Any PascalToCTranslator::visitIfStatement(PascalSParser::IfStatementContext *context) {
    // 获取条件表达式
    auto condResult = visit(context->expression());
    std::string cond = condResult.as<std::string>();

    // 输出带有条件的if语句
    output << getCurrentIndentation() << "if (" << cond << ") {\n";
    increaseIndentation();

    // 访问if分支语句
    visit(context->statement());

    decreaseIndentation();
    output << getCurrentIndentation() << "}";

    // 如果存在，访问else部分
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
 * 处理for语句（带计数器的循环）
 * @param context for语句上下文
 * @return 访问者模式的标准占位符
 */
antlrcpp::Any PascalToCTranslator::visitForStatement(PascalSParser::ForStatementContext *context) {
    // 获取循环计数器变量
    std::string id = TranslatorUtils::toCIdentifier(context->ID()->getText());

    // 获取初始值
    auto initResult = visit(context->expression(0));
    std::string init = initResult.as<std::string>();

    // 获取最终值
    auto finalResult = visit(context->expression(1));
    std::string final = finalResult.as<std::string>();

    // 输出C风格的for循环（Pascal的for循环总是以1递增）
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
 * 处理read语句（输入）
 * 翻译为C中的scanf调用
 * @param context read语句上下文
 * @return 访问者模式的标准占位符
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
 * 处理while语句（带条件的循环）
 * @param context while语句上下文
 * @return 访问者模式的标准占位符
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
 * 处理write语句（输出）
 * 翻译为C中的printf调用
 * @param context write语句上下文
 * @return 访问者模式的标准占位符
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

/**
 * 处理break语句
 * @param context break语句上下文
 * @return 访问者模式的标准占位符
 */
antlrcpp::Any PascalToCTranslator::visitBreakStatement(PascalSParser::BreakStatementContext *context) {
    output << getCurrentIndentation() << "break;\n";
    return antlrcpp::Any();
}


/**
 * 处理用于输入/输出或其他操作的变量列表
 * @param context 变量列表上下文
 * @return C语法中变量字符串表示的向量
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
 * 处理变量标识符，可以是简单变量或数组元素
 * 处理特殊情况，如函数结果变量和引用参数
 * @param context 变量上下文
 * @return C语法中变量的字符串表示或函数结果的特殊标记
 */
antlrcpp::Any PascalToCTranslator::visitVariable(PascalSParser::VariableContext *context) {
    std::string id = TranslatorUtils::toCIdentifier(context->ID()->getText());

    // 检查变量是否是当前作用域中的函数名
    std::string currentScopeName = symbolTable->getCurrentScope().getScopeName();

    // 检查我们是否在一个函数中，且变量名与函数名匹配
    if (id == currentScopeName) {
        // 对于函数返回值，返回一个特殊的对来表示这一点
        // 我们将在visitStatement中处理这个情况
        std::pair<std::string, std::string> resultPair("FUNCTION_RESULT", id);
        return resultPair;
    }

    // 检查变量是否为引用参数（不是局部变量）
    bool isReferenceParam = false;
    bool isArray = false;

    if (symbolTable->hasSymbol(id)) {
        const SymbolEntry &entry = symbolTable->getSymbol(id);
        // 仅当它实际上是一个参数且标记为引用时才视为引用参数
        isReferenceParam = entry.isReference && entry.symbolType == SymbolType::PARAMETER;
        isArray = (entry.dataType == PascalType::ARRAY);
    } else {
        std::cout << "----------------------------------------------------------" << std::endl;
        std::cout << "Error: Undefined variable " << id << " in " << symbolTable->getCurrentScope().getScopeName()
                  << ", line :" << context->start->getLine() << std::endl;
        std::cout << "----------------------------------------------------------" << std::endl;
    }

    // 检查是否是数组访问
    std::string result;
    if (context->idVarPart()) {
        auto partResult = visit(context->idVarPart());
        std::string indices = partResult.as<std::string>();

        // 只有当引用参数（不是局部变量）在被传递到的函数内部使用时才解引用
        if (isReferenceParam && !isArray && symbolTable->hasSymbolInCurrentScope(id)) {
            // 对于非数组引用参数，在访问时需要解引用
            result = "(*" + id + ")" + indices;
        } else {
            result = id + indices;
        }
    } else {
        // 不是数组访问
        if (isReferenceParam && !isArray && symbolTable->hasSymbolInCurrentScope(id)) {
            // 对于非数组引用参数，需要解引用
            result = "(*" + id + ")";
        } else {
            result = id;
        }
    }

    return result;
}

/**
 * 处理变量的数组索引表达式
 * @param context ID变量部分上下文（数组索引）
 * @return C语法中数组索引的字符串表示
 */
antlrcpp::Any PascalToCTranslator::visitIdVarPart(PascalSParser::IdVarPartContext *context) {
    // 空数组访问
    if (!context->expressionList()) {
        return antlrcpp::Any(std::string(""));
    }

    // 从表达式列表获取数组索引
    auto result = visit(context->expressionList());
    std::vector<std::string> indices = result.as<std::vector<std::string>>();

    // 使用C风格的索引格式化数组访问
    std::stringstream ss;
    for (const auto &index: indices) {
        ss << "[" << index << "]";
    }

    return ss.str();
}

/**
 * 处理过程调用语句
 * @param context 过程调用上下文
 * @return C语法中过程调用的字符串表示
 */
antlrcpp::Any PascalToCTranslator::visitProcedureCall(PascalSParser::ProcedureCallContext *context) {
    std::string id = TranslatorUtils::toCIdentifier(context->ID()->getText());

    // 检查是否是带参数的过程调用
    if (context->expressionList()) {
        auto result = visit(context->expressionList());
        std::vector<std::string> args = result.as<std::vector<std::string>>();

        // 格式化带参数的过程调用
        std::stringstream ss;
        ss << id << "(";

        // 获取过程定义（如果可用）以检查引用参数
        bool hasProcedureSymbol = symbolTable->hasSymbol(id);
        std::vector<SymbolEntry> parameters;

        if (hasProcedureSymbol) {
            // 获取此过程的参数
            if (symbolTable->hasScope(id)) {
                const ScopeEntry &scope = symbolTable->getScope(id);
                parameters = scope.getParameters();

                // 调试输出以验证参数
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

            // 检查此参数是否应通过引用传递
            bool isReferenceParam = false;
            bool isArrayType = false;
            bool isMultidimensionalArray = false;

            // 修复参数排序问题：作用域参数列表中的参数
            // 与它们在Pascal源代码中出现的顺序相比是相反的。
            // 因此需要反转索引以匹配正确的参数。
            if (parameters.size() == args.size()) {
                // 计算正确的参数索引（参数顺序相反）
                size_t paramIndex = parameters.size() - 1 - i;

                isReferenceParam = parameters[paramIndex].isReference;

                // 调试输出以验证引用参数检测
                TranslatorUtils::logDebug("  Checking arg " + std::to_string(i) + ": " + args[i] +
                                          ", isRef: " + (isReferenceParam ? "true" : "false") +
                                          ", paramIndex: " + std::to_string(paramIndex));

                // 检查参数是否为数组
                std::string argBase = args[i];
                size_t bracketPos = argBase.find('[');
                size_t parenPos = argBase.find('(');

                // 如果有数组索引或函数调用，提取基本变量名
                if (bracketPos != std::string::npos) {
                    argBase = argBase.substr(0, bracketPos);
                } else if (parenPos != std::string::npos) {
                    argBase = argBase.substr(0, parenPos);
                }

                // 检查参数是否为数组以及是否为多维数组
                if (symbolTable->hasSymbol(argBase)) {
                    const SymbolEntry &argEntry = symbolTable->getSymbol(argBase);
                    isArrayType = (argEntry.dataType == PascalType::ARRAY);
                    isMultidimensionalArray = (isArrayType && argEntry.arrayDimensions.size() > 1);

                    TranslatorUtils::logDebug("    Arg " + argBase + " is array: " + (isArrayType ? "true" : "false") +
                                              ", is multidimensional: " + (isMultidimensionalArray ? "true" : "false") +
                                              ", dimensions: " + std::to_string(argEntry.arrayDimensions.size()));
                }

                // 区别处理常规数组和多维数组
                if (isArrayType) {
                    // 如果是数组索引操作，我们需要检查是否传递的是数组的一部分
                    if (args[i].find('[') != std::string::npos) {
                        // 计算原始数组与数组访问中的维度数
                        int accessedDimensions = 0;
                        size_t pos = 0;
                        while ((pos = args[i].find('[', pos)) != std::string::npos) {
                            accessedDimensions++;
                            pos++;
                        }

                        bool isFullyIndexed = false;
                        if (symbolTable->hasSymbol(argBase)) {
                            const SymbolEntry &argEntry = symbolTable->getSymbol(argBase);
                            isFullyIndexed = (accessedDimensions >= argEntry.arrayDimensions.size());
                        }

                        // 如果我们传递的是一部分或参数需要一个数组
                        if (!isFullyIndexed) {
                            // 直接传递数组元素（它是多维数组的一部分）
                            ss << args[i];
                        } else {
                            // 传递完全索引的元素（如果是VAR参数可能需要使用&）
                            if (isReferenceParam) {
                                ss << "(&(" << args[i] << "))";
                            } else {
                                ss << args[i];
                            }
                        }
                    } else {
                        // 传递整个数组 - 不需要使用&，因为数组默认按引用传递
                        ss << args[i];
                    }
                }
                    // 对于通过引用传递的非数组参数
                else if (isReferenceParam) {
                    ss << "(&(" << args[i] << "))";
                    TranslatorUtils::logDebug("  Adding & to " + args[i]);
                } else {
                    // 常规值参数
                    ss << args[i];
                }
                std::cout << "arg :" << args[i] << std::endl;
            } else {
                // 如果我们无法匹配参数，则按原样传递参数
                ss << args[i];
                std::cout << "can't match parameters, arg :" << args[i] << std::endl;
            }
        }

        ss << ")";

        return ss.str();
    }

    // 无参数的过程调用
    return id + "()";
}

/**
 * 处理if语句的else部分
 * @param context else部分上下文
 * @return "else"的字符串表示（为了访问者模式的一致性）
 */
antlrcpp::Any PascalToCTranslator::visitElsePart(PascalSParser::ElsePartContext *context) {
    // 空的else部分
    if (!context->statement()) {
        return antlrcpp::Any(std::string(""));
    }

    // 访问else语句
    visit(context->statement());

    return antlrcpp::Any(std::string("else"));
}

/**
 * 处理函数/过程参数或数组索引的表达式列表
 * @param context 表达式列表上下文
 * @return C语法中表达式的字符串表示向量
 */
antlrcpp::Any PascalToCTranslator::visitExpressionList(PascalSParser::ExpressionListContext *context) {
    std::vector<std::string> exprs;

    try {
        // 在Pascal中，列表中的表达式从左到右出现在源代码中，
        // 但ANTLR解析器处理它们的方式是，最右边的表达式成为
        // 当前节点，而较早的表达式在嵌套的expressionList中。

        // 首先，处理嵌套expressionList中更早出现的表达式
        if (context->expressionList()) {
            auto earlierExprs = visit(context->expressionList());
            exprs = earlierExprs.as<std::vector<std::string>>();
        }

        // 然后添加当前表达式，它在源代码中出现较晚
        auto result = visit(context->expression());
        exprs.push_back(result.as<std::string>());
    } catch (const std::bad_cast &e) {
        TranslatorUtils::logError("Type conversion error in expression list: " + std::string(e.what()));
    }

    return exprs;
}

/**
 * 处理可以是简单表达式或关系表达式的表达式
 * @param context 表达式上下文
 * @return C语法中表达式的字符串表示
 */
antlrcpp::Any PascalToCTranslator::visitExpression(PascalSParser::ExpressionContext *context) {
    // 简单表达式（没有关系运算符）
    if (!context->relop()) {
        return visit(context->simpleExpression(0));
    }

    // 关系表达式（带比较运算符）
    auto leftResult = visit(context->simpleExpression(0));
    std::string left = leftResult.as<std::string>();

    auto relopResult = visit(context->relop());
    std::string op = relopResult.as<std::string>();

    auto rightResult = visit(context->simpleExpression(1));
    std::string right = rightResult.as<std::string>();

    // 检查左操作数或右操作数是否为应使用其tmp变量的函数名
    std::string currentScopeName = symbolTable->getCurrentScope().getScopeName();
    if (left == currentScopeName) {
        left = left + "tmp";
    }
    if (right == currentScopeName) {
        right = right + "tmp";
    }

    // 将比较用括号括起来以确保安全
    std::string result = "(" + left + " " + op + " " + right + ")";
    return antlrcpp::Any(result);
}

/**
 * 处理可以是项或加法表达式的简单表达式
 * @param context 简单表达式上下文
 * @return C语法中简单表达式的字符串表示
 */
antlrcpp::Any PascalToCTranslator::visitSimpleExpression(PascalSParser::SimpleExpressionContext *context) {
    // 单个项（没有加法运算符）
    if (!context->addop()) {
        return visit(context->term());
    }

    // 带加法运算符的表达式（+ - OR）
    auto leftResult = visit(context->simpleExpression());
    std::string left = leftResult.as<std::string>();

    auto addopResult = visit(context->addop());
    std::string op = addopResult.as<std::string>();

    auto rightResult = visit(context->term());
    std::string right = rightResult.as<std::string>();

    // 检查左操作数或右操作数是否为应使用其tmp变量的函数名
    std::string currentScopeName = symbolTable->getCurrentScope().getScopeName();
    if (left == currentScopeName) {
        left = left + "tmp";
    }
    if (right == currentScopeName) {
        right = right + "tmp";
    }

    // 将表达式用括号括起来以确保正确的优先级
    return antlrcpp::Any(std::string("(") + left + " " + op + " " + right + ")");
}

/**
 * 处理可以是因子或乘法表达式的项
 * @param context 项上下文
 * @return C语法中项的字符串表示
 */
antlrcpp::Any PascalToCTranslator::visitTerm(PascalSParser::TermContext *context) {
    // 单个因子（没有乘法运算符）
    if (!context->mulop()) {
        return visit(context->factor());
    }

    // 带乘法运算符的项（* / DIV MOD AND）
    auto leftResult = visit(context->term());
    std::string left = leftResult.as<std::string>();

    auto mulopResult = visit(context->mulop());
    std::string op = mulopResult.as<std::string>();

    auto rightResult = visit(context->factor());
    std::string right = rightResult.as<std::string>();

    // 检查左操作数或右操作数是否为应使用其tmp变量的函数名
    std::string currentScopeName = symbolTable->getCurrentScope().getScopeName();
    if (left == currentScopeName) {
        left = left + "tmp";
    }
    if (right == currentScopeName) {
        right = right + "tmp";
    }

    // 将表达式用括号括起来以确保正确的优先级
    return antlrcpp::Any(std::string("(") + left + " " + op + " " + right + ")");
}

/**
 * 处理因子，可以是常量、变量、表达式、函数调用或一元操作
 * @param context 因子上下文
 * @return C语法中因子的字符串表示
 */
antlrcpp::Any PascalToCTranslator::visitFactor(PascalSParser::FactorContext *context) {
    // 数字字面量
    if (context->num()) {
        return visit(context->num());
    }
        // 变量（可以是简单变量或数组元素）
    else if (context->variable()) {
        return visit(context->variable());
    }
        // 带括号的表达式
    else if (context->LPAREN() && context->expression()) {
        auto result = visit(context->expression());
        std::string expr = result.as<std::string>();

        return antlrcpp::Any(std::string("(") + expr + ")");
    }
        // 函数调用
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

        // 格式化函数调用
        std::stringstream ss;
        ss << id << "(";

        // 获取函数定义（如果可用）以检查引用参数
        bool hasFunctionSymbol = symbolTable->hasSymbol(id);
        std::vector<SymbolEntry> parameters;

        if (hasFunctionSymbol) {
            // 获取此函数的参数
            if (symbolTable->hasScope(id)) {
                const ScopeEntry &scope = symbolTable->getScope(id);
                parameters = scope.getParameters();

                // 调试输出以验证参数
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

            // 检查此参数是否应通过引用传递
            bool isReferenceParam = false;
            bool isArrayType = false;
            bool isMultidimensionalArray = false;

            // 修复参数排序问题：作用域参数列表中的参数
            // 与它们在Pascal源代码中出现的顺序相比是相反的。
            // 我们需要反转索引以匹配正确的参数。
            if (parameters.size() == args.size()) {
                // 计算正确的参数索引（参数顺序相反）
                size_t paramIndex = parameters.size() - 1 - i;

                isReferenceParam = parameters[paramIndex].isReference;

                // 调试输出以验证引用参数检测
                TranslatorUtils::logDebug("  Checking arg " + std::to_string(i) + ": " + args[i] +
                                          ", isRef: " + (isReferenceParam ? "true" : "false") +
                                          ", paramIndex: " + std::to_string(paramIndex));

                // 检查参数是否为数组
                std::string argBase = args[i];
                size_t bracketPos = argBase.find('[');
                size_t parenPos = argBase.find('(');

                // 如果有数组索引或函数调用，提取基本变量名
                if (bracketPos != std::string::npos) {
                    argBase = argBase.substr(0, bracketPos);
                } else if (parenPos != std::string::npos) {
                    argBase = argBase.substr(0, parenPos);
                }

                // 检查参数是否为数组以及是否为多维数组
                if (symbolTable->hasSymbol(argBase)) {
                    const SymbolEntry &argEntry = symbolTable->getSymbol(argBase);
                    isArrayType = (argEntry.dataType == PascalType::ARRAY);
                    isMultidimensionalArray = (isArrayType && argEntry.arrayDimensions.size() > 1);

                    TranslatorUtils::logDebug("    Arg " + argBase + " is array: " + (isArrayType ? "true" : "false") +
                                              ", is multidimensional: " + (isMultidimensionalArray ? "true" : "false") +
                                              ", dimensions: " + std::to_string(argEntry.arrayDimensions.size()));
                }

                // 区别处理常规数组和多维数组
                if (isArrayType) {
                    // 如果是数组索引操作，我们需要检查是否传递的是数组的一部分
                    if (args[i].find('[') != std::string::npos) {
                        // 计算原始数组与数组访问中的维度数
                        int accessedDimensions = 0;
                        size_t pos = 0;
                        while ((pos = args[i].find('[', pos)) != std::string::npos) {
                            accessedDimensions++;
                            pos++;
                        }

                        bool isFullyIndexed = false;
                        if (symbolTable->hasSymbol(argBase)) {
                            const SymbolEntry &argEntry = symbolTable->getSymbol(argBase);
                            isFullyIndexed = (accessedDimensions >= argEntry.arrayDimensions.size());
                        }

                        // 如果我们传递的是一部分或参数需要一个数组
                        if (!isFullyIndexed) {
                            // 直接传递数组元素（它是多维数组的一部分）
                            ss << args[i];
                        } else {
                            // 传递完全索引的元素（如果是VAR参数可能需要使用&）
                            if (isReferenceParam) {
                                ss << "(&(" << args[i] << "))";
                            } else {
                                ss << args[i];
                            }
                        }
                    } else {
                        // 传递整个数组 - 不需要使用&，因为数组默认按引用传递
                        ss << args[i];
                    }
                }
                    // 对于通过引用传递的非数组参数
                else if (isReferenceParam) {
                    ss << "(&(" << args[i] << "))";
                    TranslatorUtils::logDebug("  Adding & to " + args[i]);
                } else {
                    // 常规值参数
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
        // 不带括号的函数调用（适用于没有参数的Pascal函数）
    else if (context->ID() && !context->expressionList()) {
        std::string id = TranslatorUtils::toCIdentifier(context->ID()->getText());

        if (!symbolTable->hasSymbol(id)) {
            std::cout << "----------------------------------------------------------" << std::endl;
            std::cout << "Error: Undefined variable " << id << " in "
                      << symbolTable->getCurrentScope().getScopeName() << ", line :" << context->start->getLine()
                      << std::endl;
            std::cout << "----------------------------------------------------------" << std::endl;
        }

        // 检查此ID是否是符号表中的函数
        if (symbolTable->hasSymbol(id)) {
            const SymbolEntry &entry = symbolTable->getSymbol(id);

            // 如果它是一个函数，并且它有一个作用域（意味着它是一个函数声明，而不是变量）
            if (entry.symbolType == SymbolType::FUNCTION && symbolTable->hasScope(id)) {
                const ScopeEntry &scope = symbolTable->getScope(id);
                // 检查函数是否没有参数
                if (scope.getParameters().empty()) {
                    // 这是一个不带括号的无参数函数调用
                    // 在C中，我们需要添加括号
                    return id + "()";
                }
            } else if (entry.symbolType == SymbolType::PARAMETER) {
                if (entry.isReference && symbolTable->hasSymbolInCurrentScope(id)) {
                    // 对于非数组引用参数，在访问时需要解引用
                    return "(*" + id + ")";
                }
            }

            // 特殊情况：如果我们在一个函数中，并且我们引用的是函数自身的名称
            // 作为变量（在Pascal递归函数中很典型）
            if (id == symbolTable->getCurrentScope().getScopeName()) {
                // 这是访问我们自己函数的返回值
                return id + "tmp";
            }
        }

        // 如果未被识别为无参数函数，则视为常规变量
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
        // 一元负号操作
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
        // 一元正号操作
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
        // 字符串字面量
    else if (context->STRING()) {
        return context->STRING()->getText();
    }
        // 字符字面量
    else if (context->LETTER()) {
        return antlrcpp::Any(
                std::string((TranslatorUtils::toCIdentifier(context->LETTER()->getText()) == "true") ? "1" : "0"));
    }

    return antlrcpp::Any(std::string(""));
}

/**
 * 处理数字字面量
 * @param context 数字上下文
 * @return 数字的字符串表示
 */
antlrcpp::Any PascalToCTranslator::visitNum(PascalSParser::NumContext *context) {
    return context->NUM()->getText();
}

/**
 * 处理关系运算符（==, !=, <, <=, >, >=）
 * @param context 关系运算符上下文
 * @return C语法中运算符的字符串表示
 */
antlrcpp::Any PascalToCTranslator::visitRelop(PascalSParser::RelopContext *context) {
    if (context->EQUAL()) {
        return antlrcpp::Any(std::string("=="));  // Pascal的=在C中变为==
    } else if (context->NOTEQUAL()) {
        return antlrcpp::Any(std::string("!="));  // Pascal的<>在C中变为!=
    } else if (context->LT()) {
        return antlrcpp::Any(std::string("<"));   // Pascal的<在C中保持不变
    } else if (context->LE()) {
        return antlrcpp::Any(std::string("<="));  // Pascal的<=在C中保持不变
    } else if (context->GT()) {
        return antlrcpp::Any(std::string(">"));   // Pascal的>在C中保持不变
    } else if (context->GE()) {
        return antlrcpp::Any(std::string(">="));  // Pascal的>=在C中保持不变
    }

    return antlrcpp::Any(std::string(""));
}

/**
 * 处理加法运算符（+, -, OR）
 * @param context 加法运算符上下文
 * @return C语法中运算符的字符串表示
 */
antlrcpp::Any PascalToCTranslator::visitAddop(PascalSParser::AddopContext *context) {
    if (context->PLUS()) {
        return antlrcpp::Any(std::string("+"));   // Pascal的+在C中保持不变
    } else if (context->MINUS()) {
        return antlrcpp::Any(std::string("-"));   // Pascal的-在C中保持不变
    } else if (context->OR()) {
        return antlrcpp::Any(std::string("||"));  // Pascal的OR在C中变为||
    }

    return antlrcpp::Any(std::string(""));
}

/**
 * 处理乘法运算符（*, /, DIV, MOD, AND）
 * @param context 乘法运算符上下文
 * @return C语法中运算符的字符串表示
 */
antlrcpp::Any PascalToCTranslator::visitMulop(PascalSParser::MulopContext *context) {
    if (context->STAR()) {
        return antlrcpp::Any(std::string("*"));   // Pascal的*在C中保持不变
    } else if (context->SLASH()) {
        return antlrcpp::Any(std::string("/"));   // Pascal的/在C中保持不变（浮点除法）
    } else if (context->DIV()) {
        return antlrcpp::Any(std::string("/"));   // Pascal的DIV在C中变为/（整数除法）
    } else if (context->MOD()) {
        return antlrcpp::Any(std::string("%"));   // Pascal的MOD在C中变为%
    } else if (context->AND()) {
        return antlrcpp::Any(std::string("&&"));  // Pascal的AND在C中变为&&
    }

    return antlrcpp::Any(std::string(""));
}