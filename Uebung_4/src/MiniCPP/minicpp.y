/* Parser specification */
%{
  #ifndef YYSTYPE
  #define YYSTYPE char*
  #endif
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>

  // Extern members
  extern int yylineno;
  extern FILE *yyin;
  extern char* yylval;

  // Variable declarations
  FILE *outFile = NULL; // The output file
  char *methodArr[255]; // Array of calls per method. TODO Should be dynamic.
  int curLen    = 0;          // Current methodArr index

  int yylex(void);
  int yyerror(char *msg);
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
%token ASSIGN
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
%token ASTERIX
%token DIV
%token MOD
%token SIGNCALL

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
    ASSIGN TypeVal
    ;
TypeVal:
  FALSE
  | TRUE
  | NUMBER
  ;
VarDef:
  Type OptAsterixList IDENT OptInit VarDefList ';'
  ;
VarDefList:
  /* EPSILON */
  | VarDefList ',' OptAsterixList IDENT OptInit
  ;
OptAsterixList:
  /* EPSILON */
  | OptAsterixList ASTERIX
  ;
OptInit:
  /* EPSILON */
  | Init
  ;
FuncDecl:
  FuncHead ';'
  ;
FuncDef:
  FuncHead Block  {
                    // iterate over all current remembered methods
                    for(int i=0;i<curLen;i++){
                      // Write to dot system
                      fprintf(outFile,"%s -> %s\n",$1,methodArr[i]);
                      // Free string produced by strdup
                      free(methodArr[i]);
                    }
                    // Reset current methodArr index
                    curLen=0;
                  }
  ;
FuncHead:
  Type OptAsterixList IDENT '(' FormParList ')' {$$ = $4;}
  ;
FormParList:
  /* EPSILON */
  | VOID
  | Type OptAsterixList IDENT OptBrackets FormParListList
  ;
OptBrackets:
  /* EPSILON */
  | '[' ']'
  ;
FormParListList:
  /* EPSILON */
  | FormParListList ',' Type OptAsterixList IDENT OptBrackets
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
  IDENT AssignOptExpr ASSIGN Expr ';'
  ;
AssignOptExpr:
  /* EPSILON */
  | '[' Expr ']'
  ;
CallStat:
  IDENT '(' OptActParList ')' ';' { methodArr[curLen]=$1; curLen++; }
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
  | ELSE Stat
  ;
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
  | OptOperator SimpleExpr
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
Sign:
  PLUS
  | MINUS
  ;
OptSign:
  /* EPSILON */
  | Sign
  ;
SimpleExprList:
  /* EPSILON */
  | SimpleExprList Sign Term
  ;
Term:
  NotFact TermList
  ;
TermList:
  /* EPSILON */
  | TermList OptNotFactOperator NotFact
  ;
OptNotFactOperator:
  ASTERIX
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

%%

int yyerror(char *msg) {
    printf("syntac error in line %i: %s\n", yylineno, msg);
    return 0;
} /*yyerror*/


int main(int argc, char *argv[]) {
    //if(argc > 1) {
        FILE *f_handle = fopen("../test.mcpp","r"); // fopen(argv[1],"r");
        if(f_handle != NULL){
            yyin = f_handle;
        } else {
            printf("ERROR: file not found");
            return EXIT_FAILURE;
        }
    //}

    //grahviz output file
    outFile = fopen("graph.gv","w");
    if(outFile == NULL){
        printf("ERROR: could not open output file graph.gv");
            return EXIT_FAILURE;
    }

    // write graphviz init line to file
    fprintf(outFile, "digraph G {");

    yydebug = 1;
    if(yyparse() == 0) {
        // write graphviz closing bracket to file
        fprintf(outFile, "}");
        fclose(outFile);

        printf("successfully parsed %i lines\n", yylineno);
        return 0;
    }

    // write graphviz closing bracket to file
    fprintf(outFile, "}");
    fclose(outFile);

    return 1;
} /*main*/
