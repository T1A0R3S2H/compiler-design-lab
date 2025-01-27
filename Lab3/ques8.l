%{
#include <stdio.h>
%}

%%

[+-]?([0-9]*[.])?[0-9]+([eE][+-]?[0-9]+)?  { printf("Floating point number: %s\n", yytext); }

%%

int main() {
    yylex();
    return 0;
}

int yywrap(){
    return 1;
}


// lex ques8.l
// gcc lex.yy.c
// ./a.out
