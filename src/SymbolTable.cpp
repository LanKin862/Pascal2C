#include "../include/SymbolTable.h"

#include "../include/TranslatorUtils.h"

// ScopeEntry实现

/**
 * 作用域条目的构造函数
 * @param name 作用域的名称（例如，函数名或"global"）
 */
ScopeEntry::ScopeEntry(const std::string& name) : scopeName(name) {}

/**
 * 向当前作用域添加符号
 * @param symbol 要添加的符号条目
 * @return 如果符号成功添加则返回true，如果同名符号已存在则返回false
 */
bool ScopeEntry::addSymbol(const SymbolEntry& symbol) {
    // 检查符号是否已存在于此作用域
    if (hasSymbol(symbol.name)) {
        return false;
    }
    
    // 将符号添加到映射中
    symbols[symbol.name] = symbol;
    
    // 如果这是一个参数，将其添加到有序参数列表中
    // 这对函数调用匹配参数很重要
    if (symbol.symbolType == SymbolType::PARAMETER) {
        addParameter(symbol);
    }
    
    return true;
}

/**
 * 将参数添加到有序参数列表中
 * 这与符号映射分开，以维护参数顺序
 * @param param 要添加的参数符号
 */
void ScopeEntry::addParameter(const SymbolEntry& param) {
    parameters.push_back(param);
}

/**
 * 获取此作用域的参数列表
 * @return 参数列表的常量引用
 */
const std::vector<SymbolEntry>& ScopeEntry::getParameters() const {
    return parameters;
}

/**
 * 获取此作用域的参数列表（可变版本）
 * @return 可以修改的参数列表引用
 */
std::vector<SymbolEntry>& ScopeEntry::getParameters() {
    return parameters;
}

/**
 * 检查符号是否存在于此作用域
 * @param name 要查找的符号名称
 * @return 如果符号存在于此作用域则返回true，否则返回false
 */
bool ScopeEntry::hasSymbol(const std::string& name) const {
    return symbols.find(name) != symbols.end();
}

/**
 * 从此作用域获取符号
 * @param name 要检索的符号名称
 * @return 符号条目的引用
 * @throws TranslatorException 如果符号不存在
 */
SymbolEntry& ScopeEntry::getSymbol(const std::string& name) {
    if (!hasSymbol(name)) {
        throw TranslatorException("Symbol '" + name + "' not found in scope '" + scopeName + "'");
    }
    return symbols[name];
}

/**
 * 从此作用域获取符号（常量版本）
 * @param name 要检索的符号名称
 * @return 符号条目的常量引用
 * @throws TranslatorException 如果符号不存在
 */
const SymbolEntry& ScopeEntry::getSymbol(const std::string& name) const {
    if (!hasSymbol(name)) {
        throw TranslatorException("Symbol '" + name + "' not found in scope '" + scopeName + "'");
    }
    return symbols.at(name);
}

/**
 * 获取此作用域中的所有符号
 * @return 所有符号映射的引用
 */
std::map<std::string, SymbolEntry>& ScopeEntry::getSymbols() {
    return symbols;
}

/**
 * 获取此作用域中的所有符号（常量版本）
 * @return 所有符号映射的常量引用
 */
const std::map<std::string, SymbolEntry>& ScopeEntry::getSymbols() const {
    return symbols;
}

/**
 * 获取此作用域的名称
 * @return 作用域名称
 */
std::string ScopeEntry::getScopeName() const {
    return scopeName;
}

/**
 * 符号表的构造函数
 * 默认使用全局作用域初始化
 */
SymbolTable::SymbolTable() : currentScopeIndex(-1) {
    // 使用全局作用域初始化
    enterScope("global");
}

/**
 * 创建新作用域并使其成为当前作用域
 * 在进入函数、过程或块时使用
 * @param scopeName 新作用域的名称
 */
void SymbolTable::enterScope(const std::string& scopeName) {
    scopes.push_back(std::unique_ptr<ScopeEntry>(new ScopeEntry(scopeName)));
    currentScopeIndex = scopes.size() - 1;
}

/**
 * 退出当前作用域并返回到父作用域
 * 在离开函数、过程或块时使用
 * @throws TranslatorException 如果尝试退出全局作用域
 */
