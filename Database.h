//
// Created by nathan on 10/21/22.
//

#ifndef PROJECT_0_MAIN_DATABASE_H
#define PROJECT_0_MAIN_DATABASE_H
#include "Relation.h"
#include <map>
#include <iostream>


class Database {
private:
    std::map<std::string, Relation*> relations;

public:
    Database();
    ~Database();
    void addRelation(Relation* newRelation);
    Relation* GetRelation(std::string relationName);
    Relation GetRelationCopy(std::string relationName);
    void unite(Relation rel);
    void printAllRelations();
    int countAllTuples();
    int countTuples(std::string name);

};


#endif //PROJECT_0_MAIN_DATABASE_H
