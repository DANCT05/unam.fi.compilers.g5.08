#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "Lexer/lexer_utils.h"
#include "Parser/parser.h"
#include "SDT/sdt.h"

using namespace std;

string openFile(const string& path);

int main() {

    string path = "cadena_de_prueba.txt";
    string input = openFile(path);

    // Lexical analysis
    cout << "\n========== LEXICAL ANALYSIS ==========\n";

    vector<Token> tokens = tokenize(input);

    if (printLexicalErrors(tokens)) {
        cout << "Analisis lexico incorrecto" << endl;
        return 1;
    }

    cout << "Analisis lexico correcto" << endl;

    // Syntax analysis LL(1)
    cout << "\n========== SYNTAX ANALYSIS ==========\n";

    string error;
    ParseTree tree;
    bool result = parse(tokens, error, tree);

    if (!result) {
        cout << error << endl;
        cout << "Parsing error" << endl;
        return 1;
    }

    cout << "Parsing Success!" << endl;

    // Semantic analysis SDT
    cout << "\n========== SEMANTIC ANALYSIS ==========\n";
    if (!verifySDT(tree, tokens, error)) {
        cout << "SDT error: " << error << endl;
        return 1;
    }
    cout << "SDT Verified!" << endl;

    return 0;
}

string openFile(const string& path) {

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