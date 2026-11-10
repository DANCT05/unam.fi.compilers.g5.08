#ifndef LL1_SDT_H
#define LL1_SDT_H

#include <string>
#include <vector>

#include "../Parser/parse_tree.h"
#include "../Token/token.h"

using namespace std;

// Recorre el arbol LL(1) y evalua reglas semanticas.
// error: descripcion y linea del primer problema encontrado.
bool verifySDT(const ParseTree& tree, const vector<Token>& tokens,
               string& error);

#endif // LL1_SDT_H
