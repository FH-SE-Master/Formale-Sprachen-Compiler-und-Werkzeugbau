/* MiniCpp lexical scanner specification */
%{
  #include "minicpp.tab.h"
%}

%%

[ \t]+  { ; }  /* ignore whitespace and tabs */
"/*"    {
          /* skip multiline comments */
          int prevChar = 0;
          int ch = input();
          for(;;){
            if(ch == EOF) { /* common unclosed and end of file found */
              break;
            } /* if */
            if(ch == '\n') { /* Multiline comment, new line found */
              yylineno++;
            } else if ((prevChar == '*') && (ch == '/')) { /* correct comment ending */
              break;
            } /* if */
            prevChar = ch;
            ch = input();
          } /* for */
        }
"//"    {
          /* skip single line comments */
          int ch = input();
          for(;;){
            if(ch == EOF) { /* comment contains end of file */
              break;
            } /* if */
            if(ch == '\n') { /* single line comment new line found */
              yylineno;
              break;
            } /* if */
            ch = input();
          } /* for */
        }


void   { return VOID;   }
int    { return INT;    }
bool   { return BOOL;   }
string { return STRING; }
cout   { return COUT;   }
cin    { return CIN;    }
endl   { return ENDL;   }
ident  { return IDENT;  }
number { return NUMBER; }
true   { return TRUE;   }
false  { return FALSE;  }
const  { return CONST;  }
if     { return IF;     }
else   { return ELSE;   }
while  { return WHILE;  }
break  { return BREAK;  }
return { return RETURN; }
new    { return NEW;    }
delete { return DELETE; }

"||"   { return OR;     }
"&&"   { return AND;    }
">>"   { return SHIFTR; }
"<<"   { return SHIFTL; }
"="    { return ASSIGN; }
"!="   { return NEQ;    }
"=="   { return EQ;     }
"<="   { return LE;     }
">="   { return GE;     }
"<"    { return LT;     }
">"    { return GT;     }
"++"   { return INC;    }
"--"   { return DEC;    }
"+"    { return PLUS;   }
"-"    { return MINUS;  }
"*"    { return ASTERIX;   }
"/"    { return DIV;    }
"%"    { return MOD;    }
"!"    { return SIGNCALL;}

[a-zA-Z][a-zA-Z0-9]*    { yylval = strdup(yytext); return IDENT; }
\"[^\"]*\"              { ; return STRING;  }
[0-9]+                  { ; return NUMBER;  }
\n                      { yylineno++;       }
.                       { return yytext[0]; } /* all other chars as tokens for parsers */

%%

int yywrap() {
  return 1;   /* on end no further files to scan */
} /*int  yywrap */
