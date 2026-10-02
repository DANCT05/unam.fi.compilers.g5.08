#include <iostream>

using namespace std;

extern "C" {
    int yylex();
}

int main() {

    int token;

    do {
        token = yylex();
    } while (token != 0);

    return 0;
}