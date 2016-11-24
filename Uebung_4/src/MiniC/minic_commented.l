/* C comments are allowed here */
/* yytext is c character chain which holds current token text */
/* First part enclosed by %{%} */
%{
	#include "Minic.tab.h"
	extern int yylval;
	extern int yylineno;
%}

/* second part */
%%
/* exclude all whitespace and tabs and do nothing on such sequences */
[ \t]+ { ; }

/* handle keyword */
int         { return INT; }
main        { return MAIN; }
printf      { return PRINTF; }
scanf void  { return SCANF; }

/* Rule for identifiers (hint: ']* {' must be on first line) */
[a-zA-Z][a-zA-z0-9]* { return IDENT; }
[0-9]+               { yylval=atoi(yytext); return NUMBER; }

/* Handle line end */
\n          { yylineno++; }

/* Current toke string holds character which is returned as terminal symbol */
*           { return yytext[0]; }
+           { return yytext[0]; }
%%

/* Skip further source file scanning, means stop after current file */
int yywrap() {
	return 1;
}

