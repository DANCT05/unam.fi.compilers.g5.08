#ifndef LL1_PARSER_GRAMMAR_H
#define LL1_PARSER_GRAMMAR_H

#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

// Una regla A -> B C se guarda con su izquierda y su derecha.
struct Production {
    string left;
    vector<string> right;
};

extern map<int, Production> productions;
extern set<string> terminals;
extern set<string> nonterminals;
extern const string epsilon;
extern const string initialSymbol;

void loadGrammar();
int countProductions();
#endif // LL1_PARSER_GRAMMAR_H
