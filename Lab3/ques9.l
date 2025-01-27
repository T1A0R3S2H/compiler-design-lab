%{
#include <stdio.h>
#include <ctype.h>
#include <string.h>
%}

%%
"int"|"float"|"char"|"return"|"if"|"else"|"while"|"for"|"do"  { printf("Keyword: %s\n", yytext); }
[A-Za-z_][A-Za-z0-9_]*                                       { printf("Identifier: %s\n", yytext); }
[0-9]+                                                        { printf("Constant: %s\n", yytext); }
[+\-*/%=&|!<>]=?|==|!=|&&|\|\|                                { printf("Operator: %s\n", yytext); }
[.,;:{}()[\]]                                                 { printf("Punctuation: %s\n", yytext); }
[ \t\n]+                                                      { /* Ignore whitespace */ }
.                                                             { printf("Unrecognized: %s\n", yytext); }

%%

int main() {
    yylex();
    return 0;
}



// (base) iiitkota@iiitkota-HP-Elite-Tower-600-G9-Desktop-PC:~/compilerlab/ques7$ flex ques9.l
// (base) iiitkota@iiitkota-HP-Elite-Tower-600-G9-Desktop-PC:~/compilerlab/ques7$ gcc lex.yy.c -o lexer -lfl
// (base) iiitkota@iiitkota-HP-Elite-Tower-600-G9-Desktop-PC:~/compilerlab/ques7$ ./lexer
