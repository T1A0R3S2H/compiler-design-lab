#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int evaluate(char* expression, int start, int end) {
    // Base case: if there's only one number
    if (start == end) {
        return expression[start] - '0';
    }

    int result = 0;
    for (int i = start + 1; i < end; i++) {
        if (expression[i] == '+' || expression[i] == '-') {
            int left = evaluate(expression, start, i - 1);  // Left operand
            int right = evaluate(expression, i + 1, end);   // Right operand

            if (expression[i] == '+') {
                result = left + right;
            } else if (expression[i] == '-') {
                result = left - right;
            }
        }
    }

    return result;
}

int parse_expression(char* expression) {
    int n = strlen(expression);
    return evaluate(expression, 0, n - 1);
}

int main() {
    char expression[100];
    
    printf("Enter the expression: ");
    scanf("%s", expression);

    int result = parse_expression(expression);
    
    printf("Result: %d\n", result);
    
    return 0;
}


// Enter the expression: 3+2-5

