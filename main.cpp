#include <iostream>
#include <fstream>

#include "token.h"

//Lexer Analyzer function.
bool yylex(const char *&YYCURSOR,TokenType &token,TokenError &errorValue,string &lexeme);

string openFile(const string &path);
void printToken(const pair<int, pair<int, string>> &token);
void printTokenCounters(int keywordCount,int identifierCount,int punctuationCount,int operatorCount,int constantCount,int literalCount);

int main() {

    string path = "cadena_de_prueba.txt";
    string input = openFile(path);

    const char *YYCURSOR = input.c_str();

    TokenType tokenType;
    TokenError errorValue;
    string lexeme;

    pair<int, pair<int, string>> token;

    int keywordCount = 0;
    int identifierCount = 0;
    int punctuationCount = 0;
    int operatorCount = 0;
    int constantCount = 0;
    int literalCount = 0;


    while (yylex(YYCURSOR, tokenType, errorValue, lexeme)) {

        token.first = tokenType;

        switch (tokenType) {

            case TOKEN_IDENTIFIER:
                token.second = {-1, lexeme};
                identifierCount++;
                break;

            case TOKEN_CONSTANT:
                token.second = {-1, lexeme};
                constantCount++;
                break;

            case TOKEN_LITERAL:
                token.second = {-1, lexeme};
                literalCount++;
                break;

            case TOKEN_KEYWORD:
                token.second = {
                    getKeywordValue(lexeme),
                    lexeme
                };

                keywordCount++;
                break;

            case TOKEN_PUNCTUATION:
                token.second = {
                    getPunctuationValue(lexeme),
                    lexeme
                };

                punctuationCount++;
                break;

            case TOKEN_OPERATOR:
                token.second = {
                    getOperatorValue(lexeme),
                    lexeme
                };

                operatorCount++;
                break;

            case TOKEN_ERROR:
                token.second = {errorValue,lexeme};
                break;

            default:
                token.second = {-1, lexeme};
                break;
        }

        printToken(token);
    }

    printTokenCounters(keywordCount,identifierCount,punctuationCount,operatorCount,constantCount,literalCount);

    return 0;
}

string openFile(const string &path) {

    ifstream file(path);

    if (!file.is_open()) {
        cerr << "Error opening file: " << path << endl;
        return "";
    }

    string input(
        (istreambuf_iterator<char>(file)),
        istreambuf_iterator<char>()
    );

    file.close();

    return input;
}


void printToken(const pair<int, pair<int, string>> &token) {

    TokenType tokenType =
        static_cast<TokenType>(token.first);

    int tokenValue = token.second.first;
    string lexeme = token.second.second;

    cout << "<"
         << tokenToString(tokenType)
         << ", ";

    if (tokenValue == -1) {

        cout << "NO_SUBTYPE_VALUE"
             << ", ";

    } else {

        switch (tokenType) {

            case TOKEN_KEYWORD:
                cout << keywordToString(
                    static_cast<TokenKeyword>(tokenValue)
                ) << ", ";
                break;

            case TOKEN_PUNCTUATION:
                cout << punctuationToString(
                    static_cast<TokenPunctuation>(tokenValue)
                ) << ", ";
                break;

            case TOKEN_OPERATOR:
                cout << operatorToString(
                    static_cast<TokenOperator>(tokenValue)
                ) << ", ";
                break;

            case TOKEN_ERROR:
                cout << errorToString(
                    static_cast<TokenError>(tokenValue)
                ) << ", ";
                break;

            default:
                cout << tokenValue << ", ";
                break;
        }
    }

    cout << lexeme << ">" << endl;
}

void printTokenCounters(int keywordCount,int identifierCount,int punctuationCount,int operatorCount,int constantCount,int literalCount) {

    int totalTokens = keywordCount + identifierCount + punctuationCount + operatorCount + constantCount + literalCount;

    cout << "\nToken counters:" << endl;

    cout << "TOKEN_KEYWORD: "
         << keywordCount << endl;

    cout << "TOKEN_IDENTIFIER: "
         << identifierCount << endl;

    cout << "TOKEN_PUNCTUATION: "
         << punctuationCount << endl;

    cout << "TOKEN_OPERATOR: "
         << operatorCount << endl;

    cout << "TOKEN_CONSTANT: "
         << constantCount << endl;

    cout << "TOKEN_LITERAL: "
         << literalCount << endl;

    cout << "TOTAL VALID TOKENS: "
         << totalTokens << endl;
}