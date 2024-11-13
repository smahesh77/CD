%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);
%}

%token ID NUM FOR IF ELSEIF ELSE LE GE EQ NE OR AND INC DEC
%token INT

%right '='
%left OR AND
%left '>' '<' LE GE EQ NE
%left '+' '-'
%left '*' '/'
%right UMINUS '!' /* Unary Minus and Logical NOT */
%left INC DEC     /* Postfix Increment/Decrement */
%nonassoc IFX ELSE /* To handle dangling else */

%%
S       : ST                    { printf("Input accepted\n"); exit(0); }

ST      : IF '(' E2 ')' DEF
        |IF '(' E2 ')' DEF ELSE_ST 
        ;

ELSE_ST : ELSE_IF
        | ELSE DEF
        ;

DEF     : '{' BODY '}'
        | E ';'
        | /* empty */
        ;

ELSE_IF : ELSEIF '(' E2 ')' DEF ELSE_ST
        | ELSEIF '(' E2 ')' DEF
        ;

E2      : E '<' E
        | E '>' E
        | E LE E
        | E GE E
        | E EQ E
        | E NE E
        | E OR E
        | E AND E
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
        | E INC              /* Postfix Increment */
        | E DEC              /* Postfix Decrement */
        | '-' E %prec UMINUS /* Unary Minus */
        | '!' E              /* Logical NOT */
        | ID
        | NUM
        | '(' E ')'
        ;

BODY    : BODY E ';'
        | BODY ST
        | /* empty */         /* Allow BODY to terminate recursion */
        ;
%%
void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main(void) {
    printf("Enter the expression:\n");
    return yyparse();
}
