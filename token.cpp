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

        case TOKEN_ERROR:
            return "TOKEN_ERROR";

        case WHITESPACE:
            return "WHITESPACE";

        default:
            return "UNKNOWN";
    }
}

TokenKeyword getKeywordValue(const string &lexeme) {

    if (lexeme == "if")
        return TOKEN_IF;

    else if (lexeme == "else")
        return TOKEN_ELSE;

    else if (lexeme == "char")
        return TOKEN_CHAR;

    else if (lexeme == "int")
        return TOKEN_INT;

    else if (lexeme == "float")
        return TOKEN_FLOAT;

    else if (lexeme == "return")
        return TOKEN_RETURN;
}

string keywordToString(TokenKeyword keyword) {

    switch (keyword) {

        case TOKEN_IF:
            return "TOKEN_IF";

        case TOKEN_ELSE:
            return "TOKEN_ELSE";

        case TOKEN_CHAR:
            return "TOKEN_CHAR";

        case TOKEN_INT:
            return "TOKEN_INT";

        case TOKEN_FLOAT:
            return "TOKEN_FLOAT";

        case TOKEN_RETURN:
            return "TOKEN_RETURN";

        default:
            return "UNKNOWN";
    }
}

TokenPunctuation getPunctuationValue(const string &lexeme) {

    if (lexeme == "(")
        return PUNCTUATION_LPAREN;

    else if (lexeme == ")")
        return PUNCTUATION_RPAREN;

    else if (lexeme == "{")
        return PUNCTUATION_LBRACE;

    else if (lexeme == "}")
        return PUNCTUATION_RBRACE;

    else if (lexeme == ",")
        return PUNCTUATION_COMMA;

    else if (lexeme == ";")
        return PUNCTUATION_SEMICOLON;
}

string punctuationToString(TokenPunctuation punctuation) {

    switch (punctuation) {

        case PUNCTUATION_LPAREN:
            return "PUNCTUATION_LPAREN";

        case PUNCTUATION_RPAREN:
            return "PUNCTUATION_RPAREN";

        case PUNCTUATION_LBRACE:
            return "PUNCTUATION_LBRACE";

        case PUNCTUATION_RBRACE:
            return "PUNCTUATION_RBRACE";

        case PUNCTUATION_COMMA:
            return "PUNCTUATION_COMMA";

        case PUNCTUATION_SEMICOLON:
            return "PUNCTUATION_SEMICOLON";

        default:
            return "UNKNOWN";
    }
}

TokenOperator getOperatorValue(const string &lexeme) {

    if (lexeme == "+")
        return OPERATOR_PLUS;

    else if (lexeme == "-")
        return OPERATOR_MINUS;

    else if (lexeme == "*")
        return OPERATOR_MULT;

    else if (lexeme == "/")
        return OPERATOR_DIV;

    else if (lexeme == "==")
        return OPERATOR_EQUAL;

    else if (lexeme == ">=")
        return OPERATOR_GREATER_EQUAL;

    else if (lexeme == "<=")
        return OPERATOR_LESS_EQUAL;

    else if (lexeme == "=")
        return OPERATOR_ASSIGN;

    return OPERATOR_INVALID;
}

string operatorToString(TokenOperator op) {

    switch (op) {

        case OPERATOR_PLUS:
            return "OPERATOR_PLUS";

        case OPERATOR_MINUS:
            return "OPERATOR_MINUS";

        case OPERATOR_MULT:
            return "OPERATOR_MULT";

        case OPERATOR_DIV:
            return "OPERATOR_DIV";

        case OPERATOR_EQUAL:
            return "OPERATOR_EQUAL";

        case OPERATOR_GREATER_EQUAL:
            return "OPERATOR_GREATER_EQUAL";

        case OPERATOR_LESS_EQUAL:
            return "OPERATOR_LESS_EQUAL";

        case OPERATOR_ASSIGN:
            return "OPERATOR_ASSIGN";

        case OPERATOR_INVALID:
            return "OPERATOR_INVALID";

        default:
            return "UNKNOWN";
    }
}

string errorToString(TokenError error) {

    switch (error) {

        case ERROR_ID_START_DIGIT:
            return "ERROR_ID_START_DIGIT";

        case ERROR_ID_START_SYMBOL:
            return "ERROR_ID_START_SYMBOL";

        case ERROR_ID_MIDDLE_SYMBOL:
            return "ERROR_ID_MIDDLE_SYMBOL";

        case ERROR_ID_LAST_SYMBOL:
            return "ERROR_ID_LAST_SYMBOL";

        case ERROR_INVALID_CHAR:
            return "ERROR_INVALID_CHAR";

        default:
            return "ERROR_UNKNOWN";
    }
}