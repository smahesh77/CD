#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char input[15], pos = 0;
char expr[50] = "";

void advance() { pos++; }

void print_step(const char* rule) {
    printf("E=%-25s%s\n", expr, rule);
}

void update_expr(const char* new_expr) {
    strcpy(expr, new_expr);
}

// Function declarations
void E();
void E_prime();
void T();
void T_prime();
void F();

void E() {
    update_expr("TE'");
    print_step("E->TE'");
    T();
    E_prime();
}

void E_prime() {
    char temp[50];
    if (input[pos] == '+') {
        strcpy(temp, expr);
        int i;
        for(i = 0; temp[i] != 'E'; i++);
        sprintf(expr, "%.*s+TE'%s", i, temp, temp + i + 2);
        print_step("E'->+TE'");
        advance();
        T();
        E_prime();
    } else {
        int i;
        for(i = 0; expr[i] != 'E'; i++);
        expr[i] = 'e';
        memmove(expr + i + 1, expr + i + 2, strlen(expr) - i);
        print_step("E'->e");
    }
}

void T() {
    char temp[50];
    strcpy(temp, expr);
    int i;
    for(i = 0; temp[i] != 'T'; i++);
    sprintf(expr, "%.*sFT'%s", i, temp, temp + i + 1);
    print_step("T->FT'");
    F();
    T_prime();
}

void T_prime() {
    char temp[50];
    if (input[pos] == '*') {
        strcpy(temp, expr);
        int i;
        for(i = 0; temp[i] != 'T'; i++);
        sprintf(expr, "%.*s*FT'%s", i, temp, temp + i + 2);
        print_step("T'->*FT'");
        advance();
        F();
        T_prime();
    } else {
        int i;
        for(i = 0; expr[i] != 'T'; i++);
        expr[i] = 'e';
        memmove(expr + i + 1, expr + i + 2, strlen(expr));
        print_step("T'->e");
    }
}

void F() {
    int i;
    for(i = 0; expr[i] != 'F'; i++);
    
    if (input[pos] == 'i' || input[pos] == 'I') {
        expr[i] = 'i';
        print_step("F->i");
        advance();
    } else if (input[pos] == '(') {
        char temp[50];
        strcpy(temp, expr);
        sprintf(expr, "%.*s(E)%s", i, temp, temp + i + 1);
        print_step("F->(E)");
        advance();
        E();
        if (input[pos] == ')') {
            advance();
        } else {
            printf("\nSyntax error");
            exit(1);
        }
    } else {
        printf("\nSyntax error");
        exit(1);
    }
}

int main() {
    printf("\nGrammar without left recursion");
    printf("\n\t\t E->TE' \n\t\t E'->+TE'|e \n\t\t T->FT' ");
    printf("\n\t\t T'->*FT'|e \n\t\t F->(E)|i");
    printf("\nEnter the input expression:");
    strcpy(input, "i+i*i");
    printf("Expressions\t Sequence of production rules\n");
    
    E();
    
    for(int i = 0; i < strlen(expr); i++) {
        if(expr[i] == 'e') {
            memmove(&expr[i], &expr[i + 1], strlen(expr) - i);
            i--;
        }
    }
    printf("E=%-25s\n", expr);
    
    return 0;
}