#include "../include/PascalToCTranslator.h"

#include <antlr4-runtime.h>

#include <fstream>
#include <regex>

#include "../antlr/PascalSLexer.h"
#include "../antlr/PascalSParser.h"
#include "../include/TranslatorUtils.h"

PascalToCTranslator::PascalToCTranslator() : symbolTable(std::make_unique<SymbolTable>()),
                                             typeConverter(std::make_unique<TypeConverter>()),
                                             indentation(""),
                                             isInGlobalScope(true),
                                             tempVarCounter(0) {
}

std::string PascalToCTranslator::translate(const std::string &inputFile) {
    // Clear state
    output.str("");
    indentation = "";
    isInGlobalScope = true;
    tempVarCounter = 0;

    // Set up ANTLR
    std::ifstream stream;
    stream.open(inputFile);
    antlr4::ANTLRInputStream input(stream);
    PascalSLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    PascalSParser parser(&tokens);

    // Parse the input
    PascalSParser::ProgramContext *tree = parser.program();

    // Visit the parse tree
    try {
        visitProgram(tree);
    } catch (const TranslatorException &e) {
        TranslatorUtils::logError(e.what());
        return "";
    }

    // Return the generated C code
    return output.str();
}

void PascalToCTranslator::increaseIndentation() {
    indentation += "    ";
}

void PascalToCTranslator::decreaseIndentation() {
    if (!indentation.empty()) {
        indentation.resize(indentation.size() - 4);
    }
}

std::string PascalToCTranslator::getCurrentIndentation() const {
    return indentation;
}

std::string PascalToCTranslator::getNextTempVar() {
    return "temp_" + std::to_string(tempVarCounter++);
}

std::any PascalToCTranslator::visitProgram(PascalSParser::ProgramContext *context) {
    // Generate standard includes
    output << "#include <stdio.h>\n";
    output << "#include <stdlib.h>\n";
    output << "#include <stdbool.h>\n";
    output << "#include <string.h>\n";
    output << "#include <stdarg.h>\n\n";

    // Define Pascal-specific functions and types
    output << "// Pascal-specific functions and types\n";
    output << "typedef int boolean;\n";
    output << "typedef char *string;\n\n";
    output << "// Helper function for read/readln\n";
    output << "void read_value(const char* format, void* value) {\n";
    output << "    scanf(format, value);\n";
    output << "}\n\n";
    output << "// Helper function for write/writeln\n";
    output << "void write_value(const char* format, ...) {\n";
    output << "    va_list args;\n";
    output << "    va_start(args, format);\n";
    output << "    vprintf(format, args);\n";
    output << "    va_end(args);\n";
    output << "}\n\n";

    // Visit the program structure
    return visit(context->programStruct());
}

std::any PascalToCTranslator::visitProgramStruct(PascalSParser::ProgramStructContext *context) {
    // Visit the program header
    visit(context->programHead());

    // Visit the program body
    visit(context->programBody());

    return std::any();
}

std::any PascalToCTranslator::visitProgramHead(PascalSParser::ProgramHeadContext *context) {
    // Get the program name
    std::string programName = context->ID()->getText();

    // Add program name as a comment
    output << "// Program: " << programName << "\n\n";

    return std::any();
}

std::any PascalToCTranslator::visitProgramBody(PascalSParser::ProgramBodyContext *context) {
    // Visit const declarations
    if (context->constDeclarations()) {
        visit(context->constDeclarations());
    }

    // Visit var declarations
    if (context->varDeclarations()) {
        visit(context->varDeclarations());
    }
    
    // First create forward declarations for all subprograms to facilitate reference parameter detection
    if (context->subprogramDeclarations()) {
        // Create a temporary string stream to collect forward declarations
        std::stringstream forwardDeclsStream;
        std::stringstream tempOutput = std::move(output);
        output = std::move(forwardDeclsStream);
        
        output << "// Forward declarations\n";
        generateForwardDeclarations(context->subprogramDeclarations());
        output << "\n";
        
        // Restore the original output and add forward declarations
        std::string forwardDecls = output.str();
        output = std::move(tempOutput);
        output << forwardDecls;
    }

    // Visit subprogram declarations
    if (context->subprogramDeclarations()) {
        visit(context->subprogramDeclarations());
    }

    // Generate main function
    output << "int main() {\n";
    increaseIndentation();

    // Visit compound statement
    if (context->compoundStatement()) {
        visit(context->compoundStatement());
    }

    // Return 0
    output << getCurrentIndentation() << "return 0;\n";

    decreaseIndentation();
    output << "}\n";

    return std::any();
}

// Helper method to generate forward declarations
void PascalToCTranslator::generateForwardDeclarations(PascalSParser::SubprogramDeclarationsContext *context) {
    if (!context) return;
    
    // Process the current subprogram first (earlier in source)
    if (context->subprogram()) {
        PascalSParser::SubprogramHeadContext* headContext = context->subprogram()->subprogramHead();
        if (headContext) {
            std::string name = TranslatorUtils::toCIdentifier(headContext->ID()->getText());
            bool isFunction = headContext->FUNCTION() != nullptr;
            
            // Get return type for functions
            std::string returnType = "void";
            if (isFunction && headContext->basicType()) {
                auto result = visit(headContext->basicType());
                PascalType pascalReturnType = std::any_cast<PascalType>(result);
                returnType = typeConverter->convertType(pascalReturnType);
            }
            
            // Get parameters
            std::string params = "()";
            if (headContext->formalParameter()) {
                auto paramsResult = visit(headContext->formalParameter());
                params = std::any_cast<std::string>(paramsResult);

                // Clean up array brackets in parameters for forward declarations
                std::regex pattern("\\[.*?\\]");
                params = std::regex_replace(params, pattern, "");
            }
            
            // Output forward declaration
            output << returnType << " " << name << params << ";\n";
        }
    }
    
    // Then process any nested declarations (later in source)
    if (context->subprogramDeclarations()) {
        generateForwardDeclarations(context->subprogramDeclarations());
    }
}

std::any PascalToCTranslator::visitIdList(PascalSParser::IdListContext *context) {
    std::vector<std::string> ids;

    // Collect all identifiers
    for (auto id : context->ID()) {
        ids.push_back(TranslatorUtils::toCIdentifier(id->getText()));
    }

    return ids;
}

