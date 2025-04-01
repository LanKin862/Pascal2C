#include "../include/SymbolTable.h"

#include "../include/TranslatorUtils.h"

// ScopeEntry implementation

/**
 * Constructor for a scope entry
 * @param name The name of the scope (e.g., function name or "global")
 */
ScopeEntry::ScopeEntry(const std::string& name) : scopeName(name) {}

/**
 * Adds a symbol to the current scope
 * @param symbol The symbol entry to add
 * @return true if the symbol was added successfully, false if a symbol with the same name already exists
 */
bool ScopeEntry::addSymbol(const SymbolEntry& symbol) {
    // Check if symbol already exists in this scope
    if (hasSymbol(symbol.name)) {
        return false;
    }
    
    // Add the symbol to the map
    symbols[symbol.name] = symbol;
    
    // If this is a parameter, add it to the ordered parameter list
    // This is important for function calls to match arguments with parameters
    if (symbol.symbolType == SymbolType::PARAMETER) {
        addParameter(symbol);
    }
    
    return true;
}

/**
 * Adds a parameter to the ordered parameter list
 * This is separate from the symbol map to maintain parameter order
 * @param param The parameter symbol to add
 */
void ScopeEntry::addParameter(const SymbolEntry& param) {
    parameters.push_back(param);
}

/**
 * Gets the list of parameters for this scope
 * @return Const reference to the parameter list
 */
const std::vector<SymbolEntry>& ScopeEntry::getParameters() const {
    return parameters;
}

/**
 * Gets the list of parameters for this scope (mutable version)
 * @return Reference to the parameter list that can be modified
 */
std::vector<SymbolEntry>& ScopeEntry::getParameters() {
    return parameters;
}

/**
 * Checks if a symbol exists in this scope
 * @param name The name of the symbol to look for
 * @return true if the symbol exists in this scope, false otherwise
 */
bool ScopeEntry::hasSymbol(const std::string& name) const {
    return symbols.find(name) != symbols.end();
}

/**
 * Gets a symbol from this scope
 * @param name The name of the symbol to retrieve
 * @return Reference to the symbol entry
 * @throws TranslatorException if the symbol doesn't exist
 */
SymbolEntry& ScopeEntry::getSymbol(const std::string& name) {
    if (!hasSymbol(name)) {
        throw TranslatorException("Symbol '" + name + "' not found in scope '" + scopeName + "'");
    }
    return symbols[name];
}

/**
 * Gets a symbol from this scope (const version)
 * @param name The name of the symbol to retrieve
 * @return Const reference to the symbol entry
 * @throws TranslatorException if the symbol doesn't exist
 */
const SymbolEntry& ScopeEntry::getSymbol(const std::string& name) const {
    if (!hasSymbol(name)) {
        throw TranslatorException("Symbol '" + name + "' not found in scope '" + scopeName + "'");
    }
    return symbols.at(name);
}

/**
 * Gets all symbols in this scope
 * @return Reference to the map of all symbols
 */
std::map<std::string, SymbolEntry>& ScopeEntry::getSymbols() {
    return symbols;
}

/**
 * Gets all symbols in this scope (const version)
 * @return Const reference to the map of all symbols
 */
const std::map<std::string, SymbolEntry>& ScopeEntry::getSymbols() const {
    return symbols;
}

/**
 * Gets the name of this scope
 * @return The scope name
 */
std::string ScopeEntry::getScopeName() const {
    return scopeName;
}

// SymbolTable implementation

/**
 * Constructor for the symbol table
 * Initializes with a global scope by default
 */
SymbolTable::SymbolTable() : currentScopeIndex(-1) {
    // Initialize with global scope
    enterScope("global");
}

/**
 * Creates a new scope and makes it the current scope
 * Used when entering functions, procedures, or blocks
 * @param scopeName The name of the new scope
 */
