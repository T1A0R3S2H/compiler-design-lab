#include<stdio.h>
#include<string.h>
#define SIZE 10

int main() {
    char non_terminal;
    char beta[SIZE], alpha[SIZE];
    int num;
    char production[10][SIZE];

    printf("Enter Number of Production: ");
    scanf("%d", &num);
    printf("Enter the grammar in the format A->Aalpha or A->beta:\n");

    for (int i = 0; i < num; i++) {
        scanf("%s", production[i]);
    }
    for (int i = 0; i < num; i++) {
        printf("\nGRAMMAR : %s", production[i]);
        non_terminal = production[i][0]; 

        if (production[i][3] == non_terminal) {
            printf(" is left recursive.\n");

            int index = 3; 
            int j = 0;

            while (production[i][index] != '\0' && production[i][index] != '|') {
                alpha[j++] = production[i][index++];
            }
            alpha[j] = '\0'; 

            if (production[i][index] != '\0') {
                index++;
                j = 0;
                while (production[i][index] != '\0') {
                    beta[j++] = production[i][index++];
                }
                beta[j] = '\0';  

                printf("Grammar with left recursion:\n");
                printf("%c->%s%c'\n", non_terminal, beta, non_terminal);
                printf("%c'->%s%c'|E\n", non_terminal, alpha, non_terminal);
            } else {
                printf(" can't be reduced\n");
            }
        } else {
            printf(" is not left recursive.\n");
        }
    }
    return 0;
}
