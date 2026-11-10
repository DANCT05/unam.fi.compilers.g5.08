#include "parsing_table.h"
#include "first_follow.h"
#include <stdexcept>

using namespace std;

map<string, map<string, int>> table;

void createPredictiveTable() {
    table.clear();

    int ruleNumber = 1;
    int total = productions.size();

    while (ruleNumber <= total) {
        Production production = productions[ruleNumber];
        set<string> selectedFirst = firstOfSequence(production.right);
        set<string> columns;

        // Para A -> alpha, utilizar FIRST(alpha) sin epsilon.
        auto current = selectedFirst.begin();
        while (current != selectedFirst.end()) {
            if (*current != epsilon) {
                columns.insert(*current);
            }
            current++;
        }

        // Si alpha puede ser vacia, utilizar tambien FOLLOW(A).
        if (selectedFirst.count(epsilon) > 0) {
            set<string> leftFollow = follow[production.left];
            auto terminal = leftFollow.begin();
            while (terminal != leftFollow.end()) {
                columns.insert(*terminal);
                terminal++;
            }
        }

        // Cada celda M[A, token] almacena el numero de produccion.
        auto column = columns.begin();
        while (column != columns.end()) {
            string terminal = *column;

            // Comprobar si la celda ya estaba ocupada.
            int previousRule = 0;
            if (table[production.left].count(terminal) > 0) {
                previousRule = table[production.left][terminal];
            }

            if (previousRule != 0 && previousRule != ruleNumber) {
                string message = "Conflicto LL(1) en M[";
                message = message + production.left + ", " + terminal + "]";
                message = message + " entre las reglas ";
                message = message + to_string(previousRule) + " y ";
                message = message + to_string(ruleNumber);
                throw runtime_error(message);
            }

            table[production.left][terminal] = ruleNumber;
            column++;
        }

        ruleNumber++;
    }
}


void printParsingTable() {

    cout << "\n========== PARSING TABLE ==========\n";

    for (const auto& row : table) {

        string nonTerminal = row.first;

        for (const auto& cell : row.second) {

            string terminal = cell.first;
            int production = cell.second;

            cout << "M[" << nonTerminal
                 << ", " << terminal
                 << "] = " << production << "\n";
        }
    }
}
