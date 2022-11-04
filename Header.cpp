//
// Created by nathan on 10/21/22.
//

#include "Header.h"
Header::Header() {

}
Header::Header(std::vector<std::string> atts) {
    attributes = atts;
}

Header::~Header() {

}

std::vector<std::string> Header::getVecAttributes() {
    return attributes;
}

std::string Header::printAllAttributes() {
    std::string str;
    for (auto att : attributes) {
        str += att + ", ";
    }
    return str;
}

std::string Header::printAttributeAt(int index) {
    return attributes[index];
}

void Header::setAllAttributes(std::vector<std::string> vec) {
    attributes = vec;
}

void Header::setAttributeAt(int index) {

}