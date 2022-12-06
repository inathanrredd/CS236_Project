//
// Created by nathan on 10/21/22.
//

#include "Relation.h"
#include <algorithm>

Relation::Relation() {

}
Relation::Relation(std::string str, Header* columnNames) {
    name = str;
    this->columnNames = columnNames;
}

Relation::~Relation() {

}

std::string Relation::GetName() {
    return name;
}

void Relation::setName(std::string str) {
    name = str;
}

void Relation::AddTuple(Tuple newTuple) {
    tuples.insert(newTuple);
}

std::string Relation::toString() {
    if (this->columnNames->getVecAttributes().empty()) {
        std::string s;
        return s;
    }
    std::string str = "  ";
    for (auto tuple : tuples) {
        for (unsigned i=0;i < columnNames->getVecAttributes().size();i++) {
            if (i < columnNames->getVecAttributes().size()-1) {
                str = str + columnNames->printAttributeAt(i) + "=";
                str = str + tuple.printTuple(i) + ", ";
            }
            else {
                str = str + columnNames->printAttributeAt(i) + "=";
                str = str + tuple.printTuple(i);
            }
        }
        str += "\n  ";
    }
    if (!str.empty()) {
        str.pop_back();
    }
    if (!str.empty()) {
        str.pop_back();
    }

    return str;
}

std::string Relation::toString(int num) {
    if (this->columnNames->getVecAttributes().empty()) {
        std::string s;
        return s;
    }
    std::string str = "  ";
    for (auto tuple : tuples) {
        for (unsigned i=num;i < columnNames->getVecAttributes().size();i++) {
            if (i < columnNames->getVecAttributes().size()-1) {
                str = str + columnNames->printAttributeAt(i) + "=";
                str = str + tuple.printTuple(i) + ", ";
            }
            else {
                str = str + columnNames->printAttributeAt(i) + "=";
                str = str + tuple.printTuple(i);
            }
        }
        str += "\n  ";
    }
    if (!str.empty()) {
        str.pop_back();
    }
    if (!str.empty()) {
        str.pop_back();
    }

    return str;
}

void Relation::select1(int columnIndex, std::string value, Relation rel) {
    for (auto tuple : rel.tuples) {
        std::vector<std::string> values = tuple.getTuple();
        if (values[columnIndex] == value) {
            this->AddTuple(tuple);
        }
    }
}

void Relation::select2(int columnIndex1, int columnIndex2, Relation rel) {
//    std::cout << "In select2" << std::endl;
//    Relation relation;
//    relation = relation.rename(columnNames->getVecAttributes());
    for (auto tuple : rel.tuples) {
        std::vector<std::string> values = tuple.getTuple();
        if (values[columnIndex1] == values[columnIndex2]) {
            this->AddTuple(tuple);
        }
    }
//    return relation;
}

void Relation::project(std::vector<int> columnsToProject, Relation rel) {
//    std::cout << "In project" << std::endl;
//    Relation relation;
    std::vector<std::string> newNames;
    for (auto index : columnsToProject) {
        newNames.emplace_back(rel.columnNames->getVecAttributes()[index]);
    }
//    for (auto i : newNames) {
//        std::cout << i << ", ";
//    }
//    std::cout << std::endl;
    Header* head = new Header(newNames);
    this->setColumnNames(head);
    for (auto tuple : rel.tuples) {
        std::vector<std::string> values = {};
        for (auto value : columnsToProject) {
            values.emplace_back(tuple.getTuple()[value]);
        }
        Tuple tup = Tuple(values);
        this->AddTuple(tup);
    }
//    return relation;
}

void Relation::rename(std::vector<std::string> newColumnNames) {
//    std::cout << "In rename" << std::endl;
//    Relation relation;
    Header* head = new Header(newColumnNames);
    if (head->getVecAttributes().size() == this->columnNames->getVecAttributes().size()) {
        this->setColumnNames(head);
    }
    else {
        std::cout << "The renamed columns do not match the size of the relation" << std::endl;
        std::cout << "Relation columns = " << this->columnNames->printAllAttributes() << std::endl;
        std::cout << "New columns = " << head->printAllAttributes() << std::endl;

    }
//    return relation;
}

Header *Relation::getColumnNames() {
    return columnNames;
}

std::set<Tuple> Relation::getTuples() {
    return tuples;
}

void Relation::clearTuples() {
    tuples.clear();
}

void Relation::setColumnNames(Header *cols) {
    columnNames = cols;
}

Relation Relation::join(Relation rel) {
    Header* head1 = rel.getColumnNames();
    Header* newHeader = joinHeader(head1);
    Relation newRelation = Relation("new", newHeader);
    std::set<Tuple> tupList1 = this->getTuples();
    std::set<Tuple> tupList2 = rel.getTuples();
    std::set<Tuple> newTupList;
    for (auto each:tupList1) {
        for (auto tup:tupList2) {
            if (isJoinable(each,tup,this->getColumnNames(),rel.getColumnNames())) {
                newRelation.AddTuple(combineTuples(each,tup,this->getColumnNames(),rel.getColumnNames()));
            }
        }
    }
    return newRelation;
}

Header *Relation::joinHeader(Header *head2) {
    //std::cout << "In joinHeader" << std::endl;
    std::vector<std::string> colNames = this->getColumnNames()->getVecAttributes();
    for (auto name:head2->getVecAttributes()) {
        if (std::find(colNames.begin(), colNames.end(), name) == colNames.end()) {
            colNames.emplace_back(name);
        }
    }
    Header* newHeader = new Header(colNames);
//    std::cout << newHeader->printAllAttributes() << std::endl;
    return newHeader;
}

bool Relation::isJoinable(Tuple tup1, Tuple tup2, Header *head1, Header *head2) {
    for (unsigned int i=0; i<head2->getVecAttributes().size(); i++) {
        for(unsigned int j=0; j<head1->getVecAttributes().size(); j++) {
            if (head2->getVecAttributes()[i] == head1->getVecAttributes()[j]) {
                if (tup1.getTuple()[j] != tup2.getTuple()[i]) {
                    //std::cout << "Not joinable" << std::endl;
                    return false;
                }
            }
        }
    }
    //std::cout << "Joinable" << std::endl;
    return true;
}

Tuple Relation::combineTuples(Tuple tup1, Tuple tup2, Header *head1, Header *head2) {
    std::vector<std::string> values = tup1.getTuple();
    std::vector<std::string> colNames = head1->getVecAttributes();
    for (unsigned int i=0; i<head2->getVecAttributes().size(); i++) {
        if (std::find(colNames.begin(), colNames.end(), head2->getVecAttributes()[i]) == colNames.end()) {
            values.emplace_back(tup2.getTuple()[i]);
        }
    }
    Tuple newTuple = Tuple(values);
    //std::cout << "New tuple created" << std::endl;
    return newTuple;
}