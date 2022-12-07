//
// Created by nathan on 10/21/22.
//

#include "Tuple.h"

Tuple::Tuple() {

}
Tuple::Tuple(std::vector<std::string> vals) {
    values = vals;
}
Tuple::~Tuple() {

}

void Tuple::addToTuple(std::string str) {
    values.emplace_back(str);
}

std::string Tuple::printTuple(int index) {
    std::string str = values[index];
    return str;
}

bool Tuple::operator<(const Tuple &rhs) const {
    return values < rhs.values;
}

std::vector<std::string> Tuple::getTuple() {
    return values;
}

std::string Tuple::toString() {
    std::string str;
    for (auto each:this->getTuple()) {
        str += each + ", ";
    }
    return str;
}