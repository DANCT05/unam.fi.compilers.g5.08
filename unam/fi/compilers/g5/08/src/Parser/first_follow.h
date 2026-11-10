#ifndef LL1_PARSER_FIRST_FOLLOW_H
#define LL1_PARSER_FIRST_FOLLOW_H

#include <map>
#include <set>
#include <string>
#include <iostream>

#include "grammar.h"

// FIRST y FOLLOW de cada no terminal.
extern map<string, set<string>> first;
extern map<string, set<string>> follow;

set<string> firstOfSequence(const vector<string>& symbols);
void calculateFirst();
void calculateFollow();

void printFirst(const map<string, set<string>>& first);
void printFollow(const map<string, set<string>>& follow);

#endif // LL1_PARSER_FIRST_FOLLOW_H
