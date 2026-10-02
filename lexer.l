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

if {
	 printf("%Esto es un if\n", yytext);
}

else {
	 printf("Esto es un else\n", yytext);
}

char {
	printf("%Esto es un char\n", yytext);
}

int {
	 printf("%Esto es un int\n", yytext);
}

float {
	 printf("%Esto es un float\n", yytext);
}

return {
	 printf("Esto es un return\n", yytext);
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