%option noyywrap

%{
#include "y.tab.h"
%}

DIGIT [0-9]
NUMBER {DIGIT}+
PLUS "+"
MINUS "-"
MULT "*"
DIV "/"
LPAREN "("
RPAREN ")"
WS [ \t\r\n]+

%%
{NUMBER}  { yylval = atoi(yytext); return NUMBER; }
{PLUS}    { return PLUS; }
{MINUS}   { return MINUS; }
{MULT}    { return MULT; }
{DIV}     { return DIV; }
{LPAREN}  { return LPAREN; }
{RPAREN}  { return RPAREN; }
{WS}      { /* ignore whitespace */ }
\n        { /* ignore newline */ }
.         { printf("Invalid character: %c\n", *yytext); }
%%

