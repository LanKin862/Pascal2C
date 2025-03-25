#include "../include/PascalToCTranslator.h"

#include <antlr4-runtime.h>

#include <fstream>

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
    std::pair<std::string, PascalType> typePair = std::any_cast<std::pair<std::string, PascalType>>(typeResult);
    std::string typeStr = typePair.first;
    PascalType pascalType = typePair.second;

    // Output variable declarations
    for (const auto &id : ids) {
        output << typeStr << " " << id;

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

        output << ";\n";

        // Add to symbol table
        SymbolEntry entry;
        entry.name = id;
        entry.symbolType = SymbolType::VARIABLE;
        entry.dataType = pascalType;

        symbolTable->addSymbol(entry);
    }

    // Process additional variable declarations if any
    if (context->varDeclaration()) {
        visit(context->varDeclaration());
    }

    return std::any();
}

std::any PascalToCTranslator::visitType(PascalSParser::TypeContext *context) {
    if (context->basicType()) {
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

        return std::make_pair(arrayTypeStr, PascalType::ARRAY);
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

    // Process the subprogram
    if (context->subprogram()) {
        visit(context->subprogram());
    }

    // Process additional subprogram declarations if any
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

    // Create a new scope for the function/procedure
    symbolTable->enterScope(name);

    // Get return type for functions
    std::string returnType = "void";
    PascalType pascalReturnType = PascalType::INTEGER;  // Default

    if (isFunction) {
        auto result = visit(context->basicType());
        pascalReturnType = std::any_cast<PascalType>(result);
        returnType = typeConverter->convertType(pascalReturnType);
    }

    // Output function/procedure declaration
    output << returnType << " " << name;

    // Visit formal parameters
    auto paramsResult = visit(context->formalParameter());
    std::string params = std::any_cast<std::string>(paramsResult);
    output << params;

    // Add function/procedure to symbol table
    SymbolEntry entry;
    entry.name = name;
    entry.symbolType = isFunction ? SymbolType::FUNCTION : SymbolType::PROCEDURE;
    entry.dataType = pascalReturnType;

    symbolTable->addSymbol(entry);

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
    // Visit first parameter
    auto result = visit(context->parameter());
    std::string params = std::any_cast<std::string>(result);

    // Visit additional parameters if any
    if (context->parameterList()) {
        auto moreParams = visit(context->parameterList());
        std::string moreParamsStr = std::any_cast<std::string>(moreParams);
        params = moreParamsStr + ", " + params;
    }

    return params;
}

std::any PascalToCTranslator::visitParameter(PascalSParser::ParameterContext *context) {
    if (context->varParameter()) {
        return visit(context->varParameter());
    } else if (context->valueParameter()) {
        return visit(context->valueParameter());
    }

    return std::string("");
}

std::any PascalToCTranslator::visitVarParameter(PascalSParser::VarParameterContext *context) {
    // Get value parameter
    auto result = visit(context->valueParameter());
    std::string params = std::any_cast<std::string>(result);

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

    // Get type
    auto typeResult = visit(context->type());
    std::pair<std::string, PascalType> typePair = std::any_cast<std::pair<std::string, PascalType>>(typeResult);
    std::string typeStr = typePair.first;
    PascalType pascalType = typePair.second;

    // Format parameters
    std::stringstream ss;
    for (size_t i = 0; i < ids.size(); ++i) {
        if (i > 0) {
            ss << ", ";
        }

        ss << typeStr << " " << ids[i];

        // Add to symbol table
        SymbolEntry entry;
        entry.name = ids[i];
        entry.symbolType = SymbolType::PARAMETER;
        entry.dataType = pascalType;
        entry.isReference = false;

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

    // Assignment to variable
    if (context->variable() && context->ASSIGNOP()) {
        auto varResult = visit(context->variable());
        std::string var = std::any_cast<std::string>(varResult);

        auto exprResult = visit(context->expression());
        std::string expr = std::any_cast<std::string>(exprResult);

        output << getCurrentIndentation() << var << " = " << expr << ";\n";
    }
    // Assignment to identifier (procedure or function result)
    else if (context->ID() && context->ASSIGNOP()) {
        std::string id = TranslatorUtils::toCIdentifier(context->ID()->getText());

        auto exprResult = visit(context->expression());
        std::string expr = std::any_cast<std::string>(exprResult);

        output << getCurrentIndentation() << id << " = " << expr << ";\n";
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
    // Get condition
    auto condResult = visit(context->expression());
    std::string cond = std::any_cast<std::string>(condResult);

    // Output if statement
    output << getCurrentIndentation() << "if (" << cond << ") {\n";
    increaseIndentation();

    // Visit then statement
    visit(context->statement());

    decreaseIndentation();
    output << getCurrentIndentation() << "}";

    // Visit else part if present
    if (context->elsePart()) {
        auto result = visit(context->elsePart());
        std::string elsePart = std::any_cast<std::string>(result);

        if (!elsePart.empty()) {
            output << " else {\n";
            increaseIndentation();

            // The actual code will be output by the elsePart visitor

            decreaseIndentation();
            output << getCurrentIndentation() << "}";
        }
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
    // Get variable list
    auto result = visit(context->variableList());
    std::vector<std::string> vars = std::any_cast<std::vector<std::string>>(result);

    // Output read statements for each variable
    for (const auto &var : vars) {
        if (symbolTable->hasSymbol(var)) {
            const SymbolEntry &entry = symbolTable->getSymbol(var);
            std::string format;

            if (entry.dataType == PascalType::INTEGER) {
                format = "\"%d\"";
            } else if (entry.dataType == PascalType::REAL) {
                format = "\"%f\"";
            } else if (entry.dataType == PascalType::CHAR) {
                format = "\" %c\"";
            } else {
                format = "\"%s\"";
            }

            output << getCurrentIndentation() << "scanf(" << format << ", &" << var << ");\n";
        } else {
            // Default to integer if type is unknown
            output << getCurrentIndentation() << "scanf(\"%d\", &" << var << ");\n";
        }
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
    // Get expression list
    auto result = visit(context->expressionList());
    std::vector<std::string> exprs = std::any_cast<std::vector<std::string>>(result);

    // Output printf statement
    output << getCurrentIndentation() << "printf(";

    // Format string
    std::string formatStr = "\"";
    for (size_t i = 0; i < exprs.size(); ++i) {
        // Try to determine the type of the expression
        std::string expr = exprs[i];
        if (expr.find('.') != std::string::npos) {
            formatStr += "%f";  // Real/float
        } else if (expr.find('\"') != std::string::npos) {
            formatStr += "%s";  // String
        } else if (expr.find('\'') != std::string::npos) {
            formatStr += "%c";  // Character
        } else if (expr == "0" || expr == "1" || expr == "true" || expr == "false") {
            formatStr += "%d";  // Boolean
        } else {
            // Try to look up the type in the symbol table
            bool found = false;
            if (expr.find('(') == std::string::npos && expr.find('[') == std::string::npos) {
                // Simple identifier
                if (symbolTable->hasSymbol(expr)) {
                    const SymbolEntry &entry = symbolTable->getSymbol(expr);
                    switch (entry.dataType) {
                        case PascalType::INTEGER:
                            formatStr += "%d";
                            found = true;
                            break;
                        case PascalType::REAL:
                            formatStr += "%f";
                            found = true;
                            break;
                        case PascalType::BOOLEAN:
                            formatStr += "%d";
                            found = true;
                            break;
                        case PascalType::CHAR:
                            formatStr += "%c";
                            found = true;
                            break;
                        default:
                            break;
                    }
                }
            }
            if (!found) {
                formatStr += "%d";  // Default to integer
            }
        }
    }
    formatStr += "\\n\"";

    output << formatStr;

    // Arguments
    for (const auto &expr : exprs) {
        output << ", " << expr;
    }

    output << ");\n";

    return std::any();
}

std::any PascalToCTranslator::visitVariableList(PascalSParser::VariableListContext *context) {
    std::vector<std::string> vars;

    // Get first variable
    auto result = visit(context->variable());
    vars.push_back(std::any_cast<std::string>(result));

    // Get additional variables if any
    if (context->variableList()) {
        auto moreVars = visit(context->variableList());
        std::vector<std::string> moreVarsVec = std::any_cast<std::vector<std::string>>(moreVars);

        vars.insert(vars.end(), moreVarsVec.begin(), moreVarsVec.end());
    }

    return vars;
}

std::any PascalToCTranslator::visitVariable(PascalSParser::VariableContext *context) {
    std::string id = TranslatorUtils::toCIdentifier(context->ID()->getText());

    // Check if it's an array access
    if (context->idVarPart()) {
        auto result = visit(context->idVarPart());
        std::string indices = std::any_cast<std::string>(result);

        return id + indices;
    }

    return id;
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

        for (size_t i = 0; i < args.size(); ++i) {
            if (i > 0) {
                ss << ", ";
            }
            ss << args[i];
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

    // Get first expression
    auto result = visit(context->expression());
    exprs.push_back(std::any_cast<std::string>(result));

    // Get additional expressions if any
    if (context->expressionList()) {
        auto moreExprs = visit(context->expressionList());
        std::vector<std::string> moreExprsVec = std::any_cast<std::vector<std::string>>(moreExprs);

        exprs.insert(exprs.end(), moreExprsVec.begin(), moreExprsVec.end());
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

        for (size_t i = 0; i < args.size(); ++i) {
            if (i > 0) {
                ss << ", ";
            }
            ss << args[i];
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