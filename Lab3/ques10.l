%{
#include <stdio.h>
#include <stdlib.h>
int vowels = 0, consonants = 0;
FILE *input_file;  // Declare a file pointer to read from a file
%}

%%
[AEIOUaeiou]   { vowels++; }
[A-Za-z]       { consonants++; }
.              { /* Ignore other characters */ }
\n             { /* Handle new lines */ }

%%

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    input_file = fopen(argv[1], "r");  // Open the file passed as an argument
    if (!input_file) {
        perror("Error opening file");
        return 1;
    }

    // Set the input stream for yylex() to the file
    yyin = input_file;
    
    yylex();  // Start scanning the file
    
    printf("Vowels: %d\n", vowels);
    printf("Consonants: %d\n", consonants);
    
    fclose(input_file);  // Close the file after processing
    return 0;
}
