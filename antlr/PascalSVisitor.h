
// Generated from PascalS.g4 by ANTLR 4.13.2

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
    virtual std::any visitProgram(PascalSParser::ProgramContext *context) = 0;

    virtual std::any visitProgramStruct(PascalSParser::ProgramStructContext *context) = 0;

    virtual std::any visitProgramHead(PascalSParser::ProgramHeadContext *context) = 0;

    virtual std::any visitProgramBody(PascalSParser::ProgramBodyContext *context) = 0;

    virtual std::any visitIdList(PascalSParser::IdListContext *context) = 0;

    virtual std::any visitConstDeclarations(PascalSParser::ConstDeclarationsContext *context) = 0;

    virtual std::any visitConstDeclaration(PascalSParser::ConstDeclarationContext *context) = 0;

    virtual std::any visitConstValue(PascalSParser::ConstValueContext *context) = 0;

    virtual std::any visitVarDeclarations(PascalSParser::VarDeclarationsContext *context) = 0;

    virtual std::any visitVarDeclaration(PascalSParser::VarDeclarationContext *context) = 0;

    virtual std::any visitType(PascalSParser::TypeContext *context) = 0;

    virtual std::any visitBasicType(PascalSParser::BasicTypeContext *context) = 0;

    virtual std::any visitPeriod(PascalSParser::PeriodContext *context) = 0;

    virtual std::any visitSubprogramDeclarations(PascalSParser::SubprogramDeclarationsContext *context) = 0;

    virtual std::any visitSubprogram(PascalSParser::SubprogramContext *context) = 0;

    virtual std::any visitSubprogramHead(PascalSParser::SubprogramHeadContext *context) = 0;

    virtual std::any visitFormalParameter(PascalSParser::FormalParameterContext *context) = 0;

    virtual std::any visitParameterList(PascalSParser::ParameterListContext *context) = 0;

    virtual std::any visitParameter(PascalSParser::ParameterContext *context) = 0;

    virtual std::any visitVarParameter(PascalSParser::VarParameterContext *context) = 0;

    virtual std::any visitValueParameter(PascalSParser::ValueParameterContext *context) = 0;

    virtual std::any visitSubprogramBody(PascalSParser::SubprogramBodyContext *context) = 0;

    virtual std::any visitCompoundStatement(PascalSParser::CompoundStatementContext *context) = 0;

    virtual std::any visitStatementList(PascalSParser::StatementListContext *context) = 0;

    virtual std::any visitStatement(PascalSParser::StatementContext *context) = 0;

    virtual std::any visitIfStatement(PascalSParser::IfStatementContext *context) = 0;

    virtual std::any visitForStatement(PascalSParser::ForStatementContext *context) = 0;

    virtual std::any visitReadStatement(PascalSParser::ReadStatementContext *context) = 0;

    virtual std::any visitWhileStatement(PascalSParser::WhileStatementContext *context) = 0;

    virtual std::any visitWriteStatement(PascalSParser::WriteStatementContext *context) = 0;

    virtual std::any visitVariableList(PascalSParser::VariableListContext *context) = 0;

    virtual std::any visitVariable(PascalSParser::VariableContext *context) = 0;

    virtual std::any visitIdVarPart(PascalSParser::IdVarPartContext *context) = 0;

    virtual std::any visitProcedureCall(PascalSParser::ProcedureCallContext *context) = 0;

    virtual std::any visitElsePart(PascalSParser::ElsePartContext *context) = 0;

    virtual std::any visitExpressionList(PascalSParser::ExpressionListContext *context) = 0;

    virtual std::any visitExpression(PascalSParser::ExpressionContext *context) = 0;

    virtual std::any visitSimpleExpression(PascalSParser::SimpleExpressionContext *context) = 0;

    virtual std::any visitTerm(PascalSParser::TermContext *context) = 0;

    virtual std::any visitFactor(PascalSParser::FactorContext *context) = 0;

    virtual std::any visitNum(PascalSParser::NumContext *context) = 0;

    virtual std::any visitRelop(PascalSParser::RelopContext *context) = 0;

    virtual std::any visitAddop(PascalSParser::AddopContext *context) = 0;

    virtual std::any visitMulop(PascalSParser::MulopContext *context) = 0;


};

