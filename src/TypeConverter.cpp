#include "../include/TypeConverter.h"

#include <sstream>

#include "../include/TranslatorUtils.h"


/**
 * TypeConverter类的构造函数
 * 初始化Pascal类型与其C等效项之间的映射
 */
TypeConverter::TypeConverter() {
    // 初始化从Pascal类型到C类型的映射
    typeMap[PascalType::INTEGER] = "int";        // Pascal INTEGER映射到C int
    typeMap[PascalType::REAL] = "float";         // Pascal REAL映射到C float
    typeMap[PascalType::BOOLEAN] = "int";        // Pascal BOOLEAN映射到C int（0表示false，非零表示true）
    typeMap[PascalType::CHAR] = "char";          // Pascal CHAR映射到C char
    typeMap[PascalType::ARRAY] = "";             // 数组根据元素类型和维度单独处理
}

/**
 * 将Pascal基本类型转换为其C等效项
 * @param type 要转换的Pascal类型
 * @return 相应的C类型，以字符串形式
 * @throws TranslatorException 如果Pascal类型未知
 */
std::string TypeConverter::convertType(PascalType type) const {
    // 在映射中查找Pascal类型
    auto it = typeMap.find(type);
    if (it == typeMap.end()) {
        throw TranslatorException("未知的Pascal类型");
    }
    return it->second;
}

/**
 * 将Pascal数组类型转换为其C等效项
 * 在Pascal中，数组可以有任意界限（例如，array[5..10] of integer）
 * 在C中，数组是从零开始的，大小是元素的数量
 * 
 * @param elementType 数组元素的Pascal类型
 * @param dimensions 每个维度的数组界限（下界和上界）向量
 * @return 相应的C数组类型，以字符串形式（例如，"int[6]"）
 */
std::string TypeConverter::convertArrayType(PascalType elementType, const std::vector<ArrayBounds>& dimensions) const {
    // 获取数组的基本类型（元素类型）
    std::string baseType = convertType(elementType);
    std::stringstream ss;
    ss << baseType;

    // 以C风格添加维度（例如，对于array[1..10] of integer，使用int[10]）
    // 对于每个维度，我们计算大小为(upperBound - lowerBound + 1)
    // 保持维度的顺序与它们在Pascal中出现的顺序相同
    for (const auto& dim : dimensions) {
        int size = dim.upperBound - dim.lowerBound + 1;
        ss << "[" << size << "]";
    }

    return ss.str();
}

/**
 * 将Pascal运算符转换为其C等效项
 * Pascal和C之间的许多运算符不同，特别是
 * 比较运算符和逻辑运算符
 * 
 * @param op Pascal运算符，以字符串形式
 * @return 相应的C运算符，以字符串形式
 */
std::string TypeConverter::convertOperator(const std::string& op) const {
    // 将Pascal运算符映射到C运算符
    if (op == "=") return "==";        // Pascal相等(=)变为C相等(==)
    if (op == "<>") return "!=";       // Pascal不等(<>)变为C不等(!=)
    if (op == "AND") return "&&";      // Pascal逻辑AND变为C逻辑AND(&&)
    if (op == "OR") return "||";       // Pascal逻辑OR变为C逻辑OR(||)
    if (op == "NOT") return "!";       // Pascal逻辑NOT变为C逻辑NOT(!)
    if (op == "DIV") return "/";       // Pascal整数除法(DIV)变为C除法(/)
    if (op == "MOD") return "%";       // Pascal模(MOD)变为C模(%)

    // 默认情况：返回不变的运算符（例如，+, -, *, /, <, >, <=, >=）
    return op;
}

/**
 * 将Pascal布尔字面量转换为其C等效项
 * Pascal使用TRUE/FALSE，而C使用1/0表示布尔值
 * 
 * @param value Pascal布尔值，以字符串形式
 * @return 相应的C布尔值，以字符串形式
 */
std::string TypeConverter::convertBooleanValue(const std::string& value) const {
    // 将Pascal布尔值转换为C布尔值
    if (value == "TRUE" || value == "true") {
        return "1";                    // Pascal TRUE变为C 1
    } else if (value == "FALSE" || value == "false") {
        return "0";                    // Pascal FALSE变为C 0
    }

    // 如果不是布尔字面量，则保持不变
    // 这处理计算为布尔值的变量和表达式
    return value;
}