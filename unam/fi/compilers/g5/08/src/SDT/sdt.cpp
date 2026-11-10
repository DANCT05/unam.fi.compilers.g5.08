#include "sdt.h"
#include "symbol_table.h"

using namespace std;

// Devuelve el indice de un hijo; -1 significa que no existe.
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

int getRule(const ParseTree& tree, int nodeIndex) {
    if (nodeIndex < 0 || nodeIndex >= (int)tree.nodes.size()) {
        return 0;
    }
    return tree.nodes[nodeIndex].ruleNumber;
}

string getLexeme(const ParseTree& tree,
                 const vector<Token>& tokens, int nodeIndex) {
    if (nodeIndex < 0 || nodeIndex >= (int)tree.nodes.size()) {
        return "";
    }
    int index = tree.nodes[nodeIndex].tokenIndex;
    if (index < 0 || index >= (int)tokens.size()) {
        return "";
    }
    return tokens[index].lexeme;
}

int getLine(const ParseTree& tree,
            const vector<Token>& tokens, int nodeIndex) {
    if (nodeIndex < 0 || nodeIndex >= (int)tree.nodes.size()) {
        return 1;
    }
    int index = tree.nodes[nodeIndex].tokenIndex;
    if (index < 0 || index >= (int)tokens.size()) {
        return 1;
    }
    return tokens[index].line;
}

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

string getType(const ParseTree& tree,
               const vector<Token>& tokens, int nodeIndex) {
    if (nodeIndex < 0 || nodeIndex >= (int)tree.nodes.size()) {
        return "";
    }
    string symbol = tree.nodes[nodeIndex].symbol;
    if (symbol == "Tipo" || symbol == "TipoFuncion") {
        return getType(tree, tokens, getChild(tree, nodeIndex, 0));
    }
    return getLexeme(tree, tokens, nodeIndex);
}

// Politica de tipos: int->float se permite, float->int se rechaza.
bool compatibleTypes(const string& declared, const string& value) {
    if (declared == value) {
        return true;
    }
    if (declared == "float" && value == "int") {
        return true;
    }
    return false;
}

bool numericType(const string& type) {
    return type == "int" || type == "float";
}

// Produce un mensaje de error para un nodo que tiene un token valido.
string semanticError(const ParseTree& tree, const vector<Token>& tokens,
                     int nodeIndex, const string& detail) {
    return "Error semantico en linea "
         + to_string(getLine(tree, tokens, nodeIndex)) + ": " + detail;
}

// Declaracion anticipada: estas funciones se llaman mutuamente.
string inferExpressionType(SymbolTable& table, const ParseTree& tree,
                           const vector<Token>& tokens, int nodeIndex,
                           string& error);

// Consume los sufijos de operadores +, -, * y /.
string inferArithmeticTail(SymbolTable& table, const ParseTree& tree,
                           const vector<Token>& tokens, int nodeIndex,
                           const string& baseType, string& error) {
    if (error != "" || nodeIndex < 0 || isEmpty(tree, nodeIndex)) {
        return baseType;
    }
    int rule = getRule(tree, nodeIndex);
    if (rule == 45) {
        string afterTerm = inferArithmeticTail(
            table, tree, tokens, getChild(tree, nodeIndex, 0), baseType, error);
        if (error != "") {
            return "";
        }
        return inferArithmeticTail(
            table, tree, tokens, getChild(tree, nodeIndex, 1), afterTerm, error);
    }
    if (rule == 24 || rule == 25 || rule == 28 || rule == 29) {
        string rightType = inferExpressionType(
            table, tree, tokens, getChild(tree, nodeIndex, 1), error);
        if (error != "") {
            return "";
        }
        if (!numericType(baseType) || !numericType(rightType)) {
            error = semanticError(tree, tokens, getChild(tree, nodeIndex, 0),
                                  "operador aritmetico requiere tipos numericos ("
                                  + baseType + " y " + rightType + ")");
            return "";
        }
        string combined = "int";
        if (baseType == "float" || rightType == "float") {
            combined = "float";
        }
        return inferArithmeticTail(
            table, tree, tokens, getChild(tree, nodeIndex, 2), combined, error);
    }
    error = "Error semantico: continuacion aritmetica desconocida";
    return "";
}

