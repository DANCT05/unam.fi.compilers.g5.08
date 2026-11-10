#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <string>
#include <map>

using namespace std;

// Representa una variable declarada.
struct Symbol {
    string name;
    string type;
    int line;
};

// Almacena las variables registradas.
struct SymbolTable {
    map<string, Symbol> symbols;
};

void initializeSymbolTable(SymbolTable& table);

bool declareSymbol(SymbolTable& table, const Symbol& symbol);

#endif
