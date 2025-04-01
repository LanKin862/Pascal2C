#include "../include/TypeConverter.h"

#include <sstream>

#include "../include/TranslatorUtils.h"


/**
 * Constructor for the TypeConverter class
 * Initializes the mapping between Pascal types and their C equivalents
 */
TypeConverter::TypeConverter() {
    // Initialize the type mapping from Pascal types to C types
    typeMap[PascalType::INTEGER] = "int";        // Pascal INTEGER maps to C int
    typeMap[PascalType::REAL] = "float";         // Pascal REAL maps to C float
    typeMap[PascalType::BOOLEAN] = "int";        // Pascal BOOLEAN maps to C int (0 for false, non-zero for true)
    typeMap[PascalType::CHAR] = "char";          // Pascal CHAR maps to C char
    typeMap[PascalType::ARRAY] = "";             // Arrays are handled separately based on element type and dimensions
}

/**
 * Converts a Pascal basic type to its C equivalent
 * @param type The Pascal type to convert
 * @return The corresponding C type as a string
 * @throws TranslatorException if the Pascal type is unknown
 */
std::string TypeConverter::convertType(PascalType type) const {
    // Look up the Pascal type in the map
    auto it = typeMap.find(type);
    if (it == typeMap.end()) {
        throw TranslatorException("Unknown Pascal type");
    }
    return it->second;
}

/**
 * Converts a Pascal array type to its C equivalent
 * In Pascal, arrays can have arbitrary bounds (e.g., array[5..10] of integer)
 * In C, arrays are zero-based and the size is the number of elements
 * 
 * @param elementType The Pascal type of the array elements
 * @param dimensions Vector of array bounds (lower and upper) for each dimension
 * @return The corresponding C array type as a string (e.g., "int[6]")
 */
std::string TypeConverter::convertArrayType(PascalType elementType, const std::vector<ArrayBounds>& dimensions) const {
    // Get the base type (element type) for the array
    std::string baseType = convertType(elementType);
    std::stringstream ss;
    ss << baseType;

    // Add dimensions in C style (e.g., int[10] for array[1..10] of integer)
    // For each dimension, we calculate the size as (upperBound - lowerBound + 1)
    // Keep dimensions in the same order as they appear in Pascal
    for (const auto& dim : dimensions) {
        int size = dim.upperBound - dim.lowerBound + 1;
        ss << "[" << size << "]";
    }

    return ss.str();
}

/**
 * Converts Pascal operators to their C equivalents
 * Many operators are different between Pascal and C, especially
 * comparison operators and logical operators
 * 
 * @param op The Pascal operator as a string
 * @return The corresponding C operator as a string
 */
std::string TypeConverter::convertOperator(const std::string& op) const {
    // Map Pascal operators to C operators
    if (op == "=") return "==";        // Pascal equality (=) becomes C equality (==)
    if (op == "<>") return "!=";       // Pascal inequality (<>) becomes C inequality (!=)
    if (op == "AND") return "&&";      // Pascal logical AND becomes C logical AND (&&)
    if (op == "OR") return "||";       // Pascal logical OR becomes C logical OR (||)
    if (op == "NOT") return "!";       // Pascal logical NOT becomes C logical NOT (!)
    if (op == "DIV") return "/";       // Pascal integer division (DIV) becomes C division (/)
    if (op == "MOD") return "%";       // Pascal modulo (MOD) becomes C modulo (%)

    // Default case: return the operator unchanged (e.g., +, -, *, /, <, >, <=, >=)
    return op;
}

/**
 * Converts Pascal boolean literals to their C equivalents
 * Pascal uses TRUE/FALSE, while C uses 1/0 for boolean values
 * 
 * @param value The Pascal boolean value as a string
 * @return The corresponding C boolean value as a string
 */
std::string TypeConverter::convertBooleanValue(const std::string& value) const {
    // Convert Pascal boolean values to C boolean values
    if (value == "TRUE" || value == "true") {
        return "1";                    // Pascal TRUE becomes C 1
    } else if (value == "FALSE" || value == "false") {
        return "0";                    // Pascal FALSE becomes C 0
    }

    // If it's not a boolean literal, return it unchanged
    // This handles variables and expressions that evaluate to boolean
    return value;
}