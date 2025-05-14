#include "../include/TranslatorUtils.h"

#include <algorithm>
#include <cctype>
#include <regex>

/**
 * Logs an error message to the standard error output
 * Used for critical issues that may prevent successful translation
 * @param message The error message to log
 */
void TranslatorUtils::logError(const std::string& message) {
    std::cerr << "ERROR: " << message << std::endl;
}

/**
 * Logs a warning message to the standard error output
 * Used for non-critical issues that might affect translation quality
 * @param message The warning message to log
 */
void TranslatorUtils::logWarning(const std::string& message) {
    std::cerr << "WARNING: " << message << std::endl;
}

/**
 * Logs an informational message to the standard output
 * Used for general status updates during translation
 * @param message The information message to log
 */
void TranslatorUtils::logInfo(const std::string& message) {
    std::cout << "INFO: " << message << std::endl;
}

/**
 * Logs a debug message to the standard output
 * Used for detailed information helpful during development and debugging
 * @param message The debug message to log
 */
void TranslatorUtils::logDebug(const std::string& message) {
    std::cout << "DEBUG: " << message << std::endl;
}

/**
 * Converts a Pascal identifier to a C-compatible identifier
 * Handles differences in identifier rules between Pascal and C:
 * 1. Pascal identifiers are case-insensitive, while C identifiers are case-sensitive
 * 2. C has reserved keywords that might conflict with Pascal identifiers
 * 
 * @param pascalIdentifier The Pascal identifier to convert
 * @return A C-compatible identifier
 */
std::string TranslatorUtils::toCIdentifier(const std::string& pascalIdentifier) {
    // Convert Pascal identifiers to C identifiers
    // In Pascal, identifiers are case-insensitive, in C they are case-sensitive
    // We'll convert Pascal identifiers to lowercase in C to avoid issues

    std::string result = pascalIdentifier;

    // Convert to lowercase for consistency
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    // Check for C keywords and add underscore prefix if necessary
    // This prevents conflicts with reserved words in C
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
 * Escapes special characters in a string for C string literals
 * Ensures strings with special characters are properly escaped in the generated C code
 * 
 * @param str The string to escape
 * @return The escaped string
 */
std::string TranslatorUtils::escapeString(const std::string& str) {
    // Escape special characters in a string for C output
    std::string result;
    for (char c : str) {
        if (c == '\\') result += "\\\\";        // Backslash needs to be escaped
        else if (c == '\"') result += "\\\"";   // Double quote needs to be escaped
        else if (c == '\'') result += "\\\'";   // Single quote needs to be escaped
        else if (c == '\n') result += "\\n";    // Newline needs to be escaped
        else if (c == '\r') result += "\\r";    // Carriage return needs to be escaped
        else if (c == '\t') result += "\\t";    // Tab needs to be escaped
        else result += c;                        // Regular character, no escaping needed
    }
    return result;
}

/**
 * Checks if a string is a valid identifier in both Pascal and C
 * Valid identifiers start with a letter or underscore and can contain
 * letters, digits, and underscores
 * 
 * @param str The string to check
 * @return true if the string is a valid identifier, false otherwise
 */
bool TranslatorUtils::isValidIdentifier(const std::string& str) {
    // Check if a string is a valid identifier
    // In both Pascal and C, identifiers must start with a letter or underscore
    // and can contain letters, digits, and underscores
    
    // Empty strings are not valid identifiers
    if (str.empty()) {
        return false;
    }

    // First character must be a letter or underscore
    if (!std::isalpha(str[0]) && str[0] != '_') {
        return false;
    }

    // Remaining characters must be letters, digits, or underscores
    return std::all_of(str.begin() + 1, str.end(), [](char c) {
        return std::isalnum(c) || c == '_';
    });
}