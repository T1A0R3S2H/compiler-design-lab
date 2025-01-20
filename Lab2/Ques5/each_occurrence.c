#include <stdio.h>
#include <stdlib.h>

#define ASCII_SIZE 256 // Total number of ASCII characters

int main() {
    char filename[100], ch;
    int count[ASCII_SIZE] = {0}; // Array to store the count of each character
    FILE *file;

    // Prompt user for the file name
    printf("Enter the file name: ");
    scanf("%s", filename);

    // Open the file
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return 1;
    }

    // Read the file character by character
    while ((ch = fgetc(file)) != EOF) {
        count[(unsigned char)ch]++; // Increment count for the character
    }

    fclose(file);

    // Display the results
    printf("Character frequencies in the file:\n");
    for (int i = 0; i < ASCII_SIZE; i++) {
        if (count[i] > 0) {
            if (i == '\n')
                printf("'\\n': %d\n", count[i]); // Display newline explicitly
            else if (i == '\t')
                printf("'\\t': %d\n", count[i]); // Display tab explicitly
            else if (i == ' ')
                printf("' ': %d\n", count[i]);   // Display space explicitly
            else
                printf("'%c': %d\n", i, count[i]);
        }
    }

    return 0;
}