std::any PascalToCTranslator::visitConstDeclarations(PascalSParser::ConstDeclarationsContext *context) {
    // Check if there are any constant declarations
    if (!context->constDeclaration()) {
        return std::any();
    }

    output << "// Constants\n";

    // Visit const declaration
    visit(context->constDeclaration());

    output << "\n";

    return std::any();
}

std::any PascalToCTranslator::visitConstDeclaration(PascalSParser::ConstDeclarationContext *context) {
    // First constant declaration
    std::string id = TranslatorUtils::toCIdentifier(context->ID()->getText());
    std::string value = std::any_cast<std::string>(visit(context->constValue()));

    output << "#define " << id << " " << value << "\n";

    // Add to symbol table
    SymbolEntry entry;
    entry.name = id;
    entry.symbolType = SymbolType::CONSTANT;
    entry.value = value;

    // Try to infer the type from the value
    if (value.find('.') != std::string::npos) {
        entry.dataType = PascalType::REAL;
    } else if (value == "0" || value == "1") {
        entry.dataType = PascalType::BOOLEAN;
    } else if (value.length() >= 2 && value[0] == '\'' && value.back() == '\'') {
        entry.dataType = PascalType::CHAR;
    } else {
        entry.dataType = PascalType::INTEGER;
    }

    symbolTable->addSymbol(entry);

    // Process additional constant declarations if any
    if (context->constDeclaration()) {
        visit(context->constDeclaration());
    }

    return std::any();
}

std::any PascalToCTranslator::visitConstValue(PascalSParser::ConstValueContext *context) {
    if (context->num()) {
        if (context->PLUS()) {
            return "+" + context->num()->getText();
        } else if (context->MINUS()) {
            return "-" + context->num()->getText();
        } else {
            return context->num()->getText();
        }
    } else if (context->LETTER()) {
        return context->LETTER()->getText();
    } else if (context->STRING()) {
        return context->STRING()->getText();
    }

    return std::string("");
}

std::any PascalToCTranslator::visitVarDeclarations(PascalSParser::VarDeclarationsContext *context) {
    // Check if there are any variable declarations
    if (!context->varDeclaration()) {
        return std::any();
    }

    output << "// Variables\n";

    // Visit var declaration
    visit(context->varDeclaration());

    output << "\n";

    return std::any();
}

std::any PascalToCTranslator::visitVarDeclaration(PascalSParser::VarDeclarationContext *context) {
    // Get identifiers
    std::vector<std::string> ids = std::any_cast<std::vector<std::string>>(visit(context->idList()));

    // Get type
    auto typeResult = visit(context->type());
    
    // Initialize variables for type information
    std::string typeStr;
    PascalType pascalType;
    PascalType elementType = PascalType::INTEGER; // Default
    std::vector<ArrayBounds> dimensions;
    
    // Extract type information based on whether it's an array or basic type
    try {
        // Try to extract as a basic type first
        auto typePair = std::any_cast<std::pair<std::string, PascalType>>(typeResult);
        typeStr = typePair.first;
        pascalType = typePair.second;
    } catch (const std::bad_any_cast&) {
        // If it fails, it's an array type
        try {
            auto arrayTypeInfo = std::any_cast<std::tuple<std::string, PascalType, PascalType, std::vector<ArrayBounds>>>(typeResult);
            typeStr = std::get<0>(arrayTypeInfo);
            pascalType = std::get<1>(arrayTypeInfo);
            elementType = std::get<2>(arrayTypeInfo);
            dimensions = std::get<3>(arrayTypeInfo);
        } catch (const std::bad_any_cast& e) {
            throw TranslatorException("Failed to extract type information: " + std::string(e.what()));
        }
    }

    // Output variable declarations
    for (auto &id : ids) {
        // Output the variable declaration with its type
        std::regex pattern("\\[.*?\\]");
        std::smatch matches;
        if (std::regex_search(typeStr, matches, pattern)) {
            // Array type
            std::string tmpId = id + std::string(matches[0]);
            std::string tmpTypeStr = std::regex_replace(typeStr, pattern, "");
            output << tmpTypeStr << " " << tmpId;
        } else {
            // Basic type
            output << typeStr << " " << id;
        }
        // Only add initialization for non-array types
        if (pascalType != PascalType::ARRAY) {
            // Initialize with default values based on type
            if (pascalType == PascalType::INTEGER) {
                output << " = 0";
            } else if (pascalType == PascalType::REAL) {
                output << " = 0.0";
            } else if (pascalType == PascalType::BOOLEAN) {
                output << " = 0";  // false
            } else if (pascalType == PascalType::CHAR) {
                output << " = '\\0'";
            }
        }
        output << ";\n";

        // Add to symbol table
        SymbolEntry entry;
        entry.name = id;
        entry.symbolType = SymbolType::VARIABLE;
        entry.dataType = pascalType;
        
        // Store array-specific information if needed
        if (pascalType == PascalType::ARRAY) {
            entry.arrayElementType = elementType;
            entry.arrayDimensions = dimensions;
        }
        
        symbolTable->addSymbol(entry);
    }

    // Process additional variable declarations if any
    if (context->varDeclaration()) {
        visit(context->varDeclaration());
    }

    return std::any();
}

std::any PascalToCTranslator::visitType(PascalSParser::TypeContext *context) {
    if (context->basicType() && context->ARRAY() == nullptr) {
        auto result = visit(context->basicType());
        PascalType type = std::any_cast<PascalType>(result);
        std::string typeStr = typeConverter->convertType(type);
        return std::make_pair(typeStr, type);
    } else if (context->ARRAY()) {
        // Array type
        auto basicTypeResult = visit(context->basicType());
        PascalType elementType = std::any_cast<PascalType>(basicTypeResult);

        // Get array dimensions
        auto periodResult = visit(context->period());
        std::vector<ArrayBounds> dimensions = std::any_cast<std::vector<ArrayBounds>>(periodResult);

        // Convert to C array type
        std::string arrayTypeStr = typeConverter->convertArrayType(elementType, dimensions);

        // Return array type, element type, and dimensions
        return std::make_tuple(arrayTypeStr, PascalType::ARRAY, elementType, dimensions);
    }

    throw TranslatorException("Unknown type");
}

