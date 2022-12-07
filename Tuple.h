//
// Created by nathan on 10/21/22.
//

#ifndef PROJECT_0_MAIN_TUPLE_H
#define PROJECT_0_MAIN_TUPLE_H
#include <vector>
#include <string>


class Tuple {
private:
    std::vector<std::string> values;

public:
    Tuple();
    Tuple(std::vector<std::string> vals);
    ~Tuple();
    void addToTuple(std::string str);
    std::string printTuple(int index);
    bool operator< (const Tuple &rhs) const;
    std::vector<std::string> getTuple();
    std::string toString();


};


#endif //PROJECT_0_MAIN_TUPLE_H
