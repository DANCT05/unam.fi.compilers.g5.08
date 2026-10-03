#include <iostream>
#include <string>
#include "token.h"

using namespace std;

bool yylex(const char *&YYCURSOR,TokenType &token,string &lexeme);

int main() {

    string input(
        (istreambuf_iterator<char>(cin)),
        istreambuf_iterator<char>()
    );

    const char *YYCURSOR = input.c_str();

    TokenType tokenType;
    string lexeme;

    while (yylex(YYCURSOR, tokenType, lexeme)) {
        cout << "<" << tokenToString(tokenType) << ", " << lexeme << ">" << '\n';
    }

    return 0;
}