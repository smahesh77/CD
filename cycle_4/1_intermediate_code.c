#include <stdio.h>
#include <string.h>

void gen_code_for_operator(char *inp, char operator, char *reg)
{
    int i = 0, j = 0;
    char temp[100];
    while (inp[i] != '\0')
    {
        if (inp[i] == operator)
        {
            printf("%c\t%c\t%c\t%c\n", operator, *reg, inp[i - 1], inp[i + 1]);
            temp[j - 1] = *reg;  // Correctly replace the left operand with the result register
            i += 2;              // Skip over the operator and right operand
            (*reg)--;            // Decrement register for next use
            continue;
        }
        temp[j] = inp[i];
        i++;
        j++;
    }
    temp[j] = '\0';              // Fix off-by-one error in null termination
    strcpy(inp, temp);
}

void gen_code(char *inp)
{
    // Operator precedence - /, *, +, -, =
    char reg = 'Z'; 
    gen_code_for_operator(inp, '/', &reg);
    gen_code_for_operator(inp, '*', &reg);
    gen_code_for_operator(inp, '+', &reg);
    gen_code_for_operator(inp, '-', &reg);
    gen_code_for_operator(inp, '=', &reg);
}

int main()
{
    char inp[100];
    printf("Enter expression:\n\n");
    scanf("%s", inp);
    printf("Op  \tDestn\tArg1\tArg2\n");
    gen_code(inp);
    return 0;
}
