#include "lexer_utils.h"

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

bool yylex(const char*& YYCURSOR, TokenType& token,
           TokenError& errorValue, string& lexeme, int& line);

// Funciones auxiliares
void printTokenTableHeader();
void printToken(const Token& token);
void printTokenCounterHeader();
void printTokenCounters(int keywordCount, int identifierCount,
                        int punctuationCount, int operatorCount,
                        int constantCount, int literalCount);


vector<Token> tokenize(const string& input) {

    const char* YYCURSOR = input.c_str();

    TokenType tokenType;
    TokenError errorValue;
    string lexeme;
    int line = 1;

    Token token;
    vector<Token> tokens;

    int keywordCount = 0;
    int identifierCount = 0;
    int punctuationCount = 0;
    int operatorCount = 0;
    int constantCount = 0;
    int literalCount = 0;

    //printTokenTableHeader();

    bool result;

    do {
        result = yylex(YYCURSOR, tokenType, errorValue, lexeme, line);

        token.type = tokenType;
        token.lexeme = lexeme;
        token.subtype = -1;
        token.line = line;

        switch (tokenType) {

            case TOKEN_IDENTIFIER:
                identifierCount++;
                break;

            case TOKEN_CONSTANT:
                constantCount++;
                break;

            case TOKEN_LITERAL:
                literalCount++;
                break;

            case TOKEN_KEYWORD:
                token.subtype = getKeywordValue(lexeme);
                keywordCount++;
                break;

            case TOKEN_PUNCTUATION:
                token.subtype = getPunctuationValue(lexeme);
                punctuationCount++;
                break;

            case TOKEN_OPERATOR:
                token.subtype = getOperatorValue(lexeme);
                operatorCount++;
                break;

            case TOKEN_EOF:
                token.lexeme = "$";
                break;

            case TOKEN_ERROR:
                token.subtype = errorValue;
                break;

            default:
                break;
        }

        //printToken(token);
        tokens.push_back(token);

    } while (result);

    //printTokenCounters(keywordCount, identifierCount,punctuationCount, operatorCount,constantCount, literalCount);

    return tokens;
}

bool printLexicalErrors(const vector<Token>& tokens) {

    bool lexicalError = false;

    for (const Token& token : tokens) {
        if (token.type == TOKEN_ERROR) {
            cout << "Error lexico en linea " << token.line;
            cout << ": " << errorToString((TokenError)token.subtype);
            cout << " ('" << token.lexeme << "')" << endl;

            lexicalError = true;
        }
    }

    return lexicalError;
}

void printTokenTableHeader() {

    cout << left
         << setw(25) << "TOKEN TYPE"
         << setw(30) << "SUBTYPE"
         << setw(30) << "LEXEME"
         << setw(10) << "LINE"
         << endl;

    cout << string(95, '-') << endl;
}

void printToken(const Token& token) {

    string subtype;

    if (token.subtype == -1) {

        subtype = "NO_SUBTYPE_VALUE";

    } else {

        switch (token.type) {

            case TOKEN_KEYWORD:
                subtype = keywordToString(
                    static_cast<TokenKeyword>(token.subtype)
                );
                break;

            case TOKEN_PUNCTUATION:
                subtype = punctuationToString(
                    static_cast<TokenPunctuation>(token.subtype)
                );
                break;

            case TOKEN_OPERATOR:
                subtype = operatorToString(
                    static_cast<TokenOperator>(token.subtype)
                );
                break;

            case TOKEN_ERROR:
                subtype = errorToString(
                    static_cast<TokenError>(token.subtype)
                );
                break;

            default:
                subtype = "NO_SUBTYPE_VALUE";
                break;
        }
    }

    cout << left
         << setw(25) << tokenToString(token.type)
         << setw(30) << subtype
         << setw(30) << token.lexeme
         << setw(10) << token.line
         << endl;
}

void printTokenCounterHeader() {

    cout << left
         << setw(30) << "TOKEN TYPE"
         << setw(10) << "COUNT"
         << endl;

    cout << string(40, '-') << endl;
}

void printTokenCounters(int keywordCount, int identifierCount,
                        int punctuationCount, int operatorCount,
                        int constantCount, int literalCount) {

    int totalTokens = keywordCount + identifierCount
                    + punctuationCount + operatorCount
                    + constantCount + literalCount;

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