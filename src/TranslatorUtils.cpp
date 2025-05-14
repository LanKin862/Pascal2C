#include "../include/TranslatorUtils.h"

#include <algorithm>
#include <cctype>
#include <regex>
#include <set>
#include <sstream>

// 设置C语言保留关键字
static const std::set<std::string> cReservedKeywords = {
    "auto", "break", "case", "char", "const", "continue", "default",
    "do", "double", "else", "enum", "extern", "float", "for", "goto",
    "if", "int", "long", "register", "return", "short", "signed",
    "sizeof", "static", "struct", "switch", "typedef", "union",
    "unsigned", "void", "volatile", "while"
};

/**
 * 记录错误消息到标准错误输出
 * @param message 要记录的错误消息
 */
void TranslatorUtils::logError(const std::string& message) {
    std::cerr << "ERROR: " << message << std::endl;
}

/**
 * 记录警告消息到标准错误输出
 * @param message 要记录的警告消息
 */
void TranslatorUtils::logWarning(const std::string& message) {
    std::cerr << "WARNING: " << message << std::endl;
}

/**
 * 记录信息消息到标准输出
 * @param message 要记录的信息消息
 */
void TranslatorUtils::logInfo(const std::string& message) {
    std::cout << "INFO: " << message << std::endl;
}

/**
 * 记录调试消息到标准输出
 * @param message 要记录的调试消息
 */
void TranslatorUtils::logDebug(const std::string& message) {
#ifdef _DEBUG
    std::cout << "DEBUG: " << message << std::endl;
#endif
}

/**
 * 将Pascal标识符转换为C兼容的标识符
 * 
 * Pascal标识符不区分大小写，而C标识符区分大小写。
 * 此外，Pascal和C都有不能用作标识符的保留关键字。
 * 
 * @param identifier Pascal标识符
 * @return 转换后的C标识符
 */
std::string TranslatorUtils::toCIdentifier(const std::string& identifier) {
    // 首先检查是否为C关键字
    std::string lowerIdentifier = identifier;
    std::transform(lowerIdentifier.begin(), lowerIdentifier.end(), lowerIdentifier.begin(), ::tolower);
    
    // 如果是C保留关键字，添加前缀
    if (cReservedKeywords.find(lowerIdentifier) != cReservedKeywords.end()) {
        return "p_" + identifier;
    }
    
    // 保持标识符不变，但注意Pascal不区分大小写，而C区分大小写
    // 通常需要确保在C代码中唯一的标识符
    return identifier;
}

/**
 * 转义字符串中的特殊字符以用于C字符串文字
 * 
 * @param str 要转义的原始字符串
 * @return 转义后的字符串，可用作C字符串文字
 */
std::string TranslatorUtils::escapeString(const std::string& str) {
    std::stringstream escaped;
    
    for (char c : str) {
        // 处理需要在C字符串中转义的特殊字符
        switch (c) {
            case '\\': escaped << "\\\\"; break;
            case '\"': escaped << "\\\""; break;
            case '\'': escaped << "\\\'"; break;
            case '\n': escaped << "\\n"; break;
            case '\r': escaped << "\\r"; break;
            case '\t': escaped << "\\t"; break;
            case '\0': escaped << "\\0"; break;
            default:
                // 处理不可打印字符
                if (std::iscntrl(c)) {
                    // 使用八进制转义序列
                    char buffer[4];
                    std::snprintf(buffer, sizeof(buffer), "\\%03o", static_cast<unsigned char>(c));
                    escaped << buffer;
                } else {
                    escaped << c;
                }
                break;
        }
    }
    
    return escaped.str();
}

/**
 * 检查字符串是否是有效的标识符
 * 
 * 标识符必须以字母开头，后跟字母、数字或下划线。
 * Pascal和C的标识符定义基本相同，但Pascal不区分大小写。
 * 
 * @param str 要检查的字符串
 * @return 如果字符串是有效的标识符则为true，否则为false
 */
bool TranslatorUtils::isValidIdentifier(const std::string& str) {
    if (str.empty() || (!std::isalpha(str[0]) && str[0] != '_')) {
        return false;
    }
    
    return std::all_of(str.begin() + 1, str.end(), [](char c) {
        return std::isalnum(c) || c == '_';
    });
}