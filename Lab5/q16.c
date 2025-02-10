#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RULES 10
#define MAX_LENGTH 20

// Structure to store a production rule
typedef struct {
    char non_terminal;
    char production[MAX_LENGTH];
} Production;

// Function to check if the grammar is non-deterministic
int is_non_deterministic(Production rules[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (rules[i].non_terminal == rules[j].non_terminal) {
                // Check if the first character of both productions is the same
                if (rules[i].production[0] == rules[j].production[0]) {
                    return 1; // Non-deterministic
                }
            }
        }
    }
    return 0; // Deterministic
}

int main() {
    int n;
    printf("Enter the number of production rules: ");
    scanf("%d", &n);

    Production rules[MAX_RULES];

    printf("Enter the production rules (in the format: A->X): \n");
    for (int i = 0; i < n; i++) {
        char buffer[MAX_LENGTH];
        scanf("%s", buffer);

        // Separate the non-terminal and production
        rules[i].non_terminal = buffer[0];
        strcpy(rules[i].production, buffer + 3); // Skip "A->"
    }

    if (is_non_deterministic(rules, n)) {
        printf("The grammar is non-deterministic.\n");
    } else {
        printf("The grammar is deterministic.\n");
    }

    return 0;
}




// iiitkota@iiitkota-HP-Elite-Tower-600-G9-Desktop-PC:~/2022kucp1032$ gcc q16.c
// iiitkota@iiitkota-HP-Elite-Tower-600-G9-Desktop-PC:~/2022kucp1032$ ./a.out
// Enter the number of production rules: 3
// Enter the production rules (in the format: A->X): 
// S->aS
// S->bS
// S->aA
// The grammar is non-deterministic.
// iiitkota@iiitkota-HP-Elite-Tower-600-G9-Desktop-PC:~/2022kucp1032$ ./a.out
// Enter the number of production rules: 4
// Enter the production rules (in the format: A->X): 
// S->aS
// S->bS
// S->aA
// S->ε
// The grammar is non-deterministic.
// iiitkota@iiitkota-HP-Elite-Tower-600-G9-Desktop-PC:~/2022kucp1032$ ./a.out
// Enter the number of production rules: 3
// Enter the production rules (in the format: A->X): 
// S->aA
// A->bB
// B->c
// The grammar is deterministic.
