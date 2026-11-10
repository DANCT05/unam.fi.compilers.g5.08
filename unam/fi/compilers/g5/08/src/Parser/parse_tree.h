#ifndef LL1_PARSE_TREE_H
#define LL1_PARSE_TREE_H

#include <string>
#include <ostream>
#include <vector>

using namespace std;

// Los indices permanecen validos aunque crezca el vector.
struct ParseNode {
    string symbol;
    int ruleNumber = 0;    // 0 si es terminal
    int tokenIndex = -1;   // indice en vector<Token>, -1 si no es terminal
    vector<int> children;
};

struct ParseTree {
    vector<ParseNode> nodes;
    int root = -1;
};


#endif // LL1_PARSE_TREE_H
