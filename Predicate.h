#ifndef PREDICATE_H
#define PREDICATE_H
#include "Parameter.h"
#include <string>
#include <vector>

class Predicate {

private:
    std::string name;
    std::vector<Parameter*> parameters;

public:
    Predicate();
    Predicate(std::string str);
    ~Predicate();
    std::string toString();
    void addParameter(std::string str);
    void addParameter(std::string str, bool constant);
    std::string getName();
    std::vector<Parameter*> getParameters();
};

#endif