/**/
%{
	#include <stdio.h>
	#include <stdlib.h>
	extern int yylineno;
	extern int yylval;
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
	VOID MAIN '(' ')' Block
	;

Block: 
	'{' OptVarDecl StateSeq '}'
	;

OptVarDecl: 
    /* Epsilon */
	| INT IdentList ';'
	;
IdentList:
	IDENT
	| IdentList ',' IDENT  
	;
StateSeq: 
	Stat OptStatSeq
	;
OptStatSeq:
	/* Epsilon */
	| Stat OptStatSeq
Stat:
	OptStat ";"
OptStat:
	/* Epsilon */
	| IDENT "=" Expr 
	| "scanf" "(" IDENT ")"
	| "printf" "(" Expr ")"
Expr: Term         { $$ = $1; /*default*/ }
  | Expr '+' Term  { $$ = $1 + $3;        }
  | Expr '-' Term  { $$ = $1 - $3;        }
  ;

Term: Fact         { $$ = $1; /*default*/ }
  | Term '*' Fact  { $$ = $1 * $3;        }
  | Term '/' Fact  { $$ = $1 / $3;        }
  ;
  
Fact: NUMBER       { $$ = $1; /*default*/ }
  | '(' Expr ')'   { $$ = $2;             }
  ;
%%

extern FILE *yyin;
extern int yylineno;

int yyerror(char **msg){
	printf("Error: %s in line %d", msg, yylineno);
	return 0;
}

int main (int argc, char** argv) {
	if(argc > 1) {
		FILE *fin=fopen(argv[1], "r");
		if(fin != NULL){
			yyin = fin;
		}else{
			printf("Error druing file read");
			exit(EXIT_FAILURE);
		}
	}
	yyparse();
	printf("%d line analysed\n", yylineno);
	
	return 0;
}
	