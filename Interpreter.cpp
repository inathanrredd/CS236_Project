//
// Created by nathan on 11/2/22.
//

#include "Interpreter.h"
#include <algorithm>

Interpreter::Interpreter(DatalogProgram* program) {
    this->program = program;
}

void Interpreter::interpret() {
    interpretSchemes();
    interpretFacts();
    interpretRules();
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
    std::cout << "Query Evaluation" << std::endl;
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

void Interpreter::interpretRules() {
    std::cout << "Rule Evaluation" << std::endl;
    std::vector<Rule*> rules = program->getRules();
    int startCount = 0;
    int endCount = 1;
    int rulesIterations = 0;
    while(startCount != endCount) {
        startCount = endCount;
        for (auto rule: rules) {
            if (rulesIterations == 0) {
                std::cout << rule->toString() << std::endl;
            }
            for (auto pred: rule->getPredicates()) {
                myMap.clear();
                varIndexes.clear();
                myVars.clear();
                std::string name = pred->getName();
                Relation rel = database.GetRelationCopy(name);
                Relation newRel = Relation(name, rel.getColumnNames());
                bool doneSelect1 = false;
                bool doneSelect2 = false;
                for (unsigned int i = 0; i < pred->getParameters().size(); i++) {

                    if (pred->getParameters()[i]->isItConstant()) {
                        newRel.clearTuples();
                        auto it = myMap.find(pred->getParameters()[i]->getValue());
                        if (it == myMap.end()) {
                            myMap.insert(std::pair<std::string, int>(pred->getParameters()[i]->getValue(), i));
                        }
                        newRel.select1(i, pred->getParameters()[i]->getValue(), rel);
                        doneSelect1 = true;
                        rel = newRel;
                    } else {
                        auto it = myMap.find(pred->getParameters()[i]->getValue());
                        if (it == myMap.end()) {
                            myMap.insert(std::pair<std::string, int>(pred->getParameters()[i]->getValue(), i));
                            varIndexes.emplace_back(i);
                            myVars.emplace_back(pred->getParameters()[i]->getValue());
                        } else {
                            newRel.clearTuples();
                            newRel.select2(it->second, i, rel);
                            doneSelect2 = true;
                            rel = newRel;
                        }
                    }
                }
                if (!doneSelect1 && !doneSelect2) {
                    newRel = rel;
                }
                //int numTuples = newRel.getTuples().size();
                rel = newRel;
                newRel.clearTuples();
                newRel.project(varIndexes, rel);
                newRel.rename(myVars);
//                std::string str = pred->toString();
//                str.pop_back();
//                str = str + " Rule ";
//                if (numTuples > 0) {
//                    str = str + "Yes(" + std::to_string(numTuples) + ")\n";
//                } else {
//                    str = str + "No\n";
//                }
//                std::cout << str;
//                std::cout << newRel.toString();
                tempRelations.emplace_back(newRel);
            }
            Relation joinedRelation = tempRelations[0];
            for (unsigned int i = 0; i < tempRelations.size(); i++) {
                joinedRelation = joinedRelation.join(tempRelations[i]);
            }

            //std::cout << joinedRelation.toString() << std::endl;
            std::vector<Parameter *> parameters = rule->getHeadPredicate()->getParameters();
            std::vector<std::string> parameterStrings;
            for (auto each: parameters) {
                parameterStrings.emplace_back(each->getValue());
            }
            std::vector<int> columnsToProject;
            for (unsigned int i = 0; i < joinedRelation.getColumnNames()->getVecAttributes().size(); i++) {
                if (std::find(parameterStrings.begin(), parameterStrings.end(),
                              joinedRelation.getColumnNames()->getVecAttributes()[i]) != parameterStrings.end()) {
                    columnsToProject.emplace_back(i);
                }
            }
            joinedRelation.project(columnsToProject, joinedRelation);
            joinedRelation.setName(rule->getHeadPredicate()->getName());
            database.unite(joinedRelation);
        }
        endCount = database.countAllTuples();
        rulesIterations++;
    }

}
//
//Relation* Interpreter::evaluatePredicate(Predicate* p) {
//
//}

void Interpreter::printAllRelations() {
    database.printAllRelations();
}