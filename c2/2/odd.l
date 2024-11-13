%{
#include <stdio.h>
#include <stdlib.h>  // For atoi()
%}

%%

[0-9]+ { 
    int num = atoi(yytext);  // Convert yytext to an integer
    if (num % 2 == 0) 
        printf("even\n");
    else 
        printf("odd\n");
}
. {
    printf("Invalid input\n");
}
%%

int main() {
    printf("Enter a number: ");
    yylex();  // Call lexical analyzer
    return 0;
}

int yywrap() {
    return 1;  // End of input
}