// Calcula un tipo sintetizado para una expresion de la gramatica.
string inferExpressionType(SymbolTable& table, const ParseTree& tree,
                           const vector<Token>& tokens, int nodeIndex,
                           string& error) {
    if (error != "") {
        return "";
    }
    if (nodeIndex < 0 || nodeIndex >= (int)tree.nodes.size()) {
        error = "Error semantico: nodo de expresion invalido";
        return "";
    }

    string symbol = tree.nodes[nodeIndex].symbol;
    int rule = getRule(tree, nodeIndex);

    // Tipos inferidos directamente del lexer.
    if (symbol == "TOKEN_CONSTANT") {
        string value = getLexeme(tree, tokens, nodeIndex);
        if (value.find_first_of(".eE") != string::npos) {
            return "float";
        }
        return "int";
    }
    if (symbol == "TOKEN_LITERAL") {
        return "string";
    }
    if (symbol == "TOKEN_IDENTIFIER") {
        string name = getLexeme(tree, tokens, nodeIndex);
        auto found = table.symbols.find(name);
        if (found == table.symbols.end()) {
            error = semanticError(tree, tokens, nodeIndex,
                                  "variable '" + name + "' no declarada");
            return "";
        }
        return found->second.type;
    }

    // Expresion -> Termino ExpresionPrima
    // Termino -> Unario TerminoPrima
    if (rule == 23 || rule == 27) {
        string base = inferExpressionType(
            table, tree, tokens, getChild(tree, nodeIndex, 0), error);
        if (error != "") {
            return "";
        }
        return inferArithmeticTail(
            table, tree, tokens, getChild(tree, nodeIndex, 1), base, error);
    }

    // Unario -> (+|-) Unario
    // InicioSinId -> (+|-) Unario
    if (rule == 31 || rule == 32 || rule == 49 || rule == 50) {
        string valueType = inferExpressionType(
            table, tree, tokens, getChild(tree, nodeIndex, 1), error);
        if (error == "" && !numericType(valueType)) {
            error = semanticError(tree, tokens, getChild(tree, nodeIndex, 0),
                                  "operador unario requiere un tipo numerico");
            return "";
        }
        return valueType;
    }

    // Unario -> Primario
    if (rule == 33) {
        return inferExpressionType(
            table, tree, tokens, getChild(tree, nodeIndex, 0), error);
    }

    // Primario o InicioSinId con numero/cadena.
    if (rule == 34 || rule == 35 || rule == 46 || rule == 47) {
        return inferExpressionType(
            table, tree, tokens, getChild(tree, nodeIndex, 0), error);
    }

    // Primario o InicioSinId con parentesis.
    if (rule == 37 || rule == 48) {
        return inferExpressionType(
            table, tree, tokens, getChild(tree, nodeIndex, 1), error);
    }

    // Primario -> id LlamadaFuncionPrima
    if (rule == 36) {
        int suffix = getChild(tree, nodeIndex, 1);
        if (getRule(tree, suffix) == 38) {
            error = "Error semantico: llamadas a funcion no soportadas "
                    "por este SDT simplificado";
            return "";
        }
        return inferExpressionType(
            table, tree, tokens, getChild(tree, nodeIndex, 0), error);
    }

    // Asignacion -> id ContinuarAsignacion
    if (rule == 41) {
        int suffix = getChild(tree, nodeIndex, 1);
        if (getRule(tree, suffix) == 43) {
            error = "Error semantico: asignaciones encadenadas no soportadas";
            return "";
        }
        if (getRule(tree, suffix) != 44) {
            error = "Error semantico: asignacion inesperada";
            return "";
        }
        int callSuffix = getChild(tree, suffix, 0);
        if (getRule(tree, callSuffix) == 38) {
            error = "Error semantico: llamadas a funcion no soportadas "
                    "por este SDT simplificado";
            return "";
        }
        string base = inferExpressionType(
            table, tree, tokens, getChild(tree, nodeIndex, 0), error);
        if (error != "") {
            return "";
        }
        return inferArithmeticTail(
            table, tree, tokens, getChild(tree, suffix, 1), base, error);
    }

    // Asignacion -> InicioSinId ContinuarExpresion
    if (rule == 42) {
        string base = inferExpressionType(
            table, tree, tokens, getChild(tree, nodeIndex, 0), error);
        if (error != "") {
            return "";
        }
        return inferArithmeticTail(
            table, tree, tokens, getChild(tree, nodeIndex, 1), base, error);
    }

    error = "Error semantico: expresion no soportada (regla "
          + to_string(rule) + ", nodo " + symbol + ")";
    return "";
}

