#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

// 符号类型枚举，用于区分各种符号类型
enum class SymbolType {
    VARIABLE,
    CONSTANT,
    PROCEDURE,
    FUNCTION,
    PARAMETER
};

// Pascal-S 类型的基本类型枚举
enum class PascalType {
    INTEGER,
    REAL,
    BOOLEAN,
    CHAR,
    ARRAY,
    STRING
};

namespace std {
    template<>
    struct hash<PascalType> {
        size_t operator()(PascalType pt) const noexcept {
            return static_cast<size_t>(pt);
        }
    };
}

// 用于存储数组边界信息的结构体
struct ArrayBounds {
    int lowerBound;
    int upperBound;
};

// 符号表的符号条目
struct SymbolEntry {
    std::string name;
    SymbolType symbolType;
    PascalType dataType;
    bool isReference;                          // 用于 VAR 参数
    std::vector<ArrayBounds> arrayDimensions;  // 用于数组类型
    PascalType arrayElementType;               // 用于数组类型，元素的类型
    std::string value;                         // 用于常量
};

// 符号表的作用域条目
class ScopeEntry {
private:
    std::map<std::string, SymbolEntry> symbols;
    std::string scopeName;
    std::vector<SymbolEntry> parameters;  // 按声明顺序存储参数
    ScopeEntry *parentScope;

public:
    ScopeEntry(const std::string &name);

    ScopeEntry(const std::string &name, ScopeEntry *parent);

    bool addSymbol(const SymbolEntry &symbol);

    bool hasSymbol(const std::string &name) const;

    SymbolEntry &getSymbol(const std::string &name);

    const SymbolEntry &getSymbol(const std::string &name) const;

    std::map<std::string, SymbolEntry> &getSymbols();

    const std::map<std::string, SymbolEntry> &getSymbols() const;

    std::string getScopeName() const;

    // 将参数添加到有序列表（用于过程和函数）
    void addParameter(const SymbolEntry &param);

    // 按顺序获取参数
    const std::vector<SymbolEntry> &getParameters() const;

    // 获取参数向量的可变引用以进行修改
    std::vector<SymbolEntry> &getParameters();

    //设置父作用域
    void setParentScope(ScopeEntry *parent);

    // 获取父作用域
    ScopeEntry *getParentScope();
};

// 符号表类，用于管理符号和作用域
class SymbolTable {
private:
    std::vector<std::unique_ptr<ScopeEntry>> scopes;
    int currentScopeIndex;

public:
    SymbolTable();

    // 作用域管理
    void enterScope(const std::string &scopeName);

    void exitScope();

    bool isInGlobalScope() const;

    ScopeEntry &getCurrentScope();

    const ScopeEntry &getCurrentScope() const;

    bool hasScope(const std::string &scopeName) const;

    const ScopeEntry &getScope(const std::string &scopeName) const;

    // 符号管理
    bool addSymbol(const SymbolEntry &symbol);

    bool hasSymbolInCurrentScope(const std::string &name) const;

    bool hasSymbol(const std::string &name) const;

    SymbolEntry &getSymbol(const std::string &name);

    const SymbolEntry &getSymbol(const std::string &name) const;

    //设置父作用域
    void setCurrentScopeParent(ScopeEntry *parent);

    // 获取父作用域
    ScopeEntry &getParentScope();
};