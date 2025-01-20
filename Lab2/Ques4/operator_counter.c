#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int is_operator(char ch) {
    char operators[] = "+-*/=<>!&|%^";
    for (int i = 0; i < strlen(operators); i++) {
        if (ch == operators[i]) {
            return 1;
        }
    }
    return 0;
}

int main() {
    char filename[100], ch, prev = '\0';
    FILE *file;
    int count = 0;

    // Prompt user for the file name
    printf("Enter the file name: ");
    scanf("%s", filename);

    // Open the file
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return 1;
    }

    // Read file character by character
    while ((ch = fgetc(file)) != EOF) {
        if (is_operator(ch)) {
            count++;
            // Handle compound operators (e.g., +=, ==, <=)
            if ((prev == '+' && ch == '=') || (prev == '-' && ch == '=') ||
                (prev == '*' && ch == '=') || (prev == '/' && ch == '=') ||
                (prev == '=' && ch == '=') || (prev == '!' && ch == '=') ||
                (prev == '<' && ch == '=') || (prev == '>' && ch == '=') ||
                (prev == '&' && ch == '&') || (prev == '|' && ch == '|')) {
                count--;
            }
        }
        prev = ch;
    }

    fclose(file);

    // Display the result
    printf("Total number of operators in the file: %d\n", count);

    return 0;
}

