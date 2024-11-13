%{
#include "y.tab.h"
#include <stdio.h>
%}
%option noyywrap

alpha [A-Za-z]
digit [0-9]

%%

[ \t\n]         ; /* Ignore whitespace */
for             return FOR;
int             return INT;
if              return IF;
"else if"       { return ELSEIF; }
else            return ELSE;
{digit}+        { yylval = atoi(yytext); return NUM; }
{alpha}({alpha}|{digit})* { return ID; }
"<="            return LE;
">="            return GE;
"=="            return EQ;
"!="            return NE;
"||"            return OR;
"&&"            return AND;
.               return yytext[0];

%%

