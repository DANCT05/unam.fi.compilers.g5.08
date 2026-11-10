#include "parser.h"
#include "grammar.h"
#include "first_follow.h"
#include "parsing_table.h"

using namespace std;

string currentTerminal(const vector<Token>& tokens, int position) {
    if (position >= (int)tokens.size()) return "TOKEN_EOF";
    return tokenSymbol(tokens[position]);
}

string currentLexeme(const vector<Token>& tokens, int position) {
    if (position >= (int)tokens.size()) return "$";
    if (tokens[position].type == TOKEN_EOF) return "$";
    return tokens[position].lexeme;
}

int currentLine(const vector<Token>& tokens, int position) {
    if (tokens.empty()) return 1;
    if (position >= (int)tokens.size()) return tokens.back().line;
    return tokens[position].line;
}

bool syntaxError(const vector<Token>& tokens, int position, string& error,
                 const string& expected, const string& context) {
    error = "Error sintactico en linea " + to_string(currentLine(tokens, position));
    error += ": se encontro '" + currentLexeme(tokens, position) + "'";
    error += " (" + currentTerminal(tokens, position) + ")";
    error += ". Se esperaba: " + expected;
    if (context != "") error += ". Contexto: " + context;
    return false;
}

string productionText(int number, const Production& production) {
    string result = "[" + to_string(number) + "] " + production.left + " ->";
    if (production.right.empty()) return result + " epsilon";
    for (const string& symbol : production.right) result += " " + symbol;
    return result;
}

struct StackEntry {
    string symbol;
    int nodeIndex;
};

bool analyzeTokens(const vector<Token>& tokens, string& error,
                   ParseTree& tree, ostream* trace) {
    tree.nodes.clear();
    tree.root = -1;
    error.clear();

    for (const Token& token : tokens) {
        if (token.type == TOKEN_ERROR) {
            error = "Error lexico en linea " + to_string(token.line);
            error += ": '" + token.lexeme + "'";
            return false;
        }
    }

    ParseNode root;
    root.symbol = initialSymbol;
    tree.nodes.push_back(root);
    tree.root = 0;

    vector<StackEntry> stack;
    stack.push_back({"TOKEN_EOF", -1});
    stack.push_back({initialSymbol, tree.root});

    int position = 0;

    while (!stack.empty()) {
        StackEntry item = stack.back();
        stack.pop_back();

        string top = item.symbol;
        string terminal = currentTerminal(tokens, position);

        if (terminals.count(top) > 0) {
            if (top != terminal) {
                return syntaxError(tokens, position, error, top,
                                   "coincidencia de terminales");
            }

            if (item.nodeIndex >= 0) {
                tree.nodes[item.nodeIndex].tokenIndex = position;
            }
            if (trace != nullptr) {
                *trace << "Consumir " << terminal << " ('"
                       << currentLexeme(tokens, position) << "')\n";
            }

            if (top == "TOKEN_EOF") {
                // Si el EOF es explicito, no deben existir tokens posteriores.
                if (position < (int)tokens.size() &&
                    position + 1 < (int)tokens.size()) {
                    return syntaxError(tokens, position + 1, error,
                                       "fin de archivo", "tokens despues de EOF");
                }
                return true;
            }

            position++;
            continue;
        }

        if (nonterminals.count(top) == 0) {
            return syntaxError(tokens, position, error,
                               "simbolo valido de la gramatica", top);
        }

        int ruleNumber = 0;
        if (table[top].count(terminal) > 0) ruleNumber = table[top][terminal];

        if (ruleNumber == 0) {
            string expected;
            for (const auto& column : table[top]) {
                if (expected != "") expected += ", ";
                expected += column.first;
            }
            if (expected == "") expected = "ningun terminal valido";
            return syntaxError(tokens, position, error, expected, top);
        }

        const Production& production = productions[ruleNumber];
        tree.nodes[item.nodeIndex].ruleNumber = ruleNumber;

        if (trace != nullptr) {
            *trace << productionText(ruleNumber, production) << '\n';
        }

        if (production.right.empty()) {
            ParseNode empty;
            empty.symbol = epsilon;
            int emptyIndex = (int)tree.nodes.size();
            tree.nodes.push_back(empty);
            tree.nodes[item.nodeIndex].children.push_back(emptyIndex);
            continue;
        }

        vector<int> childIndices;
        for (const string& symbol : production.right) {
            ParseNode child;
            child.symbol = symbol;
            int childIndex = (int)tree.nodes.size();
            tree.nodes.push_back(child);
            childIndices.push_back(childIndex);
        }
        tree.nodes[item.nodeIndex].children = childIndices;

        for (int j = (int)production.right.size() - 1; j >= 0; j--) {
            stack.push_back({production.right[j], childIndices[j]});
        }
    }

    return syntaxError(tokens, position, error, "TOKEN_EOF", "pila vacia");
}

bool parse(const vector<Token>& tokens, string& error,
           ParseTree& tree, ostream* trace) {

    loadGrammar();
    calculateFirst();
    calculateFollow();
    createPredictiveTable();

    //printFirst(first);
    //printFollow(follow);
    //printParsingTable();

    return analyzeTokens(tokens, error, tree, trace);
}

bool parse(const vector<Token>& tokens, string& error, ostream* trace) {
    ParseTree tree;
    return parse(tokens, error, tree, trace);
}
