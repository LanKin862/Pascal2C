
// Generated from PascalS.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"




class  PascalSLexer : public antlr4::Lexer {
public:
  enum {
    PROGRAM = 1, CONST = 2, VAR = 3, PROCEDURE = 4, FUNCTION = 5, BEGIN = 6, 
    END = 7, ARRAY = 8, OF = 9, IF = 10, THEN = 11, ELSE = 12, FOR = 13, 
    TO = 14, DO = 15, READ = 16, WRITE = 17, INTEGER = 18, REAL = 19, BOOLEAN = 20, 
    CHAR = 21, DIV = 22, MOD = 23, AND = 24, OR = 25, NOT = 26, WHILE = 27, 
    BREAK = 28, LETTER = 29, SEMICOLON = 30, COLON = 31, DOT = 32, COMMA = 33, 
    EQUAL = 34, NOTEQUAL = 35, LT = 36, LE = 37, GT = 38, GE = 39, PLUS = 40, 
    MINUS = 41, STAR = 42, SLASH = 43, LPAREN = 44, RPAREN = 45, LBRACKET = 46, 
    RBRACKET = 47, ASSIGNOP = 48, DOTDOT = 49, ID = 50, NUM = 51, STRING = 52, 
    COMMENT = 53, LINE_COMMENT = 54, WS = 55
  };

  PascalSLexer(antlr4::CharStream *input);
  ~PascalSLexer();

  virtual std::string getGrammarFileName() const override;
  virtual const std::vector<std::string>& getRuleNames() const override;

  virtual const std::vector<std::string>& getChannelNames() const override;
  virtual const std::vector<std::string>& getModeNames() const override;
  virtual const std::vector<std::string>& getTokenNames() const override; // deprecated, use vocabulary instead
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;

  virtual const std::vector<uint16_t> getSerializedATN() const override;
  virtual const antlr4::atn::ATN& getATN() const override;

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;
  static std::vector<std::string> _channelNames;
  static std::vector<std::string> _modeNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

