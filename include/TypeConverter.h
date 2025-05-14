#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "SymbolTable.h"

/**
 * TypeConverter类负责将Pascal类型和表达式转换为C语言等效形式
 */
class TypeConverter {
private:
    // Pascal类型到C类型的映射
    std::unordered_map<PascalType, std::string> typeMap;

public:
    // 构造函数初始化类型映射
    TypeConverter();

    // 将Pascal基本类型转换为C类型
    std::string convertType(PascalType type) const;

    // 将Pascal数组类型转换为C数组类型
    std::string convertArrayType(PascalType elementType, const std::vector<ArrayBounds>& dimensions) const;

    // 将Pascal运算符转换为C运算符
    std::string convertOperator(const std::string& op) const;

    // 将Pascal布尔值转换为C布尔值
    std::string convertBooleanValue(const std::string& value) const;
};
