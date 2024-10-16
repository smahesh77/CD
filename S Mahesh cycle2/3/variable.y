/* Parser (yacc.y) */
%{
    #include <stdio.h>
    #include <stdlib.h>
    
    int valid = 1;
    int yylex(void);
    void yyerror(const char *s);
%}

%token DIGIT LETTER

%%
start : LETTER s
s     : LETTER s
      | DIGIT s
      |
      ;
%%

void yyerror(const char *s) {
    printf("\nIt's not an identifier!\n");
    valid = 0;
}

int main() {
    printf("\nEnter a name to be tested for identifier: ");
    yyparse();
    if(valid) {
        printf("\nIt is an identifier!\n");
    }
    return 0;
}