
// Generated from PascalS.g4 by ANTLR 4.7.1


#include "PascalSVisitor.h"

#include "PascalSParser.h"


using namespace antlrcpp;
using namespace antlr4;

PascalSParser::PascalSParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

PascalSParser::~PascalSParser() {
  delete _interpreter;
}

std::string PascalSParser::getGrammarFileName() const {
  return "PascalS.g4";
}

const std::vector<std::string>& PascalSParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& PascalSParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- ProgramContext ------------------------------------------------------------------

PascalSParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PascalSParser::ProgramStructContext* PascalSParser::ProgramContext::programStruct() {
  return getRuleContext<PascalSParser::ProgramStructContext>(0);
}

tree::TerminalNode* PascalSParser::ProgramContext::EOF() {
  return getToken(PascalSParser::EOF, 0);
}


size_t PascalSParser::ProgramContext::getRuleIndex() const {
  return PascalSParser::RuleProgram;
}

antlrcpp::Any PascalSParser::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::ProgramContext* PascalSParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, PascalSParser::RuleProgram);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(90);
    programStruct();
    setState(91);
    match(PascalSParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ProgramStructContext ------------------------------------------------------------------

PascalSParser::ProgramStructContext::ProgramStructContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PascalSParser::ProgramHeadContext* PascalSParser::ProgramStructContext::programHead() {
  return getRuleContext<PascalSParser::ProgramHeadContext>(0);
}

tree::TerminalNode* PascalSParser::ProgramStructContext::SEMICOLON() {
  return getToken(PascalSParser::SEMICOLON, 0);
}

PascalSParser::ProgramBodyContext* PascalSParser::ProgramStructContext::programBody() {
  return getRuleContext<PascalSParser::ProgramBodyContext>(0);
}

tree::TerminalNode* PascalSParser::ProgramStructContext::DOT() {
  return getToken(PascalSParser::DOT, 0);
}


size_t PascalSParser::ProgramStructContext::getRuleIndex() const {
  return PascalSParser::RuleProgramStruct;
}

antlrcpp::Any PascalSParser::ProgramStructContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitProgramStruct(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::ProgramStructContext* PascalSParser::programStruct() {
  ProgramStructContext *_localctx = _tracker.createInstance<ProgramStructContext>(_ctx, getState());
  enterRule(_localctx, 2, PascalSParser::RuleProgramStruct);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(93);
    programHead();
    setState(94);
    match(PascalSParser::SEMICOLON);
    setState(95);
    programBody();
    setState(96);
    match(PascalSParser::DOT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ProgramHeadContext ------------------------------------------------------------------

PascalSParser::ProgramHeadContext::ProgramHeadContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PascalSParser::ProgramHeadContext::PROGRAM() {
  return getToken(PascalSParser::PROGRAM, 0);
}

tree::TerminalNode* PascalSParser::ProgramHeadContext::ID() {
  return getToken(PascalSParser::ID, 0);
}

tree::TerminalNode* PascalSParser::ProgramHeadContext::LPAREN() {
  return getToken(PascalSParser::LPAREN, 0);
}

PascalSParser::IdListContext* PascalSParser::ProgramHeadContext::idList() {
  return getRuleContext<PascalSParser::IdListContext>(0);
}

tree::TerminalNode* PascalSParser::ProgramHeadContext::RPAREN() {
  return getToken(PascalSParser::RPAREN, 0);
}


size_t PascalSParser::ProgramHeadContext::getRuleIndex() const {
  return PascalSParser::RuleProgramHead;
}

antlrcpp::Any PascalSParser::ProgramHeadContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitProgramHead(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::ProgramHeadContext* PascalSParser::programHead() {
  ProgramHeadContext *_localctx = _tracker.createInstance<ProgramHeadContext>(_ctx, getState());
  enterRule(_localctx, 4, PascalSParser::RuleProgramHead);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(98);
    match(PascalSParser::PROGRAM);
    setState(99);
    match(PascalSParser::ID);
    setState(104);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PascalSParser::LPAREN) {
      setState(100);
      match(PascalSParser::LPAREN);
      setState(101);
      idList();
      setState(102);
      match(PascalSParser::RPAREN);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ProgramBodyContext ------------------------------------------------------------------

PascalSParser::ProgramBodyContext::ProgramBodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PascalSParser::ConstDeclarationsContext* PascalSParser::ProgramBodyContext::constDeclarations() {
  return getRuleContext<PascalSParser::ConstDeclarationsContext>(0);
}

PascalSParser::VarDeclarationsContext* PascalSParser::ProgramBodyContext::varDeclarations() {
  return getRuleContext<PascalSParser::VarDeclarationsContext>(0);
}

PascalSParser::SubprogramDeclarationsContext* PascalSParser::ProgramBodyContext::subprogramDeclarations() {
  return getRuleContext<PascalSParser::SubprogramDeclarationsContext>(0);
}

PascalSParser::CompoundStatementContext* PascalSParser::ProgramBodyContext::compoundStatement() {
  return getRuleContext<PascalSParser::CompoundStatementContext>(0);
}


size_t PascalSParser::ProgramBodyContext::getRuleIndex() const {
  return PascalSParser::RuleProgramBody;
}

antlrcpp::Any PascalSParser::ProgramBodyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitProgramBody(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::ProgramBodyContext* PascalSParser::programBody() {
  ProgramBodyContext *_localctx = _tracker.createInstance<ProgramBodyContext>(_ctx, getState());
  enterRule(_localctx, 6, PascalSParser::RuleProgramBody);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(106);
    constDeclarations();
    setState(107);
    varDeclarations();
    setState(108);
    subprogramDeclarations(0);
    setState(109);
    compoundStatement();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IdListContext ------------------------------------------------------------------

PascalSParser::IdListContext::IdListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> PascalSParser::IdListContext::ID() {
  return getTokens(PascalSParser::ID);
}

tree::TerminalNode* PascalSParser::IdListContext::ID(size_t i) {
  return getToken(PascalSParser::ID, i);
}

std::vector<tree::TerminalNode *> PascalSParser::IdListContext::COMMA() {
  return getTokens(PascalSParser::COMMA);
}

tree::TerminalNode* PascalSParser::IdListContext::COMMA(size_t i) {
  return getToken(PascalSParser::COMMA, i);
}


size_t PascalSParser::IdListContext::getRuleIndex() const {
  return PascalSParser::RuleIdList;
}

antlrcpp::Any PascalSParser::IdListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitIdList(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::IdListContext* PascalSParser::idList() {
  IdListContext *_localctx = _tracker.createInstance<IdListContext>(_ctx, getState());
  enterRule(_localctx, 8, PascalSParser::RuleIdList);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(111);
    match(PascalSParser::ID);
    setState(116);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PascalSParser::COMMA) {
      setState(112);
      match(PascalSParser::COMMA);
      setState(113);
      match(PascalSParser::ID);
      setState(118);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstDeclarationsContext ------------------------------------------------------------------

PascalSParser::ConstDeclarationsContext::ConstDeclarationsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PascalSParser::ConstDeclarationsContext::CONST() {
  return getToken(PascalSParser::CONST, 0);
}

PascalSParser::ConstDeclarationContext* PascalSParser::ConstDeclarationsContext::constDeclaration() {
  return getRuleContext<PascalSParser::ConstDeclarationContext>(0);
}

tree::TerminalNode* PascalSParser::ConstDeclarationsContext::SEMICOLON() {
  return getToken(PascalSParser::SEMICOLON, 0);
}


size_t PascalSParser::ConstDeclarationsContext::getRuleIndex() const {
  return PascalSParser::RuleConstDeclarations;
}

antlrcpp::Any PascalSParser::ConstDeclarationsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitConstDeclarations(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::ConstDeclarationsContext* PascalSParser::constDeclarations() {
  ConstDeclarationsContext *_localctx = _tracker.createInstance<ConstDeclarationsContext>(_ctx, getState());
  enterRule(_localctx, 10, PascalSParser::RuleConstDeclarations);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(124);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);

      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(120);
      match(PascalSParser::CONST);
      setState(121);
      constDeclaration(0);
      setState(122);
      match(PascalSParser::SEMICOLON);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstDeclarationContext ------------------------------------------------------------------

PascalSParser::ConstDeclarationContext::ConstDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PascalSParser::ConstDeclarationContext::ID() {
  return getToken(PascalSParser::ID, 0);
}

tree::TerminalNode* PascalSParser::ConstDeclarationContext::EQUAL() {
  return getToken(PascalSParser::EQUAL, 0);
}

PascalSParser::ConstValueContext* PascalSParser::ConstDeclarationContext::constValue() {
  return getRuleContext<PascalSParser::ConstValueContext>(0);
}

PascalSParser::ConstDeclarationContext* PascalSParser::ConstDeclarationContext::constDeclaration() {
  return getRuleContext<PascalSParser::ConstDeclarationContext>(0);
}

tree::TerminalNode* PascalSParser::ConstDeclarationContext::SEMICOLON() {
  return getToken(PascalSParser::SEMICOLON, 0);
}


size_t PascalSParser::ConstDeclarationContext::getRuleIndex() const {
  return PascalSParser::RuleConstDeclaration;
}

antlrcpp::Any PascalSParser::ConstDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitConstDeclaration(this);
  else
    return visitor->visitChildren(this);
}


PascalSParser::ConstDeclarationContext* PascalSParser::constDeclaration() {
   return constDeclaration(0);
}

PascalSParser::ConstDeclarationContext* PascalSParser::constDeclaration(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  PascalSParser::ConstDeclarationContext *_localctx = _tracker.createInstance<ConstDeclarationContext>(_ctx, parentState);
  PascalSParser::ConstDeclarationContext *previousContext = _localctx;
  size_t startState = 12;
  enterRecursionRule(_localctx, 12, PascalSParser::RuleConstDeclaration, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(127);
    match(PascalSParser::ID);
    setState(128);
    match(PascalSParser::EQUAL);
    setState(129);
    constValue();
    _ctx->stop = _input->LT(-1);
    setState(138);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<ConstDeclarationContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleConstDeclaration);
        setState(131);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(132);
        match(PascalSParser::SEMICOLON);
        setState(133);
        match(PascalSParser::ID);
        setState(134);
        match(PascalSParser::EQUAL);
        setState(135);
        constValue(); 
      }
      setState(140);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- ConstValueContext ------------------------------------------------------------------

PascalSParser::ConstValueContext::ConstValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PascalSParser::NumContext* PascalSParser::ConstValueContext::num() {
  return getRuleContext<PascalSParser::NumContext>(0);
}

tree::TerminalNode* PascalSParser::ConstValueContext::PLUS() {
  return getToken(PascalSParser::PLUS, 0);
}

tree::TerminalNode* PascalSParser::ConstValueContext::MINUS() {
  return getToken(PascalSParser::MINUS, 0);
}

tree::TerminalNode* PascalSParser::ConstValueContext::LETTER() {
  return getToken(PascalSParser::LETTER, 0);
}

tree::TerminalNode* PascalSParser::ConstValueContext::STRING() {
  return getToken(PascalSParser::STRING, 0);
}


size_t PascalSParser::ConstValueContext::getRuleIndex() const {
  return PascalSParser::RuleConstValue;
}

antlrcpp::Any PascalSParser::ConstValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitConstValue(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::ConstValueContext* PascalSParser::constValue() {
  ConstValueContext *_localctx = _tracker.createInstance<ConstValueContext>(_ctx, getState());
  enterRule(_localctx, 14, PascalSParser::RuleConstValue);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(151);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(142);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == PascalSParser::PLUS) {
        setState(141);
        match(PascalSParser::PLUS);
      }
      setState(144);
      num();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(146);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == PascalSParser::MINUS) {
        setState(145);
        match(PascalSParser::MINUS);
      }
      setState(148);
      num();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(149);
      match(PascalSParser::LETTER);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(150);
      match(PascalSParser::STRING);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarDeclarationsContext ------------------------------------------------------------------

PascalSParser::VarDeclarationsContext::VarDeclarationsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PascalSParser::VarDeclarationsContext::VAR() {
  return getToken(PascalSParser::VAR, 0);
}

PascalSParser::VarDeclarationContext* PascalSParser::VarDeclarationsContext::varDeclaration() {
  return getRuleContext<PascalSParser::VarDeclarationContext>(0);
}

tree::TerminalNode* PascalSParser::VarDeclarationsContext::SEMICOLON() {
  return getToken(PascalSParser::SEMICOLON, 0);
}


size_t PascalSParser::VarDeclarationsContext::getRuleIndex() const {
  return PascalSParser::RuleVarDeclarations;
}

antlrcpp::Any PascalSParser::VarDeclarationsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitVarDeclarations(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::VarDeclarationsContext* PascalSParser::varDeclarations() {
  VarDeclarationsContext *_localctx = _tracker.createInstance<VarDeclarationsContext>(_ctx, getState());
  enterRule(_localctx, 16, PascalSParser::RuleVarDeclarations);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(158);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);

      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(154);
      match(PascalSParser::VAR);
      setState(155);
      varDeclaration(0);
      setState(156);
      match(PascalSParser::SEMICOLON);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarDeclarationContext ------------------------------------------------------------------

PascalSParser::VarDeclarationContext::VarDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PascalSParser::IdListContext* PascalSParser::VarDeclarationContext::idList() {
  return getRuleContext<PascalSParser::IdListContext>(0);
}

tree::TerminalNode* PascalSParser::VarDeclarationContext::COLON() {
  return getToken(PascalSParser::COLON, 0);
}

PascalSParser::TypeContext* PascalSParser::VarDeclarationContext::type() {
  return getRuleContext<PascalSParser::TypeContext>(0);
}

PascalSParser::VarDeclarationContext* PascalSParser::VarDeclarationContext::varDeclaration() {
  return getRuleContext<PascalSParser::VarDeclarationContext>(0);
}

tree::TerminalNode* PascalSParser::VarDeclarationContext::SEMICOLON() {
  return getToken(PascalSParser::SEMICOLON, 0);
}


size_t PascalSParser::VarDeclarationContext::getRuleIndex() const {
  return PascalSParser::RuleVarDeclaration;
}

antlrcpp::Any PascalSParser::VarDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitVarDeclaration(this);
  else
    return visitor->visitChildren(this);
}


PascalSParser::VarDeclarationContext* PascalSParser::varDeclaration() {
   return varDeclaration(0);
}

PascalSParser::VarDeclarationContext* PascalSParser::varDeclaration(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  PascalSParser::VarDeclarationContext *_localctx = _tracker.createInstance<VarDeclarationContext>(_ctx, parentState);
  PascalSParser::VarDeclarationContext *previousContext = _localctx;
  size_t startState = 18;
  enterRecursionRule(_localctx, 18, PascalSParser::RuleVarDeclaration, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(161);
    idList();
    setState(162);
    match(PascalSParser::COLON);
    setState(163);
    type();
    _ctx->stop = _input->LT(-1);
    setState(173);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<VarDeclarationContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleVarDeclaration);
        setState(165);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(166);
        match(PascalSParser::SEMICOLON);
        setState(167);
        idList();
        setState(168);
        match(PascalSParser::COLON);
        setState(169);
        type(); 
      }
      setState(175);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- TypeContext ------------------------------------------------------------------

PascalSParser::TypeContext::TypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PascalSParser::BasicTypeContext* PascalSParser::TypeContext::basicType() {
  return getRuleContext<PascalSParser::BasicTypeContext>(0);
}

tree::TerminalNode* PascalSParser::TypeContext::ARRAY() {
  return getToken(PascalSParser::ARRAY, 0);
}

tree::TerminalNode* PascalSParser::TypeContext::LBRACKET() {
  return getToken(PascalSParser::LBRACKET, 0);
}

PascalSParser::PeriodContext* PascalSParser::TypeContext::period() {
  return getRuleContext<PascalSParser::PeriodContext>(0);
}

tree::TerminalNode* PascalSParser::TypeContext::RBRACKET() {
  return getToken(PascalSParser::RBRACKET, 0);
}

tree::TerminalNode* PascalSParser::TypeContext::OF() {
  return getToken(PascalSParser::OF, 0);
}


size_t PascalSParser::TypeContext::getRuleIndex() const {
  return PascalSParser::RuleType;
}

antlrcpp::Any PascalSParser::TypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitType(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::TypeContext* PascalSParser::type() {
  TypeContext *_localctx = _tracker.createInstance<TypeContext>(_ctx, getState());
  enterRule(_localctx, 20, PascalSParser::RuleType);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(184);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PascalSParser::INTEGER:
      case PascalSParser::REAL:
      case PascalSParser::BOOLEAN:
      case PascalSParser::CHAR: {
        enterOuterAlt(_localctx, 1);
        setState(176);
        basicType();
        break;
      }

      case PascalSParser::ARRAY: {
        enterOuterAlt(_localctx, 2);
        setState(177);
        match(PascalSParser::ARRAY);
        setState(178);
        match(PascalSParser::LBRACKET);
        setState(179);
        period(0);
        setState(180);
        match(PascalSParser::RBRACKET);
        setState(181);
        match(PascalSParser::OF);
        setState(182);
        basicType();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BasicTypeContext ------------------------------------------------------------------

PascalSParser::BasicTypeContext::BasicTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PascalSParser::BasicTypeContext::INTEGER() {
  return getToken(PascalSParser::INTEGER, 0);
}

tree::TerminalNode* PascalSParser::BasicTypeContext::REAL() {
  return getToken(PascalSParser::REAL, 0);
}

tree::TerminalNode* PascalSParser::BasicTypeContext::BOOLEAN() {
  return getToken(PascalSParser::BOOLEAN, 0);
}

tree::TerminalNode* PascalSParser::BasicTypeContext::CHAR() {
  return getToken(PascalSParser::CHAR, 0);
}


size_t PascalSParser::BasicTypeContext::getRuleIndex() const {
  return PascalSParser::RuleBasicType;
}

antlrcpp::Any PascalSParser::BasicTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitBasicType(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::BasicTypeContext* PascalSParser::basicType() {
  BasicTypeContext *_localctx = _tracker.createInstance<BasicTypeContext>(_ctx, getState());
  enterRule(_localctx, 22, PascalSParser::RuleBasicType);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(186);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << PascalSParser::INTEGER)
      | (1ULL << PascalSParser::REAL)
      | (1ULL << PascalSParser::BOOLEAN)
      | (1ULL << PascalSParser::CHAR))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PeriodContext ------------------------------------------------------------------

PascalSParser::PeriodContext::PeriodContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> PascalSParser::PeriodContext::NUM() {
  return getTokens(PascalSParser::NUM);
}

tree::TerminalNode* PascalSParser::PeriodContext::NUM(size_t i) {
  return getToken(PascalSParser::NUM, i);
}

tree::TerminalNode* PascalSParser::PeriodContext::DOTDOT() {
  return getToken(PascalSParser::DOTDOT, 0);
}

PascalSParser::PeriodContext* PascalSParser::PeriodContext::period() {
  return getRuleContext<PascalSParser::PeriodContext>(0);
}

tree::TerminalNode* PascalSParser::PeriodContext::COMMA() {
  return getToken(PascalSParser::COMMA, 0);
}


size_t PascalSParser::PeriodContext::getRuleIndex() const {
  return PascalSParser::RulePeriod;
}

antlrcpp::Any PascalSParser::PeriodContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitPeriod(this);
  else
    return visitor->visitChildren(this);
}


PascalSParser::PeriodContext* PascalSParser::period() {
   return period(0);
}

PascalSParser::PeriodContext* PascalSParser::period(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  PascalSParser::PeriodContext *_localctx = _tracker.createInstance<PeriodContext>(_ctx, parentState);
  PascalSParser::PeriodContext *previousContext = _localctx;
  size_t startState = 24;
  enterRecursionRule(_localctx, 24, PascalSParser::RulePeriod, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(189);
    match(PascalSParser::NUM);
    setState(190);
    match(PascalSParser::DOTDOT);
    setState(191);
    match(PascalSParser::NUM);
    _ctx->stop = _input->LT(-1);
    setState(200);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<PeriodContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RulePeriod);
        setState(193);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(194);
        match(PascalSParser::COMMA);
        setState(195);
        match(PascalSParser::NUM);
        setState(196);
        match(PascalSParser::DOTDOT);
        setState(197);
        match(PascalSParser::NUM); 
      }
      setState(202);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- SubprogramDeclarationsContext ------------------------------------------------------------------

PascalSParser::SubprogramDeclarationsContext::SubprogramDeclarationsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PascalSParser::SubprogramDeclarationsContext* PascalSParser::SubprogramDeclarationsContext::subprogramDeclarations() {
  return getRuleContext<PascalSParser::SubprogramDeclarationsContext>(0);
}

PascalSParser::SubprogramContext* PascalSParser::SubprogramDeclarationsContext::subprogram() {
  return getRuleContext<PascalSParser::SubprogramContext>(0);
}

tree::TerminalNode* PascalSParser::SubprogramDeclarationsContext::SEMICOLON() {
  return getToken(PascalSParser::SEMICOLON, 0);
}


size_t PascalSParser::SubprogramDeclarationsContext::getRuleIndex() const {
  return PascalSParser::RuleSubprogramDeclarations;
}

antlrcpp::Any PascalSParser::SubprogramDeclarationsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitSubprogramDeclarations(this);
  else
    return visitor->visitChildren(this);
}


PascalSParser::SubprogramDeclarationsContext* PascalSParser::subprogramDeclarations() {
   return subprogramDeclarations(0);
}

PascalSParser::SubprogramDeclarationsContext* PascalSParser::subprogramDeclarations(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  PascalSParser::SubprogramDeclarationsContext *_localctx = _tracker.createInstance<SubprogramDeclarationsContext>(_ctx, parentState);
  PascalSParser::SubprogramDeclarationsContext *previousContext = _localctx;
  size_t startState = 26;
  enterRecursionRule(_localctx, 26, PascalSParser::RuleSubprogramDeclarations, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    _ctx->stop = _input->LT(-1);
    setState(210);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<SubprogramDeclarationsContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleSubprogramDeclarations);
        setState(204);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(205);
        subprogram();
        setState(206);
        match(PascalSParser::SEMICOLON); 
      }
      setState(212);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- SubprogramContext ------------------------------------------------------------------

PascalSParser::SubprogramContext::SubprogramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PascalSParser::SubprogramHeadContext* PascalSParser::SubprogramContext::subprogramHead() {
  return getRuleContext<PascalSParser::SubprogramHeadContext>(0);
}

tree::TerminalNode* PascalSParser::SubprogramContext::SEMICOLON() {
  return getToken(PascalSParser::SEMICOLON, 0);
}

PascalSParser::SubprogramBodyContext* PascalSParser::SubprogramContext::subprogramBody() {
  return getRuleContext<PascalSParser::SubprogramBodyContext>(0);
}


size_t PascalSParser::SubprogramContext::getRuleIndex() const {
  return PascalSParser::RuleSubprogram;
}

antlrcpp::Any PascalSParser::SubprogramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitSubprogram(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::SubprogramContext* PascalSParser::subprogram() {
  SubprogramContext *_localctx = _tracker.createInstance<SubprogramContext>(_ctx, getState());
  enterRule(_localctx, 28, PascalSParser::RuleSubprogram);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(213);
    subprogramHead();
    setState(214);
    match(PascalSParser::SEMICOLON);
    setState(215);
    subprogramBody();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SubprogramHeadContext ------------------------------------------------------------------

PascalSParser::SubprogramHeadContext::SubprogramHeadContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PascalSParser::SubprogramHeadContext::PROCEDURE() {
  return getToken(PascalSParser::PROCEDURE, 0);
}

tree::TerminalNode* PascalSParser::SubprogramHeadContext::ID() {
  return getToken(PascalSParser::ID, 0);
}

PascalSParser::FormalParameterContext* PascalSParser::SubprogramHeadContext::formalParameter() {
  return getRuleContext<PascalSParser::FormalParameterContext>(0);
}

tree::TerminalNode* PascalSParser::SubprogramHeadContext::FUNCTION() {
  return getToken(PascalSParser::FUNCTION, 0);
}

tree::TerminalNode* PascalSParser::SubprogramHeadContext::COLON() {
  return getToken(PascalSParser::COLON, 0);
}

PascalSParser::BasicTypeContext* PascalSParser::SubprogramHeadContext::basicType() {
  return getRuleContext<PascalSParser::BasicTypeContext>(0);
}


size_t PascalSParser::SubprogramHeadContext::getRuleIndex() const {
  return PascalSParser::RuleSubprogramHead;
}

antlrcpp::Any PascalSParser::SubprogramHeadContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitSubprogramHead(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::SubprogramHeadContext* PascalSParser::subprogramHead() {
  SubprogramHeadContext *_localctx = _tracker.createInstance<SubprogramHeadContext>(_ctx, getState());
  enterRule(_localctx, 30, PascalSParser::RuleSubprogramHead);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(226);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PascalSParser::PROCEDURE: {
        enterOuterAlt(_localctx, 1);
        setState(217);
        match(PascalSParser::PROCEDURE);
        setState(218);
        match(PascalSParser::ID);
        setState(219);
        formalParameter();
        break;
      }

      case PascalSParser::FUNCTION: {
        enterOuterAlt(_localctx, 2);
        setState(220);
        match(PascalSParser::FUNCTION);
        setState(221);
        match(PascalSParser::ID);
        setState(222);
        formalParameter();
        setState(223);
        match(PascalSParser::COLON);
        setState(224);
        basicType();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FormalParameterContext ------------------------------------------------------------------

PascalSParser::FormalParameterContext::FormalParameterContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PascalSParser::FormalParameterContext::LPAREN() {
  return getToken(PascalSParser::LPAREN, 0);
}

tree::TerminalNode* PascalSParser::FormalParameterContext::RPAREN() {
  return getToken(PascalSParser::RPAREN, 0);
}

PascalSParser::ParameterListContext* PascalSParser::FormalParameterContext::parameterList() {
  return getRuleContext<PascalSParser::ParameterListContext>(0);
}


size_t PascalSParser::FormalParameterContext::getRuleIndex() const {
  return PascalSParser::RuleFormalParameter;
}

antlrcpp::Any PascalSParser::FormalParameterContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitFormalParameter(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::FormalParameterContext* PascalSParser::formalParameter() {
  FormalParameterContext *_localctx = _tracker.createInstance<FormalParameterContext>(_ctx, getState());
  enterRule(_localctx, 32, PascalSParser::RuleFormalParameter);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(234);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PascalSParser::SEMICOLON:
      case PascalSParser::COLON: {
        enterOuterAlt(_localctx, 1);

        break;
      }

      case PascalSParser::LPAREN: {
        enterOuterAlt(_localctx, 2);
        setState(229);
        match(PascalSParser::LPAREN);
        setState(231);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PascalSParser::VAR

        || _la == PascalSParser::ID) {
          setState(230);
          parameterList(0);
        }
        setState(233);
        match(PascalSParser::RPAREN);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParameterListContext ------------------------------------------------------------------

PascalSParser::ParameterListContext::ParameterListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PascalSParser::ParameterContext* PascalSParser::ParameterListContext::parameter() {
  return getRuleContext<PascalSParser::ParameterContext>(0);
}

PascalSParser::ParameterListContext* PascalSParser::ParameterListContext::parameterList() {
  return getRuleContext<PascalSParser::ParameterListContext>(0);
}

tree::TerminalNode* PascalSParser::ParameterListContext::SEMICOLON() {
  return getToken(PascalSParser::SEMICOLON, 0);
}


size_t PascalSParser::ParameterListContext::getRuleIndex() const {
  return PascalSParser::RuleParameterList;
}

antlrcpp::Any PascalSParser::ParameterListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitParameterList(this);
  else
    return visitor->visitChildren(this);
}


PascalSParser::ParameterListContext* PascalSParser::parameterList() {
   return parameterList(0);
}

PascalSParser::ParameterListContext* PascalSParser::parameterList(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  PascalSParser::ParameterListContext *_localctx = _tracker.createInstance<ParameterListContext>(_ctx, parentState);
  PascalSParser::ParameterListContext *previousContext = _localctx;
  size_t startState = 34;
  enterRecursionRule(_localctx, 34, PascalSParser::RuleParameterList, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(237);
    parameter();
    _ctx->stop = _input->LT(-1);
    setState(244);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<ParameterListContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleParameterList);
        setState(239);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(240);
        match(PascalSParser::SEMICOLON);
        setState(241);
        parameter(); 
      }
      setState(246);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- ParameterContext ------------------------------------------------------------------

PascalSParser::ParameterContext::ParameterContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PascalSParser::VarParameterContext* PascalSParser::ParameterContext::varParameter() {
  return getRuleContext<PascalSParser::VarParameterContext>(0);
}

PascalSParser::ValueParameterContext* PascalSParser::ParameterContext::valueParameter() {
  return getRuleContext<PascalSParser::ValueParameterContext>(0);
}


size_t PascalSParser::ParameterContext::getRuleIndex() const {
  return PascalSParser::RuleParameter;
}

antlrcpp::Any PascalSParser::ParameterContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitParameter(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::ParameterContext* PascalSParser::parameter() {
  ParameterContext *_localctx = _tracker.createInstance<ParameterContext>(_ctx, getState());
  enterRule(_localctx, 36, PascalSParser::RuleParameter);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(249);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PascalSParser::VAR: {
        enterOuterAlt(_localctx, 1);
        setState(247);
        varParameter();
        break;
      }

      case PascalSParser::ID: {
        enterOuterAlt(_localctx, 2);
        setState(248);
        valueParameter();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarParameterContext ------------------------------------------------------------------

PascalSParser::VarParameterContext::VarParameterContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PascalSParser::VarParameterContext::VAR() {
  return getToken(PascalSParser::VAR, 0);
}

PascalSParser::ValueParameterContext* PascalSParser::VarParameterContext::valueParameter() {
  return getRuleContext<PascalSParser::ValueParameterContext>(0);
}


size_t PascalSParser::VarParameterContext::getRuleIndex() const {
  return PascalSParser::RuleVarParameter;
}

antlrcpp::Any PascalSParser::VarParameterContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitVarParameter(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::VarParameterContext* PascalSParser::varParameter() {
  VarParameterContext *_localctx = _tracker.createInstance<VarParameterContext>(_ctx, getState());
  enterRule(_localctx, 38, PascalSParser::RuleVarParameter);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(251);
    match(PascalSParser::VAR);
    setState(252);
    valueParameter();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ValueParameterContext ------------------------------------------------------------------

PascalSParser::ValueParameterContext::ValueParameterContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PascalSParser::IdListContext* PascalSParser::ValueParameterContext::idList() {
  return getRuleContext<PascalSParser::IdListContext>(0);
}

tree::TerminalNode* PascalSParser::ValueParameterContext::COLON() {
  return getToken(PascalSParser::COLON, 0);
}

PascalSParser::TypeContext* PascalSParser::ValueParameterContext::type() {
  return getRuleContext<PascalSParser::TypeContext>(0);
}


size_t PascalSParser::ValueParameterContext::getRuleIndex() const {
  return PascalSParser::RuleValueParameter;
}

antlrcpp::Any PascalSParser::ValueParameterContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitValueParameter(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::ValueParameterContext* PascalSParser::valueParameter() {
  ValueParameterContext *_localctx = _tracker.createInstance<ValueParameterContext>(_ctx, getState());
  enterRule(_localctx, 40, PascalSParser::RuleValueParameter);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(254);
    idList();
    setState(255);
    match(PascalSParser::COLON);
    setState(256);
    type();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SubprogramBodyContext ------------------------------------------------------------------

PascalSParser::SubprogramBodyContext::SubprogramBodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PascalSParser::ConstDeclarationsContext* PascalSParser::SubprogramBodyContext::constDeclarations() {
  return getRuleContext<PascalSParser::ConstDeclarationsContext>(0);
}

PascalSParser::VarDeclarationsContext* PascalSParser::SubprogramBodyContext::varDeclarations() {
  return getRuleContext<PascalSParser::VarDeclarationsContext>(0);
}

PascalSParser::CompoundStatementContext* PascalSParser::SubprogramBodyContext::compoundStatement() {
  return getRuleContext<PascalSParser::CompoundStatementContext>(0);
}


size_t PascalSParser::SubprogramBodyContext::getRuleIndex() const {
  return PascalSParser::RuleSubprogramBody;
}

antlrcpp::Any PascalSParser::SubprogramBodyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitSubprogramBody(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::SubprogramBodyContext* PascalSParser::subprogramBody() {
  SubprogramBodyContext *_localctx = _tracker.createInstance<SubprogramBodyContext>(_ctx, getState());
  enterRule(_localctx, 42, PascalSParser::RuleSubprogramBody);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(258);
    constDeclarations();
    setState(259);
    varDeclarations();
    setState(260);
    compoundStatement();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CompoundStatementContext ------------------------------------------------------------------

PascalSParser::CompoundStatementContext::CompoundStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PascalSParser::CompoundStatementContext::BEGIN() {
  return getToken(PascalSParser::BEGIN, 0);
}

PascalSParser::StatementListContext* PascalSParser::CompoundStatementContext::statementList() {
  return getRuleContext<PascalSParser::StatementListContext>(0);
}

tree::TerminalNode* PascalSParser::CompoundStatementContext::END() {
  return getToken(PascalSParser::END, 0);
}


size_t PascalSParser::CompoundStatementContext::getRuleIndex() const {
  return PascalSParser::RuleCompoundStatement;
}

antlrcpp::Any PascalSParser::CompoundStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitCompoundStatement(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::CompoundStatementContext* PascalSParser::compoundStatement() {
  CompoundStatementContext *_localctx = _tracker.createInstance<CompoundStatementContext>(_ctx, getState());
  enterRule(_localctx, 44, PascalSParser::RuleCompoundStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(262);
    match(PascalSParser::BEGIN);
    setState(263);
    statementList(0);
    setState(264);
    match(PascalSParser::END);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementListContext ------------------------------------------------------------------

PascalSParser::StatementListContext::StatementListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PascalSParser::StatementContext* PascalSParser::StatementListContext::statement() {
  return getRuleContext<PascalSParser::StatementContext>(0);
}

PascalSParser::StatementListContext* PascalSParser::StatementListContext::statementList() {
  return getRuleContext<PascalSParser::StatementListContext>(0);
}

tree::TerminalNode* PascalSParser::StatementListContext::SEMICOLON() {
  return getToken(PascalSParser::SEMICOLON, 0);
}


size_t PascalSParser::StatementListContext::getRuleIndex() const {
  return PascalSParser::RuleStatementList;
}

antlrcpp::Any PascalSParser::StatementListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitStatementList(this);
  else
    return visitor->visitChildren(this);
}


PascalSParser::StatementListContext* PascalSParser::statementList() {
   return statementList(0);
}

PascalSParser::StatementListContext* PascalSParser::statementList(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  PascalSParser::StatementListContext *_localctx = _tracker.createInstance<StatementListContext>(_ctx, parentState);
  PascalSParser::StatementListContext *previousContext = _localctx;
  size_t startState = 46;
  enterRecursionRule(_localctx, 46, PascalSParser::RuleStatementList, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(267);
    statement();
    _ctx->stop = _input->LT(-1);
    setState(274);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<StatementListContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleStatementList);
        setState(269);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(270);
        match(PascalSParser::SEMICOLON);
        setState(271);
        statement(); 
      }
      setState(276);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

PascalSParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PascalSParser::VariableContext* PascalSParser::StatementContext::variable() {
  return getRuleContext<PascalSParser::VariableContext>(0);
}

tree::TerminalNode* PascalSParser::StatementContext::ASSIGNOP() {
  return getToken(PascalSParser::ASSIGNOP, 0);
}

PascalSParser::ExpressionContext* PascalSParser::StatementContext::expression() {
  return getRuleContext<PascalSParser::ExpressionContext>(0);
}

tree::TerminalNode* PascalSParser::StatementContext::ID() {
  return getToken(PascalSParser::ID, 0);
}

PascalSParser::ProcedureCallContext* PascalSParser::StatementContext::procedureCall() {
  return getRuleContext<PascalSParser::ProcedureCallContext>(0);
}

PascalSParser::CompoundStatementContext* PascalSParser::StatementContext::compoundStatement() {
  return getRuleContext<PascalSParser::CompoundStatementContext>(0);
}

PascalSParser::IfStatementContext* PascalSParser::StatementContext::ifStatement() {
  return getRuleContext<PascalSParser::IfStatementContext>(0);
}

PascalSParser::ForStatementContext* PascalSParser::StatementContext::forStatement() {
  return getRuleContext<PascalSParser::ForStatementContext>(0);
}

PascalSParser::ReadStatementContext* PascalSParser::StatementContext::readStatement() {
  return getRuleContext<PascalSParser::ReadStatementContext>(0);
}

PascalSParser::BreakStatementContext* PascalSParser::StatementContext::breakStatement() {
  return getRuleContext<PascalSParser::BreakStatementContext>(0);
}

PascalSParser::WhileStatementContext* PascalSParser::StatementContext::whileStatement() {
  return getRuleContext<PascalSParser::WhileStatementContext>(0);
}

PascalSParser::WriteStatementContext* PascalSParser::StatementContext::writeStatement() {
  return getRuleContext<PascalSParser::WriteStatementContext>(0);
}


size_t PascalSParser::StatementContext::getRuleIndex() const {
  return PascalSParser::RuleStatement;
}

antlrcpp::Any PascalSParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::StatementContext* PascalSParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 48, PascalSParser::RuleStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(293);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);

      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(278);
      variable();
      setState(279);
      match(PascalSParser::ASSIGNOP);
      setState(280);
      expression();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(282);
      match(PascalSParser::ID);
      setState(283);
      match(PascalSParser::ASSIGNOP);
      setState(284);
      expression();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(285);
      procedureCall();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(286);
      compoundStatement();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(287);
      ifStatement();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(288);
      forStatement();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(289);
      readStatement();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(290);
      breakStatement();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(291);
      whileStatement();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(292);
      writeStatement();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IfStatementContext ------------------------------------------------------------------

PascalSParser::IfStatementContext::IfStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PascalSParser::IfStatementContext::IF() {
  return getToken(PascalSParser::IF, 0);
}

PascalSParser::ExpressionContext* PascalSParser::IfStatementContext::expression() {
  return getRuleContext<PascalSParser::ExpressionContext>(0);
}

tree::TerminalNode* PascalSParser::IfStatementContext::THEN() {
  return getToken(PascalSParser::THEN, 0);
}

PascalSParser::StatementContext* PascalSParser::IfStatementContext::statement() {
  return getRuleContext<PascalSParser::StatementContext>(0);
}

PascalSParser::ElsePartContext* PascalSParser::IfStatementContext::elsePart() {
  return getRuleContext<PascalSParser::ElsePartContext>(0);
}


size_t PascalSParser::IfStatementContext::getRuleIndex() const {
  return PascalSParser::RuleIfStatement;
}

antlrcpp::Any PascalSParser::IfStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitIfStatement(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::IfStatementContext* PascalSParser::ifStatement() {
  IfStatementContext *_localctx = _tracker.createInstance<IfStatementContext>(_ctx, getState());
  enterRule(_localctx, 50, PascalSParser::RuleIfStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(295);
    match(PascalSParser::IF);
    setState(296);
    expression();
    setState(297);
    match(PascalSParser::THEN);
    setState(298);
    statement();
    setState(299);
    elsePart();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ForStatementContext ------------------------------------------------------------------

PascalSParser::ForStatementContext::ForStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PascalSParser::ForStatementContext::FOR() {
  return getToken(PascalSParser::FOR, 0);
}

tree::TerminalNode* PascalSParser::ForStatementContext::ID() {
  return getToken(PascalSParser::ID, 0);
}

tree::TerminalNode* PascalSParser::ForStatementContext::ASSIGNOP() {
  return getToken(PascalSParser::ASSIGNOP, 0);
}

std::vector<PascalSParser::ExpressionContext *> PascalSParser::ForStatementContext::expression() {
  return getRuleContexts<PascalSParser::ExpressionContext>();
}

PascalSParser::ExpressionContext* PascalSParser::ForStatementContext::expression(size_t i) {
  return getRuleContext<PascalSParser::ExpressionContext>(i);
}

tree::TerminalNode* PascalSParser::ForStatementContext::TO() {
  return getToken(PascalSParser::TO, 0);
}

tree::TerminalNode* PascalSParser::ForStatementContext::DO() {
  return getToken(PascalSParser::DO, 0);
}

PascalSParser::StatementContext* PascalSParser::ForStatementContext::statement() {
  return getRuleContext<PascalSParser::StatementContext>(0);
}


size_t PascalSParser::ForStatementContext::getRuleIndex() const {
  return PascalSParser::RuleForStatement;
}

antlrcpp::Any PascalSParser::ForStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitForStatement(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::ForStatementContext* PascalSParser::forStatement() {
  ForStatementContext *_localctx = _tracker.createInstance<ForStatementContext>(_ctx, getState());
  enterRule(_localctx, 52, PascalSParser::RuleForStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(301);
    match(PascalSParser::FOR);
    setState(302);
    match(PascalSParser::ID);
    setState(303);
    match(PascalSParser::ASSIGNOP);
    setState(304);
    expression();
    setState(305);
    match(PascalSParser::TO);
    setState(306);
    expression();
    setState(307);
    match(PascalSParser::DO);
    setState(308);
    statement();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ReadStatementContext ------------------------------------------------------------------

PascalSParser::ReadStatementContext::ReadStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PascalSParser::ReadStatementContext::READ() {
  return getToken(PascalSParser::READ, 0);
}

tree::TerminalNode* PascalSParser::ReadStatementContext::LPAREN() {
  return getToken(PascalSParser::LPAREN, 0);
}

PascalSParser::VariableListContext* PascalSParser::ReadStatementContext::variableList() {
  return getRuleContext<PascalSParser::VariableListContext>(0);
}

tree::TerminalNode* PascalSParser::ReadStatementContext::RPAREN() {
  return getToken(PascalSParser::RPAREN, 0);
}


size_t PascalSParser::ReadStatementContext::getRuleIndex() const {
  return PascalSParser::RuleReadStatement;
}

antlrcpp::Any PascalSParser::ReadStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitReadStatement(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::ReadStatementContext* PascalSParser::readStatement() {
  ReadStatementContext *_localctx = _tracker.createInstance<ReadStatementContext>(_ctx, getState());
  enterRule(_localctx, 54, PascalSParser::RuleReadStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(310);
    match(PascalSParser::READ);
    setState(311);
    match(PascalSParser::LPAREN);
    setState(312);
    variableList(0);
    setState(313);
    match(PascalSParser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- WhileStatementContext ------------------------------------------------------------------

PascalSParser::WhileStatementContext::WhileStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PascalSParser::WhileStatementContext::WHILE() {
  return getToken(PascalSParser::WHILE, 0);
}

PascalSParser::ExpressionContext* PascalSParser::WhileStatementContext::expression() {
  return getRuleContext<PascalSParser::ExpressionContext>(0);
}

tree::TerminalNode* PascalSParser::WhileStatementContext::DO() {
  return getToken(PascalSParser::DO, 0);
}

PascalSParser::StatementContext* PascalSParser::WhileStatementContext::statement() {
  return getRuleContext<PascalSParser::StatementContext>(0);
}


size_t PascalSParser::WhileStatementContext::getRuleIndex() const {
  return PascalSParser::RuleWhileStatement;
}

antlrcpp::Any PascalSParser::WhileStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitWhileStatement(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::WhileStatementContext* PascalSParser::whileStatement() {
  WhileStatementContext *_localctx = _tracker.createInstance<WhileStatementContext>(_ctx, getState());
  enterRule(_localctx, 56, PascalSParser::RuleWhileStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(315);
    match(PascalSParser::WHILE);
    setState(316);
    expression();
    setState(317);
    match(PascalSParser::DO);
    setState(318);
    statement();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- WriteStatementContext ------------------------------------------------------------------

PascalSParser::WriteStatementContext::WriteStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PascalSParser::WriteStatementContext::WRITE() {
  return getToken(PascalSParser::WRITE, 0);
}

tree::TerminalNode* PascalSParser::WriteStatementContext::LPAREN() {
  return getToken(PascalSParser::LPAREN, 0);
}

PascalSParser::ExpressionListContext* PascalSParser::WriteStatementContext::expressionList() {
  return getRuleContext<PascalSParser::ExpressionListContext>(0);
}

tree::TerminalNode* PascalSParser::WriteStatementContext::RPAREN() {
  return getToken(PascalSParser::RPAREN, 0);
}


size_t PascalSParser::WriteStatementContext::getRuleIndex() const {
  return PascalSParser::RuleWriteStatement;
}

antlrcpp::Any PascalSParser::WriteStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitWriteStatement(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::WriteStatementContext* PascalSParser::writeStatement() {
  WriteStatementContext *_localctx = _tracker.createInstance<WriteStatementContext>(_ctx, getState());
  enterRule(_localctx, 58, PascalSParser::RuleWriteStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(320);
    match(PascalSParser::WRITE);
    setState(321);
    match(PascalSParser::LPAREN);
    setState(322);
    expressionList(0);
    setState(323);
    match(PascalSParser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BreakStatementContext ------------------------------------------------------------------

PascalSParser::BreakStatementContext::BreakStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PascalSParser::BreakStatementContext::BREAK() {
  return getToken(PascalSParser::BREAK, 0);
}


size_t PascalSParser::BreakStatementContext::getRuleIndex() const {
  return PascalSParser::RuleBreakStatement;
}

antlrcpp::Any PascalSParser::BreakStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitBreakStatement(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::BreakStatementContext* PascalSParser::breakStatement() {
  BreakStatementContext *_localctx = _tracker.createInstance<BreakStatementContext>(_ctx, getState());
  enterRule(_localctx, 60, PascalSParser::RuleBreakStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(325);
    match(PascalSParser::BREAK);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableListContext ------------------------------------------------------------------

PascalSParser::VariableListContext::VariableListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PascalSParser::VariableContext* PascalSParser::VariableListContext::variable() {
  return getRuleContext<PascalSParser::VariableContext>(0);
}

PascalSParser::VariableListContext* PascalSParser::VariableListContext::variableList() {
  return getRuleContext<PascalSParser::VariableListContext>(0);
}

tree::TerminalNode* PascalSParser::VariableListContext::COMMA() {
  return getToken(PascalSParser::COMMA, 0);
}


size_t PascalSParser::VariableListContext::getRuleIndex() const {
  return PascalSParser::RuleVariableList;
}

antlrcpp::Any PascalSParser::VariableListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitVariableList(this);
  else
    return visitor->visitChildren(this);
}


PascalSParser::VariableListContext* PascalSParser::variableList() {
   return variableList(0);
}

PascalSParser::VariableListContext* PascalSParser::variableList(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  PascalSParser::VariableListContext *_localctx = _tracker.createInstance<VariableListContext>(_ctx, parentState);
  PascalSParser::VariableListContext *previousContext = _localctx;
  size_t startState = 62;
  enterRecursionRule(_localctx, 62, PascalSParser::RuleVariableList, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(328);
    variable();
    _ctx->stop = _input->LT(-1);
    setState(335);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<VariableListContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleVariableList);
        setState(330);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(331);
        match(PascalSParser::COMMA);
        setState(332);
        variable(); 
      }
      setState(337);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- VariableContext ------------------------------------------------------------------

PascalSParser::VariableContext::VariableContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PascalSParser::VariableContext::ID() {
  return getToken(PascalSParser::ID, 0);
}

PascalSParser::IdVarPartContext* PascalSParser::VariableContext::idVarPart() {
  return getRuleContext<PascalSParser::IdVarPartContext>(0);
}


size_t PascalSParser::VariableContext::getRuleIndex() const {
  return PascalSParser::RuleVariable;
}

antlrcpp::Any PascalSParser::VariableContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitVariable(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::VariableContext* PascalSParser::variable() {
  VariableContext *_localctx = _tracker.createInstance<VariableContext>(_ctx, getState());
  enterRule(_localctx, 64, PascalSParser::RuleVariable);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(338);
    match(PascalSParser::ID);
    setState(339);
    idVarPart();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IdVarPartContext ------------------------------------------------------------------

PascalSParser::IdVarPartContext::IdVarPartContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PascalSParser::IdVarPartContext::LBRACKET() {
  return getToken(PascalSParser::LBRACKET, 0);
}

PascalSParser::ExpressionListContext* PascalSParser::IdVarPartContext::expressionList() {
  return getRuleContext<PascalSParser::ExpressionListContext>(0);
}

tree::TerminalNode* PascalSParser::IdVarPartContext::RBRACKET() {
  return getToken(PascalSParser::RBRACKET, 0);
}


size_t PascalSParser::IdVarPartContext::getRuleIndex() const {
  return PascalSParser::RuleIdVarPart;
}

antlrcpp::Any PascalSParser::IdVarPartContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitIdVarPart(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::IdVarPartContext* PascalSParser::idVarPart() {
  IdVarPartContext *_localctx = _tracker.createInstance<IdVarPartContext>(_ctx, getState());
  enterRule(_localctx, 66, PascalSParser::RuleIdVarPart);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(346);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);

      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(342);
      match(PascalSParser::LBRACKET);
      setState(343);
      expressionList(0);
      setState(344);
      match(PascalSParser::RBRACKET);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ProcedureCallContext ------------------------------------------------------------------

PascalSParser::ProcedureCallContext::ProcedureCallContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PascalSParser::ProcedureCallContext::ID() {
  return getToken(PascalSParser::ID, 0);
}

tree::TerminalNode* PascalSParser::ProcedureCallContext::LPAREN() {
  return getToken(PascalSParser::LPAREN, 0);
}

tree::TerminalNode* PascalSParser::ProcedureCallContext::RPAREN() {
  return getToken(PascalSParser::RPAREN, 0);
}

PascalSParser::ExpressionListContext* PascalSParser::ProcedureCallContext::expressionList() {
  return getRuleContext<PascalSParser::ExpressionListContext>(0);
}


size_t PascalSParser::ProcedureCallContext::getRuleIndex() const {
  return PascalSParser::RuleProcedureCall;
}

antlrcpp::Any PascalSParser::ProcedureCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitProcedureCall(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::ProcedureCallContext* PascalSParser::procedureCall() {
  ProcedureCallContext *_localctx = _tracker.createInstance<ProcedureCallContext>(_ctx, getState());
  enterRule(_localctx, 68, PascalSParser::RuleProcedureCall);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(355);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(348);
      match(PascalSParser::ID);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(349);
      match(PascalSParser::ID);
      setState(350);
      match(PascalSParser::LPAREN);
      setState(352);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << PascalSParser::NOT)
        | (1ULL << PascalSParser::LETTER)
        | (1ULL << PascalSParser::PLUS)
        | (1ULL << PascalSParser::MINUS)
        | (1ULL << PascalSParser::LPAREN)
        | (1ULL << PascalSParser::ID)
        | (1ULL << PascalSParser::NUM)
        | (1ULL << PascalSParser::STRING))) != 0)) {
        setState(351);
        expressionList(0);
      }
      setState(354);
      match(PascalSParser::RPAREN);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ElsePartContext ------------------------------------------------------------------

PascalSParser::ElsePartContext::ElsePartContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PascalSParser::ElsePartContext::ELSE() {
  return getToken(PascalSParser::ELSE, 0);
}

PascalSParser::StatementContext* PascalSParser::ElsePartContext::statement() {
  return getRuleContext<PascalSParser::StatementContext>(0);
}


size_t PascalSParser::ElsePartContext::getRuleIndex() const {
  return PascalSParser::RuleElsePart;
}

antlrcpp::Any PascalSParser::ElsePartContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitElsePart(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::ElsePartContext* PascalSParser::elsePart() {
  ElsePartContext *_localctx = _tracker.createInstance<ElsePartContext>(_ctx, getState());
  enterRule(_localctx, 70, PascalSParser::RuleElsePart);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(360);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);

      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(358);
      match(PascalSParser::ELSE);
      setState(359);
      statement();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionListContext ------------------------------------------------------------------

PascalSParser::ExpressionListContext::ExpressionListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PascalSParser::ExpressionContext* PascalSParser::ExpressionListContext::expression() {
  return getRuleContext<PascalSParser::ExpressionContext>(0);
}

PascalSParser::ExpressionListContext* PascalSParser::ExpressionListContext::expressionList() {
  return getRuleContext<PascalSParser::ExpressionListContext>(0);
}

tree::TerminalNode* PascalSParser::ExpressionListContext::COMMA() {
  return getToken(PascalSParser::COMMA, 0);
}


size_t PascalSParser::ExpressionListContext::getRuleIndex() const {
  return PascalSParser::RuleExpressionList;
}

antlrcpp::Any PascalSParser::ExpressionListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitExpressionList(this);
  else
    return visitor->visitChildren(this);
}


PascalSParser::ExpressionListContext* PascalSParser::expressionList() {
   return expressionList(0);
}

PascalSParser::ExpressionListContext* PascalSParser::expressionList(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  PascalSParser::ExpressionListContext *_localctx = _tracker.createInstance<ExpressionListContext>(_ctx, parentState);
  PascalSParser::ExpressionListContext *previousContext = _localctx;
  size_t startState = 72;
  enterRecursionRule(_localctx, 72, PascalSParser::RuleExpressionList, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(363);
    expression();
    _ctx->stop = _input->LT(-1);
    setState(370);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<ExpressionListContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleExpressionList);
        setState(365);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(366);
        match(PascalSParser::COMMA);
        setState(367);
        expression(); 
      }
      setState(372);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- ExpressionContext ------------------------------------------------------------------

PascalSParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<PascalSParser::SimpleExpressionContext *> PascalSParser::ExpressionContext::simpleExpression() {
  return getRuleContexts<PascalSParser::SimpleExpressionContext>();
}

PascalSParser::SimpleExpressionContext* PascalSParser::ExpressionContext::simpleExpression(size_t i) {
  return getRuleContext<PascalSParser::SimpleExpressionContext>(i);
}

PascalSParser::RelopContext* PascalSParser::ExpressionContext::relop() {
  return getRuleContext<PascalSParser::RelopContext>(0);
}


size_t PascalSParser::ExpressionContext::getRuleIndex() const {
  return PascalSParser::RuleExpression;
}

antlrcpp::Any PascalSParser::ExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitExpression(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::ExpressionContext* PascalSParser::expression() {
  ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, getState());
  enterRule(_localctx, 74, PascalSParser::RuleExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(378);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(373);
      simpleExpression(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(374);
      simpleExpression(0);
      setState(375);
      relop();
      setState(376);
      simpleExpression(0);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SimpleExpressionContext ------------------------------------------------------------------

PascalSParser::SimpleExpressionContext::SimpleExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PascalSParser::TermContext* PascalSParser::SimpleExpressionContext::term() {
  return getRuleContext<PascalSParser::TermContext>(0);
}

PascalSParser::SimpleExpressionContext* PascalSParser::SimpleExpressionContext::simpleExpression() {
  return getRuleContext<PascalSParser::SimpleExpressionContext>(0);
}

PascalSParser::AddopContext* PascalSParser::SimpleExpressionContext::addop() {
  return getRuleContext<PascalSParser::AddopContext>(0);
}


size_t PascalSParser::SimpleExpressionContext::getRuleIndex() const {
  return PascalSParser::RuleSimpleExpression;
}

antlrcpp::Any PascalSParser::SimpleExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitSimpleExpression(this);
  else
    return visitor->visitChildren(this);
}


PascalSParser::SimpleExpressionContext* PascalSParser::simpleExpression() {
   return simpleExpression(0);
}

PascalSParser::SimpleExpressionContext* PascalSParser::simpleExpression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  PascalSParser::SimpleExpressionContext *_localctx = _tracker.createInstance<SimpleExpressionContext>(_ctx, parentState);
  PascalSParser::SimpleExpressionContext *previousContext = _localctx;
  size_t startState = 76;
  enterRecursionRule(_localctx, 76, PascalSParser::RuleSimpleExpression, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(381);
    term(0);
    _ctx->stop = _input->LT(-1);
    setState(389);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<SimpleExpressionContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleSimpleExpression);
        setState(383);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(384);
        addop();
        setState(385);
        term(0); 
      }
      setState(391);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- TermContext ------------------------------------------------------------------

PascalSParser::TermContext::TermContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PascalSParser::FactorContext* PascalSParser::TermContext::factor() {
  return getRuleContext<PascalSParser::FactorContext>(0);
}

PascalSParser::TermContext* PascalSParser::TermContext::term() {
  return getRuleContext<PascalSParser::TermContext>(0);
}

PascalSParser::MulopContext* PascalSParser::TermContext::mulop() {
  return getRuleContext<PascalSParser::MulopContext>(0);
}


size_t PascalSParser::TermContext::getRuleIndex() const {
  return PascalSParser::RuleTerm;
}

antlrcpp::Any PascalSParser::TermContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitTerm(this);
  else
    return visitor->visitChildren(this);
}


PascalSParser::TermContext* PascalSParser::term() {
   return term(0);
}

PascalSParser::TermContext* PascalSParser::term(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  PascalSParser::TermContext *_localctx = _tracker.createInstance<TermContext>(_ctx, parentState);
  PascalSParser::TermContext *previousContext = _localctx;
  size_t startState = 78;
  enterRecursionRule(_localctx, 78, PascalSParser::RuleTerm, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(393);
    factor();
    _ctx->stop = _input->LT(-1);
    setState(401);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<TermContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleTerm);
        setState(395);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(396);
        mulop();
        setState(397);
        factor(); 
      }
      setState(403);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- FactorContext ------------------------------------------------------------------

PascalSParser::FactorContext::FactorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PascalSParser::NumContext* PascalSParser::FactorContext::num() {
  return getRuleContext<PascalSParser::NumContext>(0);
}

tree::TerminalNode* PascalSParser::FactorContext::ID() {
  return getToken(PascalSParser::ID, 0);
}

tree::TerminalNode* PascalSParser::FactorContext::LPAREN() {
  return getToken(PascalSParser::LPAREN, 0);
}

tree::TerminalNode* PascalSParser::FactorContext::RPAREN() {
  return getToken(PascalSParser::RPAREN, 0);
}

PascalSParser::ExpressionListContext* PascalSParser::FactorContext::expressionList() {
  return getRuleContext<PascalSParser::ExpressionListContext>(0);
}

PascalSParser::VariableContext* PascalSParser::FactorContext::variable() {
  return getRuleContext<PascalSParser::VariableContext>(0);
}

PascalSParser::ExpressionContext* PascalSParser::FactorContext::expression() {
  return getRuleContext<PascalSParser::ExpressionContext>(0);
}

tree::TerminalNode* PascalSParser::FactorContext::NOT() {
  return getToken(PascalSParser::NOT, 0);
}

PascalSParser::FactorContext* PascalSParser::FactorContext::factor() {
  return getRuleContext<PascalSParser::FactorContext>(0);
}

tree::TerminalNode* PascalSParser::FactorContext::MINUS() {
  return getToken(PascalSParser::MINUS, 0);
}

tree::TerminalNode* PascalSParser::FactorContext::PLUS() {
  return getToken(PascalSParser::PLUS, 0);
}

tree::TerminalNode* PascalSParser::FactorContext::STRING() {
  return getToken(PascalSParser::STRING, 0);
}

tree::TerminalNode* PascalSParser::FactorContext::LETTER() {
  return getToken(PascalSParser::LETTER, 0);
}


size_t PascalSParser::FactorContext::getRuleIndex() const {
  return PascalSParser::RuleFactor;
}

antlrcpp::Any PascalSParser::FactorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitFactor(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::FactorContext* PascalSParser::factor() {
  FactorContext *_localctx = _tracker.createInstance<FactorContext>(_ctx, getState());
  enterRule(_localctx, 80, PascalSParser::RuleFactor);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(426);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(404);
      num();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(405);
      match(PascalSParser::ID);
      setState(411);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx)) {
      case 1: {
        setState(406);
        match(PascalSParser::LPAREN);
        setState(408);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << PascalSParser::NOT)
          | (1ULL << PascalSParser::LETTER)
          | (1ULL << PascalSParser::PLUS)
          | (1ULL << PascalSParser::MINUS)
          | (1ULL << PascalSParser::LPAREN)
          | (1ULL << PascalSParser::ID)
          | (1ULL << PascalSParser::NUM)
          | (1ULL << PascalSParser::STRING))) != 0)) {
          setState(407);
          expressionList(0);
        }
        setState(410);
        match(PascalSParser::RPAREN);
        break;
      }

      }
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(413);
      variable();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(414);
      match(PascalSParser::LPAREN);
      setState(415);
      expression();
      setState(416);
      match(PascalSParser::RPAREN);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(418);
      match(PascalSParser::NOT);
      setState(419);
      factor();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(420);
      match(PascalSParser::MINUS);
      setState(421);
      factor();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(422);
      match(PascalSParser::PLUS);
      setState(423);
      factor();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(424);
      match(PascalSParser::STRING);
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(425);
      match(PascalSParser::LETTER);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NumContext ------------------------------------------------------------------

PascalSParser::NumContext::NumContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PascalSParser::NumContext::NUM() {
  return getToken(PascalSParser::NUM, 0);
}


size_t PascalSParser::NumContext::getRuleIndex() const {
  return PascalSParser::RuleNum;
}

antlrcpp::Any PascalSParser::NumContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitNum(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::NumContext* PascalSParser::num() {
  NumContext *_localctx = _tracker.createInstance<NumContext>(_ctx, getState());
  enterRule(_localctx, 82, PascalSParser::RuleNum);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(428);
    match(PascalSParser::NUM);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RelopContext ------------------------------------------------------------------

PascalSParser::RelopContext::RelopContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PascalSParser::RelopContext::EQUAL() {
  return getToken(PascalSParser::EQUAL, 0);
}

tree::TerminalNode* PascalSParser::RelopContext::NOTEQUAL() {
  return getToken(PascalSParser::NOTEQUAL, 0);
}

tree::TerminalNode* PascalSParser::RelopContext::LT() {
  return getToken(PascalSParser::LT, 0);
}

tree::TerminalNode* PascalSParser::RelopContext::LE() {
  return getToken(PascalSParser::LE, 0);
}

tree::TerminalNode* PascalSParser::RelopContext::GT() {
  return getToken(PascalSParser::GT, 0);
}

tree::TerminalNode* PascalSParser::RelopContext::GE() {
  return getToken(PascalSParser::GE, 0);
}


size_t PascalSParser::RelopContext::getRuleIndex() const {
  return PascalSParser::RuleRelop;
}

antlrcpp::Any PascalSParser::RelopContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitRelop(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::RelopContext* PascalSParser::relop() {
  RelopContext *_localctx = _tracker.createInstance<RelopContext>(_ctx, getState());
  enterRule(_localctx, 84, PascalSParser::RuleRelop);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(430);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << PascalSParser::EQUAL)
      | (1ULL << PascalSParser::NOTEQUAL)
      | (1ULL << PascalSParser::LT)
      | (1ULL << PascalSParser::LE)
      | (1ULL << PascalSParser::GT)
      | (1ULL << PascalSParser::GE))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AddopContext ------------------------------------------------------------------

PascalSParser::AddopContext::AddopContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PascalSParser::AddopContext::PLUS() {
  return getToken(PascalSParser::PLUS, 0);
}

tree::TerminalNode* PascalSParser::AddopContext::MINUS() {
  return getToken(PascalSParser::MINUS, 0);
}

tree::TerminalNode* PascalSParser::AddopContext::OR() {
  return getToken(PascalSParser::OR, 0);
}


size_t PascalSParser::AddopContext::getRuleIndex() const {
  return PascalSParser::RuleAddop;
}

antlrcpp::Any PascalSParser::AddopContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitAddop(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::AddopContext* PascalSParser::addop() {
  AddopContext *_localctx = _tracker.createInstance<AddopContext>(_ctx, getState());
  enterRule(_localctx, 86, PascalSParser::RuleAddop);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(432);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << PascalSParser::OR)
      | (1ULL << PascalSParser::PLUS)
      | (1ULL << PascalSParser::MINUS))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MulopContext ------------------------------------------------------------------

PascalSParser::MulopContext::MulopContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PascalSParser::MulopContext::STAR() {
  return getToken(PascalSParser::STAR, 0);
}

tree::TerminalNode* PascalSParser::MulopContext::SLASH() {
  return getToken(PascalSParser::SLASH, 0);
}

tree::TerminalNode* PascalSParser::MulopContext::DIV() {
  return getToken(PascalSParser::DIV, 0);
}

tree::TerminalNode* PascalSParser::MulopContext::MOD() {
  return getToken(PascalSParser::MOD, 0);
}

tree::TerminalNode* PascalSParser::MulopContext::AND() {
  return getToken(PascalSParser::AND, 0);
}


size_t PascalSParser::MulopContext::getRuleIndex() const {
  return PascalSParser::RuleMulop;
}

antlrcpp::Any PascalSParser::MulopContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitMulop(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::MulopContext* PascalSParser::mulop() {
  MulopContext *_localctx = _tracker.createInstance<MulopContext>(_ctx, getState());
  enterRule(_localctx, 88, PascalSParser::RuleMulop);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(434);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << PascalSParser::DIV)
      | (1ULL << PascalSParser::MOD)
      | (1ULL << PascalSParser::AND)
      | (1ULL << PascalSParser::STAR)
      | (1ULL << PascalSParser::SLASH))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool PascalSParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 6: return constDeclarationSempred(dynamic_cast<ConstDeclarationContext *>(context), predicateIndex);
    case 9: return varDeclarationSempred(dynamic_cast<VarDeclarationContext *>(context), predicateIndex);
    case 12: return periodSempred(dynamic_cast<PeriodContext *>(context), predicateIndex);
    case 13: return subprogramDeclarationsSempred(dynamic_cast<SubprogramDeclarationsContext *>(context), predicateIndex);
    case 17: return parameterListSempred(dynamic_cast<ParameterListContext *>(context), predicateIndex);
    case 23: return statementListSempred(dynamic_cast<StatementListContext *>(context), predicateIndex);
    case 31: return variableListSempred(dynamic_cast<VariableListContext *>(context), predicateIndex);
    case 36: return expressionListSempred(dynamic_cast<ExpressionListContext *>(context), predicateIndex);
    case 38: return simpleExpressionSempred(dynamic_cast<SimpleExpressionContext *>(context), predicateIndex);
    case 39: return termSempred(dynamic_cast<TermContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool PascalSParser::constDeclarationSempred(ConstDeclarationContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool PascalSParser::varDeclarationSempred(VarDeclarationContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 1: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool PascalSParser::periodSempred(PeriodContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 2: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool PascalSParser::subprogramDeclarationsSempred(SubprogramDeclarationsContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 3: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool PascalSParser::parameterListSempred(ParameterListContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 4: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool PascalSParser::statementListSempred(StatementListContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 5: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool PascalSParser::variableListSempred(VariableListContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 6: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool PascalSParser::expressionListSempred(ExpressionListContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 7: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool PascalSParser::simpleExpressionSempred(SimpleExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 8: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool PascalSParser::termSempred(TermContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 9: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> PascalSParser::_decisionToDFA;
atn::PredictionContextCache PascalSParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN PascalSParser::_atn;
std::vector<uint16_t> PascalSParser::_serializedATN;

std::vector<std::string> PascalSParser::_ruleNames = {
  "program", "programStruct", "programHead", "programBody", "idList", "constDeclarations", 
  "constDeclaration", "constValue", "varDeclarations", "varDeclaration", 
  "type", "basicType", "period", "subprogramDeclarations", "subprogram", 
  "subprogramHead", "formalParameter", "parameterList", "parameter", "varParameter", 
  "valueParameter", "subprogramBody", "compoundStatement", "statementList", 
  "statement", "ifStatement", "forStatement", "readStatement", "whileStatement", 
  "writeStatement", "breakStatement", "variableList", "variable", "idVarPart", 
  "procedureCall", "elsePart", "expressionList", "expression", "simpleExpression", 
  "term", "factor", "num", "relop", "addop", "mulop"
};

std::vector<std::string> PascalSParser::_literalNames = {
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "';'", "':'", "'.'", "','", 
  "'='", "'<>'", "'<'", "'<='", "'>'", "'>='", "'+'", "'-'", "'*'", "'/'", 
  "'('", "')'", "'['", "']'", "':='", "'..'"
};

std::vector<std::string> PascalSParser::_symbolicNames = {
  "", "PROGRAM", "CONST", "VAR", "PROCEDURE", "FUNCTION", "BEGIN", "END", 
  "ARRAY", "OF", "IF", "THEN", "ELSE", "FOR", "TO", "DO", "READ", "WRITE", 
  "INTEGER", "REAL", "BOOLEAN", "CHAR", "DIV", "MOD", "AND", "OR", "NOT", 
  "WHILE", "BREAK", "LETTER", "SEMICOLON", "COLON", "DOT", "COMMA", "EQUAL", 
  "NOTEQUAL", "LT", "LE", "GT", "GE", "PLUS", "MINUS", "STAR", "SLASH", 
  "LPAREN", "RPAREN", "LBRACKET", "RBRACKET", "ASSIGNOP", "DOTDOT", "ID", 
  "NUM", "STRING", "COMMENT", "LINE_COMMENT", "WS"
};

dfa::Vocabulary PascalSParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> PascalSParser::_tokenNames;

PascalSParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0x39, 0x1b7, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
    0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 
    0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 
    0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 
    0x4, 0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x4, 
    0x12, 0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 0x9, 0x14, 0x4, 0x15, 
    0x9, 0x15, 0x4, 0x16, 0x9, 0x16, 0x4, 0x17, 0x9, 0x17, 0x4, 0x18, 0x9, 
    0x18, 0x4, 0x19, 0x9, 0x19, 0x4, 0x1a, 0x9, 0x1a, 0x4, 0x1b, 0x9, 0x1b, 
    0x4, 0x1c, 0x9, 0x1c, 0x4, 0x1d, 0x9, 0x1d, 0x4, 0x1e, 0x9, 0x1e, 0x4, 
    0x1f, 0x9, 0x1f, 0x4, 0x20, 0x9, 0x20, 0x4, 0x21, 0x9, 0x21, 0x4, 0x22, 
    0x9, 0x22, 0x4, 0x23, 0x9, 0x23, 0x4, 0x24, 0x9, 0x24, 0x4, 0x25, 0x9, 
    0x25, 0x4, 0x26, 0x9, 0x26, 0x4, 0x27, 0x9, 0x27, 0x4, 0x28, 0x9, 0x28, 
    0x4, 0x29, 0x9, 0x29, 0x4, 0x2a, 0x9, 0x2a, 0x4, 0x2b, 0x9, 0x2b, 0x4, 
    0x2c, 0x9, 0x2c, 0x4, 0x2d, 0x9, 0x2d, 0x4, 0x2e, 0x9, 0x2e, 0x3, 0x2, 
    0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x5, 0x4, 
    0x6b, 0xa, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 
    0x6, 0x3, 0x6, 0x3, 0x6, 0x7, 0x6, 0x75, 0xa, 0x6, 0xc, 0x6, 0xe, 0x6, 
    0x78, 0xb, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x5, 
    0x7, 0x7f, 0xa, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 
    0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x7, 0x8, 0x8b, 0xa, 
    0x8, 0xc, 0x8, 0xe, 0x8, 0x8e, 0xb, 0x8, 0x3, 0x9, 0x5, 0x9, 0x91, 0xa, 
    0x9, 0x3, 0x9, 0x3, 0x9, 0x5, 0x9, 0x95, 0xa, 0x9, 0x3, 0x9, 0x3, 0x9, 
    0x3, 0x9, 0x5, 0x9, 0x9a, 0xa, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 
    0xa, 0x3, 0xa, 0x5, 0xa, 0xa1, 0xa, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 
    0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 
    0x3, 0xb, 0x7, 0xb, 0xae, 0xa, 0xb, 0xc, 0xb, 0xe, 0xb, 0xb1, 0xb, 0xb, 
    0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 
    0x3, 0xc, 0x5, 0xc, 0xbb, 0xa, 0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 0xe, 0x3, 
    0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 
    0xe, 0x3, 0xe, 0x7, 0xe, 0xc9, 0xa, 0xe, 0xc, 0xe, 0xe, 0xe, 0xcc, 0xb, 
    0xe, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x7, 0xf, 0xd3, 
    0xa, 0xf, 0xc, 0xf, 0xe, 0xf, 0xd6, 0xb, 0xf, 0x3, 0x10, 0x3, 0x10, 
    0x3, 0x10, 0x3, 0x10, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 
    0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x5, 0x11, 0xe5, 0xa, 
    0x11, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x5, 0x12, 0xea, 0xa, 0x12, 0x3, 
    0x12, 0x5, 0x12, 0xed, 0xa, 0x12, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 
    0x13, 0x3, 0x13, 0x3, 0x13, 0x7, 0x13, 0xf5, 0xa, 0x13, 0xc, 0x13, 0xe, 
    0x13, 0xf8, 0xb, 0x13, 0x3, 0x14, 0x3, 0x14, 0x5, 0x14, 0xfc, 0xa, 0x14, 
    0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 
    0x16, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x18, 0x3, 0x18, 
    0x3, 0x18, 0x3, 0x18, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 
    0x19, 0x3, 0x19, 0x7, 0x19, 0x113, 0xa, 0x19, 0xc, 0x19, 0xe, 0x19, 
    0x116, 0xb, 0x19, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 
    0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 
    0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x5, 0x1a, 0x128, 
    0xa, 0x1a, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 
    0x1b, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 
    0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 
    0x1d, 0x3, 0x1d, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 
    0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x20, 0x3, 
    0x20, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 
    0x7, 0x21, 0x150, 0xa, 0x21, 0xc, 0x21, 0xe, 0x21, 0x153, 0xb, 0x21, 
    0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 
    0x23, 0x3, 0x23, 0x5, 0x23, 0x15d, 0xa, 0x23, 0x3, 0x24, 0x3, 0x24, 
    0x3, 0x24, 0x3, 0x24, 0x5, 0x24, 0x163, 0xa, 0x24, 0x3, 0x24, 0x5, 0x24, 
    0x166, 0xa, 0x24, 0x3, 0x25, 0x3, 0x25, 0x3, 0x25, 0x5, 0x25, 0x16b, 
    0xa, 0x25, 0x3, 0x26, 0x3, 0x26, 0x3, 0x26, 0x3, 0x26, 0x3, 0x26, 0x3, 
    0x26, 0x7, 0x26, 0x173, 0xa, 0x26, 0xc, 0x26, 0xe, 0x26, 0x176, 0xb, 
    0x26, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x5, 0x27, 
    0x17d, 0xa, 0x27, 0x3, 0x28, 0x3, 0x28, 0x3, 0x28, 0x3, 0x28, 0x3, 0x28, 
    0x3, 0x28, 0x3, 0x28, 0x7, 0x28, 0x186, 0xa, 0x28, 0xc, 0x28, 0xe, 0x28, 
    0x189, 0xb, 0x28, 0x3, 0x29, 0x3, 0x29, 0x3, 0x29, 0x3, 0x29, 0x3, 0x29, 
    0x3, 0x29, 0x3, 0x29, 0x7, 0x29, 0x192, 0xa, 0x29, 0xc, 0x29, 0xe, 0x29, 
    0x195, 0xb, 0x29, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x5, 0x2a, 
    0x19b, 0xa, 0x2a, 0x3, 0x2a, 0x5, 0x2a, 0x19e, 0xa, 0x2a, 0x3, 0x2a, 
    0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 
    0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x5, 0x2a, 
    0x1ad, 0xa, 0x2a, 0x3, 0x2b, 0x3, 0x2b, 0x3, 0x2c, 0x3, 0x2c, 0x3, 0x2d, 
    0x3, 0x2d, 0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x2, 0xc, 0xe, 0x14, 0x1a, 
    0x1c, 0x24, 0x30, 0x40, 0x4a, 0x4e, 0x50, 0x2f, 0x2, 0x4, 0x6, 0x8, 
    0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e, 0x20, 
    0x22, 0x24, 0x26, 0x28, 0x2a, 0x2c, 0x2e, 0x30, 0x32, 0x34, 0x36, 0x38, 
    0x3a, 0x3c, 0x3e, 0x40, 0x42, 0x44, 0x46, 0x48, 0x4a, 0x4c, 0x4e, 0x50, 
    0x52, 0x54, 0x56, 0x58, 0x5a, 0x2, 0x6, 0x3, 0x2, 0x14, 0x17, 0x3, 0x2, 
    0x24, 0x29, 0x4, 0x2, 0x1b, 0x1b, 0x2a, 0x2b, 0x4, 0x2, 0x18, 0x1a, 
    0x2c, 0x2d, 0x2, 0x1ba, 0x2, 0x5c, 0x3, 0x2, 0x2, 0x2, 0x4, 0x5f, 0x3, 
    0x2, 0x2, 0x2, 0x6, 0x64, 0x3, 0x2, 0x2, 0x2, 0x8, 0x6c, 0x3, 0x2, 0x2, 
    0x2, 0xa, 0x71, 0x3, 0x2, 0x2, 0x2, 0xc, 0x7e, 0x3, 0x2, 0x2, 0x2, 0xe, 
    0x80, 0x3, 0x2, 0x2, 0x2, 0x10, 0x99, 0x3, 0x2, 0x2, 0x2, 0x12, 0xa0, 
    0x3, 0x2, 0x2, 0x2, 0x14, 0xa2, 0x3, 0x2, 0x2, 0x2, 0x16, 0xba, 0x3, 
    0x2, 0x2, 0x2, 0x18, 0xbc, 0x3, 0x2, 0x2, 0x2, 0x1a, 0xbe, 0x3, 0x2, 
    0x2, 0x2, 0x1c, 0xcd, 0x3, 0x2, 0x2, 0x2, 0x1e, 0xd7, 0x3, 0x2, 0x2, 
    0x2, 0x20, 0xe4, 0x3, 0x2, 0x2, 0x2, 0x22, 0xec, 0x3, 0x2, 0x2, 0x2, 
    0x24, 0xee, 0x3, 0x2, 0x2, 0x2, 0x26, 0xfb, 0x3, 0x2, 0x2, 0x2, 0x28, 
    0xfd, 0x3, 0x2, 0x2, 0x2, 0x2a, 0x100, 0x3, 0x2, 0x2, 0x2, 0x2c, 0x104, 
    0x3, 0x2, 0x2, 0x2, 0x2e, 0x108, 0x3, 0x2, 0x2, 0x2, 0x30, 0x10c, 0x3, 
    0x2, 0x2, 0x2, 0x32, 0x127, 0x3, 0x2, 0x2, 0x2, 0x34, 0x129, 0x3, 0x2, 
    0x2, 0x2, 0x36, 0x12f, 0x3, 0x2, 0x2, 0x2, 0x38, 0x138, 0x3, 0x2, 0x2, 
    0x2, 0x3a, 0x13d, 0x3, 0x2, 0x2, 0x2, 0x3c, 0x142, 0x3, 0x2, 0x2, 0x2, 
    0x3e, 0x147, 0x3, 0x2, 0x2, 0x2, 0x40, 0x149, 0x3, 0x2, 0x2, 0x2, 0x42, 
    0x154, 0x3, 0x2, 0x2, 0x2, 0x44, 0x15c, 0x3, 0x2, 0x2, 0x2, 0x46, 0x165, 
    0x3, 0x2, 0x2, 0x2, 0x48, 0x16a, 0x3, 0x2, 0x2, 0x2, 0x4a, 0x16c, 0x3, 
    0x2, 0x2, 0x2, 0x4c, 0x17c, 0x3, 0x2, 0x2, 0x2, 0x4e, 0x17e, 0x3, 0x2, 
    0x2, 0x2, 0x50, 0x18a, 0x3, 0x2, 0x2, 0x2, 0x52, 0x1ac, 0x3, 0x2, 0x2, 
    0x2, 0x54, 0x1ae, 0x3, 0x2, 0x2, 0x2, 0x56, 0x1b0, 0x3, 0x2, 0x2, 0x2, 
    0x58, 0x1b2, 0x3, 0x2, 0x2, 0x2, 0x5a, 0x1b4, 0x3, 0x2, 0x2, 0x2, 0x5c, 
    0x5d, 0x5, 0x4, 0x3, 0x2, 0x5d, 0x5e, 0x7, 0x2, 0x2, 0x3, 0x5e, 0x3, 
    0x3, 0x2, 0x2, 0x2, 0x5f, 0x60, 0x5, 0x6, 0x4, 0x2, 0x60, 0x61, 0x7, 
    0x20, 0x2, 0x2, 0x61, 0x62, 0x5, 0x8, 0x5, 0x2, 0x62, 0x63, 0x7, 0x22, 
    0x2, 0x2, 0x63, 0x5, 0x3, 0x2, 0x2, 0x2, 0x64, 0x65, 0x7, 0x3, 0x2, 
    0x2, 0x65, 0x6a, 0x7, 0x34, 0x2, 0x2, 0x66, 0x67, 0x7, 0x2e, 0x2, 0x2, 
    0x67, 0x68, 0x5, 0xa, 0x6, 0x2, 0x68, 0x69, 0x7, 0x2f, 0x2, 0x2, 0x69, 
    0x6b, 0x3, 0x2, 0x2, 0x2, 0x6a, 0x66, 0x3, 0x2, 0x2, 0x2, 0x6a, 0x6b, 
    0x3, 0x2, 0x2, 0x2, 0x6b, 0x7, 0x3, 0x2, 0x2, 0x2, 0x6c, 0x6d, 0x5, 
    0xc, 0x7, 0x2, 0x6d, 0x6e, 0x5, 0x12, 0xa, 0x2, 0x6e, 0x6f, 0x5, 0x1c, 
    0xf, 0x2, 0x6f, 0x70, 0x5, 0x2e, 0x18, 0x2, 0x70, 0x9, 0x3, 0x2, 0x2, 
    0x2, 0x71, 0x76, 0x7, 0x34, 0x2, 0x2, 0x72, 0x73, 0x7, 0x23, 0x2, 0x2, 
    0x73, 0x75, 0x7, 0x34, 0x2, 0x2, 0x74, 0x72, 0x3, 0x2, 0x2, 0x2, 0x75, 
    0x78, 0x3, 0x2, 0x2, 0x2, 0x76, 0x74, 0x3, 0x2, 0x2, 0x2, 0x76, 0x77, 
    0x3, 0x2, 0x2, 0x2, 0x77, 0xb, 0x3, 0x2, 0x2, 0x2, 0x78, 0x76, 0x3, 
    0x2, 0x2, 0x2, 0x79, 0x7f, 0x3, 0x2, 0x2, 0x2, 0x7a, 0x7b, 0x7, 0x4, 
    0x2, 0x2, 0x7b, 0x7c, 0x5, 0xe, 0x8, 0x2, 0x7c, 0x7d, 0x7, 0x20, 0x2, 
    0x2, 0x7d, 0x7f, 0x3, 0x2, 0x2, 0x2, 0x7e, 0x79, 0x3, 0x2, 0x2, 0x2, 
    0x7e, 0x7a, 0x3, 0x2, 0x2, 0x2, 0x7f, 0xd, 0x3, 0x2, 0x2, 0x2, 0x80, 
    0x81, 0x8, 0x8, 0x1, 0x2, 0x81, 0x82, 0x7, 0x34, 0x2, 0x2, 0x82, 0x83, 
    0x7, 0x24, 0x2, 0x2, 0x83, 0x84, 0x5, 0x10, 0x9, 0x2, 0x84, 0x8c, 0x3, 
    0x2, 0x2, 0x2, 0x85, 0x86, 0xc, 0x3, 0x2, 0x2, 0x86, 0x87, 0x7, 0x20, 
    0x2, 0x2, 0x87, 0x88, 0x7, 0x34, 0x2, 0x2, 0x88, 0x89, 0x7, 0x24, 0x2, 
    0x2, 0x89, 0x8b, 0x5, 0x10, 0x9, 0x2, 0x8a, 0x85, 0x3, 0x2, 0x2, 0x2, 
    0x8b, 0x8e, 0x3, 0x2, 0x2, 0x2, 0x8c, 0x8a, 0x3, 0x2, 0x2, 0x2, 0x8c, 
    0x8d, 0x3, 0x2, 0x2, 0x2, 0x8d, 0xf, 0x3, 0x2, 0x2, 0x2, 0x8e, 0x8c, 
    0x3, 0x2, 0x2, 0x2, 0x8f, 0x91, 0x7, 0x2a, 0x2, 0x2, 0x90, 0x8f, 0x3, 
    0x2, 0x2, 0x2, 0x90, 0x91, 0x3, 0x2, 0x2, 0x2, 0x91, 0x92, 0x3, 0x2, 
    0x2, 0x2, 0x92, 0x9a, 0x5, 0x54, 0x2b, 0x2, 0x93, 0x95, 0x7, 0x2b, 0x2, 
    0x2, 0x94, 0x93, 0x3, 0x2, 0x2, 0x2, 0x94, 0x95, 0x3, 0x2, 0x2, 0x2, 
    0x95, 0x96, 0x3, 0x2, 0x2, 0x2, 0x96, 0x9a, 0x5, 0x54, 0x2b, 0x2, 0x97, 
    0x9a, 0x7, 0x1f, 0x2, 0x2, 0x98, 0x9a, 0x7, 0x36, 0x2, 0x2, 0x99, 0x90, 
    0x3, 0x2, 0x2, 0x2, 0x99, 0x94, 0x3, 0x2, 0x2, 0x2, 0x99, 0x97, 0x3, 
    0x2, 0x2, 0x2, 0x99, 0x98, 0x3, 0x2, 0x2, 0x2, 0x9a, 0x11, 0x3, 0x2, 
    0x2, 0x2, 0x9b, 0xa1, 0x3, 0x2, 0x2, 0x2, 0x9c, 0x9d, 0x7, 0x5, 0x2, 
    0x2, 0x9d, 0x9e, 0x5, 0x14, 0xb, 0x2, 0x9e, 0x9f, 0x7, 0x20, 0x2, 0x2, 
    0x9f, 0xa1, 0x3, 0x2, 0x2, 0x2, 0xa0, 0x9b, 0x3, 0x2, 0x2, 0x2, 0xa0, 
    0x9c, 0x3, 0x2, 0x2, 0x2, 0xa1, 0x13, 0x3, 0x2, 0x2, 0x2, 0xa2, 0xa3, 
    0x8, 0xb, 0x1, 0x2, 0xa3, 0xa4, 0x5, 0xa, 0x6, 0x2, 0xa4, 0xa5, 0x7, 
    0x21, 0x2, 0x2, 0xa5, 0xa6, 0x5, 0x16, 0xc, 0x2, 0xa6, 0xaf, 0x3, 0x2, 
    0x2, 0x2, 0xa7, 0xa8, 0xc, 0x3, 0x2, 0x2, 0xa8, 0xa9, 0x7, 0x20, 0x2, 
    0x2, 0xa9, 0xaa, 0x5, 0xa, 0x6, 0x2, 0xaa, 0xab, 0x7, 0x21, 0x2, 0x2, 
    0xab, 0xac, 0x5, 0x16, 0xc, 0x2, 0xac, 0xae, 0x3, 0x2, 0x2, 0x2, 0xad, 
    0xa7, 0x3, 0x2, 0x2, 0x2, 0xae, 0xb1, 0x3, 0x2, 0x2, 0x2, 0xaf, 0xad, 
    0x3, 0x2, 0x2, 0x2, 0xaf, 0xb0, 0x3, 0x2, 0x2, 0x2, 0xb0, 0x15, 0x3, 
    0x2, 0x2, 0x2, 0xb1, 0xaf, 0x3, 0x2, 0x2, 0x2, 0xb2, 0xbb, 0x5, 0x18, 
    0xd, 0x2, 0xb3, 0xb4, 0x7, 0xa, 0x2, 0x2, 0xb4, 0xb5, 0x7, 0x30, 0x2, 
    0x2, 0xb5, 0xb6, 0x5, 0x1a, 0xe, 0x2, 0xb6, 0xb7, 0x7, 0x31, 0x2, 0x2, 
    0xb7, 0xb8, 0x7, 0xb, 0x2, 0x2, 0xb8, 0xb9, 0x5, 0x18, 0xd, 0x2, 0xb9, 
    0xbb, 0x3, 0x2, 0x2, 0x2, 0xba, 0xb2, 0x3, 0x2, 0x2, 0x2, 0xba, 0xb3, 
    0x3, 0x2, 0x2, 0x2, 0xbb, 0x17, 0x3, 0x2, 0x2, 0x2, 0xbc, 0xbd, 0x9, 
    0x2, 0x2, 0x2, 0xbd, 0x19, 0x3, 0x2, 0x2, 0x2, 0xbe, 0xbf, 0x8, 0xe, 
    0x1, 0x2, 0xbf, 0xc0, 0x7, 0x35, 0x2, 0x2, 0xc0, 0xc1, 0x7, 0x33, 0x2, 
    0x2, 0xc1, 0xc2, 0x7, 0x35, 0x2, 0x2, 0xc2, 0xca, 0x3, 0x2, 0x2, 0x2, 
    0xc3, 0xc4, 0xc, 0x3, 0x2, 0x2, 0xc4, 0xc5, 0x7, 0x23, 0x2, 0x2, 0xc5, 
    0xc6, 0x7, 0x35, 0x2, 0x2, 0xc6, 0xc7, 0x7, 0x33, 0x2, 0x2, 0xc7, 0xc9, 
    0x7, 0x35, 0x2, 0x2, 0xc8, 0xc3, 0x3, 0x2, 0x2, 0x2, 0xc9, 0xcc, 0x3, 
    0x2, 0x2, 0x2, 0xca, 0xc8, 0x3, 0x2, 0x2, 0x2, 0xca, 0xcb, 0x3, 0x2, 
    0x2, 0x2, 0xcb, 0x1b, 0x3, 0x2, 0x2, 0x2, 0xcc, 0xca, 0x3, 0x2, 0x2, 
    0x2, 0xcd, 0xd4, 0x8, 0xf, 0x1, 0x2, 0xce, 0xcf, 0xc, 0x3, 0x2, 0x2, 
    0xcf, 0xd0, 0x5, 0x1e, 0x10, 0x2, 0xd0, 0xd1, 0x7, 0x20, 0x2, 0x2, 0xd1, 
    0xd3, 0x3, 0x2, 0x2, 0x2, 0xd2, 0xce, 0x3, 0x2, 0x2, 0x2, 0xd3, 0xd6, 
    0x3, 0x2, 0x2, 0x2, 0xd4, 0xd2, 0x3, 0x2, 0x2, 0x2, 0xd4, 0xd5, 0x3, 
    0x2, 0x2, 0x2, 0xd5, 0x1d, 0x3, 0x2, 0x2, 0x2, 0xd6, 0xd4, 0x3, 0x2, 
    0x2, 0x2, 0xd7, 0xd8, 0x5, 0x20, 0x11, 0x2, 0xd8, 0xd9, 0x7, 0x20, 0x2, 
    0x2, 0xd9, 0xda, 0x5, 0x2c, 0x17, 0x2, 0xda, 0x1f, 0x3, 0x2, 0x2, 0x2, 
    0xdb, 0xdc, 0x7, 0x6, 0x2, 0x2, 0xdc, 0xdd, 0x7, 0x34, 0x2, 0x2, 0xdd, 
    0xe5, 0x5, 0x22, 0x12, 0x2, 0xde, 0xdf, 0x7, 0x7, 0x2, 0x2, 0xdf, 0xe0, 
    0x7, 0x34, 0x2, 0x2, 0xe0, 0xe1, 0x5, 0x22, 0x12, 0x2, 0xe1, 0xe2, 0x7, 
    0x21, 0x2, 0x2, 0xe2, 0xe3, 0x5, 0x18, 0xd, 0x2, 0xe3, 0xe5, 0x3, 0x2, 
    0x2, 0x2, 0xe4, 0xdb, 0x3, 0x2, 0x2, 0x2, 0xe4, 0xde, 0x3, 0x2, 0x2, 
    0x2, 0xe5, 0x21, 0x3, 0x2, 0x2, 0x2, 0xe6, 0xed, 0x3, 0x2, 0x2, 0x2, 
    0xe7, 0xe9, 0x7, 0x2e, 0x2, 0x2, 0xe8, 0xea, 0x5, 0x24, 0x13, 0x2, 0xe9, 
    0xe8, 0x3, 0x2, 0x2, 0x2, 0xe9, 0xea, 0x3, 0x2, 0x2, 0x2, 0xea, 0xeb, 
    0x3, 0x2, 0x2, 0x2, 0xeb, 0xed, 0x7, 0x2f, 0x2, 0x2, 0xec, 0xe6, 0x3, 
    0x2, 0x2, 0x2, 0xec, 0xe7, 0x3, 0x2, 0x2, 0x2, 0xed, 0x23, 0x3, 0x2, 
    0x2, 0x2, 0xee, 0xef, 0x8, 0x13, 0x1, 0x2, 0xef, 0xf0, 0x5, 0x26, 0x14, 
    0x2, 0xf0, 0xf6, 0x3, 0x2, 0x2, 0x2, 0xf1, 0xf2, 0xc, 0x3, 0x2, 0x2, 
    0xf2, 0xf3, 0x7, 0x20, 0x2, 0x2, 0xf3, 0xf5, 0x5, 0x26, 0x14, 0x2, 0xf4, 
    0xf1, 0x3, 0x2, 0x2, 0x2, 0xf5, 0xf8, 0x3, 0x2, 0x2, 0x2, 0xf6, 0xf4, 
    0x3, 0x2, 0x2, 0x2, 0xf6, 0xf7, 0x3, 0x2, 0x2, 0x2, 0xf7, 0x25, 0x3, 
    0x2, 0x2, 0x2, 0xf8, 0xf6, 0x3, 0x2, 0x2, 0x2, 0xf9, 0xfc, 0x5, 0x28, 
    0x15, 0x2, 0xfa, 0xfc, 0x5, 0x2a, 0x16, 0x2, 0xfb, 0xf9, 0x3, 0x2, 0x2, 
    0x2, 0xfb, 0xfa, 0x3, 0x2, 0x2, 0x2, 0xfc, 0x27, 0x3, 0x2, 0x2, 0x2, 
    0xfd, 0xfe, 0x7, 0x5, 0x2, 0x2, 0xfe, 0xff, 0x5, 0x2a, 0x16, 0x2, 0xff, 
    0x29, 0x3, 0x2, 0x2, 0x2, 0x100, 0x101, 0x5, 0xa, 0x6, 0x2, 0x101, 0x102, 
    0x7, 0x21, 0x2, 0x2, 0x102, 0x103, 0x5, 0x16, 0xc, 0x2, 0x103, 0x2b, 
    0x3, 0x2, 0x2, 0x2, 0x104, 0x105, 0x5, 0xc, 0x7, 0x2, 0x105, 0x106, 
    0x5, 0x12, 0xa, 0x2, 0x106, 0x107, 0x5, 0x2e, 0x18, 0x2, 0x107, 0x2d, 
    0x3, 0x2, 0x2, 0x2, 0x108, 0x109, 0x7, 0x8, 0x2, 0x2, 0x109, 0x10a, 
    0x5, 0x30, 0x19, 0x2, 0x10a, 0x10b, 0x7, 0x9, 0x2, 0x2, 0x10b, 0x2f, 
    0x3, 0x2, 0x2, 0x2, 0x10c, 0x10d, 0x8, 0x19, 0x1, 0x2, 0x10d, 0x10e, 
    0x5, 0x32, 0x1a, 0x2, 0x10e, 0x114, 0x3, 0x2, 0x2, 0x2, 0x10f, 0x110, 
    0xc, 0x3, 0x2, 0x2, 0x110, 0x111, 0x7, 0x20, 0x2, 0x2, 0x111, 0x113, 
    0x5, 0x32, 0x1a, 0x2, 0x112, 0x10f, 0x3, 0x2, 0x2, 0x2, 0x113, 0x116, 
    0x3, 0x2, 0x2, 0x2, 0x114, 0x112, 0x3, 0x2, 0x2, 0x2, 0x114, 0x115, 
    0x3, 0x2, 0x2, 0x2, 0x115, 0x31, 0x3, 0x2, 0x2, 0x2, 0x116, 0x114, 0x3, 
    0x2, 0x2, 0x2, 0x117, 0x128, 0x3, 0x2, 0x2, 0x2, 0x118, 0x119, 0x5, 
    0x42, 0x22, 0x2, 0x119, 0x11a, 0x7, 0x32, 0x2, 0x2, 0x11a, 0x11b, 0x5, 
    0x4c, 0x27, 0x2, 0x11b, 0x128, 0x3, 0x2, 0x2, 0x2, 0x11c, 0x11d, 0x7, 
    0x34, 0x2, 0x2, 0x11d, 0x11e, 0x7, 0x32, 0x2, 0x2, 0x11e, 0x128, 0x5, 
    0x4c, 0x27, 0x2, 0x11f, 0x128, 0x5, 0x46, 0x24, 0x2, 0x120, 0x128, 0x5, 
    0x2e, 0x18, 0x2, 0x121, 0x128, 0x5, 0x34, 0x1b, 0x2, 0x122, 0x128, 0x5, 
    0x36, 0x1c, 0x2, 0x123, 0x128, 0x5, 0x38, 0x1d, 0x2, 0x124, 0x128, 0x5, 
    0x3e, 0x20, 0x2, 0x125, 0x128, 0x5, 0x3a, 0x1e, 0x2, 0x126, 0x128, 0x5, 
    0x3c, 0x1f, 0x2, 0x127, 0x117, 0x3, 0x2, 0x2, 0x2, 0x127, 0x118, 0x3, 
    0x2, 0x2, 0x2, 0x127, 0x11c, 0x3, 0x2, 0x2, 0x2, 0x127, 0x11f, 0x3, 
    0x2, 0x2, 0x2, 0x127, 0x120, 0x3, 0x2, 0x2, 0x2, 0x127, 0x121, 0x3, 
    0x2, 0x2, 0x2, 0x127, 0x122, 0x3, 0x2, 0x2, 0x2, 0x127, 0x123, 0x3, 
    0x2, 0x2, 0x2, 0x127, 0x124, 0x3, 0x2, 0x2, 0x2, 0x127, 0x125, 0x3, 
    0x2, 0x2, 0x2, 0x127, 0x126, 0x3, 0x2, 0x2, 0x2, 0x128, 0x33, 0x3, 0x2, 
    0x2, 0x2, 0x129, 0x12a, 0x7, 0xc, 0x2, 0x2, 0x12a, 0x12b, 0x5, 0x4c, 
    0x27, 0x2, 0x12b, 0x12c, 0x7, 0xd, 0x2, 0x2, 0x12c, 0x12d, 0x5, 0x32, 
    0x1a, 0x2, 0x12d, 0x12e, 0x5, 0x48, 0x25, 0x2, 0x12e, 0x35, 0x3, 0x2, 
    0x2, 0x2, 0x12f, 0x130, 0x7, 0xf, 0x2, 0x2, 0x130, 0x131, 0x7, 0x34, 
    0x2, 0x2, 0x131, 0x132, 0x7, 0x32, 0x2, 0x2, 0x132, 0x133, 0x5, 0x4c, 
    0x27, 0x2, 0x133, 0x134, 0x7, 0x10, 0x2, 0x2, 0x134, 0x135, 0x5, 0x4c, 
    0x27, 0x2, 0x135, 0x136, 0x7, 0x11, 0x2, 0x2, 0x136, 0x137, 0x5, 0x32, 
    0x1a, 0x2, 0x137, 0x37, 0x3, 0x2, 0x2, 0x2, 0x138, 0x139, 0x7, 0x12, 
    0x2, 0x2, 0x139, 0x13a, 0x7, 0x2e, 0x2, 0x2, 0x13a, 0x13b, 0x5, 0x40, 
    0x21, 0x2, 0x13b, 0x13c, 0x7, 0x2f, 0x2, 0x2, 0x13c, 0x39, 0x3, 0x2, 
    0x2, 0x2, 0x13d, 0x13e, 0x7, 0x1d, 0x2, 0x2, 0x13e, 0x13f, 0x5, 0x4c, 
    0x27, 0x2, 0x13f, 0x140, 0x7, 0x11, 0x2, 0x2, 0x140, 0x141, 0x5, 0x32, 
    0x1a, 0x2, 0x141, 0x3b, 0x3, 0x2, 0x2, 0x2, 0x142, 0x143, 0x7, 0x13, 
    0x2, 0x2, 0x143, 0x144, 0x7, 0x2e, 0x2, 0x2, 0x144, 0x145, 0x5, 0x4a, 
    0x26, 0x2, 0x145, 0x146, 0x7, 0x2f, 0x2, 0x2, 0x146, 0x3d, 0x3, 0x2, 
    0x2, 0x2, 0x147, 0x148, 0x7, 0x1e, 0x2, 0x2, 0x148, 0x3f, 0x3, 0x2, 
    0x2, 0x2, 0x149, 0x14a, 0x8, 0x21, 0x1, 0x2, 0x14a, 0x14b, 0x5, 0x42, 
    0x22, 0x2, 0x14b, 0x151, 0x3, 0x2, 0x2, 0x2, 0x14c, 0x14d, 0xc, 0x3, 
    0x2, 0x2, 0x14d, 0x14e, 0x7, 0x23, 0x2, 0x2, 0x14e, 0x150, 0x5, 0x42, 
    0x22, 0x2, 0x14f, 0x14c, 0x3, 0x2, 0x2, 0x2, 0x150, 0x153, 0x3, 0x2, 
    0x2, 0x2, 0x151, 0x14f, 0x3, 0x2, 0x2, 0x2, 0x151, 0x152, 0x3, 0x2, 
    0x2, 0x2, 0x152, 0x41, 0x3, 0x2, 0x2, 0x2, 0x153, 0x151, 0x3, 0x2, 0x2, 
    0x2, 0x154, 0x155, 0x7, 0x34, 0x2, 0x2, 0x155, 0x156, 0x5, 0x44, 0x23, 
    0x2, 0x156, 0x43, 0x3, 0x2, 0x2, 0x2, 0x157, 0x15d, 0x3, 0x2, 0x2, 0x2, 
    0x158, 0x159, 0x7, 0x30, 0x2, 0x2, 0x159, 0x15a, 0x5, 0x4a, 0x26, 0x2, 
    0x15a, 0x15b, 0x7, 0x31, 0x2, 0x2, 0x15b, 0x15d, 0x3, 0x2, 0x2, 0x2, 
    0x15c, 0x157, 0x3, 0x2, 0x2, 0x2, 0x15c, 0x158, 0x3, 0x2, 0x2, 0x2, 
    0x15d, 0x45, 0x3, 0x2, 0x2, 0x2, 0x15e, 0x166, 0x7, 0x34, 0x2, 0x2, 
    0x15f, 0x160, 0x7, 0x34, 0x2, 0x2, 0x160, 0x162, 0x7, 0x2e, 0x2, 0x2, 
    0x161, 0x163, 0x5, 0x4a, 0x26, 0x2, 0x162, 0x161, 0x3, 0x2, 0x2, 0x2, 
    0x162, 0x163, 0x3, 0x2, 0x2, 0x2, 0x163, 0x164, 0x3, 0x2, 0x2, 0x2, 
    0x164, 0x166, 0x7, 0x2f, 0x2, 0x2, 0x165, 0x15e, 0x3, 0x2, 0x2, 0x2, 
    0x165, 0x15f, 0x3, 0x2, 0x2, 0x2, 0x166, 0x47, 0x3, 0x2, 0x2, 0x2, 0x167, 
    0x16b, 0x3, 0x2, 0x2, 0x2, 0x168, 0x169, 0x7, 0xe, 0x2, 0x2, 0x169, 
    0x16b, 0x5, 0x32, 0x1a, 0x2, 0x16a, 0x167, 0x3, 0x2, 0x2, 0x2, 0x16a, 
    0x168, 0x3, 0x2, 0x2, 0x2, 0x16b, 0x49, 0x3, 0x2, 0x2, 0x2, 0x16c, 0x16d, 
    0x8, 0x26, 0x1, 0x2, 0x16d, 0x16e, 0x5, 0x4c, 0x27, 0x2, 0x16e, 0x174, 
    0x3, 0x2, 0x2, 0x2, 0x16f, 0x170, 0xc, 0x3, 0x2, 0x2, 0x170, 0x171, 
    0x7, 0x23, 0x2, 0x2, 0x171, 0x173, 0x5, 0x4c, 0x27, 0x2, 0x172, 0x16f, 
    0x3, 0x2, 0x2, 0x2, 0x173, 0x176, 0x3, 0x2, 0x2, 0x2, 0x174, 0x172, 
    0x3, 0x2, 0x2, 0x2, 0x174, 0x175, 0x3, 0x2, 0x2, 0x2, 0x175, 0x4b, 0x3, 
    0x2, 0x2, 0x2, 0x176, 0x174, 0x3, 0x2, 0x2, 0x2, 0x177, 0x17d, 0x5, 
    0x4e, 0x28, 0x2, 0x178, 0x179, 0x5, 0x4e, 0x28, 0x2, 0x179, 0x17a, 0x5, 
    0x56, 0x2c, 0x2, 0x17a, 0x17b, 0x5, 0x4e, 0x28, 0x2, 0x17b, 0x17d, 0x3, 
    0x2, 0x2, 0x2, 0x17c, 0x177, 0x3, 0x2, 0x2, 0x2, 0x17c, 0x178, 0x3, 
    0x2, 0x2, 0x2, 0x17d, 0x4d, 0x3, 0x2, 0x2, 0x2, 0x17e, 0x17f, 0x8, 0x28, 
    0x1, 0x2, 0x17f, 0x180, 0x5, 0x50, 0x29, 0x2, 0x180, 0x187, 0x3, 0x2, 
    0x2, 0x2, 0x181, 0x182, 0xc, 0x3, 0x2, 0x2, 0x182, 0x183, 0x5, 0x58, 
    0x2d, 0x2, 0x183, 0x184, 0x5, 0x50, 0x29, 0x2, 0x184, 0x186, 0x3, 0x2, 
    0x2, 0x2, 0x185, 0x181, 0x3, 0x2, 0x2, 0x2, 0x186, 0x189, 0x3, 0x2, 
    0x2, 0x2, 0x187, 0x185, 0x3, 0x2, 0x2, 0x2, 0x187, 0x188, 0x3, 0x2, 
    0x2, 0x2, 0x188, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x189, 0x187, 0x3, 0x2, 0x2, 
    0x2, 0x18a, 0x18b, 0x8, 0x29, 0x1, 0x2, 0x18b, 0x18c, 0x5, 0x52, 0x2a, 
    0x2, 0x18c, 0x193, 0x3, 0x2, 0x2, 0x2, 0x18d, 0x18e, 0xc, 0x3, 0x2, 
    0x2, 0x18e, 0x18f, 0x5, 0x5a, 0x2e, 0x2, 0x18f, 0x190, 0x5, 0x52, 0x2a, 
    0x2, 0x190, 0x192, 0x3, 0x2, 0x2, 0x2, 0x191, 0x18d, 0x3, 0x2, 0x2, 
    0x2, 0x192, 0x195, 0x3, 0x2, 0x2, 0x2, 0x193, 0x191, 0x3, 0x2, 0x2, 
    0x2, 0x193, 0x194, 0x3, 0x2, 0x2, 0x2, 0x194, 0x51, 0x3, 0x2, 0x2, 0x2, 
    0x195, 0x193, 0x3, 0x2, 0x2, 0x2, 0x196, 0x1ad, 0x5, 0x54, 0x2b, 0x2, 
    0x197, 0x19d, 0x7, 0x34, 0x2, 0x2, 0x198, 0x19a, 0x7, 0x2e, 0x2, 0x2, 
    0x199, 0x19b, 0x5, 0x4a, 0x26, 0x2, 0x19a, 0x199, 0x3, 0x2, 0x2, 0x2, 
    0x19a, 0x19b, 0x3, 0x2, 0x2, 0x2, 0x19b, 0x19c, 0x3, 0x2, 0x2, 0x2, 
    0x19c, 0x19e, 0x7, 0x2f, 0x2, 0x2, 0x19d, 0x198, 0x3, 0x2, 0x2, 0x2, 
    0x19d, 0x19e, 0x3, 0x2, 0x2, 0x2, 0x19e, 0x1ad, 0x3, 0x2, 0x2, 0x2, 
    0x19f, 0x1ad, 0x5, 0x42, 0x22, 0x2, 0x1a0, 0x1a1, 0x7, 0x2e, 0x2, 0x2, 
    0x1a1, 0x1a2, 0x5, 0x4c, 0x27, 0x2, 0x1a2, 0x1a3, 0x7, 0x2f, 0x2, 0x2, 
    0x1a3, 0x1ad, 0x3, 0x2, 0x2, 0x2, 0x1a4, 0x1a5, 0x7, 0x1c, 0x2, 0x2, 
    0x1a5, 0x1ad, 0x5, 0x52, 0x2a, 0x2, 0x1a6, 0x1a7, 0x7, 0x2b, 0x2, 0x2, 
    0x1a7, 0x1ad, 0x5, 0x52, 0x2a, 0x2, 0x1a8, 0x1a9, 0x7, 0x2a, 0x2, 0x2, 
    0x1a9, 0x1ad, 0x5, 0x52, 0x2a, 0x2, 0x1aa, 0x1ad, 0x7, 0x36, 0x2, 0x2, 
    0x1ab, 0x1ad, 0x7, 0x1f, 0x2, 0x2, 0x1ac, 0x196, 0x3, 0x2, 0x2, 0x2, 
    0x1ac, 0x197, 0x3, 0x2, 0x2, 0x2, 0x1ac, 0x19f, 0x3, 0x2, 0x2, 0x2, 
    0x1ac, 0x1a0, 0x3, 0x2, 0x2, 0x2, 0x1ac, 0x1a4, 0x3, 0x2, 0x2, 0x2, 
    0x1ac, 0x1a6, 0x3, 0x2, 0x2, 0x2, 0x1ac, 0x1a8, 0x3, 0x2, 0x2, 0x2, 
    0x1ac, 0x1aa, 0x3, 0x2, 0x2, 0x2, 0x1ac, 0x1ab, 0x3, 0x2, 0x2, 0x2, 
    0x1ad, 0x53, 0x3, 0x2, 0x2, 0x2, 0x1ae, 0x1af, 0x7, 0x35, 0x2, 0x2, 
    0x1af, 0x55, 0x3, 0x2, 0x2, 0x2, 0x1b0, 0x1b1, 0x9, 0x3, 0x2, 0x2, 0x1b1, 
    0x57, 0x3, 0x2, 0x2, 0x2, 0x1b2, 0x1b3, 0x9, 0x4, 0x2, 0x2, 0x1b3, 0x59, 
    0x3, 0x2, 0x2, 0x2, 0x1b4, 0x1b5, 0x9, 0x5, 0x2, 0x2, 0x1b5, 0x5b, 0x3, 
    0x2, 0x2, 0x2, 0x21, 0x6a, 0x76, 0x7e, 0x8c, 0x90, 0x94, 0x99, 0xa0, 
    0xaf, 0xba, 0xca, 0xd4, 0xe4, 0xe9, 0xec, 0xf6, 0xfb, 0x114, 0x127, 
    0x151, 0x15c, 0x162, 0x165, 0x16a, 0x174, 0x17c, 0x187, 0x193, 0x19a, 
    0x19d, 0x1ac, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

PascalSParser::Initializer PascalSParser::_init;
