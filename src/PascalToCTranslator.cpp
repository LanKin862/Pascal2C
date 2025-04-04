#include "../include/PascalToCTranslator.h"

#include <antlr4-runtime.h>

#include <fstream>
#include <regex>

#include "../antlr/PascalSLexer.h"
#include "../antlr/PascalSParser.h"
#include "../include/TranslatorUtils.h"

/**
 * Constructor for the Pascal to C translator
 * Initializes the symbol table, type converter, and other state variables
 */
PascalToCTranslator::PascalToCTranslator() : symbolTable(std::make_unique<SymbolTable>()),
                                             typeConverter(std::make_unique<TypeConverter>()),
                                             indentation(""),
                                             isInGlobalScope(true),
                                             tempVarCounter(0) {
}

/**
 * Main translation method that converts Pascal code to C code
 * @param inputFile Path to the Pascal source file
 * @return String containing the translated C code
 */
std::string PascalToCTranslator::translate(const std::string &inputFile) {
    // Clear state for a fresh translation
    output.str("");
    indentation = "";
    isInGlobalScope = true;
    tempVarCounter = 0;

    // Set up ANTLR parser components
    std::ifstream stream;
    stream.open(inputFile);
    antlr4::ANTLRInputStream input(stream);
    PascalSLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    PascalSParser parser(&tokens);

    // Parse the input file to generate the AST
    PascalSParser::ProgramContext *tree = parser.program();

    // Visit the parse tree and generate C code
    try {
        visitProgram(tree);
    } catch (const TranslatorException &e) {
        TranslatorUtils::logError(e.what());
        return "";
    }

    // Return the generated C code
    return output.str();
}

/**
 * Increases the indentation level by one unit (4 spaces)
 */
void PascalToCTranslator::increaseIndentation() {
    indentation += "    ";
}

/**
 * Decreases the indentation level by one unit (4 spaces)
 * Ensures indentation doesn't go negative
 */
void PascalToCTranslator::decreaseIndentation() {
    if (!indentation.empty()) {
        indentation.resize(indentation.size() - 4);
    }
}

/**
 * Returns the current indentation string
 * @return Current indentation as a string of spaces
 */
std::string PascalToCTranslator::getCurrentIndentation() const {
    return indentation;
}

/**
 * Generates a unique temporary variable name
 * @return A string representing a new temporary variable
 */
std::string PascalToCTranslator::getNextTempVar() {
    return "temp_" + std::to_string(tempVarCounter++);
}

/**
 * Processes the program node, which is the root of the parse tree
 * Generates standard includes and helper functions needed by Pascal programs
 * @param context The program context from the parser
 * @return Standard placeholder for visitor pattern
 */
std::any PascalToCTranslator::visitProgram(PascalSParser::ProgramContext *context) {
    // Generate standard C includes needed for Pascal functionality
    output << "#include <stdio.h>\n";
    output << "#include <stdlib.h>\n";
    output << "#include <stdbool.h>\n";
    output << "#include <string.h>\n";
    output << "#include <stdarg.h>\n\n";

    // Define Pascal-specific types and helper functions
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

    // Visit the program structure node
    return visit(context->programStruct());
}

/**
 * Processes the program structure which consists of a header and body
 * @param context The program structure context from the parser
 * @return Standard placeholder for visitor pattern
 */
std::any PascalToCTranslator::visitProgramStruct(PascalSParser::ProgramStructContext *context) {
    // Visit the program header (name and parameters)
    visit(context->programHead());

    // Visit the program body (declarations and statements)
    visit(context->programBody());

    return std::any();
}

/**
 * Processes the program header which contains the program name
 * @param context The program header context from the parser
 * @return Standard placeholder for visitor pattern
 */
std::any PascalToCTranslator::visitProgramHead(PascalSParser::ProgramHeadContext *context) {
    // Extract the program name
    std::string programName = context->ID()->getText();

    // Add program name as a comment in the C code
    output << "// Program: " << programName << "\n\n";

    return std::any();
}

/**
 * Processes the program body which contains declarations and compound statements
 * @param context The program body context from the parser
 * @return Standard placeholder for visitor pattern
 */
std::any PascalToCTranslator::visitProgramBody(PascalSParser::ProgramBodyContext *context) {
    // Process constant declarations if present
    if (context->constDeclarations()) {
        visit(context->constDeclarations());
    }

    // Process variable declarations if present
    if (context->varDeclarations()) {
        visit(context->varDeclarations());
    }

    // First create forward declarations for all subprograms to handle function references
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

    // Process subprogram (function/procedure) declarations if present
    if (context->subprogramDeclarations()) {
        visit(context->subprogramDeclarations());
    }

    // Generate the main function
    output << "int main() {\n";
    increaseIndentation();

    // Visit the main program's compound statement
    if (context->compoundStatement()) {
        visit(context->compoundStatement());
    }

    // Add return statement to main
    output << getCurrentIndentation() << "return 0;\n";

    decreaseIndentation();
    output << "}\n";

    return std::any();
}

/**
 * Helper method to generate forward declarations for all functions and procedures
 * This is needed to handle function references and maintain proper parameter types
 * @param context The subprogram declarations context
 */
void PascalToCTranslator::generateForwardDeclarations(PascalSParser::SubprogramDeclarationsContext *context) {
    if (!context) return;

    // Then process any nested declarations first (earlier in source)
    if (context->subprogramDeclarations()) {
        generateForwardDeclarations(context->subprogramDeclarations());
    }
    // Process the current subprogram (later in source)
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
//                std::regex pattern(R"((\[)\d+(\]))");
//                params = std::regex_replace(params, pattern, "$1$2");
            }

            // Output forward declaration
            output << returnType << " " << name << params << ";\n";
            std:: cout << "Forward declaration for " << name << " generated\n";
        }
    }

}

/**
 * Processes an identifier list, used for variable and parameter declarations
 * @param context The identifier list context from the parser
 * @return Vector of C-compatible identifier strings
 */
