#include <stdio.h>
#include <string.h>

#define MAX_INPUT 100  // Maximum size for the input string
#define MAX_STACK 100  // Maximum size for the stack

void check(const char *remaining_input);  // Function to perform reduction checks

// Global variables
char input[MAX_INPUT], stack[MAX_STACK];  
int input_len, stack_top = -1;  // Stack pointer initialized to -1

int main() {
    // Display the grammar to the user
    printf("GRAMMAR is:\nE -> E+E | E*E | (E) | id\n");
    
    // Read input string from the user
    printf("Enter input string: ");
    scanf("%s", input);
    input_len = strlen(input);  // Calculate the length of the input string

    // Print the table header for actions
    printf("\nStack\t\tInput\t\tAction\n");

    // Iterate through the input string
    for (int i = 0; i < input_len; i++) {
        if (input[i] == 'i' && input[i+1] == 'd') {  
            // If 'id' is found, push 'id' onto the stack
            stack[++stack_top] = 'i';
            stack[++stack_top] = 'd';
            stack[stack_top + 1] = '\0';  // Null-terminate the stack
            printf("$%s\t\t%s$\t\tSHIFT->id\n", stack, input + i + 2);
            
            // Call check() to perform reductions after the shift
            check(input + i + 2);
            i++;  // Skip the next character 'd'
        } else {
            // Push the current character onto the stack
            stack[++stack_top] = input[i];
            stack[stack_top + 1] = '\0';  // Null-terminate the stack
            printf("$%s\t\t%s$\t\tSHIFT->%c\n", stack, input + i + 1, input[i]);
            
            // Call check() to perform reductions after the shift
            check(input + i + 1);
        }
    }

    // Final check to determine if the input string was valid
    if (stack_top == 0 && stack[0] == 'E') {
        printf("\nInput string is VALID.\n");
    } else {
        printf("\nInput string is INVALID.\n");
    }

    return 0;  // End of main function
}

// Function to check and perform possible reductions
void check(const char *remaining_input) {
    int handle_size;
    char *handle;

    while (1) {
        // Check for different handles and perform reductions
        if (stack_top >= 1 && stack[stack_top - 1] == 'i' && stack[stack_top] == 'd') {
            // Handle for "id"
            handle = "id";
            handle_size = 2;
        } else if (stack_top >= 2 && stack[stack_top - 2] == 'E' && stack[stack_top - 1] == '+' && stack[stack_top] == 'E') {
            // Handle for "E+E"
            handle = "E+E";
            handle_size = 3;
        } else if (stack_top >= 2 && stack[stack_top - 2] == 'E' && stack[stack_top - 1] == '*' && stack[stack_top] == 'E') {
            // Handle for "E*E"
            handle = "E*E";
            handle_size = 3;
        } else if (stack_top >= 2 && stack[stack_top - 2] == '(' && stack[stack_top - 1] == 'E' && stack[stack_top] == ')') {
            // Handle for "(E)"
            handle = "(E)";
            handle_size = 3;
        } else {
            return;  // No reduction possible, return to main loop
        }

        // Perform reduction: replace the handle with 'E'
        stack_top -= handle_size - 1;  // Pop handle_size - 1 elements from the stack
        stack[stack_top] = 'E';  // Replace top of the stack with 'E'
        stack[stack_top + 1] = '\0';  // Null-terminate the stack
        
        // Print the reduction step
        printf("$%s\t\t%s$\t\tREDUCE->%s\n", stack, remaining_input, handle);
    }
}
