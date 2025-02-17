#include <stdio.h>
#include <string.h>

int main() {
    char gram[100], part1[50], part2[50], modifiedGram[50], newGram[50];
    int i, j = 0, k = 0, pos;

    printf("Enter Production : A->");
    fgets(gram, sizeof(gram), stdin);

    // Separate the production rules
    for (i = 0; gram[i] != '|' && gram[i] != '\0'; i++, j++) {
        part1[j] = gram[i];
    }
    part1[j] = '\0';

    if (gram[i] == '|') {
        i++; // Skip the '|' character
        j = 0;
        while (gram[i] != '\0' && gram[i] != '\n') {
            part2[j++] = gram[i++];
        }
        part2[j] = '\0';
    } else {
        strcpy(part2, ""); // If no alternative production, part2 is empty
    }

    // Find the common prefix
    k = 0;
    for (i = 0; i < strlen(part1) && i < strlen(part2); i++) {
        if (part1[i] == part2[i]) {
            modifiedGram[k++] = part1[i];
            pos = i + 1;
        } else {
            break;
        }
    }
    modifiedGram[k] = '\0';

    // Create the new production rule
    if (modifiedGram[0] != '\0') {
        sprintf(newGram, "X->");
        j = 3; // Start index for newGram

        for (i = pos; part1[i] != '\0'; i++) {
            newGram[j++] = part1[i];
        }
        if (part2[0] != '\0') {
            newGram[j++] = '|';
            for (i = pos; part2[i] != '\0'; i++) {
                newGram[j++] = part2[i];
            }
        }
        newGram[j] = '\0';

        modifiedGram[k++] = 'X';
        modifiedGram[k] = '\0';

        printf("\nGrammar Without Left Factoring:\n");
        printf(" A->%s\n", modifiedGram);
        printf(" %s\n", newGram);
    } else {
        printf("No common prefix found. Left factoring not applicable.\n");
    }

    return 0;
}
