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
#include "support/Any.h"

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
    void generateForwardDeclarations(PascalSParser::SubprogramDeclarationsContext *context);

  public:
    PascalToCTranslator();
    ~PascalToCTranslator() = default;

    std::string translate(const std::string &inputFile);

    // 访问者实现方法
    antlrcpp::Any visitProgram(PascalSParser::ProgramContext *context) override;
    antlrcpp::Any visitProgramStruct(PascalSParser::ProgramStructContext *context) override;
    antlrcpp::Any visitProgramHead(PascalSParser::ProgramHeadContext *context) override;
    antlrcpp::Any visitProgramBody(PascalSParser::ProgramBodyContext *context) override;
    antlrcpp::Any visitIdList(PascalSParser::IdListContext *context) override;
    antlrcpp::Any visitConstDeclarations(PascalSParser::ConstDeclarationsContext *context) override;
    antlrcpp::Any visitConstDeclaration(PascalSParser::ConstDeclarationContext *context) override;
    antlrcpp::Any visitConstValue(PascalSParser::ConstValueContext *context) override;
    antlrcpp::Any visitVarDeclarations(PascalSParser::VarDeclarationsContext *context) override;
    antlrcpp::Any visitVarDeclaration(PascalSParser::VarDeclarationContext *context) override;
    antlrcpp::Any visitType(PascalSParser::TypeContext *context) override;
    antlrcpp::Any visitBasicType(PascalSParser::BasicTypeContext *context) override;
    antlrcpp::Any visitPeriod(PascalSParser::PeriodContext *context) override;
    antlrcpp::Any visitSubprogramDeclarations(PascalSParser::SubprogramDeclarationsContext *context) override;
    antlrcpp::Any visitSubprogram(PascalSParser::SubprogramContext *context) override;
    antlrcpp::Any visitSubprogramHead(PascalSParser::SubprogramHeadContext *context) override;
    antlrcpp::Any visitFormalParameter(PascalSParser::FormalParameterContext *context) override;
    antlrcpp::Any visitParameterList(PascalSParser::ParameterListContext *context) override;
    antlrcpp::Any visitParameter(PascalSParser::ParameterContext *context) override;
    antlrcpp::Any visitVarParameter(PascalSParser::VarParameterContext *context) override;
    antlrcpp::Any visitValueParameter(PascalSParser::ValueParameterContext *context) override;
    antlrcpp::Any visitSubprogramBody(PascalSParser::SubprogramBodyContext *context) override;
    antlrcpp::Any visitCompoundStatement(PascalSParser::CompoundStatementContext *context) override;
    antlrcpp::Any visitStatementList(PascalSParser::StatementListContext *context) override;
    antlrcpp::Any visitStatement(PascalSParser::StatementContext *context) override;
    antlrcpp::Any visitIfStatement(PascalSParser::IfStatementContext *context) override;
    antlrcpp::Any visitForStatement(PascalSParser::ForStatementContext *context) override;
    antlrcpp::Any visitReadStatement(PascalSParser::ReadStatementContext *context) override;
    antlrcpp::Any visitWhileStatement(PascalSParser::WhileStatementContext *context) override;
    antlrcpp::Any visitWriteStatement(PascalSParser::WriteStatementContext *context) override;
    antlrcpp::Any visitBreakStatement(PascalSParser::BreakStatementContext *context) override;
    antlrcpp::Any visitVariableList(PascalSParser::VariableListContext *context) override;
    antlrcpp::Any visitVariable(PascalSParser::VariableContext *context) override;
    antlrcpp::Any visitIdVarPart(PascalSParser::IdVarPartContext *context) override;
    antlrcpp::Any visitProcedureCall(PascalSParser::ProcedureCallContext *context) override;
    antlrcpp::Any visitElsePart(PascalSParser::ElsePartContext *context) override;
    antlrcpp::Any visitExpressionList(PascalSParser::ExpressionListContext *context) override;
    antlrcpp::Any visitExpression(PascalSParser::ExpressionContext *context) override;
    antlrcpp::Any visitSimpleExpression(PascalSParser::SimpleExpressionContext *context) override;
    antlrcpp::Any visitTerm(PascalSParser::TermContext *context) override;
    antlrcpp::Any visitFactor(PascalSParser::FactorContext *context) override;
    antlrcpp::Any visitNum(PascalSParser::NumContext *context) override;
    antlrcpp::Any visitRelop(PascalSParser::RelopContext *context) override;
    antlrcpp::Any visitAddop(PascalSParser::AddopContext *context) override;
    antlrcpp::Any visitMulop(PascalSParser::MulopContext *context) override;
};