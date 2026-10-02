%{
#include<stdio.h>

%}

letter 	[A-Za-z]
digit 	[0-9]
ws 		[ \t\n]

%%

{letter} {
	printf("%s esta es una letra\n", yytext);
}

{digit} {
	printf("%s esta es un digito\n", yytext);
}

{ws} {
	printf("%s esta es un espacio\n", yytext);
}

%%

int yywrap(){
	return 1;
}