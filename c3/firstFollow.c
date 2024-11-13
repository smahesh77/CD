#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 20
#define MAX_PROD 10

char productions[MAX_PROD][MAX];
char first[MAX_PROD][MAX], follow[MAX_PROD][MAX];
int n;

int isNonTerminal(char symbol) {
    return isupper(symbol);
}

void addToSet(char result[], char symbol) {
    if (!strchr(result, symbol)) {
        strncat(result, &symbol, 1);
    }
}

void findFirst(char result[], char symbol) {
    if (!isNonTerminal(symbol)) {
        addToSet(result, symbol);
        return;
    }

    for (int i = 0; i < n; i++) {
        if (productions[i][0] == symbol) {
            int j = 2;
            while (productions[i][j] != '\0') {
                if (productions[i][j] == '|') {
                    j++;
                    continue;
                }

                char next = productions[i][j];
                char tempFirst[MAX] = "";
                findFirst(tempFirst, next);

                for (int k = 0; tempFirst[k] != '\0'; k++) {
                    if (tempFirst[k] != 'e') {
                        addToSet(result, tempFirst[k]);
                    }
                }

                if (!strchr(tempFirst, 'e')) break;
                j++;
            }

            if (productions[i][j] == '\0') {
                addToSet(result, 'e');
            }
        }
    }
}

void findFollow(char result[], char symbol) {
    if (symbol == productions[0][0]) {
        addToSet(result, '$');
    }

    for (int i = 0; i < n; i++) {
        for (int j = 2; productions[i][j] != '\0'; j++) {
            if (productions[i][j] == symbol) {
                if (productions[i][j + 1] != '\0') {
                    char tempFirst[MAX] = "";
                    findFirst(tempFirst, productions[i][j + 1]);

                    for (int k = 0; tempFirst[k] != '\0'; k++) {
                        if (tempFirst[k] != 'e') {
                            addToSet(result, tempFirst[k]);
                        }
                    }

                    if (strchr(tempFirst, 'e')) {
                        findFollow(result, productions[i][0]);
                    }
                } else {
                    if (productions[i][0] != symbol) {
                        findFollow(result, productions[i][0]);
                    }
                }
            }
        }
    }
}

int alreadyPrinted(char printed[], char symbol, int count) {
    for (int i = 0; i < count; i++) {
        if (printed[i] == symbol) {
            return 1;
        }
    }
    return 0;
}

int main() {
    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter the productions (e.g., E=TM|e):\n");
    for (int i = 0; i < n; i++) {
        scanf("%s", productions[i]);
    }

    for (int i = 0; i < n; i++) {
        findFirst(first[productions[i][0] - 'A'], productions[i][0]);
        findFollow(follow[productions[i][0] - 'A'], productions[i][0]);
    }

    char printedFirst[MAX_PROD] = {0};
    char printedFollow[MAX_PROD] = {0};
    int firstCount = 0, followCount = 0;

    printf("\nFirst Sets:\n");
    for (int i = 0; i < n; i++) {
        if (!alreadyPrinted(printedFirst, productions[i][0], firstCount)) {
            printf("First(%c) = { %s }\n", productions[i][0], first[productions[i][0] - 'A']);
            printedFirst[firstCount++] = productions[i][0];
        }
    }

    printf("\nFollow Sets:\n");
    for (int i = 0; i < n; i++) {
        if (!alreadyPrinted(printedFollow, productions[i][0], followCount)) {
            printf("Follow(%c) = { %s }\n", productions[i][0], follow[productions[i][0] - 'A']);
            printedFollow[followCount++] = productions[i][0];
        }
    }

    return 0;
}

