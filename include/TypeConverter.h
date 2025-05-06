#pragma once

#include <string>
#include <unordered_map>

#include "SymbolTable.h"

class TypeConverter {
  private:
    std::unordered_map<PascalType, std::string> typeMap;

public:
    TypeConverter();

    // Convert a Pascal-S type to a C type
    std::string convertType(PascalType type) const;

    // Convert a Pascal-S type with array dimensions to a C type
    std::string convertArrayType(PascalType elementType, const std::vector<ArrayBounds>& dimensions) const;

    // Convert a Pascal-S expression operator to a C operator
    std::string convertOperator(const std::string& op) const;

    // Convert a Pascal-S boolean value to a C boolean value
    std::string convertBooleanValue(const std::string& value) const;
};