std::any PascalToCTranslator::visitIdList(PascalSParser::IdListContext *context) {
    std::vector<std::string> ids;

    // Collect all identifiers and convert them to C-compatible names
    for (auto id : context->ID()) {
        ids.push_back(TranslatorUtils::toCIdentifier(id->getText()));
    }

    return ids;
}

/**
 * Processes constant declarations section
 * @param context The constant declarations context
 * @return Standard placeholder for visitor pattern
 */
std::any PascalToCTranslator::visitConstDeclarations(PascalSParser::ConstDeclarationsContext *context) {
    // Check if there are any constant declarations
    if (!context->constDeclaration()) {
        return std::any();
    }

    output << "// Constants\n";

    // Visit constant declaration nodes
    visit(context->constDeclaration());

    output << "\n";

    return std::any();
}

/**
 * Processes individual constant declarations
 * Converts Pascal constants to C #define statements
 * @param context The constant declaration context
 * @return Standard placeholder for visitor pattern
 */
std::any PascalToCTranslator::visitConstDeclaration(PascalSParser::ConstDeclarationContext *context) {
    // Get constant name and convert to C identifier
    std::string id = TranslatorUtils::toCIdentifier(context->ID()->getText());

    // Get constant value
    std::string value = std::any_cast<std::string>(visit(context->constValue()));

    // Output as a C preprocessor define
    output << "#define " << id << " " << value << "\n";

    // Add constant to symbol table
    SymbolEntry entry;
    entry.name = id;
    entry.symbolType = SymbolType::CONSTANT;
    entry.value = value;

    // Try to infer the type from the value's format
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

    // Process additional constant declarations if any (recursively)
    if (context->constDeclaration()) {
        visit(context->constDeclaration());
    }

    return std::any();
}

/**
 * Processes constant values including numbers, letters, and strings
 * @param context The constant value context
 * @return String representation of the constant value
 */
std::any PascalToCTranslator::visitConstValue(PascalSParser::ConstValueContext *context) {
    if (context->num()) {
        // Handle numeric constants, preserving sign
        if (context->PLUS()) {
            return "+" + context->num()->getText();
        } else if (context->MINUS()) {
            return "-" + context->num()->getText();
        } else {
            return context->num()->getText();
        }
    } else if (context->LETTER()) {
        // Handle character constants
        return context->LETTER()->getText();
    } else if (context->STRING()) {
        // Handle string constants
        return context->STRING()->getText();
    }

    return std::string("");
}

/**
 * Processes variable declarations section
 * @param context The variable declarations context
 * @return Standard placeholder for visitor pattern
 */
std::any PascalToCTranslator::visitVarDeclarations(PascalSParser::VarDeclarationsContext *context) {
    // Check if there are any variable declarations
    if (!context->varDeclaration()) {
        return std::any();
    }

    output << "// Variables\n";

    // Visit variable declaration nodes
    visit(context->varDeclaration());

    output << "\n";

    return std::any();
}

/**
 * Processes individual variable declarations
 * Converts Pascal variable declarations to C variable declarations with initialization
 * @param context The variable declaration context
 * @return Standard placeholder for visitor pattern
 */
