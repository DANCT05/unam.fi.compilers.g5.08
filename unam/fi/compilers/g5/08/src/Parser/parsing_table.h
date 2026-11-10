#ifndef LL1_PARSER_PARSING_TABLE_H
#define LL1_PARSER_PARSING_TABLE_H

#include <map>
#include <string>
#include <iostream>


using namespace std;

extern map<string, map<string, int>> table;

void createPredictiveTable();

void printParsingTable();

#endif // LL1_PARSER_PARSING_TABLE_H