void SymbolTable::exitScope() {
    if (currentScopeIndex <= 0) {
        throw TranslatorException("Cannot exit global scope");
    }
    currentScopeIndex--;
}

/**
 * 检查当前是否在全局作用域中
 * @return 如果在全局作用域中则返回true，否则返回false
 */
bool SymbolTable::isInGlobalScope() const {
    return currentScopeIndex == 0;
}

/**
 * 获取当前作用域
 * @return 当前作用域条目的引用
 */
ScopeEntry& SymbolTable::getCurrentScope() {
    return *scopes[currentScopeIndex];
}

/**
 * 获取当前作用域（常量版本）
 * @return 当前作用域条目的常量引用
 */
const ScopeEntry& SymbolTable::getCurrentScope() const {
    return *scopes[currentScopeIndex];
}

/**
 * 检查给定名称的作用域是否存在
 * @param scopeName 要查找的作用域名称
 * @return 如果作用域存在则返回true，否则返回false
 */
bool SymbolTable::hasScope(const std::string& scopeName) const {
    for (const auto& scope : scopes) {
        if (scope->getScopeName() == scopeName) {
            return true;
        }
    }
    return false;
}

/**
 * 通过名称获取作用域
 * 用于查找函数/过程作用域以获取参数信息
 * @param scopeName 要检索的作用域名称
 * @return 作用域条目的常量引用
 * @throws TranslatorException 如果作用域不存在
 */
const ScopeEntry& SymbolTable::getScope(const std::string& scopeName) const {
    for (const auto& scope : scopes) {
        if (scope->getScopeName() == scopeName) {
            return *scope;
        }
    }
    throw TranslatorException("Scope '" + scopeName + "' not found");
}

/**
 * 向当前作用域添加符号
 * @param symbol 要添加的符号条目
 * @return 如果符号成功添加则返回true，如果同名符号已存在则返回false
 */
bool SymbolTable::addSymbol(const SymbolEntry& symbol) {
    return getCurrentScope().addSymbol(symbol);
}

/**
 * 检查符号是否存在于当前作用域
 * @param name 要查找的符号名称
 * @return 如果符号存在于当前作用域则返回true，否则返回false
 */
bool SymbolTable::hasSymbolInCurrentScope(const std::string& name) const {
    return getCurrentScope().hasSymbol(name);
}

/**
 * 检查符号是否存在于当前作用域或任何父作用域
 * 这实现了Pascal的符号可见性作用域规则
 * @param name 要查找的符号名称
 * @return 如果符号存在于任何可访问的作用域则返回true，否则返回false
 */
bool SymbolTable::hasSymbol(const std::string& name) const {
    // 从当前作用域到全局作用域检查所有作用域
    for (int i = currentScopeIndex; i >= 0; i--) {
        if (scopes[i]->hasSymbol(name)) {
            return true;
        }
    }
    return false;
}

/**
 * 从当前作用域或任何父作用域获取符号
 * 遵循Pascal的作用域规则，从最局部到全局进行搜索
 * @param name 要检索的符号名称
 * @return 符号条目的引用
 * @throws TranslatorException 如果符号在任何可访问的作用域中都不存在
 */
SymbolEntry& SymbolTable::getSymbol(const std::string& name) {
    // 从当前作用域到全局作用域检查所有作用域
    for (int i = currentScopeIndex; i >= 0; i--) {
        if (scopes[i]->hasSymbol(name)) {
            return scopes[i]->getSymbol(name);
        }
    }
    throw TranslatorException("Symbol '" + name + "' not found in any accessible scope");
}

/**
 * 从当前作用域或任何父作用域获取符号（常量版本）
 * 遵循Pascal的作用域规则，从最局部到全局进行搜索
 * @param name 要检索的符号名称
 * @return 符号条目的常量引用
 * @throws TranslatorException 如果符号在任何可访问的作用域中都不存在
 */
const SymbolEntry& SymbolTable::getSymbol(const std::string& name) const {
    // 从当前作用域到全局作用域检查所有作用域
    for (int i = currentScopeIndex; i >= 0; i--) {
        if (scopes[i]->hasSymbol(name)) {
            return scopes[i]->getSymbol(name);
        }
    }
    throw TranslatorException("Symbol '" + name + "' not found in any accessible scope");
}