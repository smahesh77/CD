/* Lexer (lex.l) */
%{
    #include <stdio.h>
    #include "y.tab.h"
%}

%%
[a-zA-Z_][a-zA-Z_0-9]* return LETTER;
[0-9]                  return DIGIT;
.                      return yytext[0];
\n                     return 0;
%%

int yywrap() {
    return 1;
}