// Compara el tipo inferido de la inicializacion con el tipo declarado.
bool validateInitialization(SymbolTable& table, const ParseTree& tree,
                            const vector<Token>& tokens, int identifierNode,
                            int initNode, const string& declaredType,
                            string& error) {
    if (isEmpty(tree, initNode)) {
        return true; // Por ejemplo, int x;
    }
    if (getRule(tree, initNode) != 5) {
        error = "Error semantico: inicializacion inesperada";
        return false;
    }
    int assignmentNode = getChild(tree, initNode, 1);
    string valueType = inferExpressionType(
        table, tree, tokens, assignmentNode, error);
    if (error != "") {
        return false;
    }
    if (!compatibleTypes(declaredType, valueType)) {
        string name = getLexeme(tree, tokens, identifierNode);
        error = semanticError(tree, tokens, identifierNode,
                              "inicializacion incompatible de '" + name
                              + "': se esperaba " + declaredType
                              + ", se obtuvo " + valueType);
        return false;
    }
    return true;
}

bool registerVariable(SymbolTable& table, const ParseTree& tree,
                      const vector<Token>& tokens, int identifierNode,
                      const string& type, string& error) {
    string name = getLexeme(tree, tokens, identifierNode);
    int line = getLine(tree, tokens, identifierNode);
    Symbol symbol;
    symbol.name = name;
    symbol.type = type;
    symbol.line = line;
    if (!declareSymbol(table, symbol)) {
        error = semanticError(tree, tokens, identifierNode,
                              "variable '" + name + "' declarada previamente");
        return false;
    }
    return true;
}

bool registerVariableList(SymbolTable& table, const ParseTree& tree,
                          const vector<Token>& tokens, int nodeIndex,
                          const string& type, string& error) {
    if (isEmpty(tree, nodeIndex)) {
        return true;
    }
    int rule = getRule(tree, nodeIndex);
    int variableNode = -1;
    int nextNode = -1;
    if (rule == 1) {
        variableNode = getChild(tree, nodeIndex, 0);
        nextNode = getChild(tree, nodeIndex, 1);
    } else if (rule == 2) {
        variableNode = getChild(tree, nodeIndex, 1);
        nextNode = getChild(tree, nodeIndex, 2);
    } else {
        error = "Error semantico: lista de variables inesperada";
        return false;
    }

    int identifierNode = getChild(tree, variableNode, 0);
    int initNode = getChild(tree, variableNode, 1);

    if (!registerVariable(table, tree, tokens, identifierNode, type, error)) {
        return false;
    }
    if (!validateInitialization(table, tree, tokens,
                                identifierNode, initNode, type, error)) {
        return false;
    }
    return registerVariableList(table, tree, tokens, nextNode, type, error);
}

// Recorre solo declaraciones globales. Ignora funciones y bloques locales.
bool analyzeNode(SymbolTable& table, const ParseTree& tree,
                 const vector<Token>& tokens, int nodeIndex, string& error) {
    if (nodeIndex < 0) {
        return true;
    }
    int rule = getRule(tree, nodeIndex);
    if (rule == 92) {
        int typeNode = getChild(tree, nodeIndex, 0);
        int identifierNode = getChild(tree, nodeIndex, 1);
        int continuationNode = getChild(tree, nodeIndex, 2);
        if (getRule(tree, continuationNode) == 94) {
            return true; // Funcion con tipo de retorno.
        }
        string type = getType(tree, tokens, typeNode);
        if (!registerVariable(table, tree, tokens,
                              identifierNode, type, error)) {
            return false;
        }
        if (getRule(tree, continuationNode) == 95) {
            int initNode = getChild(tree, continuationNode, 0);
            int variableListNode = getChild(tree, continuationNode, 1);
            if (!validateInitialization(table, tree, tokens,
                                        identifierNode, initNode, type, error)) {
                return false;
            }
            if (!registerVariableList(table, tree, tokens,
                                      variableListNode, type, error)) {
                return false;
            }
        }
        return true;
    }
    if (rule == 93 || rule == 71 || tree.nodes[nodeIndex].symbol == "Bloque") {
        return true;
    }
    const ParseNode& node = tree.nodes[nodeIndex];
    for (int i = 0; i < (int)node.children.size(); i++) {
        if (!analyzeNode(table, tree, tokens, node.children[i], error)) {
            return false;
        }
    }
    return true;
}

bool verifySDT(const ParseTree& tree, const vector<Token>& tokens,
               string& error) {
    error.clear();
    if (tree.root < 0 || tree.root >= (int)tree.nodes.size()) {
        error = "Error semantico: arbol sintactico vacio";
        return false;
    }
    SymbolTable table;
    initializeSymbolTable(table);
    return analyzeNode(table, tree, tokens, tree.root, error);
}