std::any PascalToCTranslator::visitBasicType(PascalSParser::BasicTypeContext *context) {
    if (context->INTEGER()) {
        return PascalType::INTEGER;
    } else if (context->REAL()) {
        return PascalType::REAL;
    } else if (context->BOOLEAN()) {
        return PascalType::BOOLEAN;
    } else if (context->CHAR()) {
        return PascalType::CHAR;
    }

    throw TranslatorException("Unknown basic type");
}

std::any PascalToCTranslator::visitPeriod(PascalSParser::PeriodContext *context) {
    std::vector<ArrayBounds> dimensions;

    // Parse NUM DOTDOT NUM
    for (int i = 0; i < context->NUM().size(); i += 2) {
        if (i + 1 < context->NUM().size()) {
            ArrayBounds bounds;
            bounds.lowerBound = std::stoi(context->NUM(i)->getText());
            bounds.upperBound = std::stoi(context->NUM(i + 1)->getText());
            dimensions.push_back(bounds);
        }
    }

    return dimensions;
}

std::any PascalToCTranslator::visitSubprogramDeclarations(PascalSParser::SubprogramDeclarationsContext *context) {
    // Check if there are any subprogram declarations
    if (!context->subprogramDeclarations() && !context->subprogram()) {
        return std::any();
    }

    // First process the current subprogram, which comes earlier in the source
    if (context->subprogram()) {
        visit(context->subprogram());
    }

    // Then process additional subprogram declarations that come later in the source
    if (context->subprogramDeclarations()) {
        visit(context->subprogramDeclarations());
    }

    return std::any();
}

std::any PascalToCTranslator::visitSubprogram(PascalSParser::SubprogramContext *context) {
    // Visit subprogram head
    visit(context->subprogramHead());

    // Add opening brace
    output << " {\n";
    increaseIndentation();

    // Visit subprogram body
    visit(context->subprogramBody());

    // Add closing brace
    decreaseIndentation();
    output << "}\n\n";

    return std::any();
}

std::any PascalToCTranslator::visitSubprogramHead(PascalSParser::SubprogramHeadContext *context) {
    // Get function/procedure name
    std::string name = TranslatorUtils::toCIdentifier(context->ID()->getText());

    bool isFunction = context->FUNCTION() != nullptr;

    // Get return type for functions
    std::string returnType = "void";
    PascalType pascalReturnType = PascalType::INTEGER;  // Default

    if (isFunction) {
        auto result = visit(context->basicType());
        pascalReturnType = std::any_cast<PascalType>(result);
        returnType = typeConverter->convertType(pascalReturnType);
    }

    // Add function/procedure to the current scope before entering the function's scope
    SymbolEntry entry;
    entry.name = name;
    entry.symbolType = isFunction ? SymbolType::FUNCTION : SymbolType::PROCEDURE;
    entry.dataType = pascalReturnType;
    symbolTable->addSymbol(entry);

    // Create a new scope for the function/procedure
    symbolTable->enterScope(name);

    // Output function/procedure declaration
    output << returnType << " " << name;

    // Visit formal parameters
    auto paramsResult = visit(context->formalParameter());
    std::string params = std::any_cast<std::string>(paramsResult);

    // In C, array parameters in function declarations should not include size specifications
    // Replace array size brackets with empty brackets
    std::regex pattern("\\[.*?\\]");
    params = std::regex_replace(params, pattern, "");
    
    output << params;

    return std::any();
}

std::any PascalToCTranslator::visitFormalParameter(PascalSParser::FormalParameterContext *context) {
    // Default empty parameter list
    if (!context->parameterList()) {
        return std::string("()");
    }

    // Visit parameter list
    auto result = visit(context->parameterList());
    std::string params = std::any_cast<std::string>(result);

    return std::string("(") + params + ")";
}

std::any PascalToCTranslator::visitParameterList(PascalSParser::ParameterListContext *context) {
    std::string paramList = "";
    
    // First process the current parameter
    auto result = visit(context->parameter());
    std::string param = std::any_cast<std::string>(result);
    
    TranslatorUtils::logDebug("Processing parameter: " + param);
    
    // Check if there are any nested parameters (which come earlier in the Pascal code)
    if (context->parameterList()) {
        auto moreParamsResult = visit(context->parameterList());
        std::string moreParamsStr = std::any_cast<std::string>(moreParamsResult);
        
        TranslatorUtils::logDebug("Earlier parameters: " + moreParamsStr);
        
        // Put the earlier parameters first in the list
        if (!moreParamsStr.empty()) {
            paramList = moreParamsStr + ", " + param;
            TranslatorUtils::logDebug("Combined parameters: " + paramList);
        } else {
            paramList = param;
        }
    } else {
        // No nested parameters, just return the current one
        paramList = param;
    }
    
    return paramList;
}

std::any PascalToCTranslator::visitParameter(PascalSParser::ParameterContext *context) {
    if (context->varParameter()) {
        TranslatorUtils::logDebug("Processing VAR parameter");
        return visit(context->varParameter());
    } else if (context->valueParameter()) {
        TranslatorUtils::logDebug("Processing value parameter");
        return visit(context->valueParameter());
    }

    return std::string("");
}

std::any PascalToCTranslator::visitVarParameter(PascalSParser::VarParameterContext *context) {
    // Get value parameter string representation
    auto result = visit(context->valueParameter());
    std::string params = std::any_cast<std::string>(result);
    
    // Get identifiers from the context to mark them as reference parameters in the symbol table
    auto idListResult = visit(context->valueParameter()->idList());
    std::vector<std::string> ids = std::any_cast<std::vector<std::string>>(idListResult);
    
    // Debug output
    std::string idListStr;
    for (const auto& id : ids) {
        if (!idListStr.empty()) idListStr += ", ";
        idListStr += id;
    }
    TranslatorUtils::logDebug("VAR parameter identifiers: " + idListStr);
    
    // Mark all parameters as reference parameters in symbol table
    for (const auto& id : ids) {
        if (symbolTable->hasSymbolInCurrentScope(id)) {
            // Update the symbol in the symbol table
            SymbolEntry& entry = symbolTable->getSymbol(id);
            entry.isReference = true;
            
            // Check if the parameter is an array
            bool isArray = (entry.dataType == PascalType::ARRAY);
            TranslatorUtils::logDebug("  Marking " + id + " as reference parameter, isArray: " + (isArray ? "true" : "false"));
            
            // Since we already have addSymbol automatically adding parameters,
            // we need to update the existing parameters in the scope's parameters list
            std::vector<SymbolEntry>& parameters = symbolTable->getCurrentScope().getParameters();
            for (auto& param : parameters) {
                if (param.name == id) {
                    param.isReference = true;
                    break;
                }
            }
        }
    }

    // Add pointer for reference parameters
    size_t pos = params.find_first_of(" ");
    if (pos != std::string::npos) {
        params.insert(pos, "*");
    }

    return params;
}

