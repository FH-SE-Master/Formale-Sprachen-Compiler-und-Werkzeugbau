/* C comments are allowed here */
%{

	#include "Minic.tab.h"
	extern int yylval;
	extern int yylineno;

%}

%%

[ \t]+      { ; }
int         { return INT; }
main        { return MAIN; }
printf      { return PRINTF; }
scanf       { return SCANF; }
void        { return VOID; }
[a-zA-Z][a-zA-z0-9]* { return IDENT; }
[0-9]+               { yylval=atoi(yytext); return NUMBER; }
\n          { yylineno++; }
\*           { return yytext[0]; }
\+           { return yytext[0]; }

%%

int yywrap() {
	return 1;
}

