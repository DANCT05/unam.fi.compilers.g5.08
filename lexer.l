%{
#include <stdio.h>
%}

letter                  [A-Za-z]
digit                   [0-9]

keyword                 (if|else|char|int|float|return)

arithmetic_operator     [+\-*/]
relational_operator     (==|>=|<=)
assignment_operator     =
operator                ({arithmetic_operator}|{relational_operator}|{assignment_operator})

punctuation             [(){},;]

ws                      [ \t\r\n]+

valid_char_literal      ({letter}|{digit}|{operator}|{ws}|{punctuation}|[@''#$%?¿.])

id                      {letter}({letter}|{digit})*
number                  {digit}+(\.{digit}+)?([Ee][+-]?{digit}+)?
literal                 \"({valid_char_literal})*\"

invalid_char_id         [""@''#$%?¿.]

invalid_id_start_digit  {digit}+{id}
invalid_id_start_symbol {invalid_char_id}+{id}
invalid_id_middle_symbol {id}{invalid_char_id}+{id}
invalid_id_last_symbol  {id}{invalid_char_id}+

invalid_id              ({invalid_id_start_digit}|{invalid_id_start_symbol}|{invalid_id_middle_symbol}|{invalid_id_last_symbol})


%%

{ws} {
    /* ignorar whitespace */
}

{literal} {
    printf("%s es un literal\n", yytext);
}

{keyword} {
    printf("%s es un keyword\n", yytext);
}

{operator} {
    printf("%s es un operador aritmetico\n", yytext);
}

{number} {
    printf("%s es un number\n", yytext);
}

{punctuation} {
    printf("%s es un token de puntuacion\n", yytext);
}

{invalid_id} {
    printf("%s es un ID invalido\n", yytext);
}

{id} {
    printf("%s es un ID\n", yytext);
}

. {
    printf("%s es un caracter invalido\n", yytext);
}

%%

int yywrap() {
    return 1;
}