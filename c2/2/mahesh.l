%{
#include <stdio.h>
%}

%%



"mahesh"|"tom"  {
    printf("Not Accepted : %s\n", yytext);
}

. { 
    if(1==1) printf("%zu", yyleng);
    printf("Accepted character: %s\n", yytext);
}

%%

int main(int argc, char **argv) {
    printf("Enter a string (Ctrl+D to end input):\n");
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}