std::any PascalToCTranslator::visitValueParameter(PascalSParser::ValueParameterContext *context) {
    // Get identifiers
    std::vector<std::string> ids = std::any_cast<std::vector<std::string>>(visit(context->idList()));

    // Debug output
    std::string idListStr;
    for (const auto& id : ids) {
        if (!idListStr.empty()) idListStr += ", ";
        idListStr += id;
    }
    TranslatorUtils::logDebug("Value parameter identifiers: " + idListStr);

    // Get type
    auto typeResult = visit(context->type());
    
    // Initialize variables for type information
    std::string typeStr;
    PascalType pascalType;
    PascalType elementType = PascalType::INTEGER; // Default
    std::vector<ArrayBounds> dimensions;
    
    // Extract type information based on whether it's an array or basic type
    try {
        // Try to extract as a basic type first
        auto typePair = std::any_cast<std::pair<std::string, PascalType>>(typeResult);
        typeStr = typePair.first;
        pascalType = typePair.second;
    } catch (const std::bad_any_cast&) {
        // If it fails, it's an array type
        try {
            auto arrayTypeInfo = std::any_cast<std::tuple<std::string, PascalType, PascalType, std::vector<ArrayBounds>>>(typeResult);
            typeStr = std::get<0>(arrayTypeInfo);
            pascalType = std::get<1>(arrayTypeInfo);
            elementType = std::get<2>(arrayTypeInfo);
            dimensions = std::get<3>(arrayTypeInfo);
        } catch (const std::bad_any_cast& e) {
            throw TranslatorException("Failed to extract type information: " + std::string(e.what()));
        }
    }

    // Format parameters
    std::stringstream ss;
    for (size_t i = 0; i < ids.size(); ++i) {
        if (i > 0) {
            ss << ", ";
        }

        ss << typeStr << " " << ids[i];
        TranslatorUtils::logDebug("  Adding parameter: " + typeStr + " " + ids[i] + 
                                 ", type: " + (pascalType == PascalType::ARRAY ? "ARRAY" : 
                                             (pascalType == PascalType::INTEGER ? "INTEGER" : 
                                             (pascalType == PascalType::REAL ? "REAL" : 
                                             (pascalType == PascalType::BOOLEAN ? "BOOLEAN" : 
                                             (pascalType == PascalType::CHAR ? "CHAR" : "UNKNOWN"))))));

        // Add to symbol table
        SymbolEntry entry;
        entry.name = ids[i];
        entry.symbolType = SymbolType::PARAMETER;
        entry.dataType = pascalType;
        entry.isReference = false;  // Default is by value, will be updated if VAR parameter

        // Store array-specific information if needed
        if (pascalType == PascalType::ARRAY) {
            entry.arrayElementType = elementType;
            entry.arrayDimensions = dimensions;
            TranslatorUtils::logDebug(
                                     (elementType == PascalType::INTEGER ? "INTEGER" :
                                     (elementType == PascalType::REAL ? "REAL" : 
                                     (elementType == PascalType::BOOLEAN ? "BOOLEAN" : 
                                     (elementType == PascalType::CHAR ? "CHAR" : "UNKNOWN")))));
        }

        symbolTable->addSymbol(entry);
    }

    return ss.str();
}

std::any PascalToCTranslator::visitSubprogramBody(PascalSParser::SubprogramBodyContext *context) {
    // Visit const declarations
    if (context->constDeclarations()) {
        visit(context->constDeclarations());
    }

    // Visit var declarations
    if (context->varDeclarations()) {
        visit(context->varDeclarations());
    }

    // Visit compound statement
    if (context->compoundStatement()) {
        visit(context->compoundStatement());
    }

    // Exit the scope at the end of the subprogram
    symbolTable->exitScope();

    return std::any();
}

std::any PascalToCTranslator::visitCompoundStatement(PascalSParser::CompoundStatementContext *context) {
    // Skip BEGIN and END, visit statement list
    visit(context->statementList());

    return std::any();
}

std::any PascalToCTranslator::visitStatementList(PascalSParser::StatementListContext *context) {
    // Visit additional statements first if any
    if (context->statementList()) {
        visit(context->statementList());
    }

    // Visit the current statement
    visit(context->statement());

    return std::any();
}

std::any PascalToCTranslator::visitStatement(PascalSParser::StatementContext *context) {
    // Empty statement
    if (!context->variable() && !context->ID() && !context->procedureCall() && !context->compoundStatement() &&
        !context->ifStatement() && !context->forStatement() && !context->readStatement() &&
        !context->whileStatement() && !context->writeStatement()) {
        return std::any();
    }
    
    // Assignment to identifier (procedure or function result)
    if (context->ID() && context->ASSIGNOP()) {
        std::string id = TranslatorUtils::toCIdentifier(context->ID()->getText());

        auto exprResult = visit(context->expression());
        std::string expr = std::any_cast<std::string>(exprResult);

        // Get current scope name - if we're assigning to a function with the same name, it's a return
        std::string currentScopeName = symbolTable->getCurrentScope().getScopeName();

        if (currentScopeName == id) {
            // Pascal Function:=Value syntax translated to C return statement
            output << getCurrentIndentation() << "return " << expr << ";\n";
        } else {
            output << getCurrentIndentation() << id << " = " << expr << ";\n";
        }
    }
    // Assignment to variable
    else if (context->variable() && context->ASSIGNOP()) {
        auto varResult = visit(context->variable());
        
        // Check if this is a function result assignment
        try {
            if (varResult.type() == typeid(std::pair<std::string, std::string>)) {
                auto pair = std::any_cast<std::pair<std::string, std::string>>(varResult);
                if (pair.first == "FUNCTION_RESULT") {
                    // This is a function result assignment (Pascal function:=value)
                    auto exprResult = visit(context->expression());
                    std::string expr = std::any_cast<std::string>(exprResult);
                    
                    output << getCurrentIndentation() << "return " << expr << ";\n";
                    return std::any();
                }
            }
        } catch (const std::bad_any_cast& e) {
            // If there's a cast error, assume it's a regular variable assignment
            TranslatorUtils::logError("Warning: Type conversion issue in variable assignment: " + std::string(e.what()));
        }
        
        // Regular variable assignment - try with explicit string cast
        try {
            std::string var = std::any_cast<std::string>(varResult);
            auto exprResult = visit(context->expression());
            std::string expr = std::any_cast<std::string>(exprResult);

            output << getCurrentIndentation() << var << " = " << expr << ";\n";
        } catch (const std::bad_any_cast& e) {
            // If cast fails again, add error handling
            TranslatorUtils::logError("Error in variable assignment: " + std::string(e.what()));
        }
    }
    // Procedure call
    else if (context->procedureCall()) {
        auto result = visit(context->procedureCall());
        std::string call = std::any_cast<std::string>(result);

        output << getCurrentIndentation() << call << ";\n";
    }
    // Compound statement
    else if (context->compoundStatement()) {
        visit(context->compoundStatement());
    }
    // If statement
    else if (context->ifStatement()) {
        visit(context->ifStatement());
    }
    // For statement
    else if (context->forStatement()) {
        visit(context->forStatement());
    }
    // Read statement
    else if (context->readStatement()) {
        visit(context->readStatement());
    }
    // While statement
    else if (context->whileStatement()) {
        visit(context->whileStatement());
    }
    // Write statement
    else if (context->writeStatement()) {
        visit(context->writeStatement());
    }

    return std::any();
}

