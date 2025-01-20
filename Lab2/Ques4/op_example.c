#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_single_operator(char ch) {
    // Single-character operators
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
        // Skip multi-line comments
        if (prev == '/' && ch == '*') {
            while ((ch = fgetc(file)) != EOF) {
                if (prev == '*' && ch == '/') break;
                prev = ch;
            }
            prev = '\0';
            continue;
        }

        // Skip single-line comments
        if (prev == '/' && ch == '/') {
            while ((ch = fgetc(file)) != EOF && ch != '\n');
            prev = '\0';
            continue;
        }

        // Check for compound operators
        if ((prev == '+' && ch == '+') || (prev == '-' && ch == '-') || 
            (prev == '=' && ch == '=') || (prev == '!' && ch == '=') ||
            (prev == '<' && ch == '=') || (prev == '>' && ch == '=') ||
            (prev == '&' && ch == '&') || (prev == '|' && ch == '|')) {
            count++;
            printf("Compound operator found: %c%c\n", prev, ch); // Debug print
            prev = '\0'; // Clear prev to avoid double-counting
        } else if (is_single_operator(ch)) {
            if (prev != '\0' && is_single_operator(prev)) {
                // Avoid counting single operator twice if part of a compound
                prev = ch;
                continue;
            }
            count++;
            printf("Single operator found: %c\n", ch); // Debug print
            prev = ch; // Save current character for compound check
        } else {
            prev = '\0'; // Reset prev if no operator is detected
        }
    }

    fclose(file);

    // Display the result
    printf("Total number of operators in the file: %d\n", count);

    return 0;
}
