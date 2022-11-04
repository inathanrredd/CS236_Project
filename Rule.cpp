//
// Created by nathan on 10/5/22.
//

#include "Rule.h"

Rule::Rule() {
    headPredicate = NULL;
    predicates = {};
}
Rule::Rule(std::vector<Predicate*> input) {
    headPredicate = input[0];
    input.erase(input.begin());
    predicates = input;
}
Rule::~Rule() {
    headPredicate = NULL;
    while (!predicates.empty()) {
        predicates.erase(predicates.begin());
    }
}
std::string Rule::toString() {
    std::string str = headPredicate->toString();
    str.pop_back();
    str = str + " :- ";
    for (auto each:predicates) {
        str = str + each->toString();
        str.pop_back();
        str += ",";
    }
    str.pop_back();
    str += ".";
    return str;
}