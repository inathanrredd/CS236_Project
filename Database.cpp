//
// Created by nathan on 10/21/22.
//

#include "Database.h"

Database::Database() {

}
Database::~Database() {

}

void Database::addRelation(Relation* newRelation) {
    relations.insert({newRelation->GetName(), newRelation});
}

Relation* Database::GetRelation(std::string relationName) {
    auto it = relations.find(relationName);
    return it->second;
}

Relation Database::GetRelationCopy(std::string relationName) {
    auto it = relations.find(relationName);
    Relation rel = Relation(it->second->GetName(),it->second->getColumnNames());
    for (auto tuple : it->second->getTuples()) {
        rel.AddTuple(tuple);
    }
    return rel;
}

void Database::printAllRelations() {
    std::string str;
    for (auto relation : relations) {
        str = str + relation.second->toString();
        str += "\n";
    }
    std::cout << str;
}