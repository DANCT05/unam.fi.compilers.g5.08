%{
#include <stdio.h>
%}

letter  [A-Za-z]
digit   [0-9]
ws      [ \t\r\n]+

id      {letter}({letter}|{digit})*
number  {digit}+(\.{digit}+)?([Ee][+-]?{digit}+)?

%%

{ws} {
    /* ignorar whitespace */
}

{id} {
    printf("%s este es un ID\n", yytext);
}

{number} {
    printf("%s este es un number\n", yytext);
}

%%

int yywrap() {
    return 1;
}