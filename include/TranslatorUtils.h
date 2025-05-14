#pragma once

#include <iostream>
#include <stdexcept>
#include <string>

// 翻译器错误的异常类
class TranslatorException : public std::runtime_error {
  public:
    TranslatorException(const std::string& message) : std::runtime_error(message) {}
};

// 翻译器的工具类
class TranslatorUtils {
  public:
    // 日志函数
    static void logError(const std::string& message);
    static void logWarning(const std::string& message);
    static void logInfo(const std::string& message);
    static void logDebug(const std::string& message);

    // 字符串操作函数
    static std::string toCIdentifier(const std::string& pascalIdentifier);
    static std::string escapeString(const std::string& str);

    // 检查字符串是否为有效标识符
    static bool isValidIdentifier(const std::string& str);
};