void SymbolTable::enterScope(const std::string& scopeName) {
    scopes.push_back(std::unique_ptr<ScopeEntry>(new ScopeEntry(scopeName)));
    currentScopeIndex = scopes.size() - 1;
}

/**
 * Exits the current scope and returns to the parent scope
 * Used when leaving functions, procedures, or blocks
 * @throws TranslatorException if attempting to exit the global scope
 */
void SymbolTable::exitScope() {
    if (currentScopeIndex <= 0) {
        throw TranslatorException("Cannot exit global scope");
    }
    currentScopeIndex--;
}

/**
 * Checks if we're currently in the global scope
 * @return true if in global scope, false otherwise
 */
bool SymbolTable::isInGlobalScope() const {
    return currentScopeIndex == 0;
}

/**
 * Gets the current scope
 * @return Reference to the current scope entry
 */
ScopeEntry& SymbolTable::getCurrentScope() {
    return *scopes[currentScopeIndex];
}

/**
 * Gets the current scope (const version)
 * @return Const reference to the current scope entry
 */
const ScopeEntry& SymbolTable::getCurrentScope() const {
    return *scopes[currentScopeIndex];
}

/**
 * Checks if a scope with the given name exists
 * @param scopeName The name of the scope to look for
 * @return true if the scope exists, false otherwise
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
 * Gets a scope by name
 * Used to look up function/procedure scopes for parameter information
 * @param scopeName The name of the scope to retrieve
 * @return Const reference to the scope entry
 * @throws TranslatorException if the scope doesn't exist
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
 * Adds a symbol to the current scope
 * @param symbol The symbol entry to add
 * @return true if the symbol was added successfully, false if a symbol with the same name already exists
 */
bool SymbolTable::addSymbol(const SymbolEntry& symbol) {
    return getCurrentScope().addSymbol(symbol);
}

/**
 * Checks if a symbol exists in the current scope
 * @param name The name of the symbol to look for
 * @return true if the symbol exists in the current scope, false otherwise
 */
bool SymbolTable::hasSymbolInCurrentScope(const std::string& name) const {
    return getCurrentScope().hasSymbol(name);
}

/**
 * Checks if a symbol exists in the current scope or any parent scope
 * This implements Pascal's scoping rules for symbol visibility
 * @param name The name of the symbol to look for
 * @return true if the symbol exists in any accessible scope, false otherwise
 */
bool SymbolTable::hasSymbol(const std::string& name) const {
    // Check all scopes from current to global
    for (int i = currentScopeIndex; i >= 0; i--) {
        if (scopes[i]->hasSymbol(name)) {
            return true;
        }
    }
    return false;
}

/**
 * Gets a symbol from the current scope or any parent scope
 * Follows Pascal's scoping rules by searching from most local to global
 * @param name The name of the symbol to retrieve
 * @return Reference to the symbol entry
 * @throws TranslatorException if the symbol doesn't exist in any accessible scope
 */
SymbolEntry& SymbolTable::getSymbol(const std::string& name) {
    // Check all scopes from current to global
    for (int i = currentScopeIndex; i >= 0; i--) {
        if (scopes[i]->hasSymbol(name)) {
            return scopes[i]->getSymbol(name);
        }
    }
    throw TranslatorException("Symbol '" + name + "' not found in any accessible scope");
}

/**
 * Gets a symbol from the current scope or any parent scope (const version)
 * Follows Pascal's scoping rules by searching from most local to global
 * @param name The name of the symbol to retrieve
 * @return Const reference to the symbol entry
 * @throws TranslatorException if the symbol doesn't exist in any accessible scope
 */
const SymbolEntry& SymbolTable::getSymbol(const std::string& name) const {
    // Check all scopes from current to global
    for (int i = currentScopeIndex; i >= 0; i--) {
        if (scopes[i]->hasSymbol(name)) {
            return scopes[i]->getSymbol(name);
        }
    }
    throw TranslatorException("Symbol '" + name + "' not found in any accessible scope");
}