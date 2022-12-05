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
    std::vector<Predicate*> getPredicates();
    Predicate* getHeadPredicate();
};


#endif //RULE_H
