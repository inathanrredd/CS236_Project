#ifndef DATALOGPROGRAM_H
#define DATALOGPROGRAM_H
#include "Rule.h"
#include <set>

class DatalogProgram {

private:
    std::vector<Predicate*> schemes;
    std::vector<Predicate*> facts;
    std::vector<Predicate*> queries;
    std::vector<Rule*> rules;
    std::set<std::string> domain;

public:
    DatalogProgram();
    ~DatalogProgram();
    std::string toString();
    int getDomainLength();
    void setSchemes(std::vector<Predicate*> vec);
    void setFacts(std::vector<Predicate*> vec, std::set<std::string> dom);
    void setQueries(std::vector<Predicate*> vec);
    void setRules(std::vector<Rule*> vec);
    std::vector<Predicate*> getSchemes();
    std::vector<Predicate*> getFacts();
    std::vector<Predicate*> getQueries();
    std::vector<Rule*> getRules();

};






#endif