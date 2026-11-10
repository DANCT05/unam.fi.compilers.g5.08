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

        case TOKEN_EOF:
            return "TOKEN_EOF";

        case TOKEN_ERROR:
            return "TOKEN_ERROR";

        default:
            return "UNKNOWN";
    }
}

TokenKeyword getKeywordValue(const string &lexeme) {

    if (lexeme == "int")
        return KEYWORD_INT;

    else if (lexeme == "float")
        return KEYWORD_FLOAT;

    else if (lexeme == "char")
        return KEYWORD_CHAR;

    else if (lexeme == "string")
        return KEYWORD_STRING;

    else if (lexeme == "void")
        return KEYWORD_VOID;

    else if (lexeme == "if")
        return KEYWORD_IF;

    else if (lexeme == "else")
        return KEYWORD_ELSE;

    else if (lexeme == "for")
        return KEYWORD_FOR;

    else if (lexeme == "while")
        return KEYWORD_WHILE;

    else if (lexeme == "return")
        return KEYWORD_RETURN;

    return KEYWORD_INVALID;
}

string keywordToString(TokenKeyword keyword) {

    switch (keyword) {

        case KEYWORD_INT:
            return "KEYWORD_INT";

        case KEYWORD_FLOAT:
            return "KEYWORD_FLOAT";

        case KEYWORD_CHAR:
            return "KEYWORD_CHAR";

        case KEYWORD_STRING:
            return "KEYWORD_STRING";

        case KEYWORD_VOID:
            return "KEYWORD_VOID";

        case KEYWORD_IF:
            return "KEYWORD_IF";

        case KEYWORD_ELSE:
            return "KEYWORD_ELSE";

        case KEYWORD_FOR:
            return "KEYWORD_FOR";

        case KEYWORD_WHILE:
            return "KEYWORD_WHILE";

        case KEYWORD_RETURN:
            return "KEYWORD_RETURN";

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

    return PUNCTUATION_INVALID;
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

    else if (lexeme == ">")
        return OPERATOR_GREATER;

    else if (lexeme == "<")
        return OPERATOR_LESS;

    else if (lexeme == "!=")
        return OPERATOR_NOT_EQUAL;

    else if (lexeme == "&&")
        return OPERATOR_AND;

    else if (lexeme == "||")
        return OPERATOR_OR;

    else if (lexeme == "!")
        return OPERATOR_NOT;

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

        case OPERATOR_GREATER:
            return "OPERATOR_GREATER";

        case OPERATOR_LESS:
            return "OPERATOR_LESS";

        case OPERATOR_NOT_EQUAL:
            return "OPERATOR_NOT_EQUAL";

        case OPERATOR_AND:
            return "OPERATOR_AND";

        case OPERATOR_OR:
            return "OPERATOR_OR";

        case OPERATOR_NOT:
            return "OPERATOR_NOT";

        case OPERATOR_ASSIGN:
            return "OPERATOR_ASSIGN";

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

string tokenSymbol(const Token& token) {
    if (token.type == TOKEN_IDENTIFIER) {
        return "TOKEN_IDENTIFIER";
    }
    if (token.type == TOKEN_CONSTANT) {
        return "TOKEN_CONSTANT";
    }
    if (token.type == TOKEN_LITERAL) {
        return "TOKEN_LITERAL";
    }
    if (token.type == TOKEN_EOF) {
        return "TOKEN_EOF";
    }
    if (token.type == TOKEN_ERROR) {
        return "TOKEN_ERROR";
    }

    if (token.type == TOKEN_KEYWORD) {
        if (token.subtype == KEYWORD_INT) return "KEYWORD_INT";
        if (token.subtype == KEYWORD_FLOAT) return "KEYWORD_FLOAT";
        if (token.subtype == KEYWORD_CHAR) return "KEYWORD_CHAR";
        if (token.subtype == KEYWORD_STRING) return "KEYWORD_STRING";
        if (token.subtype == KEYWORD_VOID) return "KEYWORD_VOID";
        if (token.subtype == KEYWORD_IF) return "KEYWORD_IF";
        if (token.subtype == KEYWORD_ELSE) return "KEYWORD_ELSE";
        if (token.subtype == KEYWORD_FOR) return "KEYWORD_FOR";
        if (token.subtype == KEYWORD_WHILE) return "KEYWORD_WHILE";
        if (token.subtype == KEYWORD_RETURN) return "KEYWORD_RETURN";
    }

    if (token.type == TOKEN_PUNCTUATION) {
        if (token.subtype == PUNCTUATION_LPAREN) return "PUNCTUATION_LPAREN";
        if (token.subtype == PUNCTUATION_RPAREN) return "PUNCTUATION_RPAREN";
        if (token.subtype == PUNCTUATION_LBRACE) return "PUNCTUATION_LBRACE";
        if (token.subtype == PUNCTUATION_RBRACE) return "PUNCTUATION_RBRACE";
        if (token.subtype == PUNCTUATION_COMMA) return "PUNCTUATION_COMMA";
        if (token.subtype == PUNCTUATION_SEMICOLON) return "PUNCTUATION_SEMICOLON";
    }

    if (token.type == TOKEN_OPERATOR) {
        if (token.subtype == OPERATOR_PLUS) return "OPERATOR_PLUS";
        if (token.subtype == OPERATOR_MINUS) return "OPERATOR_MINUS";
        if (token.subtype == OPERATOR_MULT) return "OPERATOR_MULT";
        if (token.subtype == OPERATOR_DIV) return "OPERATOR_DIV";
        if (token.subtype == OPERATOR_EQUAL) return "OPERATOR_EQUAL";
        if (token.subtype == OPERATOR_GREATER_EQUAL) return "OPERATOR_GREATER_EQUAL";
        if (token.subtype == OPERATOR_LESS_EQUAL) return "OPERATOR_LESS_EQUAL";
        if (token.subtype == OPERATOR_GREATER) return "OPERATOR_GREATER";
        if (token.subtype == OPERATOR_LESS) return "OPERATOR_LESS";
        if (token.subtype == OPERATOR_NOT_EQUAL) return "OPERATOR_NOT_EQUAL";
        if (token.subtype == OPERATOR_AND) return "OPERATOR_AND";
        if (token.subtype == OPERATOR_OR) return "OPERATOR_OR";
        if (token.subtype == OPERATOR_NOT) return "OPERATOR_NOT";
        if (token.subtype == OPERATOR_ASSIGN) return "OPERATOR_ASSIGN";
    }

    return "UNKNOWN";
}