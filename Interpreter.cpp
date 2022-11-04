//
// Created by nathan on 11/2/22.
//

#include "Interpreter.h"

Interpreter::Interpreter(DatalogProgram* program) {
    this->program = program;
}

void Interpreter::interpret() {
    interpretSchemes();
    interpretFacts();
    interpretQueries();
}

void Interpreter::interpretSchemes() {
    std::vector<Predicate*> schemes = program->getSchemes();
    for (auto scheme : schemes) {
        std::string name = scheme->getName();
        std::vector<Parameter*> params = scheme->getParameters();
        std::vector<std::string> atts = {};
        for (auto param : params) {
            atts.emplace_back(param->getValue());
        }
        Header* header = new Header(atts);
        Relation* relation = new Relation(name, header);
        database.addRelation(relation);
    }
}

void Interpreter::interpretFacts() {
    std::vector<Predicate*> facts = program->getFacts();
    for (auto fact : facts) {
        std::string name = fact->getName();
        std::vector<Parameter*> params = fact->getParameters();
        std::vector<std::string> values = {};
        for (auto param : params) {
            values.emplace_back(param->getValue());
        }
        Tuple tuple = Tuple(values);
        Relation* relation = database.GetRelation(name);
        relation->AddTuple(tuple);
    }
}

void Interpreter::interpretQueries() {
    std::vector<Predicate*> queries = program->getQueries();
    for (auto query : queries) {
        myMap.clear();
        varIndexes.clear();
        myVars.clear();
        std::string name = query->getName();
        Relation rel = database.GetRelationCopy(name);
        Relation newRel = Relation(name, rel.getColumnNames());
        bool doneSelect1 = false;
        bool doneSelect2 = false;
        for (unsigned int i=0; i<query->getParameters().size();i++) {

            if (query->getParameters()[i]->isItConstant()) {
                newRel.clearTuples();
                auto it = myMap.find(query->getParameters()[i]->getValue());
                if (it == myMap.end()) {
                    myMap.insert(std::pair<std::string,int>(query->getParameters()[i]->getValue(),i));
                }
                newRel.select1(i,query->getParameters()[i]->getValue(), rel);
                doneSelect1 = true;
                rel = newRel;
            }
            else {
                auto it = myMap.find(query->getParameters()[i]->getValue());
                if (it == myMap.end()) {
                    myMap.insert(std::pair<std::string,int>(query->getParameters()[i]->getValue(),i));
                    varIndexes.emplace_back(i);
                    myVars.emplace_back(query->getParameters()[i]->getValue());
                }
                else {
                    newRel.clearTuples();
                    newRel.select2(it->second,i,rel);
                    doneSelect2=true;
                    rel = newRel;
                }
            }
        }
        if (!doneSelect1 && !doneSelect2) {
            newRel = rel;
        }
        int numTuples = newRel.getTuples().size();
        rel = newRel;
        newRel.clearTuples();
        newRel.project(varIndexes, rel);
        newRel.rename(myVars);
        std::string str = query->toString();
        str.pop_back();
        str = str + "? ";
        if (numTuples > 0) {
            str = str + "Yes(" + std::to_string(numTuples) + ")\n";
        }
        else {
            str = str + "No\n";
        }
        std::cout << str;
        std::cout << newRel.toString();
    }
}
//
//Relation* Interpreter::evaluatePredicate(Predicate* p) {
//
//}

void Interpreter::printAllRelations() {
    database.printAllRelations();
}