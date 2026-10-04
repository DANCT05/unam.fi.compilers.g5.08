#include <iostream>
#include <utility>
#include <iterator>

#include "token.h"

bool yylex(
    const char *&YYCURSOR,
    TokenType &token,
    TokenError &errorValue,
    string &lexeme
);

void printToken(
    const pair<int, pair<int, string>> &token
);

int main() {

    string input(
        (istreambuf_iterator<char>(cin)),
        istreambuf_iterator<char>()
    );

    const char *YYCURSOR = input.c_str();

    TokenType tokenType;
    TokenError errorValue;
    string lexeme;

    pair<int, pair<int, string>> token;

    while (yylex(YYCURSOR, tokenType, errorValue, lexeme)) {

        token.first = tokenType;

        switch (tokenType) {

            case TOKEN_IDENTIFIER:
            case TOKEN_CONSTANT:
            case TOKEN_LITERAL:
                token.second = {-1, lexeme};
                break;

            case TOKEN_KEYWORD:
                token.second = {
                    getKeywordValue(lexeme),lexeme
                };
                break;

            case TOKEN_PUNCTUATION:
                token.second = {
                    getPunctuationValue(lexeme),
                    lexeme
                };
                break;

            case TOKEN_OPERATOR:
                token.second = {
                    getOperatorValue(lexeme),
                    lexeme
                };
                break;

            case TOKEN_ERROR:
                token.second = {
                    errorValue,
                    lexeme
                };
                break;

            default:
                token.second = {-1, lexeme};
                break;
        }

        printToken(token);
    }

    return 0;
}


void printToken(
    const pair<int, pair<int, string>> &token
) {

    TokenType tokenType =
        static_cast<TokenType>(token.first);

    int tokenValue = token.second.first;
    string lexeme = token.second.second;

    cout << "<"
         << tokenToString(tokenType)
         << ", ";

    if (tokenValue == -1) {

        cout << tokenValue
             << ", "
             << lexeme;

    } else {

        switch (tokenType) {

            case TOKEN_KEYWORD:
                cout << keywordToString(
                    static_cast<TokenKeyword>(tokenValue)
                );
                break;

            case TOKEN_PUNCTUATION:
                cout << punctuationToString(
                    static_cast<TokenPunctuation>(tokenValue)
                );
                break;

            case TOKEN_OPERATOR:
                cout << operatorToString(
                    static_cast<TokenOperator>(tokenValue)
                );
                break;

            case TOKEN_ERROR:
                cout << errorToString(
                    static_cast<TokenError>(tokenValue)
                );
                break;

            default:
                cout << tokenValue;
                break;
        }

        cout << ", " << lexeme;
    }

    cout << ">" << '\n';
}