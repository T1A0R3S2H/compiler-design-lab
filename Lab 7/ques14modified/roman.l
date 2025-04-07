%{
#include <stdio.h>
#include <stdlib.h>
%}

%%
I{3}                     { printf("Valid Roman Numeral: %s\n", yytext); }
IV|IX                    { printf("Valid Roman Numeral: %s\n", yytext); }
V{0,3}I{0,3}             { printf("Valid Roman Numeral: %s\n", yytext); }
X{0,3}(IX|IV|V{0,3}I{0,3}) { printf("Valid Roman Numeral: %s\n", yytext); }
L{0,3}(IX|IV|V{0,3}I{0,3}) { printf("Valid Roman Numeral: %s\n", yytext); }
C{0,3}(IX|IV|V{0,3}I{0,3}) { printf("Valid Roman Numeral: %s\n", yytext); }
D{0,3}(IX|IV|V{0,3}I{0,3}) { printf("Valid Roman Numeral: %s\n", yytext); }
M{0,3}(IX|IV|V{0,3}I{0,3}) { printf("Valid Roman Numeral: %s\n", yytext); }

[IVXLCDM]+              { printf("Invalid Roman Numeral: %s\n", yytext); }

\n                       { /* Do nothing for newlines */ }
.|\n                     { /* Do nothing for invalid sequences */ }

%%

int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
