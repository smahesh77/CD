%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);
%}

%token ID NUM FOR LE GE EQ NE OR AND
%token INT

%right "="
%left OR AND
%left '>' '<' LE GE EQ NE
%left '+' '-'
%left '*' '/'
%right UMINUS
%left '!'

%%

S       : ST                    { printf("Input accepted\n"); exit(0); }
        ;

ST      : FOR '(' DECLARATION ';' E2 ';' E ')' DEF
        ;

DECLARATION : INT ID '=' E
            | ID '=' E
            ;

DEF     : '{' BODY '}'
        | E ';'
        | ST
        |
        ;

BODY    : BODY BODY
        | E ';'
        | ST
        |
        ;

E       : ID '=' E
        | E '+' E
        | E '-' E
        | E '*' E
        | E '/' E
        | E '<' E
        | E '>' E
        | E LE E
        | E GE E
        | E EQ E
        | E NE E
        | E OR E
        | E AND E
        | E '+' '+'
        | E '-' '-'
        | ID
        | NUM
        | '(' E ')'
        ;

E2      : E '<' E
        | E '>' E
        | E LE E
        | E GE E
        | E EQ E
        | E NE E
        | E OR E
        | E AND E
        |
        ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main(void) {
    printf("Enter the expression:\n");
    return yyparse();
}