std::any PascalToCTranslator::visitIfStatement(PascalSParser::IfStatementContext *context) {
    auto condResult = visit(context->expression());
    std::string cond = std::any_cast<std::string>(condResult);

    output << getCurrentIndentation() << "if (" << cond << ") {\n";
    increaseIndentation();

    visit(context->statement());

    decreaseIndentation();
    output << getCurrentIndentation() << "}";

    // Visit else part if present
    if (context->elsePart()) {
        output << " else {\n";
        increaseIndentation();
        
        visit(context->elsePart());
        
        decreaseIndentation();
        output << getCurrentIndentation() << "}";
    }

    output << "\n";

    return std::any();
}

std::any PascalToCTranslator::visitForStatement(PascalSParser::ForStatementContext *context) {
    // Get loop variable
    std::string id = TranslatorUtils::toCIdentifier(context->ID()->getText());

    // Get initial value
    auto initResult = visit(context->expression(0));
    std::string init = std::any_cast<std::string>(initResult);

    // Get final value
    auto finalResult = visit(context->expression(1));
    std::string final = std::any_cast<std::string>(finalResult);

    // Output for loop
    output << getCurrentIndentation() << "for (" << id << " = " << init << "; " << id << " <= " << final << "; ++" << id << ") {\n";
    increaseIndentation();

    // Visit loop body
    visit(context->statement());

    decreaseIndentation();
    output << getCurrentIndentation() << "}\n";

    return std::any();
}

std::any PascalToCTranslator::visitReadStatement(PascalSParser::ReadStatementContext *context) {
    try {
        // Get variable list
        auto result = visit(context->variableList());
        std::vector<std::string> vars = std::any_cast<std::vector<std::string>>(result);

        // Output read statements for each variable
        for (const auto &var : vars) {
            // Check if it's an array access
            std::string baseVar = var;
            size_t bracketPos = var.find('[');
            bool isArrayAccess = false;
            
            if (bracketPos != std::string::npos) {
                baseVar = var.substr(0, bracketPos);
                isArrayAccess = true;
            }
            
            if (symbolTable->hasSymbol(baseVar)) {
                const SymbolEntry &entry = symbolTable->getSymbol(baseVar);
                std::string format;

                if (isArrayAccess && entry.dataType == PascalType::ARRAY) {
                    // Use the array element type for the format
                    switch (entry.arrayElementType) {
                        case PascalType::INTEGER: format = "\"%d\""; break;
                        case PascalType::REAL: format = "\"%f\""; break;
                        case PascalType::CHAR: format = "\" %c\""; break;
                        case PascalType::BOOLEAN: format = "\"%d\""; break;
                        default: format = "\"%d\""; break;
                    }
                } else {
                    // Use the variable's own type
                    switch (entry.dataType) {
                        case PascalType::INTEGER: format = "\"%d\""; break;
                        case PascalType::REAL: format = "\"%f\""; break;
                        case PascalType::CHAR: format = "\" %c\""; break;
                        case PascalType::BOOLEAN: format = "\"%d\""; break;
                        default: format = "\"%s\""; break;
                    }
                }

                // For reference parameters (not local variables) that are not arrays, in the current scope, we don't need to use &
                if (entry.isReference && entry.symbolType == SymbolType::PARAMETER && 
                    !isArrayAccess && entry.dataType != PascalType::ARRAY && 
                    symbolTable->hasSymbolInCurrentScope(baseVar)) {
                    output << getCurrentIndentation() << "scanf(" << format << ", " << var << ");\n";
                } else {
                    output << getCurrentIndentation() << "scanf(" << format << ", &" << var << ");\n";
                }
            } else {
                // Default to integer if type is unknown
                output << getCurrentIndentation() << "scanf(\"%d\", &" << var << ");\n";
            }
        }
    } catch (const std::bad_any_cast& e) {
        TranslatorUtils::logError("Type conversion error in read statement: " + std::string(e.what()));
    }

    return std::any();
}

std::any PascalToCTranslator::visitWhileStatement(PascalSParser::WhileStatementContext *context) {
    // Get condition
    auto condResult = visit(context->expression());
    std::string cond = std::any_cast<std::string>(condResult);

    // Output while loop
    output << getCurrentIndentation() << "while (" << cond << ") {\n";
    increaseIndentation();

    // Visit loop body
    visit(context->statement());

    decreaseIndentation();
    output << getCurrentIndentation() << "}\n";

    return std::any();
}

