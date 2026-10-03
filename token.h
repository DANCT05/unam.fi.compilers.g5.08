#ifndef TOKEN_H
#define TOKEN_H

#include <string>

using namespace std;

enum TokenType {
    TOKEN_KEYWORD,
    TOKEN_IDENTIFIER,
    TOKEN_PUNCTUATION,
    TOKEN_OPERATOR,
    TOKEN_CONSTANT,
    TOKEN_LITERAL,
    TOKEN_ERROR_ID,
    TOKEN_ERROR_INVALID_CHAR,
    WHITESPACE
};

string tokenToString(TokenType token);

#endif