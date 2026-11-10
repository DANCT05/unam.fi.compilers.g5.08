#ifndef LL1_LEXER_LEXER_UTILS_H
#define LL1_LEXER_LEXER_UTILS_H

#include <vector>
#include <string>

#include "../Token/token.h"

using namespace std;

vector<Token> tokenize(const string& input);

bool printLexicalErrors(const vector<Token>& tokens);
#endif // LL1_LEXER_LEXER_UTILS_H
