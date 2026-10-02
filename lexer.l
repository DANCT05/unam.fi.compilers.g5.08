%{
#include <stdio.h>
%}

letter  [A-Za-z]
digit   [0-9]
ws      [ \t\r\n]+

id      {letter}({letter}|{digit})*
number  {digit}+(\.{digit}+)?([Ee][+-]?{digit}+)?

invalid_id   {digit}+{letter}({letter}|{digit})*

%%

{ws} {
    /* ignorar whitespace */
}

"if" {
	 printf("%s Esto es un if\n", yytext);
} 

"else" {
	 printf("%s Esto es un else\n", yytext);
}

"char" {
	printf("%s Esto es un char\n", yytext);
}

"int" {
	 printf("%s Esto es un int\n", yytext);
}

"float" {
	 printf("%s Esto es un float\n", yytext);
}

"return" {
	 printf("%s Esto es un return\n", yytext);
}

"==" {
	 printf("%s Esto es una comparación igual que\n", yytext);
}

">=" {
	 printf("%s Comparación >=\n", yytext);
}

"<=" {
	 printf("%s Comparación <=\n", yytext);
}

"=" {
	 printf("%s Operador de Asignación\n", yytext);
}

"+" {
	 printf("%s Operador de Suma\n", yytext);
}

"-" {
	 printf("%s Operador de Resta\n", yytext);
}

"*" {
	 printf("%s Operador de Multiplicación\n", yytext);
}

"/" {
	 printf("%s Operador de Diviión\n", yytext);
}

"(" {
	 printf("%s Token de puntuación.\n", yytext);
}

")" {
	 printf("%s Token de puntuación.\n", yytext);
}

"{" {
	 printf("%s Token de puntuación.\n", yytext);
}

"}" {
	 printf("%s Token de puntuación.\n", yytext);
}

"," {
	 printf("%s Token de puntuación.\n", yytext);
}

";" {
	 printf("%s Token de puntuación.\n", yytext);
}

{number} {
    printf("%s este es un number\n", yytext);
}

{invalid_id} {
	printf("%s Este es un ID invalido", yytext);
}

{id} {
    printf("%s este es un ID\n", yytext);
}

.	{ 
	printf("%s Este es un caracter invalido\n", yytext); 
}

%%

int yywrap() {
    return 1;
}