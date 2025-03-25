#include "../include/TranslatorUtils.h"

#include <algorithm>
#include <cctype>
#include <regex>

void TranslatorUtils::logError(const std::string& message) {
    std::cerr << "ERROR: " << message << std::endl;
}

void TranslatorUtils::logWarning(const std::string& message) {
    std::cerr << "WARNING: " << message << std::endl;
}

void TranslatorUtils::logInfo(const std::string& message) {
    std::cout << "INFO: " << message << std::endl;
}

std::string TranslatorUtils::toCIdentifier(const std::string& pascalIdentifier) {
    // Convert Pascal identifiers to C identifiers
    // In Pascal, identifiers are case-insensitive, in C they are case-sensitive
    // We'll convert Pascal identifiers to lowercase in C to avoid issues

    std::string result = pascalIdentifier;

    // Convert to lowercase
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    // Check for C keywords and add underscore if necessary
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

std::string TranslatorUtils::escapeString(const std::string& str) {
    // Escape special characters in a string for C output
    std::string result;
    for (char c : str) {
        if (c == '\\') result += "\\\\";
        else if (c == '\"') result += "\\\"";
        else if (c == '\'') result += "\\\'";
        else if (c == '\n') result += "\\n";
        else if (c == '\r') result += "\\r";
        else if (c == '\t') result += "\\t";
        else result += c;
    }
    return result;
}

bool TranslatorUtils::isValidIdentifier(const std::string& str) {
    // Check if a string is a valid identifier
    // In both Pascal and C, identifiers must start with a letter or underscore
    // and can contain letters, digits, and underscores
    if (str.empty()) {
        return false;
    }

    if (!std::isalpha(str[0]) && str[0] != '_') {
        return false;
    }

    return std::all_of(str.begin() + 1, str.end(), [](char c) {
        return std::isalnum(c) || c == '_';
    });
}