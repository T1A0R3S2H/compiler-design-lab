#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

// Function to check if the input is a valid identifier
bool isIdentifier(const char *str) {
    if (!isalpha(str[0]) && str[0] != '_') {
        return false;
    }

    for (int i = 1; str[i] != '\0'; i++) {
        if (!isalnum(str[i]) && str[i] != '_') {
            return false;
        }
    }

    return true;
}

// Function to check if the input is a constant (integer or floating-point)
bool isConstant(const char *str) {
    int i = 0;
    bool hasDecimal = false;

    // Check for optional sign
    if (str[i] == '+' || str[i] == '-') {
        i++;
    }

    if (!isdigit(str[i])) {
        return false;
    }

    while (str[i] != '\0') {
        if (str[i] == '.') {
            if (hasDecimal) {
                return false; // More than one decimal point
            }
            hasDecimal = true;
        } else if (!isdigit(str[i])) {
            return false;
        }
        i++;
    }

    return true;
}

// Function to check if the input is an operator
bool isOperator(const char *str) {
    const char *operators[] = {
        "+", "-", "*", "/", "%", "=", "==", "!=", "<", "<=", ">", ">=", "&&", "||", "!", "++", "--", "&", "|", "^", "~", "<<", ">>"
    };

    int numOperators = sizeof(operators) / sizeof(operators[0]);

    for (int i = 0; i < numOperators; i++) {
        if (strcmp(str, operators[i]) == 0) {
            return true;
        }
    }

    return false;
}

int main() {
    char input[100];

    printf("Enter a string to check: ");
    scanf("%s", input);

    if (isIdentifier(input)) {
        printf("\"%s\" is a valid identifier.\n", input);
    } else if (isConstant(input)) {
        printf("\"%s\" is a valid constant.\n", input);
    } else if (isOperator(input)) {
        printf("\"%s\" is a valid operator.\n", input);
    } else {
        printf("\"%s\" is not recognized as an identifier, constant, or operator.\n", input);
    }

    return 0;
}
