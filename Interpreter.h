//
// Created by nathan on 11/2/22.
//

#ifndef PROJECT_0_MAIN_INTERPRETER_H
#define PROJECT_0_MAIN_INTERPRETER_H
#include "Database.h"
#include "DatalogProgram.h"


class Interpreter {
private:
    DatalogProgram* program;
    Database database;
    std::map<std::string, int> myMap;
    std::vector<int> varIndexes;
    std::vector<std::string> myVars;
    std::vector<Relation> tempRelations;

public:
    Interpreter(DatalogProgram* program);
    void interpretSchemes();
    void interpretFacts();
    void interpretQueries();
    void interpretRules();
    void interpret();
    void printAllRelations();
//    Relation* evaluatePredicate(Predicate* p);
};


#endif //PROJECT_0_MAIN_INTERPRETER_H
