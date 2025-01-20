#include <stdio.h>
#include <string.h>
#include <ctype.h>

const char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", 
    "enum", "extern", "float", "for", "goto", "if", "inline", "int", "long", "register", "restrict", 
    "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", 
    "void", "volatile", "while"
};

int isKeyword(const char *str) {
    int total_keywords = sizeof(keywords) / sizeof(keywords[0]);
    for (int i = 0; i < total_keywords; i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return 1; // Return 1 if the string is a keyword
        }
    }
    return 0; // Return 0 if the string is not a keyword
}

// Function to trim leading/trailing whitespace
void trimWhitespace(char *str) {
    int start = 0;
    int end = strlen(str) - 1;

    // Trim leading spaces
    while (isspace((unsigned char)str[start])) {
        start++;
    }

    // Trim trailing spaces
    while (end >= start && isspace((unsigned char)str[end])) {
        end--;
    }

    // Move the trimmed string to the beginning of the array
    for (int i = start; i <= end; i++) {
        str[i - start] = str[i];
    }
    str[end - start + 1] = '\0'; // Null-terminate the string
}

int main() {
    char str[100];

    printf("Enter a string: ");
    // Use fgets to read the input line (handles spaces)
    fgets(str, sizeof(str), stdin);

    // Trim newline character from the end of the input (if present)
    str[strcspn(str, "\n")] = '\0';

    // Trim any extra spaces
    trimWhitespace(str);

    if (isKeyword(str)) {
        printf("\"%s\" is a C keyword.\n", str);
    } else {
        printf("\"%s\" is not a C keyword.\n", str);
    }

    return 0;
}

