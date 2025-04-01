
// Generated from PascalS.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"




class  PascalSParser : public antlr4::Parser {
public:
  enum {
    PROGRAM = 1, CONST = 2, VAR = 3, PROCEDURE = 4, FUNCTION = 5, BEGIN = 6, 
    END = 7, ARRAY = 8, OF = 9, IF = 10, THEN = 11, ELSE = 12, FOR = 13, 
    TO = 14, DO = 15, READ = 16, WRITE = 17, INTEGER = 18, REAL = 19, BOOLEAN = 20, 
    CHAR = 21, DIV = 22, MOD = 23, AND = 24, OR = 25, NOT = 26, WHILE = 27, 
    SEMICOLON = 28, COLON = 29, DOT = 30, COMMA = 31, EQUAL = 32, NOTEQUAL = 33, 
    LT = 34, LE = 35, GT = 36, GE = 37, PLUS = 38, MINUS = 39, STAR = 40, 
    SLASH = 41, LPAREN = 42, RPAREN = 43, LBRACKET = 44, RBRACKET = 45, 
    ASSIGNOP = 46, DOTDOT = 47, ID = 48, NUM = 49, LETTER = 50, STRING = 51, 
    COMMENT = 52, LINE_COMMENT = 53, WS = 54
  };

  enum {
    RuleProgram = 0, RuleProgramStruct = 1, RuleProgramHead = 2, RuleProgramBody = 3, 
    RuleIdList = 4, RuleConstDeclarations = 5, RuleConstDeclaration = 6, 
    RuleConstValue = 7, RuleVarDeclarations = 8, RuleVarDeclaration = 9, 
    RuleType = 10, RuleBasicType = 11, RulePeriod = 12, RuleSubprogramDeclarations = 13, 
    RuleSubprogram = 14, RuleSubprogramHead = 15, RuleFormalParameter = 16, 
    RuleParameterList = 17, RuleParameter = 18, RuleVarParameter = 19, RuleValueParameter = 20, 
    RuleSubprogramBody = 21, RuleCompoundStatement = 22, RuleStatementList = 23, 
    RuleStatement = 24, RuleIfStatement = 25, RuleForStatement = 26, RuleReadStatement = 27, 
    RuleWhileStatement = 28, RuleWriteStatement = 29, RuleVariableList = 30, 
    RuleVariable = 31, RuleIdVarPart = 32, RuleProcedureCall = 33, RuleElsePart = 34, 
    RuleExpressionList = 35, RuleExpression = 36, RuleSimpleExpression = 37, 
    RuleTerm = 38, RuleFactor = 39, RuleNum = 40, RuleRelop = 41, RuleAddop = 42, 
    RuleMulop = 43
  };

  PascalSParser(antlr4::TokenStream *input);
  ~PascalSParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  class ProgramContext;
  class ProgramStructContext;
  class ProgramHeadContext;
  class ProgramBodyContext;
  class IdListContext;
  class ConstDeclarationsContext;
  class ConstDeclarationContext;
  class ConstValueContext;
  class VarDeclarationsContext;
  class VarDeclarationContext;
  class TypeContext;
  class BasicTypeContext;
  class PeriodContext;
  class SubprogramDeclarationsContext;
  class SubprogramContext;
  class SubprogramHeadContext;
  class FormalParameterContext;
  class ParameterListContext;
  class ParameterContext;
  class VarParameterContext;
  class ValueParameterContext;
  class SubprogramBodyContext;
  class CompoundStatementContext;
  class StatementListContext;
  class StatementContext;
  class IfStatementContext;
  class ForStatementContext;
  class ReadStatementContext;
  class WhileStatementContext;
  class WriteStatementContext;
  class VariableListContext;
  class VariableContext;
  class IdVarPartContext;
  class ProcedureCallContext;
  class ElsePartContext;
  class ExpressionListContext;
  class ExpressionContext;
  class SimpleExpressionContext;
  class TermContext;
  class FactorContext;
  class NumContext;
  class RelopContext;
  class AddopContext;
  class MulopContext; 

  class  ProgramContext : public antlr4::ParserRuleContext {
  public:
    ProgramContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ProgramStructContext *programStruct();
    antlr4::tree::TerminalNode *EOF();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ProgramContext* program();

