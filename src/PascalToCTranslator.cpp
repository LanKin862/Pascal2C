#include "../include/PascalToCTranslator.h"

#include <antlr4-runtime.h>

#include <fstream>
#include <regex>

#include "../antlr/PascalSLexer.h"
#include "../antlr/PascalSParser.h"
#include "../include/TranslatorUtils.h"
#include "../include/ErrorDealer.h"

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
 * @return 包含翻译后C代码的字符串
 */
std::string PascalToCTranslator::translate(const std::string &inputFile) {
    // 清除状态，准备新的翻译
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
 * 增加缩进级别（4个空格）
 */
void PascalToCTranslator::increaseIndentation() {
    indentation += "    ";
}

/**
 * 减少缩进级别（4个空格）
 * 确保缩进不会变为负数
 */
void PascalToCTranslator::decreaseIndentation() {
    if (!indentation.empty()) {
        indentation.resize(indentation.size() - 4);
    }
}

/**
 * 返回当前缩进字符串
 * @return 当前缩进的空格字符串
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
 * 处理program节点，它是解析树的根
 * 生成Pascal程序所需的标准包含和辅助函数
 * @param context 解析器中的program上下文
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
 * 处理程序结构，包括程序头和程序体
 * @param context 解析器中的程序结构上下文
 * @return 访问者模式的标准占位符
 */
antlrcpp::Any PascalToCTranslator::visitProgramStruct(PascalSParser::ProgramStructContext *context) {
    // 访问程序头（名称和参数）
    visit(context->programHead());

    // 访问程序体（声明和语句）
    visit(context->programBody());

    return antlrcpp::Any();
}

/**
 * 处理程序头，包含程序名称
 * @param context 解析器中的程序头上下文
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
 * 处理程序体，包含声明和复合语句
 * @param context 解析器中的程序体上下文
 * @return 访问者模式的标准占位符
 */
antlrcpp::Any PascalToCTranslator::visitProgramBody(PascalSParser::ProgramBodyContext *context) {
    // 处理常量声明（如果存在）
    if (context->constDeclarations()) {
        visit(context->constDeclarations());
    }

    // 处理变量声明（如果存在）
    if (context->varDeclarations()) {
        visit(context->varDeclarations());
    }

    // 首先为所有子程序创建前向声明，以处理函数引用
    if (context->subprogramDeclarations()) {
        // 创建一个临时字符串流来收集前向声明
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

    // 处理子程序（函数/过程）声明（如果存在）
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
 * 为所有函数和过程生成前向声明的辅助方法
 * 这对于处理函数引用和维护正确的参数类型是必要的
 * @param context 子程序声明上下文
 */
void PascalToCTranslator::generateForwardDeclarations(PascalSParser::SubprogramDeclarationsContext *context) {
    if (!context) return;

    // 先处理任何嵌套声明（源代码中较早的部分）
    if (context->subprogramDeclarations()) {
        generateForwardDeclarations(context->subprogramDeclarations());
    }
    // 处理当前子程序（源代码中较晚的部分）
    if (context->subprogram()) {
        PascalSParser::SubprogramHeadContext* headContext = context->subprogram()->subprogramHead();
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
            std::cout << "已生成" << name << "的前向声明\n";
        }
    }
}

/**
 * 处理标识符列表，用于变量和参数声明
 * @param context 解析器中的标识符列表上下文
 * @return C兼容标识符字符串的向量
 */
antlrcpp::Any PascalToCTranslator::visitIdList(PascalSParser::IdListContext *context) {
    std::vector<std::string> ids;

    // 收集所有标识符并将它们转换为C兼容名称
    for (auto id : context->ID()) {
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

    output << "// 常量\n";

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

    // 输出为C预处理器define
    output << "#define " << entry.name << " " << entry.value << "\n";

    // 处理额外的常量声明（如果有）（递归）
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

    output << "// 变量\n";

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

    // 初始化类型信息的变量
    std::string typeStr;
    PascalType pascalType;
    PascalType elementType = PascalType::INTEGER; // 数组的默认元素类型
    std::vector<ArrayBounds> dimensions;

    // 根据是数组类型还是基本类型提取类型信息
    try {
        // 首先尝试提取为基本类型
        auto typePair = typeResult.as<std::pair<std::string, PascalType>>();
        typeStr = typePair.first;
        pascalType = typePair.second;
    } catch (const std::bad_cast&) {
        // 如果不是基本类型，则是数组类型
        try {
            auto arrayTypeInfo = typeResult.as<std::tuple<std::string, PascalType, PascalType, std::vector<ArrayBounds>>>();
            typeStr = std::get<0>(arrayTypeInfo);
            pascalType = std::get<1>(arrayTypeInfo);
            elementType = std::get<2>(arrayTypeInfo);
            dimensions = std::get<3>(arrayTypeInfo);

            for (auto &bounds : dimensions) {
                bounds.lowerBound--;
            }
        } catch (const std::bad_cast& e) {
            throw TranslatorException("类型信息提取失败: " + std::string(e.what()));
        }
    }

    // 为每个标识符输出变量声明
    for (auto &id : ids) {
        // 处理带有数组维度的数组类型
        std::regex pattern("\\[.*\\]");
        std::smatch matches;
        if (std::regex_search(typeStr, matches, pattern)) {
            // 对于数组类型，在标识符后放置维度
            std::string tmpId = id + std::string(matches[0]);
            std::string tmpTypeStr = std::regex_replace(typeStr, pattern, "");
            output << tmpTypeStr << " " << tmpId;

            // 对于多维数组，添加初始化代码以将所有元素清零
            if (pascalType == PascalType::ARRAY && dimensions.size() > 1) {
                output << " = {0}";  // C99及更高版本支持此语法进行零初始化
            }
        } else {
            // 对于基本类型，使用标准格式
            output << typeStr << " " << id;
        }

        // 仅为非数组类型添加初始化（数组初始化较复杂）
        if (pascalType != PascalType::ARRAY) {
            // 根据类型初始化默认值
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
            output << " = {0}";  // C99及更高版本支持此语法进行零初始化
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

    // 处理额外的变量声明（如果有）（递归）
    if (context->varDeclaration()) {
        visit(context->varDeclaration());
    }

    return antlrcpp::Any();
}

/**
 * 处理类型声明，包括基本类型和数组
 * @param context 类型上下文
 * @return 类型信息，对于基本类型是一对，对于数组类型是一个元组
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

        // 使用类型转换器将其转换为C数组类型
        std::string arrayTypeStr = typeConverter->convertArrayType(elementType, dimensions);

        // 返回数组类型、元素类型和维度作为元组
        return std::make_tuple(arrayTypeStr, PascalType::ARRAY, elementType, dimensions);
    }

    throw TranslatorException("未知类型");
}

/**
 * 处理基本类型关键字（INTEGER, REAL, BOOLEAN, CHAR）
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

    throw TranslatorException("未知基本类型");
}

/**
 * 处理数组索引范围声明（如1..10, 0..9）
 * @param context 包含范围边界的period上下文
 * @return 具有上下边界的ArrayBounds结构向量
 */
antlrcpp::Any PascalToCTranslator::visitPeriod(PascalSParser::PeriodContext *context) {
    std::vector<ArrayBounds> dimensions;
    std::vector<std::pair<std::string, std::string>> numStrings;
    std::string periodStr = context->getText();

    // 提取所有由DOTDOT（..）分隔的数字对
    std::regex pattern(R"((\d+(\.\d+)?)\.\.(\d+(\.\d+)?))");  // 匹配 "数字..数字"
    std::smatch matches;

    auto begin = periodStr.cbegin();
    auto end = periodStr.cend();

    while (std::regex_search(begin, end, matches, pattern)) {
        numStrings.push_back(std::make_pair(matches[1].str(), matches[3].str()));  // 下界（如 "1"）
        begin = matches[0].second;           // 继续匹配剩余部分
    }
    // 将边界转换为整数并存储在ArrayBounds结构中
    for (int i = 0; i < numStrings.size(); i++) {
        ArrayBounds bounds;
        bounds.lowerBound = std::stoi(numStrings[i].first);
        bounds.upperBound = std::stoi(numStrings[i].second);
        std::smatch tmpMatches;
        std::regex tmpPattern(R"(\.)");
        if (std::regex_search(numStrings[i].first, tmpMatches, tmpPattern) || std::regex_search(numStrings[i].second, tmpMatches, tmpPattern)) {
            auto *errorContext = new ErrorContext<PascalSParser::PeriodContext>();
            errorContext->context = context;
            errorContext->ss = &(output << getCurrentIndentation());

            InvalidArrayIndexStrategy(errorContext);
        }
        dimensions.push_back(bounds);
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

    // 首先处理当前子程序声明，它在源代码中较早出现
    if (context->subprogramDeclarations()) {
        visit(context->subprogramDeclarations());
    }

    // 然后处理在源代码中较晚出现的额外子程序
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
    // 访问子程序头以生成函数签名
    visit(context->subprogramHead());

    // 添加函数体的开始花括号
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

        // 同时将临时变量名存储在符号表中，以便正确引用
        SymbolEntry tmpEntry;
        tmpEntry.name = funcNameTmp;
        tmpEntry.symbolType = SymbolType::VARIABLE;
        tmpEntry.dataType = returnType;
        symbolTable->addSymbol(tmpEntry);
    }

    // 访问子程序体以生成函数实现
    visit(context->subprogramBody());

    // 对于函数，在结尾添加return语句（如果还没有）
    if (context->subprogramHead()->FUNCTION()) {
        std::string funcName = TranslatorUtils::toCIdentifier(context->subprogramHead()->ID()->getText());
        std::string funcNameTmp = funcName + "tmp";
        output << getCurrentIndentation() << "return " << funcNameTmp << ";\n";
    }

    // 添加结束花括号和额外的换行符
    decreaseIndentation();
    output << "}\n\n";

    return antlrcpp::Any();
}

/**
 * 处理子程序头（函数或过程声明）
 * @param context 子程序头上下文
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

    // 在进入其作用域之前，将函数/过程添加到符号表
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

    // 在C中，数组参数需要正确的指针表示法
    // 对于数组维度，函数参数中的第一个维度始终为空
    std::regex arrayPattern("\\[(\\d+)\\]");
    std::regex multiDimPattern("\\[(\\d+)\\](\\[\\d+\\])+");

    // 首先找到所有多维数组并正确转换它们
    std::smatch matches;
    std::string processedParams = params;
    std::string temp = processedParams;

    while (std::regex_search(temp, matches, multiDimPattern)) {
        std::string fullMatch = matches[0];

        // 提取位置并用正确的C数组表示法替换
        // 在C函数参数中，第一个维度始终为空：int[][10]
        size_t pos = processedParams.find(fullMatch);
        if (pos != std::string::npos) {
            std::string replacement = "[]" + fullMatch.substr(fullMatch.find("]") + 1);
            processedParams.replace(pos, fullMatch.length(), replacement);
        }

        // 从当前匹配之后继续搜索
        temp = matches.suffix().str();
    }

    output << processedParams;

    return antlrcpp::Any();
}

/**
 * 处理函数和过程的形式参数声明
 * @param context 形式参数上下文
 * @return 以C语法表示的参数列表字符串
 */
antlrcpp::Any PascalToCTranslator::visitFormalParameter(PascalSParser::FormalParameterContext *context) {
    // 默认空参数列表
    if (!context->parameterList()) {
        return antlrcpp::Any(std::string("()"));
    }

    // 访问参数列表生成参数声明
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

    TranslatorUtils::logDebug("处理参数: " + param);

    // 检查是否有任何嵌套参数（它们在Pascal代码中较早出现）
    if (context->parameterList()) {
        auto moreParamsResult = visit(context->parameterList());
        std::string moreParamsStr = moreParamsResult.as<std::string>();

        TranslatorUtils::logDebug("更早的参数: " + moreParamsStr);

        // 将较早的参数首先放在列表中
        if (!moreParamsStr.empty()) {
            if (param.empty()) paramList = moreParamsStr;
            else paramList = moreParamsStr + ", " + param;
            TranslatorUtils::logDebug("组合后的参数: " + paramList);
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
 * 处理单个参数，可以是传值参数或传引用参数（VAR）
 * @param context 参数上下文
 * @return 以C语法表示的参数字符串
 */
antlrcpp::Any PascalToCTranslator::visitParameter(PascalSParser::ParameterContext *context) {
    if (context->varParameter()) {
        TranslatorUtils::logDebug("处理VAR参数");
        return visit(context->varParameter());
    } else if (context->valueParameter()) {
        TranslatorUtils::logDebug("处理值参数");
        return visit(context->valueParameter());
    }

    return antlrcpp::Any(std::string(""));
}

/**
 * 处理VAR参数（传引用）
 * 在Pascal中，VAR参数是通过引用传递的
 * 在C中，这是通过指针实现的
 * @param context VAR参数上下文
 * @return 以C语法的指针表示法表示的参数字符串
 */
antlrcpp::Any PascalToCTranslator::visitVarParameter(PascalSParser::VarParameterContext *context) {
    // 获取值参数字符串表示
    auto result = visit(context->valueParameter());
    std::string params = result.as<std::string>();

    // 从上下文中获取标识符，将它们标记为符号表中的引用参数
    auto idListResult = visit(context->valueParameter()->idList());
    std::vector<std::string> ids = idListResult.as<std::vector<std::string>>();

    // 调试输出以验证参数标识符
    std::string idListStr;
    for (const auto& id : ids) {
        if (!idListStr.empty()) idListStr += ", ";
        idListStr += id;
    }
    TranslatorUtils::logDebug("VAR参数标识符: " + idListStr);

    // 同时获取类型信息以检查数组类型
    auto typeResult = visit(context->valueParameter()->type());

    // 初始化类型信息变量
    std::string typeStr;
    PascalType pascalType;
    PascalType elementType = PascalType::INTEGER; // 数组的默认值
    std::vector<ArrayBounds> dimensions;
    bool isArray = false;
    bool isMultidimensionalArray = false;

    // 根据是否为数组或基本类型提取类型信息
    try {
        // 首先尝试提取为基本类型
        auto typePair = typeResult.as<std::pair<std::string, PascalType>>();
        typeStr = typePair.first;
        pascalType = typePair.second;
        isArray = (pascalType == PascalType::ARRAY);
    } catch (const std::bad_cast&) {
        // 如果失败，则是数组类型
        try {
            auto arrayTypeInfo = typeResult.as<std::tuple<std::string, PascalType, PascalType, std::vector<ArrayBounds>>>();
            typeStr = std::get<0>(arrayTypeInfo);
            pascalType = std::get<1>(arrayTypeInfo);
            elementType = std::get<2>(arrayTypeInfo);
            dimensions = std::get<3>(arrayTypeInfo);
            isArray = true;
            isMultidimensionalArray = (dimensions.size() > 1);
        } catch (const std::bad_cast& e) {
            throw TranslatorException("类型信息提取失败: " + std::string(e.what()));
        }
    }

    // 在符号表中将所有参数标记为引用参数
    for (const auto& id : ids) {
        if (symbolTable->hasSymbolInCurrentScope(id)) {
            // 更新符号表中的符号
            SymbolEntry& entry = symbolTable->getSymbol(id);
            entry.isReference = true;

            // 检查参数是否为数组
            bool isArray = (entry.dataType == PascalType::ARRAY);
            bool isMultidim = (isArray && entry.arrayDimensions.size() > 1);
            TranslatorUtils::logDebug("  将" + id + "标记为引用参数, isArray: " +
                                     (isArray ? "true" : "false") +
                                     ", isMultidimensional: " + (isMultidim ? "true" : "false"));

            // 由于已经有addSymbol自动添加参数，
            // 需要更新作用域参数列表中的现有参数
            std::vector<SymbolEntry>& parameters = symbolTable->getCurrentScope().getParameters();
            for (auto& param : parameters) {
                if (param.name == id) {
                    param.isReference = true;
                    break;
                }
            }
        }
    }

    // 为引用参数向声明的类型部分添加指针（*）
    // 需要处理链中的多个参数
    std::stringstream ss;
    std::string baseTypeStr;
    size_t pos = params.find_first_of(" ");
    if (pos != std::string::npos) {
        baseTypeStr = params.substr(0, pos);
        std::string rest = params.substr(pos);

        // 将剩余部分分割为单独的参数声明
        std::vector<std::string> paramDecls;
        size_t start = 0;
        size_t commaPos;
        while ((commaPos = rest.find(",", start)) != std::string::npos) {
            paramDecls.push_back(rest.substr(start, commaPos - start));
            start = commaPos + 2; // 跳过", "
        }
        paramDecls.push_back(rest.substr(start));

        // 提取不含数组维度的基本类型
        std::string baseType = baseTypeStr;
        size_t bracketPos = baseType.find('[');
        if (bracketPos != std::string::npos) {
            baseType = baseType.substr(0, bracketPos);
        }

        // 检查是否处理的是多维数组
        std::vector<std::string> dimensionSizes;
        if (isMultidimensionalArray) {
            // 提取所有维度大小以正确声明C数组参数
            for (const auto& dim : dimensions) {
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
                    // 对于作为参数的多维数组，使用正确的C语法：
                    // 对于2D数组：type (*param)[dim2]
                    // 对于3D数组：type (*param)[dim2][dim3]
                    ss << baseType << " (*" << paramName << ")";

                    // 添加除第一个维度外的所有维度，在C数组参数中第一个维度被省略
                    for (size_t j = 1; j < dimensionSizes.size(); ++j) {
                        ss << "[" << dimensionSizes[j] << "]";
                    }
                } else {
                    // 对于单维数组，可以使用更简单的表示法
                    ss << baseType << " *" << paramName;
                }
            } else {
                // 非数组参数 - 普通指针
                ss << baseType << "* " << paramName;
            }
        }
    } else {
        // 如果找不到空格，只是将指针添加到整个字符串
        ss << params << "*";
    }

    return ss.str();
}

/**
 * 处理值参数（非引用传递）
 * @param context 值参数上下文
 * @return 以C风格的参数字符串
 */
antlrcpp::Any PascalToCTranslator::visitValueParameter(PascalSParser::ValueParameterContext *context) {
    //获取标识符
    std::vector<std::string> ids = visit(context->idList()).as<std::vector<std::string>>();

    //返回参数标识符的输出
    std::string idListStr;
    for (const auto& id : ids) {
        if (!idListStr.empty()) idListStr += ", ";
        idListStr += id;
    }
    TranslatorUtils::logDebug("Value parameter identifiers: " + idListStr);

    // 获取类型信息
    auto typeResult = visit(context->type());

    //初始化类型信息的变量
    std::string typeStr;
    PascalType pascalType;
    PascalType elementType = PascalType::INTEGER; // Default for arrays
    std::vector<ArrayBounds> dimensions;

    //根据数组或基本类型提取类型信息
    try {
        // 尝试作为基本类型提取
        auto typePair = typeResult.as<std::pair<std::string, PascalType>>();
        typeStr = typePair.first;
        pascalType = typePair.second;
    } catch (const std::bad_cast&) {
        //如果失败，则为数组类型
        try {
            auto arrayTypeInfo = typeResult.as<std::tuple<std::string, PascalType, PascalType, std::vector<ArrayBounds>>>();
            typeStr = std::get<0>(arrayTypeInfo);
            pascalType = std::get<1>(arrayTypeInfo);
            elementType = std::get<2>(arrayTypeInfo);
            dimensions = std::get<3>(arrayTypeInfo);
        } catch (const std::bad_cast& e) {
            throw TranslatorException("Failed to extract type information: " + std::string(e.what()));
        }
    }

    //格式化参数
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

        //将参数添加到符号表
        SymbolEntry entry;
        entry.name = ids[i];
        entry.symbolType = SymbolType::PARAMETER;
        entry.dataType = pascalType;
        entry.isReference = false;  //默认为按值，如果VAR参数为

        //如果需要，存储特定于数组的信息
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
 * 处理子程序体，包含声明和语句
 * @param context 子程序体上下文
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
 * 处理复合语句（BEGIN ... END 块）
 * @param context 复合语句上下文
 * @return 访问者模式的标准占位符
 */
antlrcpp::Any PascalToCTranslator::visitCompoundStatement(PascalSParser::CompoundStatementContext *context) {
    // 跳过BEGIN和END标记，仅访问内部的语句列表
    visit(context->statementList());

    return antlrcpp::Any();
}

/**
 * 处理语句列表
 * @param context 语句列表上下文
 * @return 访问者模式的标准占位符
 */
antlrcpp::Any PascalToCTranslator::visitStatementList(PascalSParser::StatementListContext *context) {
    // 如果有任何附加语句，先访问它们（源代码中较早的部分）
    if (context->statementList()) {
        visit(context->statementList());
    }

    // 访问当前语句（源代码中较晚的部分）
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

    // 对标识符的赋值（过程或函数结果）
    if (context->ID() && context->ASSIGNOP()) {
        std::string id = TranslatorUtils::toCIdentifier(context->ID()->getText());
        if(!symbolTable->hasSymbol(id)){
            auto *errorContext = new ErrorContext<PascalSParser::StatementContext>();
            errorContext->context = context;
            errorContext->symbolTable = symbolTable.get();
            errorContext->id = id;
            errorContext->ss = &(output << getCurrentIndentation());
            UndefinedVariableStrategy(errorContext);
        }

        auto exprResult = visit(context->expression());
        std::string expr = exprResult.as<std::string>();

        // 获取当前作用域名称 - 如果赋值给同名函数，则是返回值赋值
        std::string currentScopeName = symbolTable->getCurrentScope().getScopeName();

        // 类型检查
        if (symbolTable->hasSymbol(id)) {
            const SymbolEntry& leftEntry = symbolTable->getSymbol(id);
            PascalType leftType = leftEntry.dataType;

            // 尝试获取表达式的类型
            PascalType rightType = inferExpressionType(expr);

            // 检查类型是否匹配
            if (!areTypesCompatible(leftType, rightType)) {
                auto *errorContext = new ErrorContext<PascalSParser::StatementContext>();
                errorContext->context = context;
                errorContext->id = id;
                errorContext->leftType = leftType;
                errorContext->rightType = rightType;
                errorContext->symbolTable = symbolTable.get();
                errorContext->ss = &(output << getCurrentIndentation());
                TypeMismatchInAssignmentStrategy(errorContext);
            }
        }

        if (currentScopeName == id) {
            // 这是函数结果赋值（Pascal函数:=值）
            // 赋值给函数的tmp变量而不是直接使用函数名
            output << getCurrentIndentation() << id << "tmp = " << expr << ";\n";
        } else {
            // 对标识符的常规赋值
            output << getCurrentIndentation() << id << " = " << expr << ";\n";
        }
    }
    // 对变量的赋值（可以是数组元素或其他复杂变量）
    else if (context->variable() && context->ASSIGNOP()) {
        auto varResult = visit(context->variable());

        // 检查这是否是函数结果赋值
        try {
            if (varResult.is<std::pair<std::string, std::string>>()) {
                auto pair = varResult.as<std::pair<std::string, std::string>>();
                if (pair.first == "FUNCTION_RESULT") {
                    // 这是函数结果赋值（Pascal函数:=值）
                    auto exprResult = visit(context->expression());
                    std::string expr = exprResult.as<std::string>();

                    // 类型检查
                    if (symbolTable->hasSymbol(pair.second)) {
                        const SymbolEntry& leftEntry = symbolTable->getSymbol(pair.second);
                        PascalType leftType = leftEntry.dataType;

                        // 尝试获取表达式的类型
                        PascalType rightType = inferExpressionType(expr);

                        // 检查类型是否匹配
                        if (!areTypesCompatible(leftType, rightType)) {
                            auto *errorContext = new ErrorContext<PascalSParser::StatementContext>;
                            errorContext->context = context;
                            errorContext->id = pair.second;
                            errorContext->leftType = leftType;
                            errorContext->rightType = rightType;
                            errorContext->symbolTable = symbolTable.get();
                            errorContext->ss = &(output << getCurrentIndentation());
                            TypeMismatchInAssignmentStrategy(errorContext);
                        }
                    }

                    // 赋值给函数的tmp变量而不是直接返回
                    output << getCurrentIndentation() << pair.second << "tmp = " << expr << ";\n";
                    return antlrcpp::Any();
                }
            }
        } catch (const std::bad_cast& e) {
            // 如果有类型转换错误，假设这是常规变量赋值
            TranslatorUtils::logError("警告：变量赋值中的类型转换问题：" + std::string(e.what()));
        }

        // 常规变量赋值 - 尝试显式字符串转换
        try {
            std::string var = varResult.as<std::string>();
            auto exprResult = visit(context->expression());
            std::string expr = exprResult.as<std::string>();

            // 类型检查
            // 从变量名中提取基本变量名（去除数组索引）
            std::string baseVar = var;
            size_t bracketPos = var.find('[');
            if (bracketPos != std::string::npos) {
                baseVar = var.substr(0, bracketPos);
            }

            if (symbolTable->hasSymbol(baseVar)) {
                const SymbolEntry& leftEntry = symbolTable->getSymbol(baseVar);
                PascalType leftType;

                // 如果是数组访问，使用数组元素类型
                if (leftEntry.dataType == PascalType::ARRAY && bracketPos != std::string::npos) {
                    leftType = leftEntry.arrayElementType;
                } else {
                    leftType = leftEntry.dataType;
                }

                // 尝试获取表达式的类型
                PascalType rightType = inferExpressionType(expr);

                // 检查类型是否匹配
                if (!areTypesCompatible(leftType, rightType)) {
                    auto *errorContext = new ErrorContext<PascalSParser::StatementContext>;
                    errorContext->context = context;
                    errorContext->id = var;
                    errorContext->leftType = leftType;
                    errorContext->rightType = rightType;
                    errorContext->symbolTable = symbolTable.get();
                    errorContext->ss = &(output << getCurrentIndentation());
                    TypeMismatchInAssignmentStrategy(errorContext);
                }
            }

            output << getCurrentIndentation() << var << " = " << expr << ";\n";
        } catch (const std::bad_cast& e) {
            // 如果转换再次失败，添加错误处理
            TranslatorUtils::logError("变量赋值错误：" + std::string(e.what()));
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

    if(inferExpressionType(cond) != PascalType::BOOLEAN) {
        auto *errorContext = new ErrorContext<PascalSParser::IfStatementContext>;
        errorContext->context = context;
        errorContext->cond = cond;
        errorContext->symbolTable = symbolTable.get();
        errorContext->ss = &(output << getCurrentIndentation());
        NonBooleanConditionStrategy(errorContext);
    }

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

    // 输出C风格的for循环（Pascal的for循环总是递增1）
    output << getCurrentIndentation() << "for (" << id << " = " << init << "; " << id << " <= " << final << "; ++" << id << ") {\n";
    increaseIndentation();

    // 访问循环体语句
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
        // 获取要读入的变量列表
        auto result = visit(context->variableList());
        std::vector<std::string> vars = result.as<std::vector<std::string>>();

        // 为每个变量输出读取语句
        for (const auto &var : vars) {
            // 检查是否为数组访问
            std::string baseVar = var;
            size_t bracketPos = var.find('[');
            bool isArrayAccess = false;

            if (bracketPos != std::string::npos) {
                baseVar = var.substr(0, bracketPos);
                isArrayAccess = true;
            }

            // 在符号表中查找变量类型
            if (symbolTable->hasSymbol(baseVar)) {
                const SymbolEntry &entry = symbolTable->getSymbol(baseVar);
                std::string format;

                if (isArrayAccess && entry.dataType == PascalType::ARRAY) {
                    // 对于格式说明符，使用数组元素类型
                    switch (entry.arrayElementType) {
                        case PascalType::INTEGER: format = "\"%d\""; break;
                        case PascalType::REAL: format = "\"%f\""; break;
                        case PascalType::CHAR: format = "\" %c\""; break;
                        case PascalType::BOOLEAN: format = "\"%d\""; break;
                        default: format = "\"%d\""; break;
                    }
                } else {
                    // 对于格式说明符，使用变量自身的类型
                    switch (entry.dataType) {
                        case PascalType::INTEGER: format = "\"%d\""; break;
                        case PascalType::REAL: format = "\"%f\""; break;
                        case PascalType::CHAR: format = "\" %c\""; break;
                        case PascalType::BOOLEAN: format = "\"%d\""; break;
                        default: format = "\"%s\""; break;
                    }
                }

                // 对于当前作用域中的非数组引用参数，不需要使用&
                // 因为它们在C中已经是指针
                if (entry.isReference && entry.symbolType == SymbolType::PARAMETER &&
                    !isArrayAccess && entry.dataType != PascalType::ARRAY &&
                    symbolTable->hasSymbolInCurrentScope(baseVar)) {
                    output << getCurrentIndentation() << "scanf(" << format << ", " << var << ");\n";
                } else {
                    // 常规变量需要&来获取它们的地址用于scanf
                    output << getCurrentIndentation() << "scanf(" << format << ", &" << var << ");\n";
                }
            } else {
                // 如果类型未知，默认为整数
                output << getCurrentIndentation() << "scanf(\"%d\", &" << var << ");\n";
            }
        }
    } catch (const std::bad_cast& e) {
        TranslatorUtils::logError("read语句中的类型转换错误：" + std::string(e.what()));
    }

    return antlrcpp::Any();
}

/**
 * 处理while语句（带条件的循环）
 * @param context while语句上下文
 * @return 访问者模式的标准占位符
 */
antlrcpp::Any PascalToCTranslator::visitWhileStatement(PascalSParser::WhileStatementContext *context) {
    // 获取循环条件
    auto condResult = visit(context->expression());
    std::string cond = condResult.as<std::string>();

    // 输出带条件的while循环
    output << getCurrentIndentation() << "while (" << cond << ") {\n";
    increaseIndentation();

    // 访问循环体语句
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

    // printf的格式字符串部分
    std::string formatStr = "\"";
    std::vector<std::string> formattedArgs;

    // 按原始Pascal顺序处理表达式（已在visitExpressionList中处理）
    for (size_t i = 0; i < exprs.size(); ++i) {
        std::string expr = exprs[i];
        std::string formatSpecifier;
        std::string formattedArg = expr;

        // 检查是否为数组访问（包含方括号）
        std::string baseVar = expr;
        size_t bracketPos = expr.find('[');
        if (bracketPos != std::string::npos) {
            baseVar = expr.substr(0, bracketPos);
        }

        // 检查是否为函数调用
        size_t parenPos = baseVar.find('(');
        if (parenPos != std::string::npos) {
            baseVar = baseVar.substr(0, parenPos);
        }

        // 尝试在符号表中查找类型
        bool found = false;
        // 检查是否为字符串字面量
        if (expr.size() >= 2 && expr[0] == '\'' && expr.back() == '\'') {
            formatSpecifier = "%s";
            // 从表达式中移除单引号并为C字符串添加双引号
            formattedArg = "\"" + expr.substr(1, expr.size() - 2) + "\""; found = true;
        } else if (expr.find('.') != std::string::npos) {
            // 浮点数值使用%f
            formatSpecifier = "%f"; found = true;
        } else if (expr == "0" || expr == "1" || TranslatorUtils::toCIdentifier(expr) == "true" || TranslatorUtils::toCIdentifier(expr) == "false") {
            // 布尔值使用%d（C中的0/1）
            formatSpecifier = "%d"; found = true;
            formattedArg = expr.length() == 1 ? expr : (TranslatorUtils::toCIdentifier(expr) == "true" ? "1" : "0");
        }else {
            // 在符号表中查找变量类型
            if (symbolTable->hasSymbol(baseVar)) {
                const SymbolEntry &entry = symbolTable->getSymbol(baseVar);
                const std::string value = entry.value;
                // 根据变量类型确定格式说明符
                if (entry.dataType == PascalType::ARRAY && bracketPos != std::string::npos) {
                    // 对于数组访问，使用数组元素类型
                    switch (entry.arrayElementType) {
                        case PascalType::INTEGER: formatSpecifier = "%d"; found = true; break;
                        case PascalType::REAL: formatSpecifier = "%f"; found = true; break;
                        case PascalType::BOOLEAN: formatSpecifier = "%d"; found = true; break;
                        case PascalType::CHAR: formatSpecifier = "%c"; found = true; break;
                        case PascalType::STRING: formatSpecifier = "%s"; found = true; break;
                        default: break;
                    }
                } else {
                    // 使用变量自身的类型
                    switch (entry.dataType) {
                        case PascalType::INTEGER: formatSpecifier = "%d"; found = true; break;
                        case PascalType::REAL: formatSpecifier = "%f"; found = true; break;
                        case PascalType::BOOLEAN: formatSpecifier = "%d"; found = true; break;
                        case PascalType::CHAR: formatSpecifier = "%c"; found = true; break;
                        case PascalType::STRING: formatSpecifier = "%s"; found = true; break;
                        default: break;
                    }
                }
            }else {
                auto *errorContext = new ErrorContext<PascalSParser::WriteStatementContext>;
                errorContext->context = context;
                errorContext->symbolTable = symbolTable.get();
                errorContext->id = baseVar;
                errorContext->ss = &(output << getCurrentIndentation());
                UndefinedVariableStrategy(errorContext);
            }
        }
        if (!found) formatSpecifier = "%d";  // 默认使用整数格式

        formatStr += formatSpecifier;
        formattedArgs.push_back(formattedArg);
    }

    formatStr += "\"";
    output << formatStr;

    // 参数 - 保持它们在格式字符串中出现的相同顺序
    for (const auto &arg : formattedArgs) {
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
 * @return 以C语法表示的变量字符串向量
 */
antlrcpp::Any PascalToCTranslator::visitVariableList(PascalSParser::VariableListContext *context) {
    std::vector<std::string> vars;

    // 在Pascal中，列表中的变量在源代码中从左到右出现，
    // 但ANTLR解析器处理它们的方式是，最右边的变量成为
    // 当前节点，而较早的变量位于嵌套的variableList中。

    // 首先，处理嵌套variableList中的任何较早变量
    if (context->variableList()) {
        auto earlierVars = visit(context->variableList());
        vars = earlierVars.as<std::vector<std::string>>();
    }

    // 然后添加当前变量，它在源代码中较晚出现
    auto result = visit(context->variable());

    // 处理潜在的函数返回值标记
    if (result.is<std::pair<std::string, std::string>>()) {
        auto pair = result.as<std::pair<std::string, std::string>>();
        // 使用函数名加tmp后缀
        vars.push_back(pair.second + "tmp");
    } else {
        // 常规变量
        vars.push_back(result.as<std::string>());
    }

    return vars;
}

/**
 * 处理变量标识符，可以是简单变量或数组元素
 * 处理特殊情况，如函数结果变量和引用参数
 * @param context 变量上下文
 * @return 以C语法表示的变量字符串或函数结果的特殊标记
 */
antlrcpp::Any PascalToCTranslator::visitVariable(PascalSParser::VariableContext *context) {
    std::string id = TranslatorUtils::toCIdentifier(context->ID()->getText());

    // 检查变量是否为当前作用域中的函数名
    std::string currentScopeName = symbolTable->getCurrentScope().getScopeName();

    // 检查是否在函数中，且变量名与函数名匹配
    if (id == currentScopeName) {
        // 对于函数返回值，返回一个特殊对表示这一点
        // 将在visitStatement中处理这个
        std::pair<std::string, std::string> resultPair("FUNCTION_RESULT", id);
        return resultPair;
    }

    // 检查变量是否为引用参数（非局部变量）
    bool isReferenceParam = false;
    bool isArray = false;

    if (symbolTable->hasSymbol(id)) {
        const SymbolEntry &entry = symbolTable->getSymbol(id);
        // 仅当它实际上是一个参数且标记为引用时，才将其视为引用参数
        isReferenceParam = entry.isReference && entry.symbolType == SymbolType::PARAMETER;
        isArray = (entry.dataType == PascalType::ARRAY);
    }
    else {
        auto *errorContext = new ErrorContext<PascalSParser::VariableContext>;
        errorContext->context = context;
        errorContext->symbolTable = symbolTable.get();
        errorContext->id = id;
        errorContext->ss = &(output << getCurrentIndentation());
        UndefinedVariableStrategy(errorContext);
    }

    // 检查是否为数组访问
    std::string result;
    if (context->idVarPart()) {
        auto partResult = visit(context->idVarPart());
        std::string indices = partResult.as<std::string>();
        std::regex regex("\\d+");
        auto begin = std::sregex_token_iterator(indices.begin(), indices.end(), regex);
        auto end = std::sregex_token_iterator();
        int i = 0, flag = 0;
        for (auto it = begin; it != end; ++it, ++i) {
            if(std::stoi(*it) > (symbolTable->getSymbol(id).arrayDimensions[i].upperBound - symbolTable->getSymbol(id).arrayDimensions[i].lowerBound - 1)) flag = 1;
        }
        if(flag) {
            auto *errorContext = new ErrorContext<PascalSParser::VariableContext>;
            errorContext->context = context;
            errorContext->symbolTable = symbolTable.get();
            errorContext->id = id;
            errorContext->ss = &(output << getCurrentIndentation());
            ArrayIndexOutOfBoundsStrategy(errorContext);
        }

        // 仅在它们被传递到的函数内部使用时，才解引用引用参数（非局部变量）
        if (isReferenceParam && !isArray && symbolTable->hasSymbolInCurrentScope(id)) {
            // 对于非数组引用参数，访问时需要解引用
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
 * 处理标识符变量部分（数组索引）
 * @param context 标识符变量部分上下文（数组索引）
 * @return 以C语法表示的数组索引字符串
 */
antlrcpp::Any PascalToCTranslator::visitIdVarPart(PascalSParser::IdVarPartContext *context) {
    // 空数组访问
    if (!context->expressionList()) {
        return antlrcpp::Any(std::string(""));
    }

    // 从表达式列表获取数组索引
    auto result = visit(context->expressionList());
    std::vector<std::string> indices = result.as<std::vector<std::string>>();

    // 格式化带有C风格索引的数组访问
    std::stringstream ss;
    for (const auto &index : indices) {
        ss << "[" << index << "]";
    }

    return ss.str();
}

/**
 * 处理过程调用语句
 * @param context 过程调用上下文
 * @return 以C语法表示的过程调用字符串
 */
antlrcpp::Any PascalToCTranslator::visitProcedureCall(PascalSParser::ProcedureCallContext *context) {
    std::string id = TranslatorUtils::toCIdentifier(context->ID()->getText());
    if (symbolTable->hasSymbol(id) && symbolTable->getSymbol(id).symbolType == SymbolType::FUNCTION) {
        auto *errorContext = new ErrorContext<PascalSParser::ProcedureCallContext>;
        errorContext->context = context;
        errorContext->symbolTable = symbolTable.get();
        errorContext->id = id;
        errorContext->ss = &(output << getCurrentIndentation());
        IgnoredFunctionReturnStrategy(errorContext);
    }
    // 检查是否是带参数的过程调用
    if (context->expressionList()) {
        return visitFunction_Procedure(context);
    }
    if(!symbolTable->hasSymbol(id)) {
        auto *errorContext = new ErrorContext<PascalSParser::ProcedureCallContext>;
        errorContext->context = context;
        errorContext->id = id;
        errorContext->symbolTable = symbolTable.get();
        errorContext->ss = &(output << getCurrentIndentation());
        UndefinedFunctionStrategy(errorContext);
    }
    // 无参数的过程调用
    return id + "()";
}

/**
 * 处理if语句的else部分
 * @param context else部分上下文
 * @return "else"字符串（为了保持访问者模式的一致性）
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
 * @return 以C语法表示的表达式字符串向量
 */
antlrcpp::Any PascalToCTranslator::visitExpressionList(PascalSParser::ExpressionListContext *context) {
    std::vector<std::string> exprs;

    try {
        // 在Pascal中，列表中的表达式在源代码中从左到右出现，
        // 但ANTLR解析器处理它们的方式是，最右边的表达式成为
        // 当前节点，而较早的表达式位于嵌套的expressionList中。

        // 首先，处理嵌套expressionList中的任何较早表达式
        if (context->expressionList()) {
            auto earlierExprs = visit(context->expressionList());
            exprs = earlierExprs.as<std::vector<std::string>>();
        }

        // 然后添加当前表达式，它在源代码中较晚出现
        auto result = visit(context->expression());
        exprs.push_back(result.as<std::string>());
    } catch (const std::bad_cast& e) {
        TranslatorUtils::logError("表达式列表中的类型转换错误：" + std::string(e.what()));
    }

    return exprs;
}

/**
 * 处理表达式，可以是简单表达式或关系表达式
 * @param context 表达式上下文
 * @return 以C语法表示的表达式字符串
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

    // 类型检查：比较操作数的类型是否兼容
    PascalType leftType = inferExpressionType(left);
    PascalType rightType = inferExpressionType(right);

    // 检查比较操作数的类型是否兼容
    if (!areTypesForComparisonCompatible(leftType, rightType)) {
        auto *errorContext = new ErrorContext<PascalSParser::ExpressionContext>;
        errorContext->context = context;
        errorContext->leftType = leftType;
        errorContext->rightType = rightType;
        errorContext->symbolTable = symbolTable.get();
        errorContext->ss = &(output << getCurrentIndentation());
        IncompatibleComparisonStrategy(errorContext);
    }

    // 特殊情况：字符串比较需要使用strcmp
    if ((leftType == PascalType::STRING || rightType == PascalType::STRING) &&
        (op == "==" || op == "!=" || op == "<" || op == "<=" || op == ">" || op == ">=")) {
        std::string comparisonExpr;
        if (op == "==") {
            comparisonExpr = "(strcmp(" + left + ", " + right + ") == 0)";
        } else if (op == "!=") {
            comparisonExpr = "(strcmp(" + left + ", " + right + ") != 0)";
        } else if (op == "<") {
            comparisonExpr = "(strcmp(" + left + ", " + right + ") < 0)";
        } else if (op == "<=") {
            comparisonExpr = "(strcmp(" + left + ", " + right + ") <= 0)";
        } else if (op == ">") {
            comparisonExpr = "(strcmp(" + left + ", " + right + ") > 0)";
        } else if (op == ">=") {
            comparisonExpr = "(strcmp(" + left + ", " + right + ") >= 0)";
        }
        return antlrcpp::Any(comparisonExpr);
    }

    // 用括号括起比较以确保安全
    std::string result = "(" + left + " " + op + " " + right + ")";
    return antlrcpp::Any(result);
}

/**
 * 处理简单表达式，可以是项或加法表达式
 * @param context 简单表达式上下文
 * @return 以C语法表示的简单表达式字符串
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

    // 用括号括起表达式以保证正确的优先级
    return antlrcpp::Any(std::string("(") + left + " " + op + " " + right + ")");
}

/**
 * 处理项，可以是因子或乘法表达式
 * @param context 项上下文
 * @return 以C语法表示的项字符串
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

    // 用括号括起表达式以保证正确的优先级
    return antlrcpp::Any(std::string("(") + left + " " + op + " " + right + ")");
}

/**
 * 处理因子，可以是常量、变量、表达式、函数调用或一元操作
 * @param context 因子上下文
 * @return 以C语法表示的因子字符串
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
    else if (context->ID()) {
        std::string id = TranslatorUtils::toCIdentifier(context->ID()->getText());
        if(symbolTable->hasSymbol(id) && symbolTable->getSymbol(id).symbolType == SymbolType::PROCEDURE) {
            auto *errorContext = new ErrorContext<PascalSParser::FactorContext>;
            errorContext->context = context;
            errorContext->id = context->ID()->getText();
            errorContext->symbolTable = symbolTable.get();
            errorContext->ss = &(output << getCurrentIndentation());
            ProcedureInAssignmentStrategy(errorContext);
        }
        if(context->expressionList()) {
            return visitFunction_Procedure(context);
        }
        // 无括号的函数调用（用于没有参数的Pascal函数）
        else {
            if(!symbolTable->hasSymbol(id)){
                auto *errorContext = new ErrorContext<PascalSParser::FactorContext>;
                errorContext->context = context;
                errorContext->symbolTable = symbolTable.get();
                errorContext->id = id;
                errorContext->ss = &(output << getCurrentIndentation());
                UndefinedFunctionStrategy(errorContext);
            }

            // 检查此ID是否为符号表中的函数
            if (symbolTable->hasSymbol(id)) {
                const SymbolEntry& entry = symbolTable->getSymbol(id);

                // 如果它是一个函数且有作用域（意味着它是函数声明，而不是变量）
                if ((entry.symbolType == SymbolType::FUNCTION || entry.symbolType == SymbolType::PROCEDURE) && symbolTable->hasScope(id)) {
                    const ScopeEntry& scope = symbolTable->getScope(id);
                    // 检查函数是否没有参数
                    if (!scope.getParameters().empty()) {
                        auto *errorContext = new ErrorContext<PascalSParser::FactorContext>;
                        errorContext->context = context;
                        errorContext->id = id;
                        errorContext->symbolTable = symbolTable.get();
                        errorContext->ss = &(output << getCurrentIndentation());
                        MissingArgumentsStrategy(errorContext);
                    }
                    return id + "()";
                } else if (entry.symbolType == SymbolType::PARAMETER) {
                    if (entry.isReference && symbolTable->hasSymbolInCurrentScope(id)) {
                        // 对于非数组引用参数，访问时需要解引用
                        return "(*" + id + ")";
                    }
                }

                // 特殊情况：如果在函数中且引用了函数自身的名称
                // 作为变量（Pascal中的递归函数常见做法）
                if (id == symbolTable->getCurrentScope().getScopeName()) {
                    // 这是访问自己函数的返回值
                    return id + "tmp";
                }
            }

            // 如果未识别为无参数函数，则视为普通变量
            return id;
        }
    }
    // 逻辑NOT操作
    else if (context->NOT()) {
        auto result = visit(context->factor());
        std::string factor = result.as<std::string>();
        if(!((factor[0]>='0' && factor[0]<='9') || factor[0]=='(' || factor[0]=='-' || factor[0]=='~' ||factor[0]=='+') && (!symbolTable->hasSymbol(factor))) {
            auto *errorContext = new ErrorContext<PascalSParser::FactorContext>;
            errorContext->context = context;
            errorContext->symbolTable = symbolTable.get();
            errorContext->id = factor;
            errorContext->ss = &(output << getCurrentIndentation());
            UndefinedVariableStrategy(errorContext);
        }
        return antlrcpp::Any(std::string("~(") + factor + ")");
    }
    // 一元减操作
    else if (context->MINUS()) {
        auto result = visit(context->factor());
        std::string factor = result.as<std::string>();
        if(!((factor[0]>='0' && factor[0]<='9') || factor[0]=='(' || factor[0]=='-' || factor[0]=='~' ||factor[0]=='+') && (!symbolTable->hasSymbol(factor))) {
            auto *errorContext = new ErrorContext<PascalSParser::FactorContext>;
            errorContext->context = context;
            errorContext->symbolTable = symbolTable.get();
            errorContext->id = factor;
            errorContext->ss = &(output << getCurrentIndentation());
            UndefinedVariableStrategy(errorContext);
        }

        return antlrcpp::Any(std::string("-(") + factor + ")");
    }
    // 一元加操作
    else if (context->PLUS()) {
        auto result = visit(context->factor());
        std::string factor = result.as<std::string>();
        if(!((factor[0]>='0' && factor[0]<='9') || factor[0]=='(' || factor[0]=='-' || factor[0]=='~' ||factor[0]=='+') && (!symbolTable->hasSymbol(factor))) {
            auto *errorContext = new ErrorContext<PascalSParser::FactorContext>;
            errorContext->context = context;
            errorContext->symbolTable = symbolTable.get();
            errorContext->id = factor;
            errorContext->ss = &(output << getCurrentIndentation());
            UndefinedVariableStrategy(errorContext);
        }

        return antlrcpp::Any(std::string("+(") + factor + ")");
    }
    // 字符串字面量
    else if (context->STRING()) {
        return context->STRING()->getText();
    }
    // 字符字面量
    else if (context->LETTER()) {
        return antlrcpp::Any(std::string ((TranslatorUtils::toCIdentifier(context->LETTER()->getText()) == "true") ? "1" : "0"));
    }

    return antlrcpp::Any(std::string(""));
}

/**
 * 处理数值字面量
 * @param context 数值上下文
 * @return 数字的字符串表示
 */
antlrcpp::Any PascalToCTranslator::visitNum(PascalSParser::NumContext *context) {
    return context->NUM()->getText();
}

/**
 * 处理关系运算符（==, !=, <, <=, >, >=）
 * @param context 关系运算符上下文
 * @return 以C语法表示的运算符字符串
 */
antlrcpp::Any PascalToCTranslator::visitRelop(PascalSParser::RelopContext *context) {
    if (context->EQUAL()) {
        return antlrcpp::Any(std::string("=="));  // Pascal = 在C中变为 ==
    } else if (context->NOTEQUAL()) {
        return antlrcpp::Any(std::string("!="));  // Pascal <> 在C中变为 !=
    } else if (context->LT()) {
        return antlrcpp::Any(std::string("<"));   // Pascal < 在C中相同
    } else if (context->LE()) {
        return antlrcpp::Any(std::string("<="));  // Pascal <= 在C中相同
    } else if (context->GT()) {
        return antlrcpp::Any(std::string(">"));   // Pascal > 在C中相同
    } else if (context->GE()) {
        return antlrcpp::Any(std::string(">="));  // Pascal >= 在C中相同
    }

    return antlrcpp::Any(std::string(""));
}

/**
 * 处理加法运算符（+, -, OR）
 * @param context 加法运算符上下文
 * @return 以C语法表示的运算符字符串
 */
antlrcpp::Any PascalToCTranslator::visitAddop(PascalSParser::AddopContext *context) {
    if (context->PLUS()) {
        return antlrcpp::Any(std::string("+"));   // Pascal + 在C中相同
    } else if (context->MINUS()) {
        return antlrcpp::Any(std::string("-"));   // Pascal - 在C中相同
    } else if (context->OR()) {
        return antlrcpp::Any(std::string("||"));  // Pascal OR 在C中变为 ||
    }

    return antlrcpp::Any(std::string(""));
}

/**
 * 处理乘法运算符（*, /, DIV, MOD, AND）
 * @param context 乘法运算符上下文
 * @return 以C语法表示的运算符字符串
 */
antlrcpp::Any PascalToCTranslator::visitMulop(PascalSParser::MulopContext *context) {
    if (context->STAR()) {
        return antlrcpp::Any(std::string("*"));   // Pascal * 在C中相同
    } else if (context->SLASH()) {
        return antlrcpp::Any(std::string("/"));   // Pascal / 在C中相同（浮点除法）
    } else if (context->DIV()) {
        return antlrcpp::Any(std::string("/"));   // Pascal DIV 在C中变为 / （整数除法）
    } else if (context->MOD()) {
        return antlrcpp::Any(std::string("%"));   // Pascal MOD 在C中变为 %
    } else if (context->AND()) {
        return antlrcpp::Any(std::string("&&"));  // Pascal AND 在C中变为 &&
    }

    return antlrcpp::Any(std::string(""));
}

/**
 * 推断表达式的类型
 * @param expr 表达式字符串
 * @return 推断的Pascal类型
 */
PascalType PascalToCTranslator::inferExpressionType(const std::string& expr) {
    // 移除表达式两侧的空白
    std::string trimmedExpr = expr;
    trimmedExpr.erase(0, trimmedExpr.find_first_not_of(" \t\n\r\f\v"));
    trimmedExpr.erase(trimmedExpr.find_last_not_of(" \t\n\r\f\v") + 1);

    // 移除最外层括号（如果有）
    if (trimmedExpr.size() >= 2 && trimmedExpr[0] == '(' && trimmedExpr.back() == ')') {
        // 确保这是最外层的括号，而不是函数调用或其他结构
        bool isOutermostParen = true;
        int parenCount = 0;

        for (size_t i = 0; i < trimmedExpr.size() - 1; ++i) {
            if (trimmedExpr[i] == '(') parenCount++;
            else if (trimmedExpr[i] == ')') parenCount--;

            if (parenCount == 0 && i < trimmedExpr.size() - 1) {
                isOutermostParen = false;
                break;
            }
        }

        if (isOutermostParen) {
            return inferExpressionType(trimmedExpr.substr(1, trimmedExpr.size() - 2));
        }
    }

    // 检查是否为数字字面量
    if (std::regex_match(trimmedExpr, std::regex("^[+-]?\\d+$"))) {
        return PascalType::INTEGER;
    }

    // 检查是否为浮点数字面量
    if (std::regex_match(trimmedExpr, std::regex("^[+-]?\\d+\\.\\d*$"))) {
        return PascalType::REAL;
    }

    // 检查是否为布尔字面量
    if (trimmedExpr == "true" || trimmedExpr == "false" || trimmedExpr == "1" || trimmedExpr == "0" ||
        trimmedExpr == "~(0)" || trimmedExpr == "~(1)" || trimmedExpr == "!(0)" || trimmedExpr == "!(1)") {
        return PascalType::BOOLEAN;
    }

    // 检查是否为字符字面量
    if (trimmedExpr.size() >= 2 && trimmedExpr[0] == '\'' && trimmedExpr.back() == '\'' && trimmedExpr.size() == 3) {
        return PascalType::CHAR;
    }

    // 检查是否为字符串字面量
    if (trimmedExpr.size() >= 2 &&
        ((trimmedExpr[0] == '\'' && trimmedExpr.back() == '\'' && trimmedExpr.size() > 3) ||
         (trimmedExpr[0] == '\"' && trimmedExpr.back() == '\"'))) {
        return PascalType::STRING;
    }

    // 处理复杂表达式

    // 首先检查是否为关系表达式 (==, !=, <, <=, >, >=)
    std::vector<std::string> relOps = {"==", "!=", "<", "<=", ">", ">="};
    for (const auto& op : relOps) {
        size_t pos = findOperatorPosition(trimmedExpr, op);
        if (pos != std::string::npos) {
            // 关系表达式总是返回布尔类型
            return PascalType::BOOLEAN;
        }
    }

    // 检查逻辑运算符 (&&, ||)
    std::vector<std::string> logicalOps = {"&&", "||"};
    for (const auto& op : logicalOps) {
        size_t pos = findOperatorPosition(trimmedExpr, op);
        if (pos != std::string::npos) {
            // 逻辑表达式总是返回布尔类型
            return PascalType::BOOLEAN;
        }
    }

    // 检查加减运算符 (+, -)
    std::vector<std::string> addOps = {"+", "-"};
    for (const auto& op : addOps) {
        size_t pos = findOperatorPosition(trimmedExpr, op);
        if (pos != std::string::npos) {
            // 分割左右表达式
            std::string leftExpr = trimmedExpr.substr(0, pos);
            std::string rightExpr = trimmedExpr.substr(pos + op.length());

            // 递归推断左右表达式的类型
            PascalType leftType = inferExpressionType(leftExpr);
            PascalType rightType = inferExpressionType(rightExpr);

            // 如果任一操作数是REAL，结果是REAL
            if (leftType == PascalType::REAL || rightType == PascalType::REAL) {
                return PascalType::REAL;
            }

            // 如果两个操作数都是INTEGER，结果是INTEGER
            if (leftType == PascalType::INTEGER && rightType == PascalType::INTEGER) {
                return PascalType::INTEGER;
            }

            // 如果是字符串连接
            if (op == "+" && (leftType == PascalType::STRING || rightType == PascalType::STRING)) {
                return PascalType::STRING;
            }

            // 默认返回第一个操作数的类型
            return leftType;
        }
    }

    // 检查乘除运算符 (*, /, %)
    std::vector<std::string> mulOps = {"*", "/", "%"};
    for (const auto& op : mulOps) {
        size_t pos = findOperatorPosition(trimmedExpr, op);
        if (pos != std::string::npos) {
            // 分割左右表达式
            std::string leftExpr = trimmedExpr.substr(0, pos);
            std::string rightExpr = trimmedExpr.substr(pos + op.length());

            // 递归推断左右表达式的类型
            PascalType leftType = inferExpressionType(leftExpr);
            PascalType rightType = inferExpressionType(rightExpr);

            // 除法总是返回REAL
            if (op == "/") {
                return PascalType::REAL;
            }

            // 如果任一操作数是REAL，结果是REAL
            if (leftType == PascalType::REAL || rightType == PascalType::REAL) {
                return PascalType::REAL;
            }

            // 如果两个操作数都是INTEGER，结果是INTEGER
            if (leftType == PascalType::INTEGER && rightType == PascalType::INTEGER) {
                return PascalType::INTEGER;
            }

            // 默认返回第一个操作数的类型
            return leftType;
        }
    }

    // 检查一元运算符
    if (trimmedExpr.size() > 1) {
        if (trimmedExpr[0] == '-' || trimmedExpr[0] == '+') {
            // 一元加减不改变类型
            return inferExpressionType(trimmedExpr.substr(1));
        }
        if (trimmedExpr[0] == '~' || trimmedExpr[0] == '!') {
            // 逻辑非总是返回布尔类型
            return PascalType::BOOLEAN;
        }
    }

    // 检查是否为函数调用
    size_t parenPos = trimmedExpr.find('(');
    if (parenPos != std::string::npos && trimmedExpr.back() == ')') {
        std::string funcName = trimmedExpr.substr(0, parenPos);
        // 移除函数名中的空白
        funcName.erase(0, funcName.find_first_not_of(" \t\n\r\f\v"));
        funcName.erase(funcName.find_last_not_of(" \t\n\r\f\v") + 1);

        // 在符号表中查找函数
        if (symbolTable->hasSymbol(funcName)) {
            const SymbolEntry& entry = symbolTable->getSymbol(funcName);
            if (entry.symbolType == SymbolType::FUNCTION) {
                return entry.dataType;
            }
        }
    }

    // 检查是否为变量或数组访问
    std::string baseExpr = trimmedExpr;
    size_t bracketPos = trimmedExpr.find('[');

    // 提取基本变量名
    if (bracketPos != std::string::npos) {
        baseExpr = trimmedExpr.substr(0, bracketPos);
    }

    // 在符号表中查找变量
    if (symbolTable->hasSymbol(baseExpr)) {
        const SymbolEntry& entry = symbolTable->getSymbol(baseExpr);

        if (entry.dataType == PascalType::ARRAY && bracketPos != std::string::npos) {
            // 数组访问，返回元素类型
            return entry.arrayElementType;
        } else {
            // 变量，返回其类型
            return entry.dataType;
        }
    }

    // 如果无法确定类型，默认为INTEGER
    return PascalType::INTEGER;
}

/**
 * 在表达式中查找操作符的位置，考虑括号和嵌套表达式
 * @param expr 要搜索的表达式
 * @param op 要查找的操作符
 * @return 操作符在表达式中的位置，如果未找到则返回std::string::npos
 */
size_t PascalToCTranslator::findOperatorPosition(const std::string& expr, const std::string& op) {
    int parenCount = 0;
    int bracketCount = 0;
    bool inString = false;
    char stringDelimiter = 0;

    // 从右向左搜索，以处理右结合性
    for (int i = expr.size() - 1; i >= 0; --i) {
        // 跳过字符串内容
        if (expr[i] == '\'' || expr[i] == '\"') {
            if (!inString) {
                inString = true;
                stringDelimiter = expr[i];
            } else if (expr[i] == stringDelimiter) {
                inString = false;
            }
            continue;
        }

        if (inString) continue;

        // 跟踪括号和方括号
        if (expr[i] == ')') parenCount++;
        else if (expr[i] == '(') parenCount--;
        else if (expr[i] == ']') bracketCount++;
        else if (expr[i] == '[') bracketCount--;

        // 只在不在括号或方括号内时检查操作符
        if (parenCount == 0 && bracketCount == 0) {
            // 检查当前位置是否为操作符的开始
            if (i >= op.length() - 1) {
                bool match = true;
                for (size_t j = 0; j < op.length(); ++j) {
                    if (expr[i - op.length() + 1 + j] != op[j]) {
                        match = false;
                        break;
                    }
                }
                if (match) {
                    return i - op.length() + 1;
                }
            }
        }
    }

    return std::string::npos;
}

/**
 * 检查两个类型是否兼容（可以赋值）
 * @param leftType 左侧（目标）类型
 * @param rightType 右侧（源）类型
 * @return 如果类型兼容则返回true
 */
bool PascalToCTranslator::areTypesCompatible(PascalType leftType, PascalType rightType) {
    // 相同类型总是兼容的
    if (leftType == rightType) {
        return true;
    }

    // 类型兼容性规则
    switch (leftType) {
        case PascalType::REAL:
            // INTEGER 可以赋值给 REAL（隐式转换）
            return rightType == PascalType::INTEGER;

        case PascalType::STRING:
            // CHAR 可以赋值给 STRING
            return rightType == PascalType::CHAR;

        case PascalType::BOOLEAN:
            // 在某些情况下，INTEGER 可以视为布尔值（0为假，非0为真）
            // 但这通常不是Pascal的标准行为，所以默认不允许
            return false;

        case PascalType::INTEGER:
            // 在某些Pascal方言中，CHAR可以转换为其ASCII值
            // 但这通常不是标准行为，所以默认不允许
            return false;

        case PascalType::ARRAY:
            // 数组类型必须完全匹配（已在前面的相等检查中处理）
            return false;

        default:
            return false;
    }
}


template<typename T>
antlrcpp::Any PascalToCTranslator::visitFunction_Procedure(T *context) {
    std::string id = TranslatorUtils::toCIdentifier(context->ID()->getText());
    auto result = visit(context->expressionList());
    std::vector<std::string> args = result.template as<std::vector<std::string>>();

    // 格式化函数调用
    std::stringstream ss;

    if(!symbolTable->hasSymbol(id)){
        auto *errorContext = new ErrorContext<T>;
        errorContext->context = context;
        errorContext->id = id;
        errorContext->symbolTable = symbolTable.get();
        errorContext->ss = &ss;
        UndefinedFunctionStrategy(errorContext);
        ss << getCurrentIndentation() << id << "(";
        for (size_t i = 0; i < args.size() - 1; ++i)
            ss << args[i] << ", ";
        ss << args.back() << ")";

        return ss.str();
    }
    ss << id << "(";

    // 如果可用，获取函数定义以检查引用参数
    bool hasFunctionSymbol = symbolTable->hasSymbol(id);
    std::vector<SymbolEntry> parameters;

    if (hasFunctionSymbol) {
        // 获取此函数的参数
        if (symbolTable->hasScope(id)) {
            const ScopeEntry& scope = symbolTable->getScope(id);
            parameters = scope.getParameters();

            if(args.size() != parameters.size()) {
                auto *errorContext = new ErrorContext<T>;
                errorContext->context = context;
                errorContext->id = id;
                errorContext->symbolTable = symbolTable.get();
                errorContext->ss = &(output << getCurrentIndentation());
                ArgumentCountMismatchStrategy(errorContext);
            }

            // 调试输出以验证参数
            TranslatorUtils::logDebug("函数 " + id + " 参数：");
            for (size_t i = 0; i < parameters.size(); ++i) {
                TranslatorUtils::logDebug("  参数 " + std::to_string(i) + ": " + parameters[i].name +
                                          ", 是否引用: " + (parameters[i].isReference ? "true" : "false"));
            }
        }
    }

    if(args.size() < parameters.size()) {
        auto *errorContext = new ErrorContext<T>;
        errorContext->context = context;
        errorContext->id = id;
        errorContext->symbolTable = symbolTable.get();
        errorContext->ss = &(output << getCurrentIndentation());
        MissingArgumentsStrategy(errorContext);
    }

    for (int i = 0; i < args.size(); ++i) {
        if (i > 0) {
            ss << ", ";
        }

        // 检查此参数是否应通过引用传递
        bool isReferenceParam = false;
        bool isArrayType = false;
        bool isMultidimensionalArray = false;

        // 修复参数排序问题：作用域参数列表中的参数
        // 与它们在Pascal源代码中的出现顺序相反。
        // 需要反转索引以匹配正确的参数。
        if (i + 1 <= parameters.size()) {
            // 计算正确的参数索引（参数按相反顺序）
            size_t paramIndex = parameters.size() - 1 - i;

            isReferenceParam = parameters[paramIndex].isReference;

            // 调试输出以验证引用参数检测
            TranslatorUtils::logDebug("  检查参数 " + std::to_string(i) + ": " + args[i] +
                                      ", 是否引用: " + (isReferenceParam ? "true" : "false") +
                                      ", 参数索引: " + std::to_string(paramIndex));

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

            // 检查参数是否为数组，以及是否为多维数组
            if (symbolTable->hasSymbol(argBase)) {
                const SymbolEntry& argEntry = symbolTable->getSymbol(argBase);
                isArrayType = (argEntry.dataType == PascalType::ARRAY);
                isMultidimensionalArray = (isArrayType && argEntry.arrayDimensions.size() > 1);

                TranslatorUtils::logDebug("    参数 " + argBase + " 是数组: " + (isArrayType ? "true" : "false") +
                                          ", 是多维数组: " + (isMultidimensionalArray ? "true" : "false") +
                                          ", 维度: " + std::to_string(argEntry.arrayDimensions.size()));
            }

            // 区别处理普通数组和多维数组
            if (isArrayType) {
                // 如果是数组索引操作，需要检查是否传递数组的一部分
                if (args[i].find('[') != std::string::npos) {
                    // 计算原始数组中的维度数与数组访问中的维度数
                    int accessedDimensions = 0;
                    size_t pos = 0;
                    while ((pos = args[i].find('[', pos)) != std::string::npos) {
                        accessedDimensions++;
                        pos++;
                    }

                    // 如果将参数用作数组，检查维度
                    bool isFullyIndexed = false;
                    if (symbolTable->hasSymbol(argBase)) {
                        const SymbolEntry& argEntry = symbolTable->getSymbol(argBase);
                        isFullyIndexed = (accessedDimensions >= argEntry.arrayDimensions.size());
                    }

                    // 如果传递的是一部分或参数期望一个数组
                    if (!isFullyIndexed) {
                        // 直接传递数组元素（它是多维数组的一部分）
                        ss << args[i];
                    } else {
                        // 传递完全索引的元素（如果是VAR参数，可能需要&）
                        if (isReferenceParam) {
                            ss << "(&(" << args[i] << "))";
                        } else {
                            ss << args[i];
                        }
                    }
                } else {
                    // 传递整个数组 - 不需要&，因为数组默认通过引用传递
                    ss << args[i];
                }
            }
                // 对于通过引用传递的非数组参数
            else if (isReferenceParam) {
                ss << "(&(" << args[i] << "))";
                TranslatorUtils::logDebug("  添加&到 " + args[i]);
            } else {
                // 常规值参数
                ss << args[i];
            }
        } else {
            // 如果无法匹配参数，按原样传递参数
            ss << args[i];
            std::cout << "无法匹配参数，参数:" << args[i] << std::endl;
        }
    }

    ss << ")";

    return ss.str();
}

/**
 * 检查两个类型是否可以进行比较操作
 * @param leftType 左侧操作数类型
 * @param rightType 右侧操作数类型
 * @return 如果类型可比较则返回true
 */
bool PascalToCTranslator::areTypesForComparisonCompatible(PascalType leftType, PascalType rightType) {
    // 相同类型总是可以比较的
    if (leftType == rightType) {
        return true;
    }
    
    // 数值类型之间可以比较
    if ((leftType == PascalType::INTEGER || leftType == PascalType::REAL) &&
        (rightType == PascalType::INTEGER || rightType == PascalType::REAL)) {
        return true;
    }
    
    // 字符串和字符可以比较
    if ((leftType == PascalType::STRING && rightType == PascalType::CHAR) ||
        (leftType == PascalType::CHAR && rightType == PascalType::STRING)) {
        return true;
    }
    
    // 其他类型组合不能比较
    return false;
}



