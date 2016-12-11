/* The grammar specification of the MiniC language */
%{
	#include <stdio.h>
	#include <stdlib.h>

	extern int yylineno;
	extern int yylval;
	extern FILE *yyin;

	int yylex(void);
  int yyerror(char *msg);
%}

%token INT
%token MAIN
%token PRINTF
%token SCANF
%token VOID
%token IDENT
%token NUMBER

%%
MC:
	VOID MAIN '(' ')' '{' OptVarDecl StateSeq '}'
	;
OptVarDecl:
  /* EPSILON */
	| VarDecl
	;
VarDecl:
	INT IdentList ';'
	;
IdentList:
	IDENT
	| IdentList ',' IDENT
	;
StateSeq:
	Stat StatList
	;
StatList:
	/* EPSILON */
	| StatList Stat
	;
Stat:
	OptStat ';'
	;
OptStat:
	/* EPSILON */
	| IDENT '=' Expr
	| SCANF '(' IDENT ')'
	| PRINTF'(' Expr ')'
	;
Expr:
	Term TermList
  ;
TermList:
	/* EPSILON */
	| TermList Sign Term
	;
Sign:
	'+'
	| '-'
	;
Term:
	Fact FactList
  ;
FactList:
	/* EPSILON */
	| FactList Operator Fact
	;
Operator:
	'*'
	| '/'
	;
Fact:
	IDENT
	| NUMBER
  | '(' Expr ')'
  ;
%%

int yyerror(char *msg){
    printf("syntac error in line %i: %s\n", yylineno, msg);
    return 0;
}

int main (int argc, char** argv) {
	//if(argc > 1) {
		FILE *fin=fopen("../test.c", "r");// fopen(argv[1], "r");
		if(fin != NULL){
			yyin = fin;
		} else {
			printf("Error druing file read");
			exit(EXIT_FAILURE);
		}
	//}
  yydebug = 1;
	if(yyparse() == 0){
      printf("Successfully parsed file");
    }else{
      printf("Parsing of file failed");
    }
	printf("\n\n%d lines analysed\n", yylineno);

	return 0;
}
