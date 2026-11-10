#include "symbol_table.h"

using namespace std;

// Inicializa la tabla de simbolos eliminando su contenido.
void initializeSymbolTable(SymbolTable& table) {

    table.symbols.clear();
}

// Registra una variable en la tabla de simbolos.
// Devuelve false si el identificador ya existe.
bool declareSymbol(SymbolTable& table, const Symbol& symbol) {

    // Buscar si el identificador ya fue declarado.
    if (table.symbols.count(symbol.name) > 0) {
        return false;
    }

    // Registrar la nueva variable.
    table.symbols[symbol.name] = symbol;

    return true;
}
