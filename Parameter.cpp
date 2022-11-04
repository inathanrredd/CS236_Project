//
// Created by nathan on 10/5/22.
//

#include "Parameter.h"
Parameter::Parameter(std::string str) {
    value = str;
}
Parameter::Parameter(std::string str, bool constant) {
    value = str;
    isConstant = constant;
}
Parameter::~Parameter() {

}
std::string Parameter::getValue() {
    return value;
}

bool Parameter::isItConstant() {
    return isConstant;
}