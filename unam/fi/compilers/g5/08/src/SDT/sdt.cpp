
#include "sdt.h"
#include "symbol_table.h"

using namespace std;

// Obtiene el indice de un hijo del nodo.
int getChild(const ParseTree& tree, int nodeIndex, int childIndex) {

    if (nodeIndex < 0 || nodeIndex >= (int)tree.nodes.size()) {
        return -1;
    }

    const ParseNode& node = tree.nodes[nodeIndex];

    if (childIndex < 0 || childIndex >= (int)node.children.size()) {
        return -1;
    }

    return node.children[childIndex];
}

// Obtiene el numero de produccion del nodo.
int getRule(const ParseTree& tree, int nodeIndex) {

    if (nodeIndex < 0 || nodeIndex >= (int)tree.nodes.size()) {
        return 0;
    }

    return tree.nodes[nodeIndex].ruleNumber;
}

// Obtiene el lexema asociado a un nodo terminal.
string getLexeme(const ParseTree& tree,
                 const vector<Token>& tokens,
                 int nodeIndex) {

    if (nodeIndex < 0 || nodeIndex >= (int)tree.nodes.size()) {
        return "";
    }

    int tokenIndex = tree.nodes[nodeIndex].tokenIndex;

    if (tokenIndex < 0 || tokenIndex >= (int)tokens.size()) {
        return "";
    }

    return tokens[tokenIndex].lexeme;
}

// Obtiene la linea de un token.
int getLine(const ParseTree& tree,
            const vector<Token>& tokens,
            int nodeIndex) {

    if (nodeIndex < 0 || nodeIndex >= (int)tree.nodes.size()) {
        return 1;
    }

    int tokenIndex = tree.nodes[nodeIndex].tokenIndex;

    if (tokenIndex < 0 || tokenIndex >= (int)tokens.size()) {
        return 1;
    }

    return tokens[tokenIndex].line;
}

// Comprueba si una produccion representa epsilon.
bool isEmpty(const ParseTree& tree, int nodeIndex) {

    if (nodeIndex < 0 || nodeIndex >= (int)tree.nodes.size()) {
        return true;
    }

    const ParseNode& node = tree.nodes[nodeIndex];

    if (node.children.empty()) {
        return true;
    }

    int firstChild = node.children[0];

    if (firstChild < 0 || firstChild >= (int)tree.nodes.size()) {
        return true;
    }

    return tree.nodes[firstChild].symbol == "epsilon";
}

// Obtiene el tipo de dato de una declaracion.
string getType(const ParseTree& tree,
               const vector<Token>& tokens,
               int nodeIndex) {

    if (nodeIndex < 0 || nodeIndex >= (int)tree.nodes.size()) {
        return "";
    }

    string symbol = tree.nodes[nodeIndex].symbol;

    if (symbol == "Tipo" || symbol == "TipoFuncion") {

        int typeChild = getChild(tree, nodeIndex, 0);

        return getType(tree, tokens, typeChild);
    }

    return getLexeme(tree, tokens, nodeIndex);
}

// Registra una variable global o reporta si ya existe.
bool registerVariable(SymbolTable& table,
                      const ParseTree& tree,
                      const vector<Token>& tokens,
                      int identifierNode,
                      const string& type,
                      string& error) {

    string name = getLexeme(tree, tokens, identifierNode);
    int line = getLine(tree, tokens, identifierNode);

    Symbol symbol;

    symbol.name = name;
    symbol.type = type;
    symbol.line = line;

    bool registered = declareSymbol(table, symbol);

    if (!registered) {

        error = "Error semantico en linea " + to_string(line)
              + ": variable '" + name
              + "' declarada previamente";

        return false;
    }

    return true;
}

// Registra una lista de variables de una misma declaracion.
bool registerVariableList(SymbolTable& table,
                          const ParseTree& tree,
                          const vector<Token>& tokens,
                          int nodeIndex,
                          const string& type,
                          string& error) {

    if (isEmpty(tree, nodeIndex)) {
        return true;
    }

    int rule = getRule(tree, nodeIndex);

    int identifierNode;
    int nextNode;

    // Regla 1: primera variable de la lista.
    if (rule == 1) {

        int variableNode = getChild(tree, nodeIndex, 0);

        identifierNode = getChild(tree, variableNode, 0);
        nextNode = getChild(tree, nodeIndex, 1);

    // Regla 2: variable despues de una coma.
    } else if (rule == 2) {

        int variableNode = getChild(tree, nodeIndex, 1);

        identifierNode = getChild(tree, variableNode, 0);
        nextNode = getChild(tree, nodeIndex, 2);

    } else {
        return true;
    }

    bool valid = registerVariable(
        table, tree, tokens, identifierNode, type, error
    );

    if (!valid) {
        return false;
    }

    return registerVariableList(
        table, tree, tokens, nextNode, type, error
    );
}

// Recorre el arbol sintactico y registra variables globales.
// No analiza funciones, variables locales ni expresiones.
bool analyzeNode(SymbolTable& table,
                 const ParseTree& tree,
                 const vector<Token>& tokens,
                 int nodeIndex,
                 string& error) {

    if (nodeIndex < 0) {
        return true;
    }

    int rule = getRule(tree, nodeIndex);

    // Regla 92: declaracion global con tipo.
    if (rule == 92) {

        int typeNode = getChild(tree, nodeIndex, 0);
        int identifierNode = getChild(tree, nodeIndex, 1);
        int continuationNode = getChild(tree, nodeIndex, 2);

        // Regla 94: definicion de una funcion.
        // No registramos funciones ni recorremos sus cuerpos.
        if (getRule(tree, continuationNode) == 94) {
            return true;
        }

        string type = getType(tree, tokens, typeNode);

        // Registrar el primer identificador global.
        if (!registerVariable(
                table, tree, tokens,
                identifierNode, type, error)) {
            return false;
        }

        // Regla 95: continuacion de declaracion global.
        if (getRule(tree, continuationNode) == 95) {

            int variableListNode =
                getChild(tree, continuationNode, 1);

            if (!registerVariableList(
                    table, tree, tokens,
                    variableListNode, type, error)) {
                return false;
            }
        }

        return true;
    }

    // Regla 93: funcion void.
    // Se ignora completamente.
    if (rule == 93) {
        return true;
    }

    // No analizamos declaraciones locales.
    if (rule == 71) {
        return true;
    }

    // No recorremos bloques de codigo.
    if (tree.nodes[nodeIndex].symbol == "Bloque") {
        return true;
    }

    // Recorrer los hijos para encontrar otras
    // declaraciones globales.
    const ParseNode& node = tree.nodes[nodeIndex];

    for (int i = 0; i < (int)node.children.size(); i++) {

        int childNode = node.children[i];

        bool valid = analyzeNode(
            table, tree, tokens, childNode, error
        );

        if (!valid) {
            return false;
        }
    }

    return true;
}

// Funcion principal del analizador semantico.
bool verifySDT(const ParseTree& tree,
               const vector<Token>& tokens,
               string& error) {

    error.clear();

    if (tree.root < 0 || tree.root >= (int)tree.nodes.size()) {
        error = "Error semantico: arbol sintactico vacio";
        return false;
    }

    SymbolTable table;

    initializeSymbolTable(table);

    return analyzeNode(
        table, tree, tokens, tree.root, error
    );
}
