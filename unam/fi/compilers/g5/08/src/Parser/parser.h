#ifndef LL1_PARSER_H
#define LL1_PARSER_H

#include <iostream>
#include <vector>
#include <string>
#include "parse_tree.h"
#include "../Token/token.h"

using namespace std;

// Devuelve true si la entrada pertenece al lenguaje y entrega el arbol.
bool parse(const vector<Token>& tokens, string& error,
           ParseTree& tree, ostream* trace = nullptr);

// Sobrecarga para conservar llamadas anteriores al parser.
bool parse(const vector<Token>& tokens, string& error,
           ostream* trace = nullptr);

bool analyzeTokens(const vector<Token>& tokens, string& error,
                   ParseTree& tree, ostream* trace = nullptr);

#endif // LL1_PARSER_H
