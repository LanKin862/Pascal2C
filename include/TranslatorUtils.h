#pragma once

#include <iostream>
#include <stdexcept>
#include <string>

// Exception class for translator errors
class TranslatorException : public std::runtime_error {
  public:
    TranslatorException(const std::string& message) : std::runtime_error(message) {}
};

// Utility class for translator
class TranslatorUtils {
  public:
    // Log functions
    static void logError(const std::string& message);
    static void logWarning(const std::string& message);
    static void logInfo(const std::string& message);
    static void logDebug(const std::string& message);

    // String manipulation functions
    static std::string toCIdentifier(const std::string& pascalIdentifier);
    static std::string escapeString(const std::string& str);

    // Check if a string is a valid identifier
    static bool isValidIdentifier(const std::string& str);
};