#include "first_follow.h"
#include <stdexcept>

using namespace std;

map<string, set<string>> first;
map<string, set<string>> follow;

set<string> firstOfSequence(const vector<string>& symbols) {
    set<string> result;
    bool allEmpty = true;
    int i = 0;
    int total = symbols.size();

    while (i < total) {
        string symbol = symbols[i];

        // Si encontramos un terminal, se agrega y terminamos.
        if (terminals.count(symbol) > 0) {
            result.insert(symbol);
            allEmpty = false;
            break;
        }

        // Los simbolos de la derecha deben existir en la gramatica.
        if (nonterminals.count(symbol) == 0) {
            throw runtime_error("Simbolo desconocido: " + symbol);
        }

        // Copiar FIRST(symbol), pero sin epsilon.
        set<string> currentFirst = first[symbol];
        auto current = currentFirst.begin();

        while (current != currentFirst.end()) {
            string terminal = *current;
            if (terminal != epsilon) {
                result.insert(terminal);
            }
            current++;
        }

        // Si no produce epsilon, no podemos pasar al siguiente simbolo.
        if (currentFirst.count(epsilon) == 0) {
            allEmpty = false;
            break;
        }

        i++;
    }

    if (allEmpty) {
        result.insert(epsilon);
    }

    return result;
}

void calculateFirst() {
    first.clear();

    auto nonterminal = nonterminals.begin();
    while (nonterminal != nonterminals.end()) {
        first[*nonterminal] = set<string>();
        nonterminal++;
    }

    bool changed = true;

    while (changed) {
        changed = false;

        int ruleNumber = 1;
        int total = productions.size();

        while (ruleNumber <= total) {
            Production production = productions[ruleNumber];
            set<string> calculated = firstOfSequence(production.right);
            int oldSize = first[production.left].size();

            auto terminal = calculated.begin();
            while (terminal != calculated.end()) {
                first[production.left].insert(*terminal);
                terminal++;
            }

            int newSize = first[production.left].size();
            if (newSize != oldSize) {
                changed = true;
            }

            ruleNumber++;
        }
    }
}

void calculateFollow() {
    follow.clear();

    auto nonterminal = nonterminals.begin();
    while (nonterminal != nonterminals.end()) {
        follow[*nonterminal] = set<string>();
        nonterminal++;
    }

    follow[initialSymbol].insert("TOKEN_EOF");
    bool changed = true;

    while (changed) {
        changed = false;

        int ruleNumber = 1;
        int total = productions.size();

        while (ruleNumber <= total) {
            Production production = productions[ruleNumber];
            int i = 0;
            int rightSize = production.right.size();

            while (i < rightSize) {
                string symbol = production.right[i];

                if (nonterminals.count(symbol) > 0) {
                    // Guardamos todos los simbolos que estan despues.
                    vector<string> followingSymbols;
                    int j = i + 1;
                    while (j < rightSize) {
                        followingSymbols.push_back(production.right[j]);
                        j++;
                    }

                    set<string> followingFirst = firstOfSequence(followingSymbols);
                    int oldSize = follow[symbol].size();

                    // FIRST de lo que sigue, sin epsilon.
                    auto terminal = followingFirst.begin();
                    while (terminal != followingFirst.end()) {
                        if (*terminal != epsilon) {
                            follow[symbol].insert(*terminal);
                        }
                        terminal++;
                    }

                    // Si lo siguiente puede desaparecer, copiamos FOLLOW(A).
                    if (followingFirst.count(epsilon) > 0) {
                        set<string> leftFollow = follow[production.left];
                        auto current = leftFollow.begin();
                        while (current != leftFollow.end()) {
                            follow[symbol].insert(*current);
                            current++;
                        }
                    }

                    int newSize = follow[symbol].size();
                    if (newSize != oldSize) {
                        changed = true;
                    }
                }

                i++;
            }

            ruleNumber++;
        }
    }
}

void printFirst(const map<string, set<string>>& first) {

    cout << "\n========== FIRST ==========\n";

    for (const auto& entry : first) {

        cout << "FIRST(" << entry.first << ") = { ";

        for (const string& symbol : entry.second) {
            cout << symbol << " ";
        }

        cout << "}\n";
    }
}

void printFollow(const map<string, set<string>>& follow) {

    cout << "\n========== FOLLOW ==========\n";

    for (const auto& entry : follow) {

        cout << "FOLLOW(" << entry.first << ") = { ";

        for (const string& symbol : entry.second) {
            cout << symbol << " ";
        }

        cout << "}\n";
    }
}

