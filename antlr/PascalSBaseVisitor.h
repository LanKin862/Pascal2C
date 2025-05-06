
// Generated from PascalS.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"
#include "PascalSVisitor.h"


/**
 * This class provides an empty implementation of PascalSVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  PascalSBaseVisitor : public PascalSVisitor {
public:

  virtual antlrcpp::Any visitProgram(PascalSParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitProgramStruct(PascalSParser::ProgramStructContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitProgramHead(PascalSParser::ProgramHeadContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitProgramBody(PascalSParser::ProgramBodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIdList(PascalSParser::IdListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConstDeclarations(PascalSParser::ConstDeclarationsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConstDeclaration(PascalSParser::ConstDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConstValue(PascalSParser::ConstValueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVarDeclarations(PascalSParser::VarDeclarationsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVarDeclaration(PascalSParser::VarDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitType(PascalSParser::TypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBasicType(PascalSParser::BasicTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPeriod(PascalSParser::PeriodContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSubprogramDeclarations(PascalSParser::SubprogramDeclarationsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSubprogram(PascalSParser::SubprogramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSubprogramHead(PascalSParser::SubprogramHeadContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFormalParameter(PascalSParser::FormalParameterContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitParameterList(PascalSParser::ParameterListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitParameter(PascalSParser::ParameterContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVarParameter(PascalSParser::VarParameterContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitValueParameter(PascalSParser::ValueParameterContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSubprogramBody(PascalSParser::SubprogramBodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCompoundStatement(PascalSParser::CompoundStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStatementList(PascalSParser::StatementListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStatement(PascalSParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIfStatement(PascalSParser::IfStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitForStatement(PascalSParser::ForStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitReadStatement(PascalSParser::ReadStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitWhileStatement(PascalSParser::WhileStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitWriteStatement(PascalSParser::WriteStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBreakStatement(PascalSParser::BreakStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVariableList(PascalSParser::VariableListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVariable(PascalSParser::VariableContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIdVarPart(PascalSParser::IdVarPartContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitProcedureCall(PascalSParser::ProcedureCallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitElsePart(PascalSParser::ElsePartContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExpressionList(PascalSParser::ExpressionListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExpression(PascalSParser::ExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSimpleExpression(PascalSParser::SimpleExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTerm(PascalSParser::TermContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFactor(PascalSParser::FactorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNum(PascalSParser::NumContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitRelop(PascalSParser::RelopContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAddop(PascalSParser::AddopContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMulop(PascalSParser::MulopContext *ctx) override {
    return visitChildren(ctx);
  }


};

