#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

int is_ambiguous(char* input) {
    
    if (strstr(input, "+") != NULL && strstr(input, "*") != NULL) {
        return 1;
    }
    
    return 0;
}

int main() {
    char input[MAX];

    // Take input from the user
    printf("Enter the expression: ");
    fgets(input, MAX, stdin);

    input[strcspn(input, "\n")] = '\0';

    if (is_ambiguous(input)) {
        printf("The grammar is ambiguous.\n");
    }
    else {
        printf("The grammar is not ambiguous.\n");
    }

    return 0;
}

