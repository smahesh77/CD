%{
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void AddQuadruple(char op, char arg1, char arg2, char result);

int pop();
void push(int data);

int Index = 0, tIndex = 0, StNo, Ind, tInd;
extern int LineNo;

struct quad {
    char op;
    char arg1;
    char arg2;
    char result;
} QUAD;

struct stack {
    int items[100];
    int top;
} stk;

%}

%union {
    char var;
}

%token <var> NUM VAR RELOP
%token MAIN IF ELSE WHILE TYPE

%type <var> EXPR ASSIGNMENT CONDITION IFST ELSEST WHILELOOP

%left '-' '+'
%left '*' '/'

%%

PROGRAM : MAIN BLOCK
        ;

BLOCK : '{' CODE '}'
      ;

CODE : BLOCK
     | STATEMENT CODE
     | STATEMENT
     ;

STATEMENT : DECL ';'
          | ASSIGNMENT ';'
          | CONDITION
          | WHILEST
          ;

DECL : TYPE VARLIST
     ;

VARLIST : VAR ',' VARLIST
        | VAR
        ;

ASSIGNMENT : VAR '=' EXPR {
                strcpy(QUAD[Index].op, "=");
                strcpy(QUAD[Index].arg1, $3);
                strcpy(QUAD[Index].arg2, "");
                strcpy(QUAD[Index].result, $1);
                strcpy($$, QUAD[Index++].result);
            }
          ;

CONDITION : IFST
          | ELSEST
          ;

IFST : IF '(' CONDITION ')' BLOCK
     ;

ELSEST : ELSE BLOCK
        ;

WHILEST : WHILE '(' CONDITION ')' BLOCK
        ;

EXPR : EXPR '+' EXPR { /* Handle addition */ }
     | EXPR '-' EXPR { /* Handle subtraction */ }
     | TERM ((MUL | DIV) TERM)* { /* Handle multiplication and division */ }
     ;

TERM : FACTOR ((MUL | DIV) FACTOR)* { /* Handle multiplication and division */ }
     ;

FACTOR : NUM | VAR
        ;

%%

int main() {
    FILE *fp = fopen("input.txt", "r");
    if (!fp) {
        printf("\n File not found");
        exit(0);
    }
    yyin = fp;
    yyparse();
    printf("\n\n\t\t ----------------------------\n\t\t Pos Operator \tArg1 \tArg2 \tResult\n\t\t--------------------");
    for (int i = 0; i < Index; i++) {
        printf("\n\t\t %d\t %s\t %s\t %s\t%s", i, QUAD[i].op, QUAD[i].arg1, QUAD[i].arg2, QUAD[i].result);
    }
    printf("\n\t\t -----------------------");
    printf("\n\n");
    return 0;
}

void push(int data) {
    stk.top++;
    if (stk.top == 100) {
        printf("\n Stack overflow\n");
        exit(0);
    }
    stk.items[stk.top] = data;
}

int pop() {
    int data;
    if (stk.top == -1) {
        printf("\n Stack underflow\n");
        exit(0);
    }
    data = stk.items[stk.top];
    stk.top--;
    return data;
}