std::any PascalToCTranslator::visitVarDeclaration(PascalSParser::VarDeclarationContext *context) {
    // Get list of variable identifiers
    std::vector<std::string> ids = std::any_cast<std::vector<std::string>>(visit(context->idList()));

    // Get type information
    auto typeResult = visit(context->type());

    // Initialize variables for type information
    std::string typeStr;
    PascalType pascalType;
    PascalType elementType = PascalType::INTEGER; // Default element type for arrays
    std::vector<ArrayBounds> dimensions;

    // Extract type information based on whether it's an array or basic type
    try {
        // Try to extract as a basic type first
        auto typePair = std::any_cast<std::pair<std::string, PascalType>>(typeResult);
        typeStr = typePair.first;
        pascalType = typePair.second;
    } catch (const std::bad_any_cast&) {
        // If not a basic type, it's an array type
        try {
            auto arrayTypeInfo = std::any_cast<std::tuple<std::string, PascalType, PascalType, std::vector<ArrayBounds>>>(typeResult);
            typeStr = std::get<0>(arrayTypeInfo);
            pascalType = std::get<1>(arrayTypeInfo);
            elementType = std::get<2>(arrayTypeInfo);
            dimensions = std::get<3>(arrayTypeInfo);

            // Because Pascal arrays are 1-indexed, we need to adjust the bounds to be 0-indexed
            for (int i = 0; i < typeStr.size(); i++) {
                if (typeStr[i] >= '0' && typeStr[i] <= '9') {
                    int tmp = typeStr[i] - '0' + 1;
                    typeStr[i] = '0' + tmp;
                }
            }
            for (auto &bounds : dimensions) {
                bounds.lowerBound--;
            }
        } catch (const std::bad_any_cast& e) {
            throw TranslatorException("Failed to extract type information: " + std::string(e.what()));
        }
    }

    // Output variable declarations for each identifier
    for (auto &id : ids) {
        // Handle array types with array dimensions in the type string
        std::regex pattern("\\[.*\\]");
        std::smatch matches;
        if (std::regex_search(typeStr, matches, pattern)) {
            // For array types, put the dimensions after the identifier
            std::string tmpId = id + std::string(matches[0]);
            std::string tmpTypeStr = std::regex_replace(typeStr, pattern, "");
            output << tmpTypeStr << " " << tmpId;

            // For multidimensional arrays, add initialization code to zero out all elements
            if (pascalType == PascalType::ARRAY && dimensions.size() > 1) {
                output << " = {0}";  // C99 and later support this syntax for zero initialization
            }
        } else {
            // For basic types, standard format
            output << typeStr << " " << id;
        }

        // Only add initialization for non-array types (arrays are more complex to initialize)
        if (pascalType != PascalType::ARRAY) {
            // Initialize with default values based on type
            if (pascalType == PascalType::INTEGER) {
                output << " = 0";
            } else if (pascalType == PascalType::REAL) {
                output << " = 0.0";
            } else if (pascalType == PascalType::BOOLEAN) {
                output << " = 0";  // false in C
            } else if (pascalType == PascalType::CHAR) {
                output << " = '\\0'";
            }
        } else if (dimensions.size() == 1) {
            // For single dimension arrays, add simple zero initialization
            output << " = {0}";  // C99 and later support this syntax for zero initialization
        }
        output << ";\n";

        // Add variable to symbol table for type checking and reference
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

    // Process additional variable declarations if any (recursively)
    if (context->varDeclaration()) {
        visit(context->varDeclaration());
    }

    return std::any();
}

/**
 * Processes type declarations, handling both basic types and arrays
 * @param context The type context
 * @return Type information as either a pair (for basic types) or tuple (for array types)
 */
std::any PascalToCTranslator::visitType(PascalSParser::TypeContext *context) {
    if (context->basicType() && context->ARRAY() == nullptr) {
        // Basic type (integer, real, boolean, char)
        auto result = visit(context->basicType());
        PascalType type = std::any_cast<PascalType>(result);
        std::string typeStr = typeConverter->convertType(type);
        return std::make_pair(typeStr, type);
    } else if (context->ARRAY()) {
        // Array type with dimensions
        auto basicTypeResult = visit(context->basicType());
        PascalType elementType = std::any_cast<PascalType>(basicTypeResult);

        // Get array dimensions (bounds)
        auto periodResult = visit(context->period());
        std::vector<ArrayBounds> dimensions = std::any_cast<std::vector<ArrayBounds>>(periodResult);

        // Convert to C array type using the type converter
        std::string arrayTypeStr = typeConverter->convertArrayType(elementType, dimensions);

        // Return array type, element type, and dimensions as a tuple
        return std::make_tuple(arrayTypeStr, PascalType::ARRAY, elementType, dimensions);
    }

    throw TranslatorException("Unknown type");
}

/**
 * Processes basic type keywords (INTEGER, REAL, BOOLEAN, CHAR)
 * @param context The basic type context
 * @return PascalType enum value representing the type
 */
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

/**
 * Processes array index range declarations (e.g., 1..10, 0..9)
 * @param context The period context containing range bounds
 * @return Vector of ArrayBounds structures with lower and upper bounds
 */
std::any PascalToCTranslator::visitPeriod(PascalSParser::PeriodContext *context) {
    std::vector<ArrayBounds> dimensions;
    std::vector<std::string> numStrings;
    std::string periodStr = context->getText();

    // Extract all pairs of numbers separated by DOTDOT (..)
    std::regex pattern(R"((\d+)\.\.(\d+))");  // 匹配 "数字..数字"
    std::smatch matches;

    auto begin = periodStr.cbegin();
    auto end = periodStr.cend();

    while (std::regex_search(begin, end, matches, pattern)) {
        numStrings.push_back(matches[1].str());  // 下界（如 "1"）
        numStrings.push_back(matches[2].str());  // 上界（如 "4"）
        begin = matches[0].second;           // 继续匹配剩余部分
    }
    // Convert bounds to integers and store in ArrayBounds structures
    for (int i = 0; i < numStrings.size(); i+=2) {
        if (i + 1 < numStrings.size()) {
            ArrayBounds bounds;
            bounds.lowerBound = std::stoi(numStrings[i]);
            bounds.upperBound = std::stoi(numStrings[i+1]);
            dimensions.push_back(bounds);
        }
    }
    return dimensions;
}

/**
 * Processes subprogram (function/procedure) declarations
 * @param context The subprogram declarations context
 * @return Standard placeholder for visitor pattern
 */
std::any PascalToCTranslator::visitSubprogramDeclarations(PascalSParser::SubprogramDeclarationsContext *context) {
    // Check if there are any subprogram declarations
    if (!context->subprogramDeclarations() && !context->subprogram()) {
        return std::any();
    }

    // First process the current subprogram declarations, which comes earlier in the source
    if (context->subprogramDeclarations()) {
        visit(context->subprogramDeclarations());
    }

    // Then process additional subprogram that come later in the source
    if (context->subprogram()) {
        visit(context->subprogram());
    }
    return std::any();
}

/**
 * Processes a single subprogram (function or procedure)
 * @param context The subprogram context
 * @return Standard placeholder for visitor pattern
 */
std::any PascalToCTranslator::visitSubprogram(PascalSParser::SubprogramContext *context) {
    // Visit subprogram head to generate function signature
    visit(context->subprogramHead());

    // Add opening brace for function body
    output << " {\n";
    increaseIndentation();

    // Visit subprogram body to generate function implementation
    visit(context->subprogramBody());

    // Add closing brace and extra newline
    decreaseIndentation();
    output << "}\n\n";

    return std::any();
}

/**
 * Processes a subprogram header (function or procedure declaration)
 * @param context The subprogram header context
 * @return Standard placeholder for visitor pattern
 */
std::any PascalToCTranslator::visitSubprogramHead(PascalSParser::SubprogramHeadContext *context) {
    // Get function/procedure name and convert to C identifier
    std::string name = TranslatorUtils::toCIdentifier(context->ID()->getText());

    // Determine if this is a function or procedure
    bool isFunction = context->FUNCTION() != nullptr;

    // Get return type for functions (procedures default to void)
    std::string returnType = "void";
    PascalType pascalReturnType = PascalType::INTEGER;  // Default

    if (isFunction) {
        auto result = visit(context->basicType());
        pascalReturnType = std::any_cast<PascalType>(result);
        returnType = typeConverter->convertType(pascalReturnType);
    }

    // Add function/procedure to the symbol table before entering its scope
    SymbolEntry entry;
    entry.name = name;
    entry.symbolType = isFunction ? SymbolType::FUNCTION : SymbolType::PROCEDURE;
    entry.dataType = pascalReturnType;
    symbolTable->addSymbol(entry);

    // Create a new scope for the function/procedure
    symbolTable->enterScope(name);

    // Output function/procedure declaration with return type and name
    output << returnType << " " << name;

    // Visit formal parameters section
    auto paramsResult = visit(context->formalParameter());
    std::string params = std::any_cast<std::string>(paramsResult);

    // In C, array parameters need proper pointer notation
    // For array dimensions, first dimension is always empty in function parameters
    std::regex arrayPattern("\\[(\\d+)\\]");
    std::regex multiDimPattern("\\[(\\d+)\\](\\[\\d+\\])+");

    // First find all multidimensional arrays and convert them properly
    std::smatch matches;
    std::string processedParams = params;
    std::string temp = processedParams;

    while (std::regex_search(temp, matches, multiDimPattern)) {
        std::string fullMatch = matches[0];

        // Extract the position and replace with proper C array notation
        // In C function parameters, first dimension is always empty: int[][10]
        size_t pos = processedParams.find(fullMatch);
        if (pos != std::string::npos) {
            std::string replacement = "[]" + fullMatch.substr(fullMatch.find("]") + 1);
            processedParams.replace(pos, fullMatch.length(), replacement);
        }

        // Continue search from after the current match
        temp = matches.suffix().str();
    }

    // Then handle single dimension arrays
//    processedParams = std::regex_replace(processedParams, arrayPattern, "[]");

    output << processedParams;

    return std::any();
}

/**
 * Processes formal parameter declarations for functions and procedures
 * @param context The formal parameter context
 * @return String representation of parameter list in C syntax
 */
std::any PascalToCTranslator::visitFormalParameter(PascalSParser::FormalParameterContext *context) {
    // Default empty parameter list
    if (!context->parameterList()) {
        return std::string("()");
    }

    // Visit parameter list to generate parameter declarations
    auto result = visit(context->parameterList());
    std::string params = std::any_cast<std::string>(result);

    return std::string("(") + params + ")";
}

/**
 * Processes a list of parameters
 * @param context The parameter list context
 * @return String representation of all parameters, comma-separated
 */
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
            if (param.empty()) paramList = moreParamsStr;
            else paramList = moreParamsStr + ", " + param;
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

/**
 * Processes a single parameter, which can be either by value or by reference (VAR)
 * @param context The parameter context
 * @return String representation of the parameter in C syntax
 */
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

/**
 * Processes a VAR parameter (by reference)
 * In Pascal, VAR parameters are passed by reference
 * In C, this is implemented using pointers
 * @param context The VAR parameter context
 * @return String representation of the parameter in C syntax with pointer notation
 */
std::any PascalToCTranslator::visitVarParameter(PascalSParser::VarParameterContext *context) {
    // Get value parameter string representation
    auto result = visit(context->valueParameter());
    std::string params = std::any_cast<std::string>(result);

    // Get identifiers from the context to mark them as reference parameters in the symbol table
    auto idListResult = visit(context->valueParameter()->idList());
    std::vector<std::string> ids = std::any_cast<std::vector<std::string>>(idListResult);

    // Debug output to verify parameter identifiers
    std::string idListStr;
    for (const auto& id : ids) {
        if (!idListStr.empty()) idListStr += ", ";
        idListStr += id;
    }
    TranslatorUtils::logDebug("VAR parameter identifiers: " + idListStr);

    // Also get type information to check for array types
    auto typeResult = visit(context->valueParameter()->type());

    // Initialize variables for type information
    std::string typeStr;
    PascalType pascalType;
    PascalType elementType = PascalType::INTEGER; // Default for arrays
    std::vector<ArrayBounds> dimensions;
    bool isArray = false;
    bool isMultidimensionalArray = false;

    // Extract type information based on whether it's an array or basic type
    try {
        // Try to extract as a basic type first
        auto typePair = std::any_cast<std::pair<std::string, PascalType>>(typeResult);
        typeStr = typePair.first;
        pascalType = typePair.second;
        isArray = (pascalType == PascalType::ARRAY);
    } catch (const std::bad_any_cast&) {
        // If it fails, it's an array type
        try {
            auto arrayTypeInfo = std::any_cast<std::tuple<std::string, PascalType, PascalType, std::vector<ArrayBounds>>>(typeResult);
            typeStr = std::get<0>(arrayTypeInfo);
            pascalType = std::get<1>(arrayTypeInfo);
            elementType = std::get<2>(arrayTypeInfo);
            dimensions = std::get<3>(arrayTypeInfo);
            isArray = true;
            isMultidimensionalArray = (dimensions.size() > 1);
        } catch (const std::bad_any_cast& e) {
            throw TranslatorException("Failed to extract type information: " + std::string(e.what()));
        }
    }

    // Mark all parameters as reference parameters in symbol table
    for (const auto& id : ids) {
        if (symbolTable->hasSymbolInCurrentScope(id)) {
            // Update the symbol in the symbol table
            SymbolEntry& entry = symbolTable->getSymbol(id);
            entry.isReference = true;

            // Check if the parameter is an array
            bool isArray = (entry.dataType == PascalType::ARRAY);
            bool isMultidim = (isArray && entry.arrayDimensions.size() > 1);
            TranslatorUtils::logDebug("  Marking " + id + " as reference parameter, isArray: " +
                                     (isArray ? "true" : "false") +
                                     ", isMultidimensional: " + (isMultidim ? "true" : "false"));

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

    // Add pointer (*) for reference parameters to the type part of the declaration
    // We need to handle multiple parameters in the chain
    std::stringstream ss;
    std::string baseTypeStr;
    size_t pos = params.find_first_of(" ");
    if (pos != std::string::npos) {
        baseTypeStr = params.substr(0, pos);
        std::string rest = params.substr(pos);

        // Split the rest into individual parameter declarations
        std::vector<std::string> paramDecls;
        size_t start = 0;
        size_t commaPos;
        while ((commaPos = rest.find(",", start)) != std::string::npos) {
            paramDecls.push_back(rest.substr(start, commaPos - start));
            start = commaPos + 2; // Skip ", "
        }
        paramDecls.push_back(rest.substr(start));

        // Extract the base type without array dimensions
        std::string baseType = baseTypeStr;
        size_t bracketPos = baseType.find('[');
        if (bracketPos != std::string::npos) {
            baseType = baseType.substr(0, bracketPos);
        }

        // Check if we're dealing with a multidimensional array
        std::vector<std::string> dimensionSizes;
        if (isMultidimensionalArray) {
            // Extract all dimension sizes for proper C array parameter declaration
            for (const auto& dim : dimensions) {
                int size = dim.upperBound - dim.lowerBound + 1 + 1;
                dimensionSizes.push_back(std::to_string(size));
            }
        }

        // Add pointer type to each parameter
        for (size_t i = 0; i < paramDecls.size(); ++i) {
            if (i > 0) ss << ", ";

            // Get the parameter's variable name
            size_t last_space_pos = paramDecls[i].rfind(' ');
            std::string paramName;
            if (last_space_pos != std::string::npos) {
                paramName = paramDecls[i].substr(last_space_pos + 1);
            } else {
                paramName = paramDecls[i];
            }

            // Handle based on whether it's an array parameter or not
            if (isArray) {
                if (isMultidimensionalArray) {
                    // For multidimensional arrays as parameters, use proper C syntax:
                    // For a 2D array: type (*param)[dim2]
                    // For a 3D array: type (*param)[dim2][dim3]
                    ss << baseType << " (*" << paramName << ")";

                    // Add all dimensions except the first, which is omitted in C array parameters
                    for (size_t j = 1; j < dimensionSizes.size(); ++j) {
                        ss << "[" << dimensionSizes[j] << "]";
                    }
                } else {
                    // For single dimension arrays, we can use the simpler notation
                    ss << baseType << " *" << paramName;
                }
            } else {
                // Non-array parameter - regular pointer
                ss << baseType << "* " << paramName;
            }
        }
    } else {
        // If we can't find a space, just add the pointer to the whole string
        ss << params << "*";
    }

    return ss.str();
}

/**
 * Processes a value parameter (by value)
 * In Pascal, regular parameters are passed by value
 * @param context The value parameter context
 * @return String representation of the parameter in C syntax
 */
std::any PascalToCTranslator::visitValueParameter(PascalSParser::ValueParameterContext *context) {
    // Get identifiers
    std::vector<std::string> ids = std::any_cast<std::vector<std::string>>(visit(context->idList()));

    // Debug output for parameter identifiers
    std::string idListStr;
    for (const auto& id : ids) {
        if (!idListStr.empty()) idListStr += ", ";
        idListStr += id;
    }
    TranslatorUtils::logDebug("Value parameter identifiers: " + idListStr);

    // Get type information
    auto typeResult = visit(context->type());

    // Initialize variables for type information
    std::string typeStr;
    PascalType pascalType;
    PascalType elementType = PascalType::INTEGER; // Default for arrays
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

        // Add parameter to symbol table
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

/**
 * Processes a subprogram body which contains declarations and statements
 * @param context The subprogram body context
 * @return Standard placeholder for visitor pattern
 */
std::any PascalToCTranslator::visitSubprogramBody(PascalSParser::SubprogramBodyContext *context) {
    // Process constant declarations if present
    if (context->constDeclarations()) {
        visit(context->constDeclarations());
    }

    // Process variable declarations if present
    if (context->varDeclarations()) {
        visit(context->varDeclarations());
    }

    // Process compound statement (main body of the function/procedure)
    if (context->compoundStatement()) {
        visit(context->compoundStatement());
    }

    // Exit the scope at the end of the subprogram
    symbolTable->exitScope();

    return std::any();
}

/**
 * Processes a compound statement (BEGIN ... END block)
 * @param context The compound statement context
 * @return Standard placeholder for visitor pattern
 */
std::any PascalToCTranslator::visitCompoundStatement(PascalSParser::CompoundStatementContext *context) {
    // Skip BEGIN and END tokens, just visit the statement list inside
    visit(context->statementList());

    return std::any();
}

/**
 * Processes a list of statements
 * @param context The statement list context
 * @return Standard placeholder for visitor pattern
 */
std::any PascalToCTranslator::visitStatementList(PascalSParser::StatementListContext *context) {
    // Visit additional statements first if any (earlier in source)
    if (context->statementList()) {
        visit(context->statementList());
    }

    // Visit the current statement (later in source)
    visit(context->statement());

    return std::any();
}

/**
 * Processes individual statements (assignment, procedure call, if, for, etc.)
 * @param context The statement context
 * @return Standard placeholder for visitor pattern
 */
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
            // Regular assignment to an identifier
            output << getCurrentIndentation() << id << " = " << expr << ";\n";
        }
    }
    // Assignment to variable (can be array element or another complex variable)
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
    // Compound statement (BEGIN ... END block)
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

/**
 * Processes an if statement and optional else part
 * @param context The if statement context
 * @return Standard placeholder for visitor pattern
 */
std::any PascalToCTranslator::visitIfStatement(PascalSParser::IfStatementContext *context) {
    // Get the condition expression
    auto condResult = visit(context->expression());
    std::string cond = std::any_cast<std::string>(condResult);

    // Output if statement with condition
    output << getCurrentIndentation() << "if (" << cond << ") {\n";
    increaseIndentation();

    // Visit the if-branch statement
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

/**
 * Processes a for statement (loop with counter)
 * @param context The for statement context
 * @return Standard placeholder for visitor pattern
 */
std::any PascalToCTranslator::visitForStatement(PascalSParser::ForStatementContext *context) {
    // Get loop counter variable
    std::string id = TranslatorUtils::toCIdentifier(context->ID()->getText());

    // Get initial value
    auto initResult = visit(context->expression(0));
    std::string init = std::any_cast<std::string>(initResult);

    // Get final value
    auto finalResult = visit(context->expression(1));
    std::string final = std::any_cast<std::string>(finalResult);

    // Output C-style for loop (Pascal for-loops are always incrementing by 1)
    output << getCurrentIndentation() << "for (" << id << " = " << init << "; " << id << " <= " << final << "; ++" << id << ") {\n";
    increaseIndentation();

    // Visit loop body statement
    visit(context->statement());

    decreaseIndentation();
    output << getCurrentIndentation() << "}\n";

    return std::any();
}

/**
 * Processes a read statement (input)
 * Translates to scanf calls in C
 * @param context The read statement context
 * @return Standard placeholder for visitor pattern
 */
std::any PascalToCTranslator::visitReadStatement(PascalSParser::ReadStatementContext *context) {
    try {
        // Get list of variables to read into
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

            // Look up the variable's type in the symbol table
            if (symbolTable->hasSymbol(baseVar)) {
                const SymbolEntry &entry = symbolTable->getSymbol(baseVar);
                std::string format;

                if (isArrayAccess && entry.dataType == PascalType::ARRAY) {
                    // Use the array element type for the format specifier
                    switch (entry.arrayElementType) {
                        case PascalType::INTEGER: format = "\"%d\""; break;
                        case PascalType::REAL: format = "\"%f\""; break;
                        case PascalType::CHAR: format = "\" %c\""; break;
                        case PascalType::BOOLEAN: format = "\"%d\""; break;
                        default: format = "\"%d\""; break;
                    }
                } else {
                    // Use the variable's own type for the format specifier
                    switch (entry.dataType) {
                        case PascalType::INTEGER: format = "\"%d\""; break;
                        case PascalType::REAL: format = "\"%f\""; break;
                        case PascalType::CHAR: format = "\" %c\""; break;
                        case PascalType::BOOLEAN: format = "\"%d\""; break;
                        default: format = "\"%s\""; break;
                    }
                }

                // For reference parameters that are not arrays, in the current scope, we don't need to use &
                // because they are already pointers in C
                if (entry.isReference && entry.symbolType == SymbolType::PARAMETER &&
                    !isArrayAccess && entry.dataType != PascalType::ARRAY &&
                    symbolTable->hasSymbolInCurrentScope(baseVar)) {
                    output << getCurrentIndentation() << "scanf(" << format << ", " << var << ");\n";
                } else {
                    // Regular variables need & to get their address for scanf
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

/**
 * Processes a while statement (loop with condition)
 * @param context The while statement context
 * @return Standard placeholder for visitor pattern
 */
std::any PascalToCTranslator::visitWhileStatement(PascalSParser::WhileStatementContext *context) {
    // Get the loop condition
    auto condResult = visit(context->expression());
    std::string cond = std::any_cast<std::string>(condResult);

    // Output while loop with condition
    output << getCurrentIndentation() << "while (" << cond << ") {\n";
    increaseIndentation();

    // Visit loop body statement
    visit(context->statement());

    decreaseIndentation();
    output << getCurrentIndentation() << "}\n";

    return std::any();
}

/**
 * Processes a write statement (output)
 * Translates to printf calls in C
 * @param context The write statement context
 * @return Standard placeholder for visitor pattern
 */
std::any PascalToCTranslator::visitWriteStatement(PascalSParser::WriteStatementContext *context) {
    auto result = visit(context->expressionList());
    std::vector<std::string> exprs = std::any_cast<std::vector<std::string>>(result);

    output << getCurrentIndentation() << "printf(";

    // Format string part of printf
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
            // Remove the single quotes from the expression and add double quotes for C string
            formattedArg = "\"" + expr.substr(1, expr.size() - 2) + "\"";
        } else if (expr.find('.') != std::string::npos) {
            // Floating point values use %f
            formatSpecifier = "%f";
        } else if (expr == "0" || expr == "1" || expr == "true" || expr == "false") {
            // Boolean values use %d (0/1 in C)
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

            // Look up variable type in symbol table
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

/**
 * Processes a list of variables for input/output or other operations
 * @param context The variable list context
 * @return Vector of string representations of variables in C syntax
 */
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

/**
 * Processes a variable identifier, which could be a simple variable or array element
 * Handles special cases like function result variables and reference parameters
 * @param context The variable context
 * @return String representation of the variable in C syntax or a special marker for function results
 */
std::any PascalToCTranslator::visitVariable(PascalSParser::VariableContext *context) {
    std::string id = TranslatorUtils::toCIdentifier(context->ID()->getText());

    // Check if the variable is a function name in the current scope
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

/**
 * Processes array indexing expressions for a variable
 * @param context The ID variable part context (array indexing)
 * @return String representation of the array indices in C syntax
 */
std::any PascalToCTranslator::visitIdVarPart(PascalSParser::IdVarPartContext *context) {
    // Empty array access
    if (!context->expressionList()) {
        return std::string("");
    }

    // Get array indices from expression list
    auto result = visit(context->expressionList());
    std::vector<std::string> indices = std::any_cast<std::vector<std::string>>(result);

    // Format array access with C-style indexing
    std::stringstream ss;
    for (const auto &index : indices) {
        ss << "[" << index << "]";
    }

    return ss.str();
}

/**
 * Processes a procedure call statement
 * @param context The procedure call context
 * @return String representation of the procedure call in C syntax
 */
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
            bool isMultidimensionalArray = false;

            // Fix parameter ordering issue: The parameters in the scope's parameters list are
            // stored in reverse order compared to how they appear in Pascal source.
            // So need to reverse the index to match the correct parameter.
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

                // Check if the argument is an array and if it's multidimensional
                if (symbolTable->hasSymbol(argBase)) {
                    const SymbolEntry& argEntry = symbolTable->getSymbol(argBase);
                    isArrayType = (argEntry.dataType == PascalType::ARRAY);
                    isMultidimensionalArray = (isArrayType && argEntry.arrayDimensions.size() > 1);

                    TranslatorUtils::logDebug("    Arg " + argBase + " is array: " + (isArrayType ? "true" : "false") +
                                             ", is multidimensional: " + (isMultidimensionalArray ? "true" : "false") +
                                             ", dimensions: " + std::to_string(argEntry.arrayDimensions.size()));
                }

                // Handle regular arrays and multidimensional arrays differently
                if (isArrayType) {
                    // If it's an array indexing operation, we need to check if we're passing a slice of the array
                    if (args[i].find('[') != std::string::npos) {
                        // Count the number of dimensions in the original array vs. the array access
                        int accessedDimensions = 0;
                        size_t pos = 0;
                        while ((pos = args[i].find('[', pos)) != std::string::npos) {
                            accessedDimensions++;
                            pos++;
                        }

                        // If using the parameter as an array, check dimensions
                        bool isFullyIndexed = false;
                        if (symbolTable->hasSymbol(argBase)) {
                            const SymbolEntry& argEntry = symbolTable->getSymbol(argBase);
                            isFullyIndexed = (accessedDimensions >= argEntry.arrayDimensions.size());
                        }

                        // If we're passing a slice or the parameter expects an array
                        if (!isFullyIndexed) {
                            // Pass the array element directly (it's a slice of the multidimensional array)
                            ss << args[i];
                        } else {
                            // Pass the fully indexed element (might need & if it's a VAR parameter)
                            if (isReferenceParam) {
                                ss << "&" << args[i];
                            } else {
                                ss << args[i];
                            }
                        }
                    } else {
                        // Passing the whole array - no & needed as arrays are passed by reference by default
                        ss << args[i];
                    }
                }
                // For non-array parameters that are passed by reference
                else if (isReferenceParam) {
                    ss << "&" << args[i];
                    TranslatorUtils::logDebug("  Adding & to " + args[i]);
                } else {
                    // Regular value parameter
                    ss << args[i];
                }
                std::cout << "arg :" << args[i] << std::endl;
            } else {
                // If we can't match parameters, just pass the argument as-is
                ss << args[i];
                std::cout << "can't match parameters, arg :" << args[i] << std::endl;
            }
        }

        ss << ")";

        return ss.str();
    }

    // Procedure call without arguments
    return id + "()";
}

/**
 * Processes the else part of an if statement
 * @param context The else part context
 * @return String representation of "else" (for consistency in visitor pattern)
 */
std::any PascalToCTranslator::visitElsePart(PascalSParser::ElsePartContext *context) {
    // Empty else part
    if (!context->statement()) {
        return std::string("");
    }

    // Visit else statement
    visit(context->statement());

    return std::string("else");
}

/**
 * Processes a list of expressions for function/procedure arguments or array indices
 * @param context The expression list context
 * @return Vector of string representations of expressions in C syntax
 */
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

/**
 * Processes an expression which can be a simple expression or a relational expression
 * @param context The expression context
 * @return String representation of the expression in C syntax
 */
std::any PascalToCTranslator::visitExpression(PascalSParser::ExpressionContext *context) {
    // Simple expression (no relational operator)
    if (!context->relop()) {
        return visit(context->simpleExpression(0));
    }

    // Relational expression (with comparison operator)
    auto leftResult = visit(context->simpleExpression(0));
    std::string left = std::any_cast<std::string>(leftResult);

    auto relopResult = visit(context->relop());
    std::string op = std::any_cast<std::string>(relopResult);

    auto rightResult = visit(context->simpleExpression(1));
    std::string right = std::any_cast<std::string>(rightResult);

    // Parenthesize the comparison for safety
    return std::string("(") + left + " " + op + " " + right + ")";
}

/**
 * Processes a simple expression which can be a term or additive expressions
 * @param context The simple expression context
 * @return String representation of the simple expression in C syntax
 */
std::any PascalToCTranslator::visitSimpleExpression(PascalSParser::SimpleExpressionContext *context) {
    // Single term (no additive operator)
    if (!context->addop()) {
        return visit(context->term());
    }

    // Expression with additive operator (+ - OR)
    auto leftResult = visit(context->simpleExpression());
    std::string left = std::any_cast<std::string>(leftResult);

    auto addopResult = visit(context->addop());
    std::string op = std::any_cast<std::string>(addopResult);

    auto rightResult = visit(context->term());
    std::string right = std::any_cast<std::string>(rightResult);

    // Parenthesize the expression for correct precedence
    return std::string("(") + left + " " + op + " " + right + ")";
}

/**
 * Processes a term which can be a factor or multiplicative expressions
 * @param context The term context
 * @return String representation of the term in C syntax
 */
std::any PascalToCTranslator::visitTerm(PascalSParser::TermContext *context) {
    // Single factor (no multiplicative operator)
    if (!context->mulop()) {
        return visit(context->factor());
    }

    // Term with multiplicative operator (* / DIV MOD AND)
    auto leftResult = visit(context->term());
    std::string left = std::any_cast<std::string>(leftResult);

    auto mulopResult = visit(context->mulop());
    std::string op = std::any_cast<std::string>(mulopResult);

    auto rightResult = visit(context->factor());
    std::string right = std::any_cast<std::string>(rightResult);

    // Parenthesize the expression for correct precedence
    return std::string("(") + left + " " + op + " " + right + ")";
}

/**
 * Processes a factor, which can be a constant, variable, expression, function call, or unary operation
 * @param context The factor context
 * @return String representation of the factor in C syntax
 */
std::any PascalToCTranslator::visitFactor(PascalSParser::FactorContext *context) {
    // Number literal
    if (context->num()) {
        return visit(context->num());
    }
    // Variable (can be simple variable or array element)
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
            bool isMultidimensionalArray = false;

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

                // Check if the argument is an array and if it's multidimensional
                if (symbolTable->hasSymbol(argBase)) {
                    const SymbolEntry& argEntry = symbolTable->getSymbol(argBase);
                    isArrayType = (argEntry.dataType == PascalType::ARRAY);
                    isMultidimensionalArray = (isArrayType && argEntry.arrayDimensions.size() > 1);

                    TranslatorUtils::logDebug("    Arg " + argBase + " is array: " + (isArrayType ? "true" : "false") +
                                             ", is multidimensional: " + (isMultidimensionalArray ? "true" : "false") +
                                             ", dimensions: " + std::to_string(argEntry.arrayDimensions.size()));
                }

                // Handle regular arrays and multidimensional arrays differently
                if (isArrayType) {
                    // If it's an array indexing operation, we need to check if we're passing a slice of the array
                    if (args[i].find('[') != std::string::npos) {
                        // Count the number of dimensions in the original array vs. the array access
                        int accessedDimensions = 0;
                        size_t pos = 0;
                        while ((pos = args[i].find('[', pos)) != std::string::npos) {
                            accessedDimensions++;
                            pos++;
                        }

                        // If using the parameter as an array, check dimensions
                        bool isFullyIndexed = false;
                        if (symbolTable->hasSymbol(argBase)) {
                            const SymbolEntry& argEntry = symbolTable->getSymbol(argBase);
                            isFullyIndexed = (accessedDimensions >= argEntry.arrayDimensions.size());
                        }

                        // If we're passing a slice or the parameter expects an array
                        if (!isFullyIndexed) {
                            // Pass the array element directly (it's a slice of the multidimensional array)
                            ss << args[i];
                        } else {
                            // Pass the fully indexed element (might need & if it's a VAR parameter)
                            if (isReferenceParam) {
                                ss << "&" << args[i];
                            } else {
                                ss << args[i];
                            }
                        }
                    } else {
                        // Passing the whole array - no & needed as arrays are passed by reference by default
                        ss << args[i];
                    }
                }
                // For non-array parameters that are passed by reference
                else if (isReferenceParam &&
                         args[i].find('[') == std::string::npos &&
                         args[i].find('(') == std::string::npos &&
                         !args[i].empty() && args[i][0] != '*') {
                    ss << "&" << args[i];
                    TranslatorUtils::logDebug("  Adding & to " + args[i]);
                } else {
                    // Regular value parameter
                    ss << args[i];
                }
            } else {
                // If we can't match parameters, just pass the argument as-is
                ss << args[i];
            }
        }

        ss << ")";
        std::cout << "function call :" << ss.str() << std::endl;

        return ss.str();
    }
    // Function call without parentheses (for Pascal functions with no parameters)
    else if (context->ID() && !context->expressionList()) {
        std::string id = TranslatorUtils::toCIdentifier(context->ID()->getText());

        // Check if this ID is a function in the symbol table
        if (symbolTable->hasSymbol(id)) {
            const SymbolEntry& entry = symbolTable->getSymbol(id);

            // If it's a function and it has a scope (meaning it's a function declaration, not a variable)
            if (entry.symbolType == SymbolType::FUNCTION && symbolTable->hasScope(id)) {
                const ScopeEntry& scope = symbolTable->getScope(id);
                // Check if the function has no parameters
                if (scope.getParameters().empty()) {
                    // This is a parameter-less function call without parentheses
                    // In C, we need to add the parentheses
                    return id + "()";
                }
            }
        }

        // If not recognized as a function with no parameters, treat as a regular variable
        return id;
    }
    // Logical NOT operation
    else if (context->NOT()) {
        auto result = visit(context->factor());
        std::string factor = std::any_cast<std::string>(result);

        return std::string("!(") + factor + ")";
    }
    // Unary minus operation
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

/**
 * Processes a numeric literal
 * @param context The num context
 * @return String representation of the number
 */
std::any PascalToCTranslator::visitNum(PascalSParser::NumContext *context) {
    return context->NUM()->getText();
}

/**
 * Processes a relational operator (==, !=, <, <=, >, >=)
 * @param context The relop context
 * @return String representation of the operator in C syntax
 */
std::any PascalToCTranslator::visitRelop(PascalSParser::RelopContext *context) {
    if (context->EQUAL()) {
        return std::string("==");  // Pascal = becomes == in C
    } else if (context->NOTEQUAL()) {
        return std::string("!=");  // Pascal <> becomes != in C
    } else if (context->LT()) {
        return std::string("<");   // Pascal < same in C
    } else if (context->LE()) {
        return std::string("<=");  // Pascal <= same in C
    } else if (context->GT()) {
        return std::string(">");   // Pascal > same in C
    } else if (context->GE()) {
        return std::string(">=");  // Pascal >= same in C
    }

    return std::string("");
}

/**
 * Processes an additive operator (+, -, OR)
 * @param context The addop context
 * @return String representation of the operator in C syntax
 */
std::any PascalToCTranslator::visitAddop(PascalSParser::AddopContext *context) {
    if (context->PLUS()) {
        return std::string("+");   // Pascal + same in C
    } else if (context->MINUS()) {
        return std::string("-");   // Pascal - same in C
    } else if (context->OR()) {
        return std::string("||");  // Pascal OR becomes || in C
    }

    return std::string("");
}

/**
 * Processes a multiplicative operator (*, /, DIV, MOD, AND)
 * @param context The mulop context
 * @return String representation of the operator in C syntax
 */
std::any PascalToCTranslator::visitMulop(PascalSParser::MulopContext *context) {
    if (context->STAR()) {
        return std::string("*");   // Pascal * same in C
    } else if (context->SLASH()) {
        return std::string("/");   // Pascal / same in C (float division)
    } else if (context->DIV()) {
        return std::string("/");   // Pascal DIV becomes / in C (integer division)
    } else if (context->MOD()) {
        return std::string("%");   // Pascal MOD becomes % in C
    } else if (context->AND()) {
        return std::string("&&");  // Pascal AND becomes && in C
    }

    return std::string("");
}