#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// List of C keywords
const char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default",
    "do", "double", "else", "enum", "extern", "float", "for", "goto",
    "if", "int", "long", "register", "return", "short", "signed",
    "sizeof", "static", "struct", "switch", "typedef", "union",
    "unsigned", "void", "volatile", "while"
};

#define NUM_KEYWORDS (sizeof(keywords) / sizeof(keywords[0]))

// Function to check if a word is a keyword
int isKeyword(const char *word) {
    for (int i = 0; i < NUM_KEYWORDS; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Function to count keywords in a file
int countKeywords(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    int keywordCount = 0;
    char word[100];
    int inWord = 0;
    int index = 0;
    int ch;

    while ((ch = fgetc(file)) != EOF) {
        if (isalpha(ch) || ch == '_') {
            word[index++] = ch;
            inWord = 1;
        } else {
            if (inWord) {
                word[index] = '\0';
                if (isKeyword(word)) {
                    keywordCount++;
                }
                index = 0;
                inWord = 0;
            }
        }
    }

    fclose(file);
    return keywordCount;
}

int main() {
    const char *filename = "example.c"; // Replace with your file name
    int keywordCount = countKeywords(filename);
    if (keywordCount != -1) {
        printf("Total number of keywords: %d\n", keywordCount);
    }
    return 0;
}
