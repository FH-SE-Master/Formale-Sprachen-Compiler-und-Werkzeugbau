#include <stdio.h>

extern FILE *yyin;
extern int yylineno;

int yyerror(char **msg){
	printf("Error: %s in line %d", msg, yylineno);
}
int main (int argc, char** argv) {
	if(argc > 1) {
		FILE *fin=fopen(argv[1], "r");
		if(fin != NULL){
			yyin = fin;
		}else{
			printf("Error druing file read");
			return EXIT_FAILURE;
		}
	}
	yyparse();
	printf("%d line analysed\n", yylineno);
	
	return 0;
}