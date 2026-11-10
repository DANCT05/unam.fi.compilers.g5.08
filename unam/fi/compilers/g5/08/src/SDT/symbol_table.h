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

// Inicializa la tabla de simbolos.
void initializeSymbolTable(SymbolTable& table);

// Registra una variable si no existe previamente.
bool declareSymbol(SymbolTable& table, const Symbol& symbol);

#endif
