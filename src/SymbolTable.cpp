#include "../include/SymbolTable.h"

#include "../include/TranslatorUtils.h"

// ScopeEntry implementation
ScopeEntry::ScopeEntry(const std::string& name) : scopeName(name) {}

bool ScopeEntry::addSymbol(const SymbolEntry& symbol) {
    if (hasSymbol(symbol.name)) {
        return false;
    }
    symbols[symbol.name] = symbol;
    return true;
}

bool ScopeEntry::hasSymbol(const std::string& name) const {
    return symbols.find(name) != symbols.end();
}

SymbolEntry& ScopeEntry::getSymbol(const std::string& name) {
    if (!hasSymbol(name)) {
        throw TranslatorException("Symbol '" + name + "' not found in scope '" + scopeName + "'");
    }
    return symbols[name];
}

const SymbolEntry& ScopeEntry::getSymbol(const std::string& name) const {
    if (!hasSymbol(name)) {
        throw TranslatorException("Symbol '" + name + "' not found in scope '" + scopeName + "'");
    }
    return symbols.at(name);
}

std::map<std::string, SymbolEntry>& ScopeEntry::getSymbols() {
    return symbols;
}

const std::map<std::string, SymbolEntry>& ScopeEntry::getSymbols() const {
    return symbols;
}

std::string ScopeEntry::getScopeName() const {
    return scopeName;
}

// SymbolTable implementation
SymbolTable::SymbolTable() : currentScopeIndex(-1) {
    // Initialize with global scope
    enterScope("global");
}

void SymbolTable::enterScope(const std::string& scopeName) {
    scopes.push_back(std::make_unique<ScopeEntry>(scopeName));
    currentScopeIndex = scopes.size() - 1;
}

void SymbolTable::exitScope() {
    if (currentScopeIndex <= 0) {
        throw TranslatorException("Cannot exit global scope");
    }
    currentScopeIndex--;
}

bool SymbolTable::isInGlobalScope() const {
    return currentScopeIndex == 0;
}

ScopeEntry& SymbolTable::getCurrentScope() {
    return *scopes[currentScopeIndex];
}

const ScopeEntry& SymbolTable::getCurrentScope() const {
    return *scopes[currentScopeIndex];
}

bool SymbolTable::addSymbol(const SymbolEntry& symbol) {
    return getCurrentScope().addSymbol(symbol);
}

bool SymbolTable::hasSymbolInCurrentScope(const std::string& name) const {
    return getCurrentScope().hasSymbol(name);
}

bool SymbolTable::hasSymbol(const std::string& name) const {
    // Check all scopes from current to global
    for (int i = currentScopeIndex; i >= 0; i--) {
        if (scopes[i]->hasSymbol(name)) {
            return true;
        }
    }
    return false;
}

SymbolEntry& SymbolTable::getSymbol(const std::string& name) {
    // Check all scopes from current to global
    for (int i = currentScopeIndex; i >= 0; i--) {
        if (scopes[i]->hasSymbol(name)) {
            return scopes[i]->getSymbol(name);
        }
    }
    throw TranslatorException("Symbol '" + name + "' not found in any accessible scope");
}

const SymbolEntry& SymbolTable::getSymbol(const std::string& name) const {
    // Check all scopes from current to global
    for (int i = currentScopeIndex; i >= 0; i--) {
        if (scopes[i]->hasSymbol(name)) {
            return scopes[i]->getSymbol(name);
        }
    }
    throw TranslatorException("Symbol '" + name + "' not found in any accessible scope");
}