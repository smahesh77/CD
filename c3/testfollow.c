#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 10

char production[MAX][MAX], first[MAX][MAX], follow[MAX][MAX];
int n;

void findFirst(char, int, int);
void findFollow(char);
void addToResult(char result[], char value);

int main() {
    int i, choice;
    char c, ch;
    
    printf("Enter the number of productions: ");
    scanf("%d", &n);
    
    printf("Enter the productions (e.g., E=E+T):\n");
    for (i = 0; i < n; i++) {
        scanf("%s", production[i]);
    }
    
    // Find First Sets
    for (i = 0; i < n; i++) {
        c = production[i][0];
        findFirst(c, 0, 0);
    }
    
    printf("\nFirst sets:\n");
    for (i = 0; i < n; i++) {
        printf("First(%c) = { %s }\n", production[i][0], first[i]);
    }
    
    // Find Follow Sets
    for (i = 0; i < n; i++) {
        ch = production[i][0];
        findFollow(ch);
    }
    
    printf("\nFollow sets:\n");
    for (i = 0; i < n; i++) {
        printf("Follow(%c) = { %s }\n", production[i][0], follow[i]);
    }
    
    return 0;
}

void findFirst(char c, int q1, int q2) {
    int j;
    
    if (!(isupper(c))) {
        addToResult(first[q1], c);
    } else {
        for (j = 0; j < n; j++) {
            if (production[j][0] == c) {
                if (production[j][2] == '#') {
                    addToResult(first[q1], '#');
                } else if (islower(production[j][2])) {
                    addToResult(first[q1], production[j][2]);
                } else {
                    findFirst(production[j][2], q1, q2 + 1);
                }
            }
        }
    }
}

void findFollow(char c) {
    int i, j;
    char followResult[MAX];
    memset(followResult, 0, sizeof(followResult));
    
    if (production[0][0] == c) {
        addToResult(followResult, '$'); // Start symbol gets '$'
    }
    
    for (i = 0; i < n; i++) {
        for (j = 2; j < strlen(production[i]); j++) {
            if (production[i][j] == c) {
                if (production[i][j + 1] != '\0') {
                    findFirst(production[i][j + 1], i, 0);
                    strcat(followResult, first[i]);
                }
                
                if (production[i][j + 1] == '\0' && production[i][0] != c) {
                    findFollow(production[i][0]);
                    strcat(followResult, follow[i]);
                }
            }
        }
    }
    
    strcpy(follow[i], followResult);
}

void addToResult(char result[], char value) {
    int k;
    for (k = 0; result[k] != '\0'; k++) {
        if (result[k] == value) {
            return; // Avoid duplicate entries
        }
    }
    result[k] = value;
    result[k + 1] = '\0';
}


