#include <iostream>
#include <fstream>
#include <iomanip>

#include "token.h"

//Lexer Analyzer function.
bool yylex(const char *&YYCURSOR,TokenType &token,TokenError &errorValue,string &lexeme);

string openFile(const string &path);
void printTokenTableHeader();
void printToken(const pair<int, pair<int, string>> &token);
void printTokenCounterHeader();
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

    printTokenTableHeader();

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

void printTokenTableHeader() {

    cout << left
         << setw(25) << "TOKEN TYPE"
         << setw(30) << "SUBTYPE"
         << setw(30) << "LEXEME"
         << endl;

    cout << string(85, '-') << endl;
}


void printToken(const pair<int, pair<int, string>> &token) {

    TokenType tokenType =
        static_cast<TokenType>(token.first);

    int tokenValue = token.second.first;
    string lexeme = token.second.second;

    string subtype;

    if (tokenValue == -1) {

        subtype = "NO_SUBTYPE_VALUE";

    } else {

        switch (tokenType) {

            case TOKEN_KEYWORD:
                subtype = keywordToString(
                    static_cast<TokenKeyword>(tokenValue)
                );
                break;

            case TOKEN_PUNCTUATION:
                subtype = punctuationToString(
                    static_cast<TokenPunctuation>(tokenValue)
                );
                break;

            case TOKEN_OPERATOR:
                subtype = operatorToString(
                    static_cast<TokenOperator>(tokenValue)
                );
                break;

            case TOKEN_ERROR:
                subtype = errorToString(
                    static_cast<TokenError>(tokenValue)
                );
                break;

            default:
                subtype = "NO_SUBTYPE_VALUE";
                break;
        }
    }

    cout << left << setw(25) 
         << tokenToString(tokenType) << setw(30) 
         << subtype << setw(30) 
         << lexeme << endl;
}

void printTokenCounterHeader() {

    cout << left << setw(30) 
         << "TOKEN TYPE" << setw(10) 
         << "COUNT" << endl;

    cout << string(40, '-') << endl;
}


void printTokenCounters(int keywordCount,int identifierCount,int punctuationCount,int operatorCount,int constantCount,int literalCount) {

    int totalTokens = keywordCount + identifierCount + punctuationCount + operatorCount + constantCount + literalCount;

    cout << endl;

    printTokenCounterHeader();

    cout << left << setw(30) 
        << "TOKEN_KEYWORD" << setw(10) 
        << keywordCount << endl;

    cout << left << setw(30) 
         << "TOKEN_IDENTIFIER" << setw(10) 
         << identifierCount << endl;

    cout << left << setw(30) 
         << "TOKEN_PUNCTUATION" << setw(10) 
         << punctuationCount << endl;

    cout << left << setw(30) 
         << "TOKEN_OPERATOR" << setw(10) 
         << operatorCount << endl;

    cout << left << setw(30) 
         << "TOKEN_CONSTANT" << setw(10) 
         << constantCount << endl;

    cout << left << setw(30) 
         << "TOKEN_LITERAL" << setw(10) 
         << literalCount << endl;

    cout << string(40, '-') << endl;

    cout << left << setw(30) 
         << "TOTAL VALID TOKENS" << setw(10) 
         << totalTokens << endl;
}