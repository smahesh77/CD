%{
#include <stdio.h>
%}

%%


"mahesh"  { 
    // If "mahesh" is found, we won't print anything or accept this string
    printf("Not Accepted : %s\n",yytext);
}


.|\n { 
    // This rule will match any single character or newline
    // So, we print this character to indicate acceptance
    printf("Accepted character: %s\n", yytext);
}
%% 

int main(int argc, char **argv) {
	printf("Enter a string (Ctrl+D to end input):\n");
    yylex(); // Start the lexer
    return 0;
}

int yywrap() {
    return 1;
}

