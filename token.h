#include <string>

using namespace std;

enum TokenType {
    TOKEN_KEYWORD,
    TOKEN_IDENTIFIER,
    TOKEN_PUNCTUATION,
    TOKEN_OPERATOR,
    TOKEN_CONSTANT,
    TOKEN_LITERAL,
    TOKEN_ERROR,
    WHITESPACE
};

enum TokenKeyword {
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_CHAR,
    TOKEN_INT,
    TOKEN_FLOAT,
    TOKEN_RETURN
};

enum TokenPunctuation {
    PUNCTUATION_LPAREN,      // (
    PUNCTUATION_RPAREN,      // )
    PUNCTUATION_LBRACE,      // {
    PUNCTUATION_RBRACE,      // }
    PUNCTUATION_COMMA,       // ,
    PUNCTUATION_SEMICOLON    // ;
};

enum TokenOperator {
    OPERATOR_PLUS,
    OPERATOR_MINUS,
    OPERATOR_MULT,
    OPERATOR_DIV,

    OPERATOR_EQUAL,
    OPERATOR_GREATER_EQUAL,
    OPERATOR_LESS_EQUAL,

    OPERATOR_ASSIGN,

    OPERATOR_INVALID
};

enum TokenError {
    ERROR_ID_START_DIGIT,
    ERROR_ID_START_SYMBOL,
    ERROR_ID_MIDDLE_SYMBOL,
    ERROR_ID_LAST_SYMBOL,
    ERROR_INVALID_CHAR
};

string tokenToString(TokenType token);

TokenKeyword getKeywordValue(const string &lexeme);
string keywordToString(TokenKeyword keyword);


TokenPunctuation getPunctuationValue(const string &lexeme);
string punctuationToString(TokenPunctuation punctuation);


TokenOperator getOperatorValue(const string &lexeme);
string operatorToString(TokenOperator op);

string errorToString(TokenError error);