
// Generated from PascalS.g4 by ANTLR 4.13.2


#include "PascalSVisitor.h"

#include "PascalSParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct PascalSParserStaticData final {
  PascalSParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  PascalSParserStaticData(const PascalSParserStaticData&) = delete;
  PascalSParserStaticData(PascalSParserStaticData&&) = delete;
  PascalSParserStaticData& operator=(const PascalSParserStaticData&) = delete;
  PascalSParserStaticData& operator=(PascalSParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag pascalsParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<PascalSParserStaticData> pascalsParserStaticData = nullptr;

void pascalsParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (pascalsParserStaticData != nullptr) {
    return;
  }
#else
  assert(pascalsParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<PascalSParserStaticData>(
    std::vector<std::string>{
      "program", "programStruct", "programHead", "programBody", "idList", 
      "constDeclarations", "constDeclaration", "constValue", "varDeclarations", 
      "varDeclaration", "type", "basicType", "period", "subprogramDeclarations", 
      "subprogram", "subprogramHead", "formalParameter", "parameterList", 
      "parameter", "varParameter", "valueParameter", "subprogramBody", "compoundStatement", 
      "statementList", "statement", "ifStatement", "forStatement", "readStatement", 
      "whileStatement", "writeStatement", "variableList", "variable", "idVarPart", 
      "procedureCall", "elsePart", "expressionList", "expression", "simpleExpression", 
      "term", "factor", "num", "relop", "addop", "mulop"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "';'", "':'", "'.'", "','", 
      "'='", "'<>'", "'<'", "'<='", "'>'", "'>='", "'+'", "'-'", "'*'", 
      "'/'", "'('", "')'", "'['", "']'", "':='", "'..'"
    },
    std::vector<std::string>{
      "", "PROGRAM", "CONST", "VAR", "PROCEDURE", "FUNCTION", "BEGIN", "END", 
      "ARRAY", "OF", "IF", "THEN", "ELSE", "FOR", "TO", "DO", "READ", "WRITE", 
      "INTEGER", "REAL", "BOOLEAN", "CHAR", "DIV", "MOD", "AND", "OR", "NOT", 
      "WHILE", "SEMICOLON", "COLON", "DOT", "COMMA", "EQUAL", "NOTEQUAL", 
      "LT", "LE", "GT", "GE", "PLUS", "MINUS", "STAR", "SLASH", "LPAREN", 
      "RPAREN", "LBRACKET", "RBRACKET", "ASSIGNOP", "DOTDOT", "ID", "NUM", 
      "LETTER", "STRING", "COMMENT", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,53,423,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,7,
  	42,2,43,7,43,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,2,1,2,1,2,1,2,1,2,1,2,
  	3,2,103,8,2,1,3,1,3,1,3,1,3,1,3,1,4,1,4,1,4,5,4,113,8,4,10,4,12,4,116,
  	9,4,1,5,1,5,1,5,1,5,1,5,3,5,123,8,5,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,
  	6,1,6,5,6,135,8,6,10,6,12,6,138,9,6,1,7,3,7,141,8,7,1,7,1,7,1,7,1,7,1,
  	7,3,7,148,8,7,1,8,1,8,1,8,1,8,1,8,3,8,155,8,8,1,9,1,9,1,9,1,9,1,9,1,9,
  	1,9,1,9,1,9,1,9,1,9,5,9,168,8,9,10,9,12,9,171,9,9,1,10,1,10,1,10,1,10,
  	1,10,1,10,1,10,1,10,3,10,181,8,10,1,11,1,11,1,12,1,12,1,12,1,12,1,12,
  	1,12,1,12,1,12,1,12,1,12,5,12,195,8,12,10,12,12,12,198,9,12,1,13,1,13,
  	1,13,1,13,1,13,5,13,205,8,13,10,13,12,13,208,9,13,1,14,1,14,1,14,1,14,
  	1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,3,15,223,8,15,1,16,1,16,
  	1,16,1,16,1,16,3,16,230,8,16,1,17,1,17,1,17,1,17,1,17,1,17,5,17,238,8,
  	17,10,17,12,17,241,9,17,1,18,1,18,3,18,245,8,18,1,19,1,19,1,19,1,20,1,
  	20,1,20,1,20,1,21,1,21,1,21,1,21,1,22,1,22,1,22,1,22,1,23,1,23,1,23,1,
  	23,1,23,1,23,5,23,268,8,23,10,23,12,23,271,9,23,1,24,1,24,1,24,1,24,1,
  	24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,3,24,288,8,24,1,
  	25,1,25,1,25,1,25,1,25,1,25,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,
  	26,1,27,1,27,1,27,1,27,1,27,1,28,1,28,1,28,1,28,1,28,1,29,1,29,1,29,1,
  	29,1,29,1,30,1,30,1,30,1,30,1,30,1,30,5,30,326,8,30,10,30,12,30,329,9,
  	30,1,31,1,31,1,31,1,32,1,32,1,32,1,32,1,32,3,32,339,8,32,1,33,1,33,1,
  	33,1,33,1,33,1,33,3,33,347,8,33,1,34,1,34,1,34,3,34,352,8,34,1,35,1,35,
  	1,35,1,35,1,35,1,35,5,35,360,8,35,10,35,12,35,363,9,35,1,36,1,36,1,36,
  	1,36,1,36,3,36,370,8,36,1,37,1,37,1,37,1,37,1,37,1,37,1,37,5,37,379,8,
  	37,10,37,12,37,382,9,37,1,38,1,38,1,38,1,38,1,38,1,38,1,38,5,38,391,8,
  	38,10,38,12,38,394,9,38,1,39,1,39,1,39,1,39,1,39,1,39,1,39,1,39,1,39,
  	1,39,1,39,1,39,1,39,1,39,1,39,1,39,1,39,3,39,413,8,39,1,40,1,40,1,41,
  	1,41,1,42,1,42,1,43,1,43,1,43,0,10,12,18,24,26,34,46,60,70,74,76,44,0,
  	2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,
  	52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,82,84,86,0,4,1,0,18,21,1,
  	0,32,37,2,0,25,25,38,39,2,0,22,24,40,41,420,0,88,1,0,0,0,2,91,1,0,0,0,
  	4,96,1,0,0,0,6,104,1,0,0,0,8,109,1,0,0,0,10,122,1,0,0,0,12,124,1,0,0,
  	0,14,147,1,0,0,0,16,154,1,0,0,0,18,156,1,0,0,0,20,180,1,0,0,0,22,182,
  	1,0,0,0,24,184,1,0,0,0,26,199,1,0,0,0,28,209,1,0,0,0,30,222,1,0,0,0,32,
  	229,1,0,0,0,34,231,1,0,0,0,36,244,1,0,0,0,38,246,1,0,0,0,40,249,1,0,0,
  	0,42,253,1,0,0,0,44,257,1,0,0,0,46,261,1,0,0,0,48,287,1,0,0,0,50,289,
  	1,0,0,0,52,295,1,0,0,0,54,304,1,0,0,0,56,309,1,0,0,0,58,314,1,0,0,0,60,
  	319,1,0,0,0,62,330,1,0,0,0,64,338,1,0,0,0,66,346,1,0,0,0,68,351,1,0,0,
  	0,70,353,1,0,0,0,72,369,1,0,0,0,74,371,1,0,0,0,76,383,1,0,0,0,78,412,
  	1,0,0,0,80,414,1,0,0,0,82,416,1,0,0,0,84,418,1,0,0,0,86,420,1,0,0,0,88,
  	89,3,2,1,0,89,90,5,0,0,1,90,1,1,0,0,0,91,92,3,4,2,0,92,93,5,28,0,0,93,
  	94,3,6,3,0,94,95,5,30,0,0,95,3,1,0,0,0,96,97,5,1,0,0,97,102,5,48,0,0,
  	98,99,5,42,0,0,99,100,3,8,4,0,100,101,5,43,0,0,101,103,1,0,0,0,102,98,
  	1,0,0,0,102,103,1,0,0,0,103,5,1,0,0,0,104,105,3,10,5,0,105,106,3,16,8,
  	0,106,107,3,26,13,0,107,108,3,44,22,0,108,7,1,0,0,0,109,114,5,48,0,0,
  	110,111,5,31,0,0,111,113,5,48,0,0,112,110,1,0,0,0,113,116,1,0,0,0,114,
  	112,1,0,0,0,114,115,1,0,0,0,115,9,1,0,0,0,116,114,1,0,0,0,117,123,1,0,
  	0,0,118,119,5,2,0,0,119,120,3,12,6,0,120,121,5,28,0,0,121,123,1,0,0,0,
  	122,117,1,0,0,0,122,118,1,0,0,0,123,11,1,0,0,0,124,125,6,6,-1,0,125,126,
  	5,48,0,0,126,127,5,32,0,0,127,128,3,14,7,0,128,136,1,0,0,0,129,130,10,
  	1,0,0,130,131,5,28,0,0,131,132,5,48,0,0,132,133,5,32,0,0,133,135,3,14,
  	7,0,134,129,1,0,0,0,135,138,1,0,0,0,136,134,1,0,0,0,136,137,1,0,0,0,137,
  	13,1,0,0,0,138,136,1,0,0,0,139,141,5,38,0,0,140,139,1,0,0,0,140,141,1,
  	0,0,0,141,142,1,0,0,0,142,148,3,80,40,0,143,144,5,39,0,0,144,148,3,80,
  	40,0,145,148,5,50,0,0,146,148,5,51,0,0,147,140,1,0,0,0,147,143,1,0,0,
  	0,147,145,1,0,0,0,147,146,1,0,0,0,148,15,1,0,0,0,149,155,1,0,0,0,150,
  	151,5,3,0,0,151,152,3,18,9,0,152,153,5,28,0,0,153,155,1,0,0,0,154,149,
  	1,0,0,0,154,150,1,0,0,0,155,17,1,0,0,0,156,157,6,9,-1,0,157,158,3,8,4,
  	0,158,159,5,29,0,0,159,160,3,20,10,0,160,169,1,0,0,0,161,162,10,1,0,0,
  	162,163,5,28,0,0,163,164,3,8,4,0,164,165,5,29,0,0,165,166,3,20,10,0,166,
  	168,1,0,0,0,167,161,1,0,0,0,168,171,1,0,0,0,169,167,1,0,0,0,169,170,1,
  	0,0,0,170,19,1,0,0,0,171,169,1,0,0,0,172,181,3,22,11,0,173,174,5,8,0,
  	0,174,175,5,44,0,0,175,176,3,24,12,0,176,177,5,45,0,0,177,178,5,9,0,0,
  	178,179,3,22,11,0,179,181,1,0,0,0,180,172,1,0,0,0,180,173,1,0,0,0,181,
  	21,1,0,0,0,182,183,7,0,0,0,183,23,1,0,0,0,184,185,6,12,-1,0,185,186,5,
  	49,0,0,186,187,5,47,0,0,187,188,5,49,0,0,188,196,1,0,0,0,189,190,10,1,
  	0,0,190,191,5,31,0,0,191,192,5,49,0,0,192,193,5,47,0,0,193,195,5,49,0,
  	0,194,189,1,0,0,0,195,198,1,0,0,0,196,194,1,0,0,0,196,197,1,0,0,0,197,
  	25,1,0,0,0,198,196,1,0,0,0,199,206,6,13,-1,0,200,201,10,1,0,0,201,202,
  	3,28,14,0,202,203,5,28,0,0,203,205,1,0,0,0,204,200,1,0,0,0,205,208,1,
  	0,0,0,206,204,1,0,0,0,206,207,1,0,0,0,207,27,1,0,0,0,208,206,1,0,0,0,
  	209,210,3,30,15,0,210,211,5,28,0,0,211,212,3,42,21,0,212,29,1,0,0,0,213,
  	214,5,4,0,0,214,215,5,48,0,0,215,223,3,32,16,0,216,217,5,5,0,0,217,218,
  	5,48,0,0,218,219,3,32,16,0,219,220,5,29,0,0,220,221,3,22,11,0,221,223,
  	1,0,0,0,222,213,1,0,0,0,222,216,1,0,0,0,223,31,1,0,0,0,224,230,1,0,0,
  	0,225,226,5,42,0,0,226,227,3,34,17,0,227,228,5,43,0,0,228,230,1,0,0,0,
  	229,224,1,0,0,0,229,225,1,0,0,0,230,33,1,0,0,0,231,232,6,17,-1,0,232,
  	233,3,36,18,0,233,239,1,0,0,0,234,235,10,1,0,0,235,236,5,28,0,0,236,238,
  	3,36,18,0,237,234,1,0,0,0,238,241,1,0,0,0,239,237,1,0,0,0,239,240,1,0,
  	0,0,240,35,1,0,0,0,241,239,1,0,0,0,242,245,3,38,19,0,243,245,3,40,20,
  	0,244,242,1,0,0,0,244,243,1,0,0,0,245,37,1,0,0,0,246,247,5,3,0,0,247,
  	248,3,40,20,0,248,39,1,0,0,0,249,250,3,8,4,0,250,251,5,29,0,0,251,252,
  	3,20,10,0,252,41,1,0,0,0,253,254,3,10,5,0,254,255,3,16,8,0,255,256,3,
  	44,22,0,256,43,1,0,0,0,257,258,5,6,0,0,258,259,3,46,23,0,259,260,5,7,
  	0,0,260,45,1,0,0,0,261,262,6,23,-1,0,262,263,3,48,24,0,263,269,1,0,0,
  	0,264,265,10,1,0,0,265,266,5,28,0,0,266,268,3,48,24,0,267,264,1,0,0,0,
  	268,271,1,0,0,0,269,267,1,0,0,0,269,270,1,0,0,0,270,47,1,0,0,0,271,269,
  	1,0,0,0,272,288,1,0,0,0,273,274,3,62,31,0,274,275,5,46,0,0,275,276,3,
  	72,36,0,276,288,1,0,0,0,277,278,5,48,0,0,278,279,5,46,0,0,279,288,3,72,
  	36,0,280,288,3,66,33,0,281,288,3,44,22,0,282,288,3,50,25,0,283,288,3,
  	52,26,0,284,288,3,54,27,0,285,288,3,56,28,0,286,288,3,58,29,0,287,272,
  	1,0,0,0,287,273,1,0,0,0,287,277,1,0,0,0,287,280,1,0,0,0,287,281,1,0,0,
  	0,287,282,1,0,0,0,287,283,1,0,0,0,287,284,1,0,0,0,287,285,1,0,0,0,287,
  	286,1,0,0,0,288,49,1,0,0,0,289,290,5,10,0,0,290,291,3,72,36,0,291,292,
  	5,11,0,0,292,293,3,48,24,0,293,294,3,68,34,0,294,51,1,0,0,0,295,296,5,
  	13,0,0,296,297,5,48,0,0,297,298,5,46,0,0,298,299,3,72,36,0,299,300,5,
  	14,0,0,300,301,3,72,36,0,301,302,5,15,0,0,302,303,3,48,24,0,303,53,1,
  	0,0,0,304,305,5,16,0,0,305,306,5,42,0,0,306,307,3,60,30,0,307,308,5,43,
  	0,0,308,55,1,0,0,0,309,310,5,27,0,0,310,311,3,72,36,0,311,312,5,15,0,
  	0,312,313,3,48,24,0,313,57,1,0,0,0,314,315,5,17,0,0,315,316,5,42,0,0,
  	316,317,3,70,35,0,317,318,5,43,0,0,318,59,1,0,0,0,319,320,6,30,-1,0,320,
  	321,3,62,31,0,321,327,1,0,0,0,322,323,10,1,0,0,323,324,5,31,0,0,324,326,
  	3,62,31,0,325,322,1,0,0,0,326,329,1,0,0,0,327,325,1,0,0,0,327,328,1,0,
  	0,0,328,61,1,0,0,0,329,327,1,0,0,0,330,331,5,48,0,0,331,332,3,64,32,0,
  	332,63,1,0,0,0,333,339,1,0,0,0,334,335,5,44,0,0,335,336,3,70,35,0,336,
  	337,5,45,0,0,337,339,1,0,0,0,338,333,1,0,0,0,338,334,1,0,0,0,339,65,1,
  	0,0,0,340,347,5,48,0,0,341,342,5,48,0,0,342,343,5,42,0,0,343,344,3,70,
  	35,0,344,345,5,43,0,0,345,347,1,0,0,0,346,340,1,0,0,0,346,341,1,0,0,0,
  	347,67,1,0,0,0,348,352,1,0,0,0,349,350,5,12,0,0,350,352,3,48,24,0,351,
  	348,1,0,0,0,351,349,1,0,0,0,352,69,1,0,0,0,353,354,6,35,-1,0,354,355,
  	3,72,36,0,355,361,1,0,0,0,356,357,10,1,0,0,357,358,5,31,0,0,358,360,3,
  	72,36,0,359,356,1,0,0,0,360,363,1,0,0,0,361,359,1,0,0,0,361,362,1,0,0,
  	0,362,71,1,0,0,0,363,361,1,0,0,0,364,370,3,74,37,0,365,366,3,74,37,0,
  	366,367,3,82,41,0,367,368,3,74,37,0,368,370,1,0,0,0,369,364,1,0,0,0,369,
  	365,1,0,0,0,370,73,1,0,0,0,371,372,6,37,-1,0,372,373,3,76,38,0,373,380,
  	1,0,0,0,374,375,10,1,0,0,375,376,3,84,42,0,376,377,3,76,38,0,377,379,
  	1,0,0,0,378,374,1,0,0,0,379,382,1,0,0,0,380,378,1,0,0,0,380,381,1,0,0,
  	0,381,75,1,0,0,0,382,380,1,0,0,0,383,384,6,38,-1,0,384,385,3,78,39,0,
  	385,392,1,0,0,0,386,387,10,1,0,0,387,388,3,86,43,0,388,389,3,78,39,0,
  	389,391,1,0,0,0,390,386,1,0,0,0,391,394,1,0,0,0,392,390,1,0,0,0,392,393,
  	1,0,0,0,393,77,1,0,0,0,394,392,1,0,0,0,395,413,3,80,40,0,396,413,3,62,
  	31,0,397,398,5,42,0,0,398,399,3,72,36,0,399,400,5,43,0,0,400,413,1,0,
  	0,0,401,402,5,48,0,0,402,403,5,42,0,0,403,404,3,70,35,0,404,405,5,43,
  	0,0,405,413,1,0,0,0,406,407,5,26,0,0,407,413,3,78,39,0,408,409,5,39,0,
  	0,409,413,3,78,39,0,410,413,5,51,0,0,411,413,5,50,0,0,412,395,1,0,0,0,
  	412,396,1,0,0,0,412,397,1,0,0,0,412,401,1,0,0,0,412,406,1,0,0,0,412,408,
  	1,0,0,0,412,410,1,0,0,0,412,411,1,0,0,0,413,79,1,0,0,0,414,415,5,49,0,
  	0,415,81,1,0,0,0,416,417,7,1,0,0,417,83,1,0,0,0,418,419,7,2,0,0,419,85,
  	1,0,0,0,420,421,7,3,0,0,421,87,1,0,0,0,26,102,114,122,136,140,147,154,
  	169,180,196,206,222,229,239,244,269,287,327,338,346,351,361,369,380,392,
  	412
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  pascalsParserStaticData = std::move(staticData);
}

}

PascalSParser::PascalSParser(TokenStream *input) : PascalSParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

PascalSParser::PascalSParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  PascalSParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *pascalsParserStaticData->atn, pascalsParserStaticData->decisionToDFA, pascalsParserStaticData->sharedContextCache, options);
}