  class  ProgramStructContext : public antlr4::ParserRuleContext {
  public:
    ProgramStructContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ProgramHeadContext *programHead();
    antlr4::tree::TerminalNode *SEMICOLON();
    ProgramBodyContext *programBody();
    antlr4::tree::TerminalNode *DOT();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ProgramStructContext* programStruct();

  class  ProgramHeadContext : public antlr4::ParserRuleContext {
  public:
    ProgramHeadContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *PROGRAM();
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *LPAREN();
    IdListContext *idList();
    antlr4::tree::TerminalNode *RPAREN();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ProgramHeadContext* programHead();

  class  ProgramBodyContext : public antlr4::ParserRuleContext {
  public:
    ProgramBodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConstDeclarationsContext *constDeclarations();
    VarDeclarationsContext *varDeclarations();
    SubprogramDeclarationsContext *subprogramDeclarations();
    CompoundStatementContext *compoundStatement();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ProgramBodyContext* programBody();

  class  IdListContext : public antlr4::ParserRuleContext {
  public:
    IdListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> ID();
    antlr4::tree::TerminalNode* ID(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IdListContext* idList();

  class  ConstDeclarationsContext : public antlr4::ParserRuleContext {
  public:
    ConstDeclarationsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CONST();
    ConstDeclarationContext *constDeclaration();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConstDeclarationsContext* constDeclarations();

  class  ConstDeclarationContext : public antlr4::ParserRuleContext {
  public:
    ConstDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *EQUAL();
    ConstValueContext *constValue();
    ConstDeclarationContext *constDeclaration();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConstDeclarationContext* constDeclaration();
  ConstDeclarationContext* constDeclaration(int precedence);
  class  ConstValueContext : public antlr4::ParserRuleContext {
  public:
    ConstValueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NumContext *num();
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *MINUS();
    antlr4::tree::TerminalNode *LETTER();
    antlr4::tree::TerminalNode *STRING();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConstValueContext* constValue();

  class  VarDeclarationsContext : public antlr4::ParserRuleContext {
  public:
    VarDeclarationsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VAR();
    VarDeclarationContext *varDeclaration();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VarDeclarationsContext* varDeclarations();

  class  VarDeclarationContext : public antlr4::ParserRuleContext {
  public:
    VarDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdListContext *idList();
    antlr4::tree::TerminalNode *COLON();
    TypeContext *type();
    VarDeclarationContext *varDeclaration();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VarDeclarationContext* varDeclaration();
  VarDeclarationContext* varDeclaration(int precedence);
  class  TypeContext : public antlr4::ParserRuleContext {
  public:
    TypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BasicTypeContext *basicType();
    antlr4::tree::TerminalNode *ARRAY();
    antlr4::tree::TerminalNode *LBRACKET();
    PeriodContext *period();
    antlr4::tree::TerminalNode *RBRACKET();
    antlr4::tree::TerminalNode *OF();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeContext* type();

  class  BasicTypeContext : public antlr4::ParserRuleContext {
  public:
    BasicTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INTEGER();
    antlr4::tree::TerminalNode *REAL();
    antlr4::tree::TerminalNode *BOOLEAN();
    antlr4::tree::TerminalNode *CHAR();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BasicTypeContext* basicType();

  class  PeriodContext : public antlr4::ParserRuleContext {
  public:
    PeriodContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> NUM();
    antlr4::tree::TerminalNode* NUM(size_t i);
    antlr4::tree::TerminalNode *DOTDOT();
    PeriodContext *period();
    antlr4::tree::TerminalNode *COMMA();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PeriodContext* period();
  PeriodContext* period(int precedence);
  class  SubprogramDeclarationsContext : public antlr4::ParserRuleContext {
  public:
    SubprogramDeclarationsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SubprogramDeclarationsContext *subprogramDeclarations();
    SubprogramContext *subprogram();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SubprogramDeclarationsContext* subprogramDeclarations();
  SubprogramDeclarationsContext* subprogramDeclarations(int precedence);
  class  SubprogramContext : public antlr4::ParserRuleContext {
  public:
    SubprogramContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SubprogramHeadContext *subprogramHead();
    antlr4::tree::TerminalNode *SEMICOLON();
    SubprogramBodyContext *subprogramBody();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SubprogramContext* subprogram();

  class  SubprogramHeadContext : public antlr4::ParserRuleContext {
  public:
    SubprogramHeadContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *PROCEDURE();
    antlr4::tree::TerminalNode *ID();
    FormalParameterContext *formalParameter();
    antlr4::tree::TerminalNode *FUNCTION();
    antlr4::tree::TerminalNode *COLON();
    BasicTypeContext *basicType();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SubprogramHeadContext* subprogramHead();

  class  FormalParameterContext : public antlr4::ParserRuleContext {
  public:
    FormalParameterContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    ParameterListContext *parameterList();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FormalParameterContext* formalParameter();

  class  ParameterListContext : public antlr4::ParserRuleContext {
  public:
    ParameterListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ParameterContext *parameter();
    ParameterListContext *parameterList();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParameterListContext* parameterList();
  ParameterListContext* parameterList(int precedence);
  class  ParameterContext : public antlr4::ParserRuleContext {
  public:
    ParameterContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VarParameterContext *varParameter();
    ValueParameterContext *valueParameter();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParameterContext* parameter();

  class  VarParameterContext : public antlr4::ParserRuleContext {
  public:
    VarParameterContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VAR();
    ValueParameterContext *valueParameter();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VarParameterContext* varParameter();

  class  ValueParameterContext : public antlr4::ParserRuleContext {
  public:
    ValueParameterContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdListContext *idList();
    antlr4::tree::TerminalNode *COLON();
    TypeContext *type();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ValueParameterContext* valueParameter();

  class  SubprogramBodyContext : public antlr4::ParserRuleContext {
  public:
    SubprogramBodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConstDeclarationsContext *constDeclarations();
    VarDeclarationsContext *varDeclarations();
    CompoundStatementContext *compoundStatement();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SubprogramBodyContext* subprogramBody();

  class  CompoundStatementContext : public antlr4::ParserRuleContext {
  public:
    CompoundStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *BEGIN();
    StatementListContext *statementList();
    antlr4::tree::TerminalNode *END();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CompoundStatementContext* compoundStatement();

  class  StatementListContext : public antlr4::ParserRuleContext {
  public:
    StatementListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StatementContext *statement();
    StatementListContext *statementList();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementListContext* statementList();
  StatementListContext* statementList(int precedence);
  class  StatementContext : public antlr4::ParserRuleContext {
  public:
    StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VariableContext *variable();
    antlr4::tree::TerminalNode *ASSIGNOP();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *ID();
    ProcedureCallContext *procedureCall();
    CompoundStatementContext *compoundStatement();
    IfStatementContext *ifStatement();
    ForStatementContext *forStatement();
    ReadStatementContext *readStatement();
    WhileStatementContext *whileStatement();
    WriteStatementContext *writeStatement();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementContext* statement();

  class  IfStatementContext : public antlr4::ParserRuleContext {
  public:
    IfStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IF();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *THEN();
    StatementContext *statement();
    ElsePartContext *elsePart();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IfStatementContext* ifStatement();

  class  ForStatementContext : public antlr4::ParserRuleContext {
  public:
    ForStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FOR();
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *ASSIGNOP();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *TO();
    antlr4::tree::TerminalNode *DO();
    StatementContext *statement();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ForStatementContext* forStatement();

  class  ReadStatementContext : public antlr4::ParserRuleContext {
  public:
    ReadStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *READ();
    antlr4::tree::TerminalNode *LPAREN();
    VariableListContext *variableList();
    antlr4::tree::TerminalNode *RPAREN();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ReadStatementContext* readStatement();

  class  WhileStatementContext : public antlr4::ParserRuleContext {
  public:
    WhileStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *WHILE();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *DO();
    StatementContext *statement();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  WhileStatementContext* whileStatement();

  class  WriteStatementContext : public antlr4::ParserRuleContext {
  public:
    WriteStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *WRITE();
    antlr4::tree::TerminalNode *LPAREN();
    ExpressionListContext *expressionList();
    antlr4::tree::TerminalNode *RPAREN();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  WriteStatementContext* writeStatement();

  class  VariableListContext : public antlr4::ParserRuleContext {
  public:
    VariableListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VariableContext *variable();
    VariableListContext *variableList();
    antlr4::tree::TerminalNode *COMMA();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VariableListContext* variableList();
  VariableListContext* variableList(int precedence);
  class  VariableContext : public antlr4::ParserRuleContext {
  public:
    VariableContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    IdVarPartContext *idVarPart();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VariableContext* variable();

  class  IdVarPartContext : public antlr4::ParserRuleContext {
  public:
    IdVarPartContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACKET();
    ExpressionListContext *expressionList();
    antlr4::tree::TerminalNode *RBRACKET();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IdVarPartContext* idVarPart();

  class  ProcedureCallContext : public antlr4::ParserRuleContext {
  public:
    ProcedureCallContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    ExpressionListContext *expressionList();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ProcedureCallContext* procedureCall();

  class  ElsePartContext : public antlr4::ParserRuleContext {
  public:
    ElsePartContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ELSE();
    StatementContext *statement();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ElsePartContext* elsePart();

  class  ExpressionListContext : public antlr4::ParserRuleContext {
  public:
    ExpressionListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();
    ExpressionListContext *expressionList();
    antlr4::tree::TerminalNode *COMMA();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExpressionListContext* expressionList();
  ExpressionListContext* expressionList(int precedence);
  class  ExpressionContext : public antlr4::ParserRuleContext {
  public:
    ExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<SimpleExpressionContext *> simpleExpression();
    SimpleExpressionContext* simpleExpression(size_t i);
    RelopContext *relop();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExpressionContext* expression();

  class  SimpleExpressionContext : public antlr4::ParserRuleContext {
  public:
    SimpleExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TermContext *term();
    SimpleExpressionContext *simpleExpression();
    AddopContext *addop();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SimpleExpressionContext* simpleExpression();
  SimpleExpressionContext* simpleExpression(int precedence);
  class  TermContext : public antlr4::ParserRuleContext {
  public:
    TermContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FactorContext *factor();
    TermContext *term();
    MulopContext *mulop();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TermContext* term();
  TermContext* term(int precedence);
  class  FactorContext : public antlr4::ParserRuleContext {
  public:
    FactorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NumContext *num();
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    ExpressionListContext *expressionList();
    VariableContext *variable();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *NOT();
    FactorContext *factor();
    antlr4::tree::TerminalNode *MINUS();
    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *LETTER();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FactorContext* factor();

  class  NumContext : public antlr4::ParserRuleContext {
  public:
    NumContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NUM();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NumContext* num();

  class  RelopContext : public antlr4::ParserRuleContext {
  public:
    RelopContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EQUAL();
    antlr4::tree::TerminalNode *NOTEQUAL();
    antlr4::tree::TerminalNode *LT();
    antlr4::tree::TerminalNode *LE();
    antlr4::tree::TerminalNode *GT();
    antlr4::tree::TerminalNode *GE();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  RelopContext* relop();

  class  AddopContext : public antlr4::ParserRuleContext {
  public:
    AddopContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *MINUS();
    antlr4::tree::TerminalNode *OR();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AddopContext* addop();

  class  MulopContext : public antlr4::ParserRuleContext {
  public:
    MulopContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STAR();
    antlr4::tree::TerminalNode *SLASH();
    antlr4::tree::TerminalNode *DIV();
    antlr4::tree::TerminalNode *MOD();
    antlr4::tree::TerminalNode *AND();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MulopContext* mulop();


  virtual bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;
  bool constDeclarationSempred(ConstDeclarationContext *_localctx, size_t predicateIndex);
  bool varDeclarationSempred(VarDeclarationContext *_localctx, size_t predicateIndex);
  bool periodSempred(PeriodContext *_localctx, size_t predicateIndex);
  bool subprogramDeclarationsSempred(SubprogramDeclarationsContext *_localctx, size_t predicateIndex);
  bool parameterListSempred(ParameterListContext *_localctx, size_t predicateIndex);
  bool statementListSempred(StatementListContext *_localctx, size_t predicateIndex);
  bool variableListSempred(VariableListContext *_localctx, size_t predicateIndex);
  bool expressionListSempred(ExpressionListContext *_localctx, size_t predicateIndex);
  bool simpleExpressionSempred(SimpleExpressionContext *_localctx, size_t predicateIndex);
  bool termSempred(TermContext *_localctx, size_t predicateIndex);

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

