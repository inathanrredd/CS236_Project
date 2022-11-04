//
// Created by nathan on 10/5/22.
//

#ifndef PARAMETER_H
#define PARAMETER_H
#include <string>


class Parameter {

private:
    std::string value;
    bool isConstant;


public:
    Parameter(std::string str);
    Parameter(std::string str, bool constant);
    ~Parameter();
    std::string getValue();
    bool isItConstant();

};


#endif //PARAMETER_H