PascalSParser::~PascalSParser() {
  delete _interpreter;
}

const atn::ATN& PascalSParser::getATN() const {
  return *pascalsParserStaticData->atn;
}

std::string PascalSParser::getGrammarFileName() const {
  return "PascalS.g4";
}

const std::vector<std::string>& PascalSParser::getRuleNames() const {
  return pascalsParserStaticData->ruleNames;
}

const dfa::Vocabulary& PascalSParser::getVocabulary() const {
  return pascalsParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView PascalSParser::getSerializedATN() const {
  return pascalsParserStaticData->serializedATN;
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


std::any PascalSParser::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::ProgramContext* PascalSParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, PascalSParser::RuleProgram);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(88);
    programStruct();
    setState(89);
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


std::any PascalSParser::ProgramStructContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitProgramStruct(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::ProgramStructContext* PascalSParser::programStruct() {
  ProgramStructContext *_localctx = _tracker.createInstance<ProgramStructContext>(_ctx, getState());
  enterRule(_localctx, 2, PascalSParser::RuleProgramStruct);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(91);
    programHead();
    setState(92);
    match(PascalSParser::SEMICOLON);
    setState(93);
    programBody();
    setState(94);
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


std::any PascalSParser::ProgramHeadContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitProgramHead(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::ProgramHeadContext* PascalSParser::programHead() {
  ProgramHeadContext *_localctx = _tracker.createInstance<ProgramHeadContext>(_ctx, getState());
  enterRule(_localctx, 4, PascalSParser::RuleProgramHead);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(96);
    match(PascalSParser::PROGRAM);
    setState(97);
    match(PascalSParser::ID);
    setState(102);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PascalSParser::LPAREN) {
      setState(98);
      match(PascalSParser::LPAREN);
      setState(99);
      idList();
      setState(100);
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


std::any PascalSParser::ProgramBodyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitProgramBody(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::ProgramBodyContext* PascalSParser::programBody() {
  ProgramBodyContext *_localctx = _tracker.createInstance<ProgramBodyContext>(_ctx, getState());
  enterRule(_localctx, 6, PascalSParser::RuleProgramBody);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(104);
    constDeclarations();
    setState(105);
    varDeclarations();
    setState(106);
    subprogramDeclarations(0);
    setState(107);
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


std::any PascalSParser::IdListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitIdList(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::IdListContext* PascalSParser::idList() {
  IdListContext *_localctx = _tracker.createInstance<IdListContext>(_ctx, getState());
  enterRule(_localctx, 8, PascalSParser::RuleIdList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(109);
    match(PascalSParser::ID);
    setState(114);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PascalSParser::COMMA) {
      setState(110);
      match(PascalSParser::COMMA);
      setState(111);
      match(PascalSParser::ID);
      setState(116);
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


std::any PascalSParser::ConstDeclarationsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitConstDeclarations(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::ConstDeclarationsContext* PascalSParser::constDeclarations() {
  ConstDeclarationsContext *_localctx = _tracker.createInstance<ConstDeclarationsContext>(_ctx, getState());
  enterRule(_localctx, 10, PascalSParser::RuleConstDeclarations);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(122);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);

      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(118);
      match(PascalSParser::CONST);
      setState(119);
      constDeclaration(0);
      setState(120);
      match(PascalSParser::SEMICOLON);
      break;
    }

    default:
      break;
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


std::any PascalSParser::ConstDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
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
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 12;
  enterRecursionRule(_localctx, 12, PascalSParser::RuleConstDeclaration, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(125);
    match(PascalSParser::ID);
    setState(126);
    match(PascalSParser::EQUAL);
    setState(127);
    constValue();
    _ctx->stop = _input->LT(-1);
    setState(136);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<ConstDeclarationContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleConstDeclaration);
        setState(129);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(130);
        match(PascalSParser::SEMICOLON);
        setState(131);
        match(PascalSParser::ID);
        setState(132);
        match(PascalSParser::EQUAL);
        setState(133);
        constValue(); 
      }
      setState(138);
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


std::any PascalSParser::ConstValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitConstValue(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::ConstValueContext* PascalSParser::constValue() {
  ConstValueContext *_localctx = _tracker.createInstance<ConstValueContext>(_ctx, getState());
  enterRule(_localctx, 14, PascalSParser::RuleConstValue);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(147);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PascalSParser::PLUS:
      case PascalSParser::NUM: {
        enterOuterAlt(_localctx, 1);
        setState(140);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PascalSParser::PLUS) {
          setState(139);
          match(PascalSParser::PLUS);
        }
        setState(142);
        num();
        break;
      }

      case PascalSParser::MINUS: {
        enterOuterAlt(_localctx, 2);
        setState(143);
        match(PascalSParser::MINUS);
        setState(144);
        num();
        break;
      }

      case PascalSParser::LETTER: {
        enterOuterAlt(_localctx, 3);
        setState(145);
        match(PascalSParser::LETTER);
        break;
      }

      case PascalSParser::STRING: {
        enterOuterAlt(_localctx, 4);
        setState(146);
        match(PascalSParser::STRING);
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


std::any PascalSParser::VarDeclarationsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitVarDeclarations(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::VarDeclarationsContext* PascalSParser::varDeclarations() {
  VarDeclarationsContext *_localctx = _tracker.createInstance<VarDeclarationsContext>(_ctx, getState());
  enterRule(_localctx, 16, PascalSParser::RuleVarDeclarations);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(154);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);

      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(150);
      match(PascalSParser::VAR);
      setState(151);
      varDeclaration(0);
      setState(152);
      match(PascalSParser::SEMICOLON);
      break;
    }

    default:
      break;
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


std::any PascalSParser::VarDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
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
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 18;
  enterRecursionRule(_localctx, 18, PascalSParser::RuleVarDeclaration, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(157);
    idList();
    setState(158);
    match(PascalSParser::COLON);
    setState(159);
    type();
    _ctx->stop = _input->LT(-1);
    setState(169);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<VarDeclarationContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleVarDeclaration);
        setState(161);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(162);
        match(PascalSParser::SEMICOLON);
        setState(163);
        idList();
        setState(164);
        match(PascalSParser::COLON);
        setState(165);
        type(); 
      }
      setState(171);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx);
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


std::any PascalSParser::TypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitType(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::TypeContext* PascalSParser::type() {
  TypeContext *_localctx = _tracker.createInstance<TypeContext>(_ctx, getState());
  enterRule(_localctx, 20, PascalSParser::RuleType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(180);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PascalSParser::INTEGER:
      case PascalSParser::REAL:
      case PascalSParser::BOOLEAN:
      case PascalSParser::CHAR: {
        enterOuterAlt(_localctx, 1);
        setState(172);
        basicType();
        break;
      }

      case PascalSParser::ARRAY: {
        enterOuterAlt(_localctx, 2);
        setState(173);
        match(PascalSParser::ARRAY);
        setState(174);
        match(PascalSParser::LBRACKET);
        setState(175);
        period(0);
        setState(176);
        match(PascalSParser::RBRACKET);
        setState(177);
        match(PascalSParser::OF);
        setState(178);
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


std::any PascalSParser::BasicTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitBasicType(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::BasicTypeContext* PascalSParser::basicType() {
  BasicTypeContext *_localctx = _tracker.createInstance<BasicTypeContext>(_ctx, getState());
  enterRule(_localctx, 22, PascalSParser::RuleBasicType);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(182);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 3932160) != 0))) {
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


std::any PascalSParser::PeriodContext::accept(tree::ParseTreeVisitor *visitor) {
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
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 24;
  enterRecursionRule(_localctx, 24, PascalSParser::RulePeriod, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(185);
    match(PascalSParser::NUM);
    setState(186);
    match(PascalSParser::DOTDOT);
    setState(187);
    match(PascalSParser::NUM);
    _ctx->stop = _input->LT(-1);
    setState(196);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<PeriodContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RulePeriod);
        setState(189);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(190);
        match(PascalSParser::COMMA);
        setState(191);
        match(PascalSParser::NUM);
        setState(192);
        match(PascalSParser::DOTDOT);
        setState(193);
        match(PascalSParser::NUM); 
      }
      setState(198);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
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


std::any PascalSParser::SubprogramDeclarationsContext::accept(tree::ParseTreeVisitor *visitor) {
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
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 26;
  enterRecursionRule(_localctx, 26, PascalSParser::RuleSubprogramDeclarations, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    _ctx->stop = _input->LT(-1);
    setState(206);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<SubprogramDeclarationsContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleSubprogramDeclarations);
        setState(200);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(201);
        subprogram();
        setState(202);
        match(PascalSParser::SEMICOLON); 
      }
      setState(208);
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


std::any PascalSParser::SubprogramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitSubprogram(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::SubprogramContext* PascalSParser::subprogram() {
  SubprogramContext *_localctx = _tracker.createInstance<SubprogramContext>(_ctx, getState());
  enterRule(_localctx, 28, PascalSParser::RuleSubprogram);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(209);
    subprogramHead();
    setState(210);
    match(PascalSParser::SEMICOLON);
    setState(211);
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


std::any PascalSParser::SubprogramHeadContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitSubprogramHead(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::SubprogramHeadContext* PascalSParser::subprogramHead() {
  SubprogramHeadContext *_localctx = _tracker.createInstance<SubprogramHeadContext>(_ctx, getState());
  enterRule(_localctx, 30, PascalSParser::RuleSubprogramHead);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(222);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PascalSParser::PROCEDURE: {
        enterOuterAlt(_localctx, 1);
        setState(213);
        match(PascalSParser::PROCEDURE);
        setState(214);
        match(PascalSParser::ID);
        setState(215);
        formalParameter();
        break;
      }

      case PascalSParser::FUNCTION: {
        enterOuterAlt(_localctx, 2);
        setState(216);
        match(PascalSParser::FUNCTION);
        setState(217);
        match(PascalSParser::ID);
        setState(218);
        formalParameter();
        setState(219);
        match(PascalSParser::COLON);
        setState(220);
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

PascalSParser::ParameterListContext* PascalSParser::FormalParameterContext::parameterList() {
  return getRuleContext<PascalSParser::ParameterListContext>(0);
}

tree::TerminalNode* PascalSParser::FormalParameterContext::RPAREN() {
  return getToken(PascalSParser::RPAREN, 0);
}


size_t PascalSParser::FormalParameterContext::getRuleIndex() const {
  return PascalSParser::RuleFormalParameter;
}


std::any PascalSParser::FormalParameterContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitFormalParameter(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::FormalParameterContext* PascalSParser::formalParameter() {
  FormalParameterContext *_localctx = _tracker.createInstance<FormalParameterContext>(_ctx, getState());
  enterRule(_localctx, 32, PascalSParser::RuleFormalParameter);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(229);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PascalSParser::SEMICOLON:
      case PascalSParser::COLON: {
        enterOuterAlt(_localctx, 1);

        break;
      }

      case PascalSParser::LPAREN: {
        enterOuterAlt(_localctx, 2);
        setState(225);
        match(PascalSParser::LPAREN);
        setState(226);
        parameterList(0);
        setState(227);
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


std::any PascalSParser::ParameterListContext::accept(tree::ParseTreeVisitor *visitor) {
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
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 34;
  enterRecursionRule(_localctx, 34, PascalSParser::RuleParameterList, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(232);
    parameter();
    _ctx->stop = _input->LT(-1);
    setState(239);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<ParameterListContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleParameterList);
        setState(234);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(235);
        match(PascalSParser::SEMICOLON);
        setState(236);
        parameter(); 
      }
      setState(241);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx);
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


std::any PascalSParser::ParameterContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitParameter(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::ParameterContext* PascalSParser::parameter() {
  ParameterContext *_localctx = _tracker.createInstance<ParameterContext>(_ctx, getState());
  enterRule(_localctx, 36, PascalSParser::RuleParameter);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(244);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PascalSParser::VAR: {
        enterOuterAlt(_localctx, 1);
        setState(242);
        varParameter();
        break;
      }

      case PascalSParser::ID: {
        enterOuterAlt(_localctx, 2);
        setState(243);
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


std::any PascalSParser::VarParameterContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitVarParameter(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::VarParameterContext* PascalSParser::varParameter() {
  VarParameterContext *_localctx = _tracker.createInstance<VarParameterContext>(_ctx, getState());
  enterRule(_localctx, 38, PascalSParser::RuleVarParameter);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(246);
    match(PascalSParser::VAR);
    setState(247);
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


std::any PascalSParser::ValueParameterContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitValueParameter(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::ValueParameterContext* PascalSParser::valueParameter() {
  ValueParameterContext *_localctx = _tracker.createInstance<ValueParameterContext>(_ctx, getState());
  enterRule(_localctx, 40, PascalSParser::RuleValueParameter);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(249);
    idList();
    setState(250);
    match(PascalSParser::COLON);
    setState(251);
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


std::any PascalSParser::SubprogramBodyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitSubprogramBody(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::SubprogramBodyContext* PascalSParser::subprogramBody() {
  SubprogramBodyContext *_localctx = _tracker.createInstance<SubprogramBodyContext>(_ctx, getState());
  enterRule(_localctx, 42, PascalSParser::RuleSubprogramBody);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(253);
    constDeclarations();
    setState(254);
    varDeclarations();
    setState(255);
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


std::any PascalSParser::CompoundStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitCompoundStatement(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::CompoundStatementContext* PascalSParser::compoundStatement() {
  CompoundStatementContext *_localctx = _tracker.createInstance<CompoundStatementContext>(_ctx, getState());
  enterRule(_localctx, 44, PascalSParser::RuleCompoundStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(257);
    match(PascalSParser::BEGIN);
    setState(258);
    statementList(0);
    setState(259);
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


std::any PascalSParser::StatementListContext::accept(tree::ParseTreeVisitor *visitor) {
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
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 46;
  enterRecursionRule(_localctx, 46, PascalSParser::RuleStatementList, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(262);
    statement();
    _ctx->stop = _input->LT(-1);
    setState(269);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<StatementListContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleStatementList);
        setState(264);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(265);
        match(PascalSParser::SEMICOLON);
        setState(266);
        statement(); 
      }
      setState(271);
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

PascalSParser::WhileStatementContext* PascalSParser::StatementContext::whileStatement() {
  return getRuleContext<PascalSParser::WhileStatementContext>(0);
}

PascalSParser::WriteStatementContext* PascalSParser::StatementContext::writeStatement() {
  return getRuleContext<PascalSParser::WriteStatementContext>(0);
}


size_t PascalSParser::StatementContext::getRuleIndex() const {
  return PascalSParser::RuleStatement;
}


std::any PascalSParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::StatementContext* PascalSParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 48, PascalSParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(287);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);

      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(273);
      variable();
      setState(274);
      match(PascalSParser::ASSIGNOP);
      setState(275);
      expression();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(277);
      match(PascalSParser::ID);
      setState(278);
      match(PascalSParser::ASSIGNOP);
      setState(279);
      expression();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(280);
      procedureCall();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(281);
      compoundStatement();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(282);
      ifStatement();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(283);
      forStatement();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(284);
      readStatement();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(285);
      whileStatement();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(286);
      writeStatement();
      break;
    }

    default:
      break;
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


std::any PascalSParser::IfStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitIfStatement(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::IfStatementContext* PascalSParser::ifStatement() {
  IfStatementContext *_localctx = _tracker.createInstance<IfStatementContext>(_ctx, getState());
  enterRule(_localctx, 50, PascalSParser::RuleIfStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(289);
    match(PascalSParser::IF);
    setState(290);
    expression();
    setState(291);
    match(PascalSParser::THEN);
    setState(292);
    statement();
    setState(293);
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


std::any PascalSParser::ForStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitForStatement(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::ForStatementContext* PascalSParser::forStatement() {
  ForStatementContext *_localctx = _tracker.createInstance<ForStatementContext>(_ctx, getState());
  enterRule(_localctx, 52, PascalSParser::RuleForStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(295);
    match(PascalSParser::FOR);
    setState(296);
    match(PascalSParser::ID);
    setState(297);
    match(PascalSParser::ASSIGNOP);
    setState(298);
    expression();
    setState(299);
    match(PascalSParser::TO);
    setState(300);
    expression();
    setState(301);
    match(PascalSParser::DO);
    setState(302);
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


std::any PascalSParser::ReadStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitReadStatement(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::ReadStatementContext* PascalSParser::readStatement() {
  ReadStatementContext *_localctx = _tracker.createInstance<ReadStatementContext>(_ctx, getState());
  enterRule(_localctx, 54, PascalSParser::RuleReadStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(304);
    match(PascalSParser::READ);
    setState(305);
    match(PascalSParser::LPAREN);
    setState(306);
    variableList(0);
    setState(307);
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


std::any PascalSParser::WhileStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitWhileStatement(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::WhileStatementContext* PascalSParser::whileStatement() {
  WhileStatementContext *_localctx = _tracker.createInstance<WhileStatementContext>(_ctx, getState());
  enterRule(_localctx, 56, PascalSParser::RuleWhileStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(309);
    match(PascalSParser::WHILE);
    setState(310);
    expression();
    setState(311);
    match(PascalSParser::DO);
    setState(312);
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


std::any PascalSParser::WriteStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitWriteStatement(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::WriteStatementContext* PascalSParser::writeStatement() {
  WriteStatementContext *_localctx = _tracker.createInstance<WriteStatementContext>(_ctx, getState());
  enterRule(_localctx, 58, PascalSParser::RuleWriteStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(314);
    match(PascalSParser::WRITE);
    setState(315);
    match(PascalSParser::LPAREN);
    setState(316);
    expressionList(0);
    setState(317);
    match(PascalSParser::RPAREN);
   
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


std::any PascalSParser::VariableListContext::accept(tree::ParseTreeVisitor *visitor) {
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
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 60;
  enterRecursionRule(_localctx, 60, PascalSParser::RuleVariableList, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(320);
    variable();
    _ctx->stop = _input->LT(-1);
    setState(327);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<VariableListContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleVariableList);
        setState(322);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(323);
        match(PascalSParser::COMMA);
        setState(324);
        variable(); 
      }
      setState(329);
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


std::any PascalSParser::VariableContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitVariable(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::VariableContext* PascalSParser::variable() {
  VariableContext *_localctx = _tracker.createInstance<VariableContext>(_ctx, getState());
  enterRule(_localctx, 62, PascalSParser::RuleVariable);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(330);
    match(PascalSParser::ID);
    setState(331);
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


std::any PascalSParser::IdVarPartContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitIdVarPart(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::IdVarPartContext* PascalSParser::idVarPart() {
  IdVarPartContext *_localctx = _tracker.createInstance<IdVarPartContext>(_ctx, getState());
  enterRule(_localctx, 64, PascalSParser::RuleIdVarPart);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(338);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);

      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(334);
      match(PascalSParser::LBRACKET);
      setState(335);
      expressionList(0);
      setState(336);
      match(PascalSParser::RBRACKET);
      break;
    }

    default:
      break;
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

PascalSParser::ExpressionListContext* PascalSParser::ProcedureCallContext::expressionList() {
  return getRuleContext<PascalSParser::ExpressionListContext>(0);
}

tree::TerminalNode* PascalSParser::ProcedureCallContext::RPAREN() {
  return getToken(PascalSParser::RPAREN, 0);
}


size_t PascalSParser::ProcedureCallContext::getRuleIndex() const {
  return PascalSParser::RuleProcedureCall;
}


std::any PascalSParser::ProcedureCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitProcedureCall(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::ProcedureCallContext* PascalSParser::procedureCall() {
  ProcedureCallContext *_localctx = _tracker.createInstance<ProcedureCallContext>(_ctx, getState());
  enterRule(_localctx, 66, PascalSParser::RuleProcedureCall);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(346);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(340);
      match(PascalSParser::ID);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(341);
      match(PascalSParser::ID);
      setState(342);
      match(PascalSParser::LPAREN);
      setState(343);
      expressionList(0);
      setState(344);
      match(PascalSParser::RPAREN);
      break;
    }

    default:
      break;
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


std::any PascalSParser::ElsePartContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitElsePart(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::ElsePartContext* PascalSParser::elsePart() {
  ElsePartContext *_localctx = _tracker.createInstance<ElsePartContext>(_ctx, getState());
  enterRule(_localctx, 68, PascalSParser::RuleElsePart);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(351);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);

      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(349);
      match(PascalSParser::ELSE);
      setState(350);
      statement();
      break;
    }

    default:
      break;
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


std::any PascalSParser::ExpressionListContext::accept(tree::ParseTreeVisitor *visitor) {
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
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 70;
  enterRecursionRule(_localctx, 70, PascalSParser::RuleExpressionList, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(354);
    expression();
    _ctx->stop = _input->LT(-1);
    setState(361);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<ExpressionListContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleExpressionList);
        setState(356);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(357);
        match(PascalSParser::COMMA);
        setState(358);
        expression(); 
      }
      setState(363);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx);
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


std::any PascalSParser::ExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitExpression(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::ExpressionContext* PascalSParser::expression() {
  ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, getState());
  enterRule(_localctx, 72, PascalSParser::RuleExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(369);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(364);
      simpleExpression(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(365);
      simpleExpression(0);
      setState(366);
      relop();
      setState(367);
      simpleExpression(0);
      break;
    }

    default:
      break;
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


std::any PascalSParser::SimpleExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
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
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 74;
  enterRecursionRule(_localctx, 74, PascalSParser::RuleSimpleExpression, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(372);
    term(0);
    _ctx->stop = _input->LT(-1);
    setState(380);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<SimpleExpressionContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleSimpleExpression);
        setState(374);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(375);
        addop();
        setState(376);
        term(0); 
      }
      setState(382);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx);
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


std::any PascalSParser::TermContext::accept(tree::ParseTreeVisitor *visitor) {
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
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 76;
  enterRecursionRule(_localctx, 76, PascalSParser::RuleTerm, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(384);
    factor();
    _ctx->stop = _input->LT(-1);
    setState(392);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<TermContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleTerm);
        setState(386);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(387);
        mulop();
        setState(388);
        factor(); 
      }
      setState(394);
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

//----------------- FactorContext ------------------------------------------------------------------

PascalSParser::FactorContext::FactorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PascalSParser::NumContext* PascalSParser::FactorContext::num() {
  return getRuleContext<PascalSParser::NumContext>(0);
}

PascalSParser::VariableContext* PascalSParser::FactorContext::variable() {
  return getRuleContext<PascalSParser::VariableContext>(0);
}

tree::TerminalNode* PascalSParser::FactorContext::LPAREN() {
  return getToken(PascalSParser::LPAREN, 0);
}

PascalSParser::ExpressionContext* PascalSParser::FactorContext::expression() {
  return getRuleContext<PascalSParser::ExpressionContext>(0);
}

tree::TerminalNode* PascalSParser::FactorContext::RPAREN() {
  return getToken(PascalSParser::RPAREN, 0);
}

tree::TerminalNode* PascalSParser::FactorContext::ID() {
  return getToken(PascalSParser::ID, 0);
}

PascalSParser::ExpressionListContext* PascalSParser::FactorContext::expressionList() {
  return getRuleContext<PascalSParser::ExpressionListContext>(0);
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

tree::TerminalNode* PascalSParser::FactorContext::STRING() {
  return getToken(PascalSParser::STRING, 0);
}

tree::TerminalNode* PascalSParser::FactorContext::LETTER() {
  return getToken(PascalSParser::LETTER, 0);
}


size_t PascalSParser::FactorContext::getRuleIndex() const {
  return PascalSParser::RuleFactor;
}


std::any PascalSParser::FactorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitFactor(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::FactorContext* PascalSParser::factor() {
  FactorContext *_localctx = _tracker.createInstance<FactorContext>(_ctx, getState());
  enterRule(_localctx, 78, PascalSParser::RuleFactor);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(412);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(395);
      num();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(396);
      variable();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(397);
      match(PascalSParser::LPAREN);
      setState(398);
      expression();
      setState(399);
      match(PascalSParser::RPAREN);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(401);
      match(PascalSParser::ID);
      setState(402);
      match(PascalSParser::LPAREN);
      setState(403);
      expressionList(0);
      setState(404);
      match(PascalSParser::RPAREN);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(406);
      match(PascalSParser::NOT);
      setState(407);
      factor();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(408);
      match(PascalSParser::MINUS);
      setState(409);
      factor();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(410);
      match(PascalSParser::STRING);
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(411);
      match(PascalSParser::LETTER);
      break;
    }

    default:
      break;
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


std::any PascalSParser::NumContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitNum(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::NumContext* PascalSParser::num() {
  NumContext *_localctx = _tracker.createInstance<NumContext>(_ctx, getState());
  enterRule(_localctx, 80, PascalSParser::RuleNum);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(414);
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


std::any PascalSParser::RelopContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitRelop(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::RelopContext* PascalSParser::relop() {
  RelopContext *_localctx = _tracker.createInstance<RelopContext>(_ctx, getState());
  enterRule(_localctx, 82, PascalSParser::RuleRelop);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(416);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 270582939648) != 0))) {
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


std::any PascalSParser::AddopContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitAddop(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::AddopContext* PascalSParser::addop() {
  AddopContext *_localctx = _tracker.createInstance<AddopContext>(_ctx, getState());
  enterRule(_localctx, 84, PascalSParser::RuleAddop);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(418);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 824667275264) != 0))) {
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


std::any PascalSParser::MulopContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PascalSVisitor*>(visitor))
    return parserVisitor->visitMulop(this);
  else
    return visitor->visitChildren(this);
}

PascalSParser::MulopContext* PascalSParser::mulop() {
  MulopContext *_localctx = _tracker.createInstance<MulopContext>(_ctx, getState());
  enterRule(_localctx, 86, PascalSParser::RuleMulop);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(420);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 3298564243456) != 0))) {
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
    case 6: return constDeclarationSempred(antlrcpp::downCast<ConstDeclarationContext *>(context), predicateIndex);
    case 9: return varDeclarationSempred(antlrcpp::downCast<VarDeclarationContext *>(context), predicateIndex);
    case 12: return periodSempred(antlrcpp::downCast<PeriodContext *>(context), predicateIndex);
    case 13: return subprogramDeclarationsSempred(antlrcpp::downCast<SubprogramDeclarationsContext *>(context), predicateIndex);
    case 17: return parameterListSempred(antlrcpp::downCast<ParameterListContext *>(context), predicateIndex);
    case 23: return statementListSempred(antlrcpp::downCast<StatementListContext *>(context), predicateIndex);
    case 30: return variableListSempred(antlrcpp::downCast<VariableListContext *>(context), predicateIndex);
    case 35: return expressionListSempred(antlrcpp::downCast<ExpressionListContext *>(context), predicateIndex);
    case 37: return simpleExpressionSempred(antlrcpp::downCast<SimpleExpressionContext *>(context), predicateIndex);
    case 38: return termSempred(antlrcpp::downCast<TermContext *>(context), predicateIndex);

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

void PascalSParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  pascalsParserInitialize();
#else
  ::antlr4::internal::call_once(pascalsParserOnceFlag, pascalsParserInitialize);
#endif
}
