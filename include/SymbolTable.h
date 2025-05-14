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
    ARRAY,
    STRING
};

namespace std {
    template <>
    struct hash<PascalType> {
        size_t operator()(PascalType pt) const noexcept {
            return static_cast<size_t>(pt);
        }
    };
}

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
    std::vector<SymbolEntry> parameters;  // To store parameters in order of declaration

  public:
    ScopeEntry(const std::string& name);
    bool addSymbol(const SymbolEntry& symbol);
    bool hasSymbol(const std::string& name) const;
    SymbolEntry& getSymbol(const std::string& name);
    const SymbolEntry& getSymbol(const std::string& name) const;
    std::map<std::string, SymbolEntry>& getSymbols();
    const std::map<std::string, SymbolEntry>& getSymbols() const;
    std::string getScopeName() const;
    // Add parameter to ordered list (for procedures and functions)
    void addParameter(const SymbolEntry& param);
    // Get parameters in order
    const std::vector<SymbolEntry>& getParameters() const;
    // Get mutable reference to parameters vector for modification
    std::vector<SymbolEntry>& getParameters();
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
    bool hasScope(const std::string& scopeName) const;
    const ScopeEntry& getScope(const std::string& scopeName) const;

    // Symbol management
    bool addSymbol(const SymbolEntry& symbol);
    bool hasSymbolInCurrentScope(const std::string& name) const;
    bool hasSymbol(const std::string& name) const;
    SymbolEntry& getSymbol(const std::string& name);
    const SymbolEntry& getSymbol(const std::string& name) const;
};