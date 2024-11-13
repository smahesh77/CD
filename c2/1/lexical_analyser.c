#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_KEYWORDS 32
#define MAX_KEYWORD_LENGTH 10
#define MAX_BUFFER_SIZE 31

const char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if",
    "int", "long", "register", "return", "short", "signed", "sizeof", "static",
    "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
};

int isKeyword(const char *buffer) {
    for (int i = 0; i < MAX_KEYWORDS; i++) {
        if (strcmp(keywords[i], buffer) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    char c, buffer[MAX_BUFFER_SIZE];
    const char *operators = "+-*/%=";
    FILE *fp = fopen("program.txt", "r");
    int bufferIndex = 0;

    if (fp == NULL) {
        printf("Error while opening the file\n");
        return 1;
    }

    while ((c = fgetc(fp)) != EOF) {
        if (strchr(operators, c)) {
            printf("%c is operator\n", c);
        }

        if (isalnum(c)) {
            buffer[bufferIndex++] = c;
        } else if ((c == ' ' || c == '\t' || c == '\n') && bufferIndex > 0) {
            buffer[bufferIndex] = '\0';
            printf("%s is %s\n", buffer, isKeyword(buffer) ? "keyword" : "identifier");
            bufferIndex = 0;
        }
    }

    fclose(fp);
    return 0;
}