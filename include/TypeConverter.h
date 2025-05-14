#pragma once

#include <string>
#include <unordered_map>

#include "SymbolTable.h"

class TypeConverter {
  private:
    std::unordered_map<PascalType, std::string> typeMap;

public:
    TypeConverter();

    // 将 Pascal-S 类型转换为 C 类型
    std::string convertType(PascalType type) const;

    // 将带数组维度的 Pascal-S 类型转换为 C 类型
    std::string convertArrayType(PascalType elementType, const std::vector<ArrayBounds>& dimensions) const;

    // 将 Pascal-S 表达式运算符转换为 C 运算符
    std::string convertOperator(const std::string& op) const;

    // 将 Pascal-S 布尔值转换为 C 布尔值
    std::string convertBooleanValue(const std::string& value) const;
};
