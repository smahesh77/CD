%{
#include <stdio.h>
#include <stdlib.h>
int yylex(void);
extern FILE *yyin;
void yyerror(const char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
}
int result; // Variable to store the result
%}
%token NUMBER PLUS MINUS MULT DIV LPAREN RPAREN
%left PLUS MINUS
%left MULT DIV
%%
expression:
    term { result = $1; }
    | expression PLUS term { result = $1 + $3; }
    | expression MINUS term { result = $1 - $3; }
    ;
term:
    factor { $$ = $1; }
    | term MULT factor { $$ = $1 * $3; }
    | term DIV factor { $$ = $1 / $3; }
    ;
factor:
    NUMBER { $$ = $1; }
    | LPAREN expression RPAREN { $$ = result; } // Use result here
    ;
%%
int main() {
    char input[256];

    while (1) {
        printf("Enter an expression (or 'q' to quit): ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        if (input[0] == 'q' || input[0] == 'Q') {
            break;
        }

        yyin = fopen("temp", "w");
        if (!yyin) {
            fprintf(stderr, "Could not open temporary file\n");
            return 1;
        }

        fprintf(yyin, "%s", input);
        fclose(yyin);

        yyin = fopen("temp", "r");
        if (!yyin) {
            fprintf(stderr, "Could not open temporary file\n");
            return 1;
        }

        yyparse();
        printf("Result: %d\n", result);
    }

    return 0;
}

