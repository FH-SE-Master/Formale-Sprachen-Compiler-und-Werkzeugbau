/* Parser specification */
%{
  #include <stdio.h>
  #ifndef YYSTYPE
  #define YYSTYPE char*
  #endif

  // Extern members
  extern int yylineno;
  extern char* yylval;

  // Variable declarations
  FILE *outFile = NULL; // The output file
  char *methodArr[255]; // Array of calls per method. TODO Should be dynamic.
  int curLen    = 0;          // Current methodArr index
%}

%token VOID
%token INT
%token BOOL
%token STRING
%token COUT
%token CIN
%token ENDL
%token IDENT
%token NUMBER
%token TRUE
%token FALSE
%token CONST
%token IF
%token ELSE
%token WHILE
%token BREAK
%token RETURN
%token NEW
%token DELETE
%token OR
%token AND
%token SHIFTR
%token SHIFTL
%token NEQ
%token EQ
%token LE
%token GE
%token INC
%token DEC
%token ADD
%token SUBST
%token LT
%token GT
%token PLUS
%token MINUS
%token MULT
%token DIV
%token MOD
%token SIGNCALL;

%%
MiniCpp:
  /* EPSILON */
  | MiniCpp ConstDecl
  | MiniCpp VarDef
  | MiniCpp FuncDecl
  | MiniCpp FuncDef
  ;
ConstDecl:
    CONST Type IDENT Init ';'
    ;
Init:
    '=' TypeVal
    ;
TypeVal:
  FALSE
  | TRUE
  | NUMBER
  ;
VarDef:
  Type OptAsterix IDENT OptInit VarDefList ';'
  ;
VarDefList:
  /* EPSILON */
  | ',' OptAsterix IDENT OptInit
OptAsterix:
  /* EPSILON */
  | '*'
  ;
OptInit:
  /* EPSILON */
  | Init
FuncDecl:
  FuncHead ';'
  ;
FuncDef:
  FuncHead Block  {
                    // iterate over all current remembered methods
                    for(int i=0;i<curLen;i++){
                      // Write to dot system
                      fprintf(outputFile,"%s -> %s\n",$1,methods[i]);
                      // Free string produced by strdup
                      free(methods[i]);
                    }
                    // Reset current methodArr index
                    curLen=0;
                  }
  ;
FuncHead:
  Type OptAsterix IDENT '(' FormParList ')'
  ;
FormParList:
  /* EPSILON */
  | VOID
  | Type OptAsterix IDENT OptBrackets FormParListList
  ;
OptBrackets:
  /* EPSILON */
  | '[' ']'
  ;
FormParListList:
  /* EPSILON */
  | FormParListList ',' Type OptAsterix IDENT OptBrackets
  ;
Type:
  VOID
  | BOOL
  | INT
  ;
Block:
  '{' BlockList '}'
  ;
BlockList:
  /* EPSILON */
  | BlockList ConstDecl
  | BlockList VarDef
  | BlockList Stat
  ;
Stat:
  IncStat
  | DecStat
  | AssignStat
  | CallStat
  | IfStat
  | WhileStat
  | BreakStat
  | InputStat
  | OutputStat
  | DeleteStat
  | ReturnStat
  | Block
  | ';'
  ;
IncStat:
  IDENT INC ';'
  ;
DecStat:
  IDENT DEC ';'
  ;
AssignStat:
  IDENT AssignOptExpr '=' Expr ';'
  ;
AssignOptExpr:
  /* EPSILON */
  | '[' Expr ']'
  ;
CallStat:
  IDENT '(' OptActParList ')' ';'
  ;
OptActParList:
  /* EPSILON */
  | ActParList
  ;
ActParList:
  Expr ExprList
  ;
ExprList:
  /* EPSILON */
  | ExprList ',' Expr
  ;
IfStat:
  IF '(' Expr ')' Stat ElseStatOpt
  ;
ElseStatOpt:
  /* EPSILON */
  | ELSE Stat ;
WhileStat:
  WHILE '(' Expr ')' Stat
  ;
BreakStat:
  BREAK ';'
  ;
InputStat:
  CIN SHIFTR IDENT ';'
  ;
OutputStat:
  COUT SHIFTL OptOutputStat OutputStatList ';'
  ;
OptOutputStat:
  Expr
  | STRING
  | ENDL
  ;
OutputStatList:
  /* EPSILON */
  | OutputStatList SHIFTL OptOutputStat
  ;
DeleteStat:
    DELETE '[' ']' IDENT ';'
    ;
ReturnStat:
  RETURN OptExpr ';'
  ;
OptExpr:
  /* EPSILON */
  | Expr
  ;
Expr:
  OrExpr
  ;
OrExpr:
  AndExpr OrExprList
  ;
OrExprList:
  /* EPSILON */
  | OrExprList OR AndExpr
  ;
AndExpr:
  RelExpr AndExprList
  ;
AndExprList:
  /* EPSILON */
  | AndExprList AND RelExpr
  ;
RelExpr:
  SimpleExpr OptRelExpr
  ;
OptRelExpr:
  /* EPSILON */
  | OptRelExpr OptOperator SimpleExpr
  ;
OptOperator:
  EQ
  | NEQ
  | LT
  | LE
  | GT
  | GE
  ;
SimpleExpr:
  OptSign Term SimpleExprList
  ;
OptSign:
  PLUS
  | MINUS
  ;
SimpleExprList:
  /* EPSILON */
  | SimpleExprList OptSign Term
  ;
Term:
  NotFact TermList
  ;
TermList:
  /* EPSILON */
  | TermList OptNotFactOperator NotFact
  ;
OptNotFactOperator:
  MULT
  | DIV
  | MOD
  ;
NotFact:
  OptCallSign Fact
  ;
OptCallSign:
  /* EPSILON */
  | SIGNCALL
  ;
Fact:
  FALSE
  | TRUE
  | NUMBER
  | IDENT OptIdentFact
  | NEW Type '[' Expr ']'
  | '(' Expr ')'
  ;
OptIdentFact:
  /* EPSILON */
  | '[' Expr ']'
  | '(' OptActParList ')'
  ;
