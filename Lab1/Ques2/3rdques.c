// 3rdques.c
// write a c program to scan and count the number of characters, words, and lines in a file.
#include <stdio.h>
#include <ctype.h>
int main() {
    FILE *file;
    char filename[100];
    char ch;
    int lines=0, words=0, characters=0;
    int in_word = 0;
    printf("Enter the filename: ");
    scanf("%s", filename);
    file=fopen(filename, "r");
    if (file==NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    while ((ch=fgetc(file)) != EOF) {
        characters++;
        if (ch=='\n') {
            lines++;
        }
        if (isspace(ch) || ch=='\n') {
            if (in_word) {
                words++;
                in_word=0;
            }
        } 
        else {
            in_word=1;
        }
    }
    if (in_word) {
        words++;
    }
    fclose(file);
    printf("Lines: %d\n", lines);
    printf("Words: %d\n", words);
    printf("Characters: %d\n", characters);
    return 0;
}

