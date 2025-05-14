#pragma once

#include <iostream>
#include <stdexcept>
#include <string>

/**
 * 翻译器异常类
 * 用于在翻译过程中报告错误
 */
class TranslatorException : public std::runtime_error {
  public:
    // 使用基类构造函数
    using std::runtime_error::runtime_error;
};

/**
 * 翻译器工具类
 * 提供用于日志记录和字符串处理的静态方法
 */
class TranslatorUtils {
  public:
    // 日志记录函数
    static void logError(const std::string& message);
    static void logWarning(const std::string& message);
    static void logInfo(const std::string& message);
    static void logDebug(const std::string& message);

    // 字符串处理函数
    static std::string toCIdentifier(const std::string& identifier);
    static std::string escapeString(const std::string& str);

    // 检查字符串是否为有效标识符
    static bool isValidIdentifier(const std::string& str);
};