std::any PascalToCTranslator::visitWriteStatement(PascalSParser::WriteStatementContext *context) {
    auto result = visit(context->expressionList());
    std::vector<std::string> exprs = std::any_cast<std::vector<std::string>>(result);

    output << getCurrentIndentation() << "printf(";

    // Format string
    std::string formatStr = "\"";
    std::vector<std::string> formattedArgs;
    
    // Process expressions in the original Pascal order (already handled in visitExpressionList)
    for (size_t i = 0; i < exprs.size(); ++i) {
        std::string expr = exprs[i];
        std::string formatSpecifier;
        std::string formattedArg = expr;
        
        // Check if it's a string literal
        if (expr.size() >= 2 && expr[0] == '\'' && expr.back() == '\'') {
            formatSpecifier = "%s";
            // Remove the single quotes from the expression
            formattedArg = "\"" + expr.substr(1, expr.size() - 2) + "\"";
        } else if (expr.find('.') != std::string::npos) {
            formatSpecifier = "%f";
        } else if (expr == "0" || expr == "1" || expr == "true" || expr == "false") {
            formatSpecifier = "%d";
        } else {
            // Try to look up the type in the symbol table
            bool found = false;
            
            // Check if it's an array access (contains square brackets)
            std::string baseVar = expr;
            size_t bracketPos = expr.find('[');
            if (bracketPos != std::string::npos) {
                baseVar = expr.substr(0, bracketPos);
            }
            
            // Check for function call
            size_t parenPos = baseVar.find('(');
            if (parenPos != std::string::npos) {
                baseVar = baseVar.substr(0, parenPos);
            }
            
            if (symbolTable->hasSymbol(baseVar)) {
                const SymbolEntry &entry = symbolTable->getSymbol(baseVar);
                
                // Determine the format specifier based on the variable type
                if (entry.dataType == PascalType::ARRAY && bracketPos != std::string::npos) {
                    // Use the array element type for array accesses
                    switch (entry.arrayElementType) {
                        case PascalType::INTEGER: formatSpecifier = "%d"; found = true; break;
                        case PascalType::REAL: formatSpecifier = "%f"; found = true; break;
                        case PascalType::BOOLEAN: formatSpecifier = "%d"; found = true; break;
                        case PascalType::CHAR: formatSpecifier = "%c"; found = true; break;
                        default: break;
                    }
                } else {
                    // Use the variable's own type
                    switch (entry.dataType) {
                        case PascalType::INTEGER: formatSpecifier = "%d"; found = true; break;
                        case PascalType::REAL: formatSpecifier = "%f"; found = true; break;
                        case PascalType::BOOLEAN: formatSpecifier = "%d"; found = true; break;
                        case PascalType::CHAR: formatSpecifier = "%c"; found = true; break;
                        default: break;
                    }
                }
            }
            
            if (!found) formatSpecifier = "%d";  // Default to integer format
        }
        
        formatStr += formatSpecifier;
        formattedArgs.push_back(formattedArg);
    }
    
    formatStr += "\"";
    output << formatStr;

    // Arguments - keep them in the same order as they appear in the format string
    for (const auto &arg : formattedArgs) {
        output << ", " << arg;
    }

    output << ");\n";

    return std::any();
}

std::any PascalToCTranslator::visitVariableList(PascalSParser::VariableListContext *context) {
    std::vector<std::string> vars;

    // In Pascal, variables in a list appear from left to right in the source code,
    // but the ANTLR parser processes them in a way that the rightmost variable becomes
    // the current node and earlier variables are in the nested variableList.
    
    // First, process any earlier variables in the nested variableList
    if (context->variableList()) {
        auto earlierVars = visit(context->variableList());
        vars = std::any_cast<std::vector<std::string>>(earlierVars);
    }
    
    // Then add the current variable, which comes later in the source
    auto result = visit(context->variable());
    
    // Handle potential function return value marker
    if (result.type() == typeid(std::pair<std::string, std::string>)) {
        auto pair = std::any_cast<std::pair<std::string, std::string>>(result);
        vars.push_back(pair.second);  // Use the function name
    } else {
        // Regular variable
        vars.push_back(std::any_cast<std::string>(result));
    }

    return vars;
}

std::any PascalToCTranslator::visitVariable(PascalSParser::VariableContext *context) {
    std::string id = TranslatorUtils::toCIdentifier(context->ID()->getText());

    // Check if the variable is a function name in the current scope or any parent function scope
    // If so, we need to return special information to handle function results
    std::string currentScopeName = symbolTable->getCurrentScope().getScopeName();
    
    // Check if we're in a function and the variable name matches the function name
    if (id == currentScopeName) {
        // This is a function return value assignment (function:=value)
        std::pair<std::string, std::string> resultPair("FUNCTION_RESULT", id);
        return resultPair;
    }
    
    // Check if the variable is a reference parameter (not a local variable)
    bool isReferenceParam = false;
    bool isArray = false;
    
    if (symbolTable->hasSymbol(id)) {
        const SymbolEntry &entry = symbolTable->getSymbol(id);
        // Only consider as reference parameter if it's actually a parameter and marked as reference
        isReferenceParam = entry.isReference && entry.symbolType == SymbolType::PARAMETER;
        isArray = (entry.dataType == PascalType::ARRAY);
    }
    
    // Check if it's an array access
    std::string result;
    if (context->idVarPart()) {
        auto partResult = visit(context->idVarPart());
        std::string indices = std::any_cast<std::string>(partResult);
        
        // Only dereference reference parameters (not local variables) when they're used within the function they were passed to
        if (isReferenceParam && !isArray && symbolTable->hasSymbolInCurrentScope(id)) {
            // For non-array reference parameters, we need to dereference when accessing
            result = "(*" + id + ")" + indices;
        } else {
            result = id + indices;
        }
    } else {
        // Not an array access
        if (isReferenceParam && !isArray && symbolTable->hasSymbolInCurrentScope(id)) {
            // For non-array reference parameters, we need to dereference
            result = "*" + id;
        } else {
            result = id;
        }
    }

    return result;
}

std::any PascalToCTranslator::visitIdVarPart(PascalSParser::IdVarPartContext *context) {
    // Empty array access
    if (!context->expressionList()) {
        return std::string("");
    }

    // Get array indices
    auto result = visit(context->expressionList());
    std::vector<std::string> indices = std::any_cast<std::vector<std::string>>(result);

    // Format array access
    std::stringstream ss;
    for (const auto &index : indices) {
        ss << "[" << index << "]";
    }

    return ss.str();
}

