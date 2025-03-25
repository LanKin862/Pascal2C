#include "../include/TypeConverter.h"

#include <sstream>

#include "../include/TranslatorUtils.h"

TypeConverter::TypeConverter() {
    // Initialize the type mapping
    typeMap[PascalType::INTEGER] = "int";
    typeMap[PascalType::REAL] = "double";
    typeMap[PascalType::BOOLEAN] = "int";  // In C, boolean is typically represented as int
    typeMap[PascalType::CHAR] = "char";
    typeMap[PascalType::ARRAY] = "";  // Special case, handled separately
}

std::string TypeConverter::convertType(PascalType type) const {
    auto it = typeMap.find(type);
    if (it == typeMap.end()) {
        throw TranslatorException("Unknown Pascal type");
    }
    return it->second;
}

std::string TypeConverter::convertArrayType(PascalType elementType, const std::vector<ArrayBounds>& dimensions) const {
    std::string baseType = convertType(elementType);
    std::stringstream ss;
    ss << baseType;

    // Add dimensions in C style (e.g. int[10][20])
    for (const auto& dim : dimensions) {
        ss << "[" << (dim.upperBound - dim.lowerBound + 1) << "]";
    }

    return ss.str();
}

std::string TypeConverter::convertOperator(const std::string& op) const {
    // Map Pascal operators to C operators
    if (op == "=") return "==";
    if (op == "<>") return "!=";
    if (op == "AND") return "&&";
    if (op == "OR") return "||";
    if (op == "NOT") return "!";
    if (op == "DIV") return "/";  // Integer division in Pascal
    if (op == "MOD") return "%";

    // Default case: return the operator unchanged
    return op;
}

std::string TypeConverter::convertBooleanValue(const std::string& value) const {
    // Convert Pascal boolean values to C boolean values
    if (value == "TRUE" || value == "true") {
        return "1";
    } else if (value == "FALSE" || value == "false") {
        return "0";
    }

    // If it's not a boolean literal, return it unchanged
    return value;
}