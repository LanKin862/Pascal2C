#include "../include/TypeConverter.h"

#include <sstream>

#include "../include/TranslatorUtils.h"


/**
 * TypeConverter类的构造函数
 * 初始化Pascal类型与其C语言等效类型之间的映射
 */
TypeConverter::TypeConverter() {
    // 初始化从Pascal类型到C类型的映射
    typeMap[PascalType::INTEGER] = "int";        // Pascal INTEGER映射到C int
    typeMap[PascalType::REAL] = "float";         // Pascal REAL映射到C float
    typeMap[PascalType::BOOLEAN] = "int";        // Pascal BOOLEAN映射到C int (0表示false，非零表示true)
    typeMap[PascalType::CHAR] = "char";          // Pascal CHAR映射到C char
    typeMap[PascalType::ARRAY] = "";             // 数组根据元素类型和维度单独处理
}

/**
 * 将Pascal基本类型转换为其C语言等效类型
 * @param type 要转换的Pascal类型
 * @return 对应的C类型的字符串表示
 * @throws TranslatorException 如果Pascal类型未知
 */
std::string TypeConverter::convertType(PascalType type) const {
    // 在映射中查找Pascal类型
    auto it = typeMap.find(type);
    if (it == typeMap.end()) {
        throw TranslatorException("Unknown Pascal type");
    }
    return it->second;
}

/**
 * 将Pascal数组类型转换为其C语言等效类型
 * 在Pascal中，数组可以有任意边界（例如，array[5..10] of integer）
 * 在C中，数组是从零开始的，大小是元素的数量
 * 
 * @param elementType 数组元素的Pascal类型
 * @param dimensions 每个维度的数组边界（下界和上界）向量
 * @return 对应的C数组类型的字符串表示（例如，"int[6]"）
 */
std::string TypeConverter::convertArrayType(PascalType elementType, const std::vector<ArrayBounds>& dimensions) const {
    // 获取数组的基本类型（元素类型）
    std::string baseType = convertType(elementType);
    std::stringstream ss;
    ss << baseType;

    // 以C语言风格添加维度（例如，对于array[1..10] of integer，使用int[10]）
    // 对于每个维度，我们计算大小为(upperBound - lowerBound + 1)
    // 维度顺序与Pascal中的出现顺序相同
    for (const auto& dim : dimensions) {
        int size = dim.upperBound - dim.lowerBound + 1;
        ss << "[" << size << "]";
    }

    return ss.str();
}

/**
 * 将Pascal运算符转换为其C语言等效运算符
 * Pascal和C之间的许多运算符是不同的，特别是
 * 比较运算符和逻辑运算符
 * 
 * @param op Pascal运算符的字符串表示
 * @return 对应的C运算符的字符串表示
 */
std::string TypeConverter::convertOperator(const std::string& op) const {
    // 将Pascal运算符映射到C运算符
    if (op == "=") return "==";        // Pascal等于(=)变成C等于(==)
    if (op == "<>") return "!=";       // Pascal不等于(<>)变成C不等于(!=)
    if (op == "AND") return "&&";      // Pascal逻辑AND变成C逻辑AND(&&)
    if (op == "OR") return "||";       // Pascal逻辑OR变成C逻辑OR(||)
    if (op == "NOT") return "!";       // Pascal逻辑NOT变成C逻辑NOT(!)
    if (op == "DIV") return "/";       // Pascal整数除法(DIV)变成C除法(/)
    if (op == "MOD") return "%";       // Pascal模运算(MOD)变成C模运算(%)

    // 默认情况：保持运算符不变（例如，+, -, *, /, <, >, <=, >=）
    return op;
}

/**
 * 将Pascal布尔字面量转换为其C语言等效值
 * Pascal使用TRUE/FALSE，而C使用1/0表示布尔值
 * 
 * @param value Pascal布尔值的字符串表示
 * @return 对应的C布尔值的字符串表示
 */
std::string TypeConverter::convertBooleanValue(const std::string& value) const {
    // 将Pascal布尔值转换为C布尔值
    if (value == "TRUE" || value == "true") {
        return "1";                    // Pascal TRUE变成C 1
    } else if (value == "FALSE" || value == "false") {
        return "0";                    // Pascal FALSE变成C 0
    }

    // 如果它不是布尔字面量，保持不变
    // 这处理了计算结果为布尔值的变量和表达式
    return value;
}