#include "DatalogProgram.h"
#include <iostream>

DatalogProgram::DatalogProgram() {
    schemes = {};
    facts = {};
    queries = {};
    rules = {};
    domain = {};
}

DatalogProgram::~DatalogProgram(){

}
std::string DatalogProgram::toString() {
    std::string str = "Schemes(" + std::to_string(schemes.size()) + "):\n";
    for (auto each:schemes) {
        str = str + "  " + each->toString();
        str.pop_back();
        str += "\n";
    }
    str = str + "Facts(" + std::to_string(facts.size()) + "):\n";
    for (auto each:facts) {
        str = str + "  " + each->toString() + "\n";
    }
    str = str + "Rules(" + std::to_string(rules.size()) + "):\n";
    for (auto each:rules) {
        str = str + "  " + each->toString() + "\n";
    }
    str = str + "Queries(" + std::to_string(queries.size()) + "):\n";
    for (auto each:queries) {
        str = str + "  " + each->toString();
        str.pop_back();
        str = str + "?\n";
    }
    str = str + "Domain(" + std::to_string(domain.size()) + "):\n";
    for (auto each:domain) {
        str = str + "  " + each + "\n";
    }
    str.pop_back();
    return str;
}

int DatalogProgram::getDomainLength() {
    return domain.size();
}

void DatalogProgram::setSchemes(std::vector<Predicate*> vec) {
    schemes = vec;
}

void DatalogProgram::setFacts(std::vector<Predicate*> vec, std::set<std::string> dom) {
    facts = vec;
    domain = dom;
}

void DatalogProgram::setQueries(std::vector<Predicate*> vec) {
    queries = vec;
}

void DatalogProgram::setRules(std::vector<Rule*> vec) {
    rules = vec;
}

std::vector<Predicate*> DatalogProgram::getSchemes() {
    return schemes;
}

std::vector<Predicate*> DatalogProgram::getFacts() {
    return facts;
}

std::vector<Predicate*> DatalogProgram::getQueries() {
    return queries;
}