std::any PascalToCTranslator::visitProcedureCall(PascalSParser::ProcedureCallContext *context) {
    std::string id = TranslatorUtils::toCIdentifier(context->ID()->getText());

    // Check if it's a procedure call with arguments
    if (context->expressionList()) {
        auto result = visit(context->expressionList());
        std::vector<std::string> args = std::any_cast<std::vector<std::string>>(result);

        // Format procedure call with arguments
        std::stringstream ss;
        ss << id << "(";

        // Get procedure definition if available to check for reference parameters
        bool hasProcedureSymbol = symbolTable->hasSymbol(id);
        std::vector<SymbolEntry> parameters;
        
        if (hasProcedureSymbol) {
            // Get the parameters for this procedure
            if (symbolTable->hasScope(id)) {
                const ScopeEntry& scope = symbolTable->getScope(id);
                parameters = scope.getParameters();
                
                // Debug output to verify parameters
                TranslatorUtils::logDebug("Procedure " + id + " parameters:");
                for (size_t i = 0; i < parameters.size(); ++i) {
                    TranslatorUtils::logDebug("  Param " + std::to_string(i) + ": " + parameters[i].name + 
                                             ", isRef: " + (parameters[i].isReference ? "true" : "false"));
                }
            }
        }

        for (size_t i = 0; i < args.size(); ++i) {
            if (i > 0) {
                ss << ", ";
            }

            // Check if this parameter should be passed by reference
            bool isReferenceParam = false;
            bool isArrayType = false;
            
            // Fix parameter ordering issue: The parameters in the scope's parameters list are 
            // stored in reverse order compared to how they appear in Pascal source.
            // We need to reverse the index to match the correct parameter.
            if (parameters.size() == args.size()) {
                // Calculate the correct parameter index (parameters are in reverse order)
                size_t paramIndex = parameters.size() - 1 - i;
                
                isReferenceParam = parameters[paramIndex].isReference;
                
                // Debug output to verify reference parameter detection
                TranslatorUtils::logDebug("  Checking arg " + std::to_string(i) + ": " + args[i] + 
                                         ", isRef: " + (isReferenceParam ? "true" : "false") +
                                         ", paramIndex: " + std::to_string(paramIndex));
                
                // Check if the argument is an array
                std::string argBase = args[i];
                size_t bracketPos = argBase.find('[');
                size_t parenPos = argBase.find('(');
                
                // Extract base variable name if it has array indexing or function call
                if (bracketPos != std::string::npos) {
                    argBase = argBase.substr(0, bracketPos);
                } else if (parenPos != std::string::npos) {
                    argBase = argBase.substr(0, parenPos);
                }
                
                // Check if the argument is an array
                if (symbolTable->hasSymbol(argBase)) {
                    const SymbolEntry& argEntry = symbolTable->getSymbol(argBase);
                    isArrayType = (argEntry.dataType == PascalType::ARRAY);
                    TranslatorUtils::logDebug("    Arg " + argBase + " is array: " + (isArrayType ? "true" : "false"));
                }
                
                // Add '&' for reference parameters that are not arrays and don't have array indexing or function call
                // Also don't add '&' if the expression already starts with a '*' (it's already a reference parameter being dereferenced)
                if (isReferenceParam && !isArrayType && 
                    args[i].find('[') == std::string::npos && 
                    args[i].find('(') == std::string::npos && 
                    !args[i].empty() && args[i][0] != '*') {
                    ss << "&" << args[i];
                    TranslatorUtils::logDebug("  Adding & to " + args[i]);
                } else {
                    ss << args[i];
                    if (isReferenceParam && isArrayType) {
                        TranslatorUtils::logDebug("  NOT adding & to array " + args[i]);
                    }
                }
            }
        }

        ss << ")";

        return ss.str();
    }

    // Procedure call without arguments
    return id + "()";
}

std::any PascalToCTranslator::visitElsePart(PascalSParser::ElsePartContext *context) {
    // Empty else part
    if (!context->statement()) {
        return std::string("");
    }

    // Visit else statement
    visit(context->statement());

    return std::string("else");
}

std::any PascalToCTranslator::visitExpressionList(PascalSParser::ExpressionListContext *context) {
    std::vector<std::string> exprs;

    try {
        // In Pascal, expressions in a list appear from left to right in the source code,
        // but the ANTLR parser processes them in a way that the rightmost expression becomes
        // the current node and earlier expressions are in the nested expressionList.
        
        // First, process any earlier expressions in the nested expressionList
        if (context->expressionList()) {
            auto earlierExprs = visit(context->expressionList());
            exprs = std::any_cast<std::vector<std::string>>(earlierExprs);
        }
        
        // Then add the current expression, which comes later in the source
        auto result = visit(context->expression());
        exprs.push_back(std::any_cast<std::string>(result));
    } catch (const std::bad_any_cast& e) {
        TranslatorUtils::logError("Type conversion error in expression list: " + std::string(e.what()));
    }

    return exprs;
}

std::any PascalToCTranslator::visitExpression(PascalSParser::ExpressionContext *context) {
    // Simple expression
    if (!context->relop()) {
        return visit(context->simpleExpression(0));
    }

    // Relational expression
    auto leftResult = visit(context->simpleExpression(0));
    std::string left = std::any_cast<std::string>(leftResult);

    auto relopResult = visit(context->relop());
    std::string op = std::any_cast<std::string>(relopResult);

    auto rightResult = visit(context->simpleExpression(1));
    std::string right = std::any_cast<std::string>(rightResult);

    return std::string("(") + left + " " + op + " " + right + ")";
}

std::any PascalToCTranslator::visitSimpleExpression(PascalSParser::SimpleExpressionContext *context) {
    // Single term
    if (!context->addop()) {
        return visit(context->term());
    }

    // Expression with additive operator
    auto leftResult = visit(context->simpleExpression());
    std::string left = std::any_cast<std::string>(leftResult);

    auto addopResult = visit(context->addop());
    std::string op = std::any_cast<std::string>(addopResult);

    auto rightResult = visit(context->term());
    std::string right = std::any_cast<std::string>(rightResult);

    return std::string("(") + left + " " + op + " " + right + ")";
}

