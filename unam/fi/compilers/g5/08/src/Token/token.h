#ifndef LL1_TOKEN_TOKEN_H
#define LL1_TOKEN_TOKEN_H

#include <string>

using namespace std;

// Token types
enum TokenType {
    TOKEN_KEYWORD,
    TOKEN_IDENTIFIER,
    TOKEN_PUNCTUATION,
    TOKEN_OPERATOR,
    TOKEN_CONSTANT,
    TOKEN_LITERAL,

    TOKEN_EOF,
    TOKEN_ERROR
};

// Keyword subtypes
enum TokenKeyword {
    KEYWORD_INT,
    KEYWORD_FLOAT,
    KEYWORD_CHAR,
    KEYWORD_STRING,
    KEYWORD_VOID,

    KEYWORD_IF,
    KEYWORD_ELSE,
    KEYWORD_FOR,
    KEYWORD_WHILE,

    KEYWORD_RETURN,

    KEYWORD_INVALID
};

// Punctuation subtypes
enum TokenPunctuation {
    PUNCTUATION_LPAREN,      // (
    PUNCTUATION_RPAREN,      // )
    PUNCTUATION_LBRACE,      // {
    PUNCTUATION_RBRACE,      // }
    PUNCTUATION_COMMA,       // ,
    PUNCTUATION_SEMICOLON,   // ;

    PUNCTUATION_INVALID
};

// Operator subtypes
enum TokenOperator {
    OPERATOR_PLUS,
    OPERATOR_MINUS,
    OPERATOR_MULT,
    OPERATOR_DIV,

    OPERATOR_EQUAL,
    OPERATOR_GREATER_EQUAL,
    OPERATOR_LESS_EQUAL,
    OPERATOR_GREATER,
    OPERATOR_LESS,
    OPERATOR_NOT_EQUAL,

    OPERATOR_AND,
    OPERATOR_OR,
    OPERATOR_NOT,

    OPERATOR_ASSIGN,

    OPERATOR_INVALID
};

// Error subtypes
enum TokenError {
    ERROR_ID_START_DIGIT,
    ERROR_ID_START_SYMBOL,
    ERROR_ID_MIDDLE_SYMBOL,
    ERROR_ID_LAST_SYMBOL,
    ERROR_INVALID_CHAR
};

// Token structure
struct Token {
    TokenType type;
    int subtype;
    string lexeme;
    
    int line;
};

// Token functions
string tokenToString(TokenType token);
string tokenSymbol(const Token &token);

// Keyword functions
TokenKeyword getKeywordValue(const string &lexeme);
string keywordToString(TokenKeyword keyword);

// Punctuation functions
TokenPunctuation getPunctuationValue(const string &lexeme);
string punctuationToString(TokenPunctuation punctuation);

// Operator functions
TokenOperator getOperatorValue(const string &lexeme);
string operatorToString(TokenOperator op);

// Error functions
string errorToString(TokenError error);

#endif // LL1_TOKEN_TOKEN_H
