#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

// Symbol type enum to differentiate between various symbol types
enum class SymbolType {
    VARIABLE,
    CONSTANT,
    PROCEDURE,
    FUNCTION,
    PARAMETER
};

// Basic type enum for Pascal-S types
enum class PascalType {
    INTEGER,
    REAL,
    BOOLEAN,
    CHAR,
    ARRAY
};

// Struct to store array bounds information
struct ArrayBounds {
    int lowerBound;
    int upperBound;
};

// Symbol entry for the symbol table
struct SymbolEntry {
    std::string name;
    SymbolType symbolType;
    PascalType dataType;
    bool isReference;                          // Used for VAR parameters
    std::vector<ArrayBounds> arrayDimensions;  // For array types
    PascalType arrayElementType;               // For array types, the type of elements
    std::string value;                         // For constants
};

// Scope entry for the symbol table
class ScopeEntry {
  private:
    std::map<std::string, SymbolEntry> symbols;
    std::string scopeName;

  public:
    ScopeEntry(const std::string& name);
    bool addSymbol(const SymbolEntry& symbol);
    bool hasSymbol(const std::string& name) const;
    SymbolEntry& getSymbol(const std::string& name);
    const SymbolEntry& getSymbol(const std::string& name) const;
    std::map<std::string, SymbolEntry>& getSymbols();
    const std::map<std::string, SymbolEntry>& getSymbols() const;
    std::string getScopeName() const;
};

// Symbol table class to manage symbols and scopes
class SymbolTable {
  private:
    std::vector<std::unique_ptr<ScopeEntry>> scopes;
    int currentScopeIndex;

  public:
    SymbolTable();

    // Scope management
    void enterScope(const std::string& scopeName);
    void exitScope();
    bool isInGlobalScope() const;
    ScopeEntry& getCurrentScope();
    const ScopeEntry& getCurrentScope() const;

    // Symbol management
    bool addSymbol(const SymbolEntry& symbol);
    bool hasSymbolInCurrentScope(const std::string& name) const;
    bool hasSymbol(const std::string& name) const;
    SymbolEntry& getSymbol(const std::string& name);
    const SymbolEntry& getSymbol(const std::string& name) const;
};