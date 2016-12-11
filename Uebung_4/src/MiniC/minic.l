/* Lexical specification of the MiniC language */
%{

	#include "minic.tab.h"

	extern int yylval;
	extern int yylineno;

%}

%%

void                    { return VOID;  }
main                    { return MAIN;  }
int                     { return INT;   }
scanf                   { return SCANF; }
printf                  { return PRINTF;}

[ \t\n\r]+              { ; }                   /*ignore white space: blanks and tabs       */
"/""/"[^\n\r]*          { ; }                   /* skip line comments */
[0-9]+                  { return NUMBER;}
[a-zA-Z][_a-zA-Z0-9]*   { return IDENT; }
.                       { return yytext[0]; }   /*return all other chars as tokens to parser: '+', ...      */

%%

int yywrap() {
	return 1;
}