std::any PascalToCTranslator::visitTerm(PascalSParser::TermContext *context) {
    // Single factor
    if (!context->mulop()) {
        return visit(context->factor());
    }

    // Term with multiplicative operator
    auto leftResult = visit(context->term());
    std::string left = std::any_cast<std::string>(leftResult);

    auto mulopResult = visit(context->mulop());
    std::string op = std::any_cast<std::string>(mulopResult);

    auto rightResult = visit(context->factor());
    std::string right = std::any_cast<std::string>(rightResult);

    return std::string("(") + left + " " + op + " " + right + ")";
}

std::any PascalToCTranslator::visitFactor(PascalSParser::FactorContext *context) {
    // Number
    if (context->num()) {
        return visit(context->num());
    }
    // Variable
    else if (context->variable()) {
        return visit(context->variable());
    }
    // Parenthesized expression
    else if (context->LPAREN() && context->expression()) {
        auto result = visit(context->expression());
        std::string expr = std::any_cast<std::string>(result);

        return std::string("(") + expr + ")";
    }
    // Function call
    else if (context->ID() && context->expressionList()) {
        std::string id = TranslatorUtils::toCIdentifier(context->ID()->getText());

        auto result = visit(context->expressionList());
        std::vector<std::string> args = std::any_cast<std::vector<std::string>>(result);

        // Format function call
        std::stringstream ss;
        ss << id << "(";

        // Get function definition if available to check for reference parameters
        bool hasFunctionSymbol = symbolTable->hasSymbol(id);
        std::vector<SymbolEntry> parameters;
        
        if (hasFunctionSymbol) {
            // Get the parameters for this function
            if (symbolTable->hasScope(id)) {
                const ScopeEntry& scope = symbolTable->getScope(id);
                parameters = scope.getParameters();
                
                // Debug output to verify parameters
                TranslatorUtils::logDebug("Function " + id + " parameters:");
                for (size_t i = 0; i < parameters.size(); ++i) {
                    TranslatorUtils::logDebug("  Param " + std::to_string(i) + ": " + parameters[i].name + 
                                             ", isRef: " + (parameters[i].isReference ? "true" : "false"));
                }
            }
        }

        for (size_t i = 0; i < args.size(); ++i) {
            if (i > 0) {
                ss << ", ";
            }

            // Check if this parameter should be passed by reference
            bool isReferenceParam = false;
            bool isArrayType = false;
            
            // Fix parameter ordering issue: The parameters in the scope's parameters list are 
            // stored in reverse order compared to how they appear in Pascal source.
            // We need to reverse the index to match the correct parameter.
            if (parameters.size() == args.size()) {
                // Calculate the correct parameter index (parameters are in reverse order)
                size_t paramIndex = parameters.size() - 1 - i;
                
                isReferenceParam = parameters[paramIndex].isReference;
                
                // Debug output to verify reference parameter detection
                TranslatorUtils::logDebug("  Checking arg " + std::to_string(i) + ": " + args[i] + 
                                         ", isRef: " + (isReferenceParam ? "true" : "false") +
                                         ", paramIndex: " + std::to_string(paramIndex));
                
                // Check if the argument is an array
                std::string argBase = args[i];
                size_t bracketPos = argBase.find('[');
                size_t parenPos = argBase.find('(');
                
                // Extract base variable name if it has array indexing or function call
                if (bracketPos != std::string::npos) {
                    argBase = argBase.substr(0, bracketPos);
                } else if (parenPos != std::string::npos) {
                    argBase = argBase.substr(0, parenPos);
                }
                
                // Check if the argument is an array
                if (symbolTable->hasSymbol(argBase)) {
                    const SymbolEntry& argEntry = symbolTable->getSymbol(argBase);
                    isArrayType = (argEntry.dataType == PascalType::ARRAY);
                    TranslatorUtils::logDebug("    Arg " + argBase + " is array: " + (isArrayType ? "true" : "false"));
                }
                
                // Add '&' for reference parameters that are not arrays and don't have array indexing or function call
                // Also don't add '&' if the expression already starts with a '*' (it's already a reference parameter being dereferenced)
                if (isReferenceParam && !isArrayType && 
                    args[i].find('[') == std::string::npos && 
                    args[i].find('(') == std::string::npos && 
                    !args[i].empty() && args[i][0] != '*') {
                    ss << "&" << args[i];
                    TranslatorUtils::logDebug("  Adding & to " + args[i]);
                } else {
                    ss << args[i];
                    if (isReferenceParam && isArrayType) {
                        TranslatorUtils::logDebug("  NOT adding & to array " + args[i]);
                    }
                }
            }
        }

        ss << ")";

        return ss.str();
    }
    // Negation
    else if (context->NOT()) {
        auto result = visit(context->factor());
        std::string factor = std::any_cast<std::string>(result);

        return std::string("!(") + factor + ")";
    }
    // Unary minus
    else if (context->MINUS()) {
        auto result = visit(context->factor());
        std::string factor = std::any_cast<std::string>(result);

        return std::string("-(") + factor + ")";
    }
    // String literal
    else if (context->STRING()) {
        return context->STRING()->getText();
    }
    // Character literal
    else if (context->LETTER()) {
        return context->LETTER()->getText();
    }

    return std::string("");
}

std::any PascalToCTranslator::visitNum(PascalSParser::NumContext *context) {
    return context->NUM()->getText();
}

std::any PascalToCTranslator::visitRelop(PascalSParser::RelopContext *context) {
    if (context->EQUAL()) {
        return std::string("==");
    } else if (context->NOTEQUAL()) {
        return std::string("!=");
    } else if (context->LT()) {
        return std::string("<");
    } else if (context->LE()) {
        return std::string("<=");
    } else if (context->GT()) {
        return std::string(">");
    } else if (context->GE()) {
        return std::string(">=");
    }

    return std::string("");
}

std::any PascalToCTranslator::visitAddop(PascalSParser::AddopContext *context) {
    if (context->PLUS()) {
        return std::string("+");
    } else if (context->MINUS()) {
        return std::string("-");
    } else if (context->OR()) {
        return std::string("||");
    }

    return std::string("");
}

std::any PascalToCTranslator::visitMulop(PascalSParser::MulopContext *context) {
    if (context->STAR()) {
        return std::string("*");
    } else if (context->SLASH()) {
        return std::string("/");
    } else if (context->DIV()) {
        return std::string("/");  // Integer division in C
    } else if (context->MOD()) {
        return std::string("%");
    } else if (context->AND()) {
        return std::string("&&");
    }

    return std::string("");
}