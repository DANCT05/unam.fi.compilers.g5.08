#include <string>
#include "token.h"

bool yylex(const char *&YYCURSOR, TokenType &token, TokenError &errorValue, string &lexeme) {
    const char *YYMARKER;

    while (true) {

        const char *start = YYCURSOR;

        /*!re2c

            re2c:define:YYCTYPE = char;
            re2c:yyfill:enable = 0;

            letter = [A-Za-z];
            digit = [0-9];


            keyword = "if"|"else"|"char"|"int"|"float"|"return";


            arithmetic_operator = [-+*/];

            relational_operator = "=="|">="|"<=";

            assignment_operator = "=";


            operator = arithmetic_operator | relational_operator | assignment_operator;


            punctuation ="("|")"|"{"|"}"| ","|";";

            ws = [ \t\r\n]+;

            valid_char_literal = letter|digit|operator|ws|punctuation|[\x27@#$%?.];


            id = letter(letter | digit)*;
            number = digit+("." digit+)?([Ee][+-]? digit+)?;
            literal = "\x22"valid_char_literal*"\x22";


            invalid_char_id = [\x22\x27@#$%?.];

            invalid_id_start_digit = digit+ id;
            invalid_id_start_symbol = invalid_char_id+ id;
            invalid_id_middle_symbol = id invalid_char_id+id;
            invalid_id_last_symbol = id invalid_char_id+;

            ws {
                continue;
            }

            literal {
                lexeme.assign(start,YYCURSOR - start);
                token = TOKEN_LITERAL;

                return true;
            }

            keyword {
                lexeme.assign(start,YYCURSOR - start);
                token = TOKEN_KEYWORD;

                return true;
            }

            operator {
                lexeme.assign(start,YYCURSOR - start);
                token = TOKEN_OPERATOR;

                return true;
            }

            number {
                lexeme.assign(start,YYCURSOR - start);
                token = TOKEN_CONSTANT;

                return true;
            }

            punctuation {
                lexeme.assign(start,YYCURSOR - start);

                token = TOKEN_PUNCTUATION;
                return true;
            }


            invalid_id_start_digit {
                lexeme.assign(start, YYCURSOR - start);

                token = TOKEN_ERROR;
                errorValue = ERROR_ID_START_DIGIT;

                return true;
            }

            invalid_id_start_symbol {
                lexeme.assign(start, YYCURSOR - start);

                token = TOKEN_ERROR;
                errorValue = ERROR_ID_START_SYMBOL;

                return true;
            }

            invalid_id_middle_symbol {
                lexeme.assign(start, YYCURSOR - start);

                token = TOKEN_ERROR;
                errorValue = ERROR_ID_MIDDLE_SYMBOL;

                return true;
            }

            invalid_id_last_symbol {
                lexeme.assign(start, YYCURSOR - start);

                token = TOKEN_ERROR;
                errorValue = ERROR_ID_LAST_SYMBOL;

                return true;
            }

            id {
                lexeme.assign(start,YYCURSOR - start);
                token = TOKEN_IDENTIFIER;

                return true;
            }


            "\x00" {
                lexeme.clear();

                return false;
            }

            * {
                lexeme.assign(start, YYCURSOR - start);

                token = TOKEN_ERROR;
                errorValue = ERROR_INVALID_CHAR;

                return true;
            }

        */
    }
}