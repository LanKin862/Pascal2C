grammar PascalS;

// Parser Rules
program
    : programStruct EOF
    ;

programStruct
    : programHead SEMICOLON programBody DOT
    ;

programHead
    : PROGRAM ID (LPAREN idList RPAREN)?
    ;

programBody
    : constDeclarations
      varDeclarations
      subprogramDeclarations
      compoundStatement
    ;

idList
    : ID (COMMA ID)*
    ;

constDeclarations
    : /* empty */
    | CONST constDeclaration SEMICOLON
    ;

constDeclaration
    : ID EQUAL constValue
    | constDeclaration SEMICOLON ID EQUAL constValue
    ;

constValue
    : PLUS? num
    | MINUS? num
    | LETTER
    | STRING
    ;

varDeclarations
    : /* empty */
    | VAR varDeclaration SEMICOLON
    ;

varDeclaration
    : idList COLON type
    | varDeclaration SEMICOLON idList COLON type
    ;

type
    : basicType
    | ARRAY LBRACKET period RBRACKET OF basicType
    ;

basicType
    : INTEGER
    | REAL
    | BOOLEAN
    | CHAR
    ;

period
    : NUM DOTDOT NUM
    | period COMMA NUM DOTDOT NUM
    ;

subprogramDeclarations
    : /* empty */
    | subprogramDeclarations subprogram SEMICOLON
    ;

subprogram
    : subprogramHead SEMICOLON subprogramBody
    ;

subprogramHead
    : PROCEDURE ID formalParameter
    | FUNCTION ID formalParameter COLON basicType
    ;

formalParameter
    : /* empty */
    | LPAREN (parameterList)? RPAREN
    ;

parameterList
    : parameter
    | parameterList SEMICOLON parameter
    ;

parameter
    : varParameter
    | valueParameter
    ;

varParameter
    : VAR valueParameter
    ;

valueParameter
    : idList COLON type
    ;

subprogramBody
    : constDeclarations
      varDeclarations
      compoundStatement
    ;

compoundStatement
    : BEGIN statementList END
    ;

statementList
    : statement
    | statementList SEMICOLON statement
    ;

statement
    : /* empty */
    | variable ASSIGNOP expression
    | ID ASSIGNOP expression
    | procedureCall
    | compoundStatement
    | ifStatement
    | forStatement
    | readStatement
    | breakStatement
    | whileStatement
    | writeStatement
    ;

ifStatement
    : IF expression THEN statement elsePart
    ;

forStatement
    : FOR ID ASSIGNOP expression TO expression DO statement
    ;

readStatement
    : READ LPAREN variableList RPAREN
    ;

whileStatement
    : WHILE expression DO statement
    ;

writeStatement
    : WRITE LPAREN expressionList RPAREN
    ;

breakStatement
    : BREAK
    ;

variableList
    : variable
    | variableList COMMA variable
    ;

variable
    : ID idVarPart
    ;

idVarPart
    : /* empty */
    | LBRACKET expressionList RBRACKET
    ;

procedureCall
    : ID
    | ID LPAREN (expressionList)? RPAREN
    ;

elsePart
    : /* empty */
    | ELSE statement
    ;

expressionList
    : expression
    | expressionList COMMA expression
    ;

expression
    : simpleExpression
    | simpleExpression relop simpleExpression
    ;

simpleExpression
    : term
    | simpleExpression addop term
    ;

term
    : factor
    | term mulop factor
    ;

factor
    : num
    | ID (LPAREN (expressionList)? RPAREN)?
    | variable
    | LPAREN expression RPAREN
    | NOT factor
    | MINUS factor
    | PLUS factor
    | STRING
    | LETTER
    ;

num
    : NUM
    ;

// Operators
relop
    : EQUAL
    | NOTEQUAL
    | LT
    | LE
    | GT
    | GE
    ;

addop
    : PLUS
    | MINUS
    | OR
    ;

mulop
    : STAR
    | SLASH
    | DIV
    | MOD
    | AND
    ;

// Lexer Rules
PROGRAM : P R O G R A M ;
CONST   : C O N S T ;
VAR     : V A R ;
PROCEDURE : P R O C E D U R E ;
FUNCTION : F U N C T I O N ;
BEGIN   : B E G I N ;
END     : E N D ;
ARRAY   : A R R A Y ;
OF      : O F ;
IF      : I F ;
THEN    : T H E N ;
ELSE    : E L S E ;
FOR     : F O R ;
TO      : T O ;
DO      : D O ;
READ    : R E A D ;
WRITE   : W R I T E ;
INTEGER : I N T E G E R ;
REAL    : R E A L ;
BOOLEAN : B O O L E A N ;
CHAR    : C H A R ;
DIV     : D I V ;
MOD     : M O D ;
AND     : A N D ;
OR      : O R ;
NOT     : N O T ;
WHILE   : W H I L E ;
BREAK   : B R E A K ;
LETTER : T R U E | F A L S E;

SEMICOLON : ';' ;
COLON     : ':' ;
DOT       : '.' ;
COMMA     : ',' ;
EQUAL     : '=' ;
NOTEQUAL  : '<>' ;
LT        : '<' ;
LE        : '<=' ;
GT        : '>' ;
GE        : '>=' ;
PLUS      : '+' ;
MINUS     : '-' ;
STAR      : '*' ;
SLASH     : '/' ;
LPAREN    : '(' ;
RPAREN    : ')' ;
LBRACKET  : '[' ;
RBRACKET  : ']' ;
ASSIGNOP  : ':=' ;
DOTDOT    : '..' ;

// Define ID and NUM
ID  : [a-zA-Z_][a-zA-Z0-9_]* ;
NUM : [0-9]+ ('.' [0-9]+)? ;
STRING : '\'' (~['\r\n] | '\'\'')* '\'' ;

// Skip whitespace and handle comments
COMMENT : '{' .*? '}' -> skip ;
LINE_COMMENT : '//' .*? '\n' -> skip;
WS      : [ \t\r\n]+ -> skip ;

// Fragment rules for case insensitivity
fragment A : [aA] ;
fragment B : [bB] ;
fragment C : [cC] ;
fragment D : [dD] ;
fragment E : [eE] ;
fragment F : [fF] ;
fragment G : [gG] ;
fragment H : [hH] ;
fragment I : [iI] ;
fragment J : [jJ] ;
fragment K : [kK] ;
fragment L : [lL] ;
fragment M : [mM] ;
fragment N : [nN] ;
fragment O : [oO] ;
fragment P : [pP] ;
fragment Q : [qQ] ;
fragment R : [rR] ;
fragment S : [sS] ;
fragment T : [tT] ;
fragment U : [uU] ;
fragment V : [vV] ;
fragment W : [wW] ;
fragment X : [xX] ;
fragment Y : [yY] ;
fragment Z : [zZ] ;