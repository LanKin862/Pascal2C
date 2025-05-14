#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

/**
 * 符号类型枚举
 * 用于标识符号在符号表中的角色
 */
enum class SymbolType {
    VARIABLE,       // 变量
    CONSTANT,       // 常量
    FUNCTION,       // 函数
    PROCEDURE,      // 过程
    PARAMETER,      // 参数
    TYPE            // 类型定义
};

/**
 * Pascal类型枚举
 * 表示Pascal支持的基本数据类型
 */
enum class PascalType {
    INTEGER,        // 整数类型
    REAL,           // 实数类型
    BOOLEAN,        // 布尔类型
    CHAR,           // 字符类型
    ARRAY,          // 数组类型
    STRING,         // 字符串类型
};

namespace std {
    template <>
    struct hash<PascalType> {
        size_t operator()(PascalType pt) const noexcept {
            return static_cast<size_t>(pt);
        }
    };
}

/**
 * 数组边界结构
 * 存储数组类型的下界和上界
 */
struct ArrayBounds {
    int lowerBound;     // 数组下界
    int upperBound;     // 数组上界
};

/**
 * 符号条目结构
 * 存储关于符号的所有信息
 */
struct SymbolEntry {
    std::string name;    // 符号名称
    SymbolType symbolType;    // 符号类型（变量、常量、函数等）
    PascalType dataType;     // 数据类型（整数、实数、布尔等）
    bool isReference;                            // 是否是引用参数（用于VAR参数）
    std::vector<ArrayBounds> arrayDimensions;    // 数组维度（如果是数组类型）
    PascalType arrayElementType;
    std::string value;
};

/**
 * 作用域条目类
 * 表示符号表中的单个作用域（如全局作用域或函数作用域）
 */
class ScopeEntry {
private:
    std::string scopeName;                      // 作用域名称
    std::map<std::string, SymbolEntry> symbols; // 该作用域中的符号映射
    std::vector<SymbolEntry> parameters;        // 按顺序排列的参数（用于函数和过程）

public:
    ScopeEntry(const std::string& name);
    bool addSymbol(const SymbolEntry& symbol);
    bool hasSymbol(const std::string& name) const;
    SymbolEntry& getSymbol(const std::string& name);
    const SymbolEntry& getSymbol(const std::string& name) const;
    std::map<std::string, SymbolEntry>& getSymbols();
    const std::map<std::string, SymbolEntry>& getSymbols() const;
    std::string getScopeName() const;
    //将参数添加到有序列表中（对于过程和函数）
    void addParameter(const SymbolEntry& param);
    //按顺序获取参数
    const std::vector<SymbolEntry>& getParameters() const;
    //获取对参数vector的可变引用以进行修改
    std::vector<SymbolEntry>& getParameters();
};

/**
 * 符号表类
 * 管理嵌套作用域的符号信息
 */
class SymbolTable {
private:
    std::vector<std::unique_ptr<ScopeEntry>> scopes; // 作用域堆栈
    int currentScopeIndex;                          // 当前作用域索引

public:
    // 构造函数
    SymbolTable();

    // 作用域管理
    void enterScope(const std::string& scopeName);
    void exitScope();
    bool isInGlobalScope() const;
    ScopeEntry& getCurrentScope();
    const ScopeEntry& getCurrentScope() const;
    bool hasScope(const std::string& scopeName) const;
    const ScopeEntry& getScope(const std::string& scopeName) const;

    // 符号管理
    bool addSymbol(const SymbolEntry& symbol);
    bool hasSymbolInCurrentScope(const std::string& name) const;
    bool hasSymbol(const std::string& name) const;
    SymbolEntry& getSymbol(const std::string& name);
    const SymbolEntry& getSymbol(const std::string& name) const;
};