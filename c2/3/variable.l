/* Lexer (lex.l) */
%{
    #include <stdio.h>
    #include "y.tab.h"
%}

%option noyywrap 

%%
[a-zA-Z]+              return LETTER;
[0-9]                  return DIGIT;
\n                     return 0;
%%

