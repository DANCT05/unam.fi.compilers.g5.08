#include "token.h"

string tokenToString(TokenType token) {

    switch (token) {

        case TOKEN_KEYWORD:
            return "TOKEN_KEYWORD";

        case TOKEN_IDENTIFIER:
            return "TOKEN_IDENTIFIER";

        case TOKEN_PUNCTUATION:
            return "TOKEN_PUNCTUATION";

        case TOKEN_OPERATOR:
            return "TOKEN_OPERATOR";

        case TOKEN_CONSTANT:
            return "TOKEN_CONSTANT";

        case TOKEN_LITERAL:
            return "TOKEN_LITERAL";

        case TOKEN_ERROR_ID:
            return "TOKEN_ERROR_ID";

        case TOKEN_ERROR_INVALID_CHAR:
            return "TOKEN_ERROR_INVALID_CHAR";

        case WHITESPACE:
            return "WHITESPACE";

        default:
            return "UNKNOWN";
    }
}