
// Generated from PascalS.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  PascalSLexer : public antlr4::Lexer {
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

  explicit PascalSLexer(antlr4::CharStream *input);

  ~PascalSLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

