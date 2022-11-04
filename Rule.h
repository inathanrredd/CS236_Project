//
// Created by nathan on 10/5/22.
//

#ifndef RULE_H
#define RULE_H
#include "Predicate.h"

class Rule {
private:
    Predicate* headPredicate;
    std::vector<Predicate*> predicates;

public:
    Rule();
    Rule(std::vector<Predicate*> input);
    ~Rule();
    std::string toString();
};


#endif //RULE_H
