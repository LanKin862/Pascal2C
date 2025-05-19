#include "../include/TranslatorUtils.h"

#include <algorithm>
#include <cctype>
#include <regex>

/**
 * 将错误消息记录到标准错误输出
 * 用于可能阻止成功翻译的关键问题
 * @param message 要记录的错误消息
 */
void TranslatorUtils::logError(const std::string& message) {
    std::cerr << "ERROR: " << message << std::endl;
}

/**
 * 将警告消息记录到标准错误输出
 * 用于可能影响翻译质量的非关键问题
 * @param message 要记录的警告消息
 */
void TranslatorUtils::logWarning(const std::string& message) {
    std::cerr << "WARNING: " << message << std::endl;
}

/**
 * 将信息消息记录到标准输出
 * 用于翻译过程中的一般状态更新
 * @param message 要记录的信息消息
 */
void TranslatorUtils::logInfo(const std::string& message) {
    std::cout << "INFO: " << message << std::endl;
}

/**
 * 将调试消息记录到标准输出
 * 用于开发和调试过程中有用的详细信息
 * @param message 要记录的调试消息
 */
void TranslatorUtils::logDebug(const std::string& message) {
    std::cout << "DEBUG: " << message << std::endl;
}

/**
 * 将Pascal标识符转换为C兼容的标识符
 * 处理Pascal和C之间标识符规则的差异：
 * 1. Pascal标识符大小写不敏感，而C标识符大小写敏感
 * 2. C有可能与Pascal标识符冲突的保留关键字
 * 
 * @param pascalIdentifier 要转换的Pascal标识符
 * @return C兼容的标识符
 */
std::string TranslatorUtils::toCIdentifier(const std::string& pascalIdentifier) {
    // 将Pascal标识符转换为C标识符
    // 在Pascal中，标识符大小写不敏感，在C中它们大小写敏感
    // 我们将Pascal标识符转换为小写以避免问题

    std::string result = pascalIdentifier;

    // 为了一致性转换为小写
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    // 检查C关键字并在必要时添加下划线前缀
    // 这可以防止与C中的保留字冲突
    static const std::vector<std::string> cKeywords = {
            "auto", "break", "case", "char", "const", "continue", "default",
            "do", "double", "else", "enum", "extern", "float", "for", "goto",
            "if", "int", "long", "register", "return", "short", "signed",
            "sizeof", "static", "struct", "switch", "typedef", "union",
            "unsigned", "void", "volatile", "while"};

    if (std::find(cKeywords.begin(), cKeywords.end(), result) != cKeywords.end()) {
        result = "_" + result;
    }

    return result;
}

/**
 * 转义字符串中的特殊字符，用于C字符串字面量
 * 确保在生成的C代码中正确转义带有特殊字符的字符串
 * 
 * @param str 要转义的字符串
 * @return 转义后的字符串
 */
std::string TranslatorUtils::escapeString(const std::string& str) {
    // 为C输出转义字符串中的特殊字符
    std::string result;
    for (char c : str) {
        if (c == '\\') result += "\\\\";        // 反斜杠需要转义
        else if (c == '\"') result += "\\\"";   // 双引号需要转义
        else if (c == '\'') result += "\\\'";   // 单引号需要转义
        else if (c == '\n') result += "\\n";    // 换行符需要转义
        else if (c == '\r') result += "\\r";    // 回车符需要转义
        else if (c == '\t') result += "\\t";    // 制表符需要转义
        else result += c;                        // 普通字符，无需转义
    }
    return result;
}

/**
 * 检查字符串是否为Pascal和C中的有效标识符
 * 有效标识符以字母或下划线开头，可以包含
 * 字母、数字和下划线
 * 
 * @param str 要检查的字符串
 * @return 如果字符串是有效标识符则为true，否则为false
 */
bool TranslatorUtils::isValidIdentifier(const std::string& str) {
    // 检查字符串是否为有效标识符
    // 在Pascal和C中，标识符必须以字母或下划线开头
    // 并且可以包含字母、数字和下划线
    
    // 空字符串不是有效标识符
    if (str.empty()) {
        return false;
    }

    // 第一个字符必须是字母或下划线
    if (!std::isalpha(str[0]) && str[0] != '_') {
        return false;
    }

    // 其余字符必须是字母、数字或下划线
    return std::all_of(str.begin() + 1, str.end(), [](char c) {
        return std::isalnum(c) || c == '_';
    });
}

/**
 * 将PascalType枚举转换为可读的字符串
 * @param type Pascal类型
 * @return 类型的字符串表示c
 */
std::string TranslatorUtils::pascalTypeToString(PascalType type) {
    switch (type) {
        case PascalType::INTEGER: return "INTEGER";
        case PascalType::REAL: return "REAL";
        case PascalType::BOOLEAN: return "BOOLEAN";
        case PascalType::CHAR: return "CHAR";
        case PascalType::STRING: return "STRING";
        case PascalType::ARRAY: return "ARRAY";
        default: return "UNKNOWN";
    }
}