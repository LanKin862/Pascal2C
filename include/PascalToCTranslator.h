#pragma once

#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "../antlr/PascalSParser.h"
#include "../antlr/PascalSVisitor.h"
#include "SymbolTable.h"
#include "TypeConverter.h"
#include "antlr4-runtime.h"

class PascalToCTranslator : public PascalSVisitor {
  private:
    std::unique_ptr<SymbolTable> symbolTable;
    std::unique_ptr<TypeConverter> typeConverter;
    std::stringstream output;
    std::string indentation;
    bool isInGlobalScope;
    int tempVarCounter;

    void increaseIndentation();
    void decreaseIndentation();
    std::string getCurrentIndentation() const;
    std::string getNextTempVar();

  public:
    PascalToCTranslator();
    ~PascalToCTranslator() = default;

    std::string translate(const std::string &inputFile);

    // Visitor implementation methods
    std::any visitProgram(PascalSParser::ProgramContext *context) override;
    std::any visitProgramStruct(PascalSParser::ProgramStructContext *context) override;
    std::any visitProgramHead(PascalSParser::ProgramHeadContext *context) override;
    std::any visitProgramBody(PascalSParser::ProgramBodyContext *context) override;
    std::any visitIdList(PascalSParser::IdListContext *context) override;
    std::any visitConstDeclarations(PascalSParser::ConstDeclarationsContext *context) override;
    std::any visitConstDeclaration(PascalSParser::ConstDeclarationContext *context) override;
    std::any visitConstValue(PascalSParser::ConstValueContext *context) override;
    std::any visitVarDeclarations(PascalSParser::VarDeclarationsContext *context) override;
    std::any visitVarDeclaration(PascalSParser::VarDeclarationContext *context) override;
    std::any visitType(PascalSParser::TypeContext *context) override;
    std::any visitBasicType(PascalSParser::BasicTypeContext *context) override;
    std::any visitPeriod(PascalSParser::PeriodContext *context) override;
    std::any visitSubprogramDeclarations(PascalSParser::SubprogramDeclarationsContext *context) override;
    std::any visitSubprogram(PascalSParser::SubprogramContext *context) override;
    std::any visitSubprogramHead(PascalSParser::SubprogramHeadContext *context) override;
    std::any visitFormalParameter(PascalSParser::FormalParameterContext *context) override;
    std::any visitParameterList(PascalSParser::ParameterListContext *context) override;
    std::any visitParameter(PascalSParser::ParameterContext *context) override;
    std::any visitVarParameter(PascalSParser::VarParameterContext *context) override;
    std::any visitValueParameter(PascalSParser::ValueParameterContext *context) override;
    std::any visitSubprogramBody(PascalSParser::SubprogramBodyContext *context) override;
    std::any visitCompoundStatement(PascalSParser::CompoundStatementContext *context) override;
    std::any visitStatementList(PascalSParser::StatementListContext *context) override;
    std::any visitStatement(PascalSParser::StatementContext *context) override;
    std::any visitIfStatement(PascalSParser::IfStatementContext *context) override;
    std::any visitForStatement(PascalSParser::ForStatementContext *context) override;
    std::any visitReadStatement(PascalSParser::ReadStatementContext *context) override;
    std::any visitWhileStatement(PascalSParser::WhileStatementContext *context) override;
    std::any visitWriteStatement(PascalSParser::WriteStatementContext *context) override;
    std::any visitVariableList(PascalSParser::VariableListContext *context) override;
    std::any visitVariable(PascalSParser::VariableContext *context) override;
    std::any visitIdVarPart(PascalSParser::IdVarPartContext *context) override;
    std::any visitProcedureCall(PascalSParser::ProcedureCallContext *context) override;
    std::any visitElsePart(PascalSParser::ElsePartContext *context) override;
    std::any visitExpressionList(PascalSParser::ExpressionListContext *context) override;
    std::any visitExpression(PascalSParser::ExpressionContext *context) override;
    std::any visitSimpleExpression(PascalSParser::SimpleExpressionContext *context) override;
    std::any visitTerm(PascalSParser::TermContext *context) override;
    std::any visitFactor(PascalSParser::FactorContext *context) override;
    std::any visitNum(PascalSParser::NumContext *context) override;
    std::any visitRelop(PascalSParser::RelopContext *context) override;
    std::any visitAddop(PascalSParser::AddopContext *context) override;
    std::any visitMulop(PascalSParser::MulopContext *context) override;
};