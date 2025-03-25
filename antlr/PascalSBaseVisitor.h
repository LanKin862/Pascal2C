
// Generated from PascalS.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "PascalSVisitor.h"


/**
 * This class provides an empty implementation of PascalSVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  PascalSBaseVisitor : public PascalSVisitor {
public:

  virtual std::any visitProgram(PascalSParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProgramStruct(PascalSParser::ProgramStructContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProgramHead(PascalSParser::ProgramHeadContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProgramBody(PascalSParser::ProgramBodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIdList(PascalSParser::IdListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstDeclarations(PascalSParser::ConstDeclarationsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstDeclaration(PascalSParser::ConstDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstValue(PascalSParser::ConstValueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarDeclarations(PascalSParser::VarDeclarationsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarDeclaration(PascalSParser::VarDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitType(PascalSParser::TypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBasicType(PascalSParser::BasicTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPeriod(PascalSParser::PeriodContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSubprogramDeclarations(PascalSParser::SubprogramDeclarationsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSubprogram(PascalSParser::SubprogramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSubprogramHead(PascalSParser::SubprogramHeadContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFormalParameter(PascalSParser::FormalParameterContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParameterList(PascalSParser::ParameterListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParameter(PascalSParser::ParameterContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarParameter(PascalSParser::VarParameterContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitValueParameter(PascalSParser::ValueParameterContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSubprogramBody(PascalSParser::SubprogramBodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCompoundStatement(PascalSParser::CompoundStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatementList(PascalSParser::StatementListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatement(PascalSParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIfStatement(PascalSParser::IfStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitForStatement(PascalSParser::ForStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReadStatement(PascalSParser::ReadStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitWhileStatement(PascalSParser::WhileStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitWriteStatement(PascalSParser::WriteStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVariableList(PascalSParser::VariableListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVariable(PascalSParser::VariableContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIdVarPart(PascalSParser::IdVarPartContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProcedureCall(PascalSParser::ProcedureCallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElsePart(PascalSParser::ElsePartContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpressionList(PascalSParser::ExpressionListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpression(PascalSParser::ExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSimpleExpression(PascalSParser::SimpleExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTerm(PascalSParser::TermContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFactor(PascalSParser::FactorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNum(PascalSParser::NumContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRelop(PascalSParser::RelopContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAddop(PascalSParser::AddopContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMulop(PascalSParser::MulopContext *ctx) override {
    return visitChildren(ctx);
  }


};

