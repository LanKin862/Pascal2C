
// Generated from PascalS.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"
#include "PascalSParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by PascalSParser.
 */
class  PascalSVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by PascalSParser.
   */
    virtual antlrcpp::Any visitProgram(PascalSParser::ProgramContext *context) = 0;

    virtual antlrcpp::Any visitProgramStruct(PascalSParser::ProgramStructContext *context) = 0;

    virtual antlrcpp::Any visitProgramHead(PascalSParser::ProgramHeadContext *context) = 0;

    virtual antlrcpp::Any visitProgramBody(PascalSParser::ProgramBodyContext *context) = 0;

    virtual antlrcpp::Any visitIdList(PascalSParser::IdListContext *context) = 0;

    virtual antlrcpp::Any visitConstDeclarations(PascalSParser::ConstDeclarationsContext *context) = 0;

    virtual antlrcpp::Any visitConstDeclaration(PascalSParser::ConstDeclarationContext *context) = 0;

    virtual antlrcpp::Any visitConstValue(PascalSParser::ConstValueContext *context) = 0;

    virtual antlrcpp::Any visitVarDeclarations(PascalSParser::VarDeclarationsContext *context) = 0;

    virtual antlrcpp::Any visitVarDeclaration(PascalSParser::VarDeclarationContext *context) = 0;

    virtual antlrcpp::Any visitType(PascalSParser::TypeContext *context) = 0;

    virtual antlrcpp::Any visitBasicType(PascalSParser::BasicTypeContext *context) = 0;

    virtual antlrcpp::Any visitPeriod(PascalSParser::PeriodContext *context) = 0;

    virtual antlrcpp::Any visitSubprogramDeclarations(PascalSParser::SubprogramDeclarationsContext *context) = 0;

    virtual antlrcpp::Any visitSubprogram(PascalSParser::SubprogramContext *context) = 0;

    virtual antlrcpp::Any visitSubprogramHead(PascalSParser::SubprogramHeadContext *context) = 0;

    virtual antlrcpp::Any visitFormalParameter(PascalSParser::FormalParameterContext *context) = 0;

    virtual antlrcpp::Any visitParameterList(PascalSParser::ParameterListContext *context) = 0;

    virtual antlrcpp::Any visitParameter(PascalSParser::ParameterContext *context) = 0;

    virtual antlrcpp::Any visitVarParameter(PascalSParser::VarParameterContext *context) = 0;

    virtual antlrcpp::Any visitValueParameter(PascalSParser::ValueParameterContext *context) = 0;

    virtual antlrcpp::Any visitSubprogramBody(PascalSParser::SubprogramBodyContext *context) = 0;

    virtual antlrcpp::Any visitCompoundStatement(PascalSParser::CompoundStatementContext *context) = 0;

    virtual antlrcpp::Any visitStatementList(PascalSParser::StatementListContext *context) = 0;

    virtual antlrcpp::Any visitStatement(PascalSParser::StatementContext *context) = 0;

    virtual antlrcpp::Any visitIfStatement(PascalSParser::IfStatementContext *context) = 0;

    virtual antlrcpp::Any visitForStatement(PascalSParser::ForStatementContext *context) = 0;

    virtual antlrcpp::Any visitReadStatement(PascalSParser::ReadStatementContext *context) = 0;

    virtual antlrcpp::Any visitWhileStatement(PascalSParser::WhileStatementContext *context) = 0;

    virtual antlrcpp::Any visitWriteStatement(PascalSParser::WriteStatementContext *context) = 0;

    virtual antlrcpp::Any visitVariableList(PascalSParser::VariableListContext *context) = 0;

    virtual antlrcpp::Any visitVariable(PascalSParser::VariableContext *context) = 0;

    virtual antlrcpp::Any visitIdVarPart(PascalSParser::IdVarPartContext *context) = 0;

    virtual antlrcpp::Any visitProcedureCall(PascalSParser::ProcedureCallContext *context) = 0;

    virtual antlrcpp::Any visitElsePart(PascalSParser::ElsePartContext *context) = 0;

    virtual antlrcpp::Any visitExpressionList(PascalSParser::ExpressionListContext *context) = 0;

    virtual antlrcpp::Any visitExpression(PascalSParser::ExpressionContext *context) = 0;

    virtual antlrcpp::Any visitSimpleExpression(PascalSParser::SimpleExpressionContext *context) = 0;

    virtual antlrcpp::Any visitTerm(PascalSParser::TermContext *context) = 0;

    virtual antlrcpp::Any visitFactor(PascalSParser::FactorContext *context) = 0;

    virtual antlrcpp::Any visitNum(PascalSParser::NumContext *context) = 0;

    virtual antlrcpp::Any visitRelop(PascalSParser::RelopContext *context) = 0;

    virtual antlrcpp::Any visitAddop(PascalSParser::AddopContext *context) = 0;

    virtual antlrcpp::Any visitMulop(PascalSParser::MulopContext *context) = 0;


};

