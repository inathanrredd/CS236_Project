#include "IDAutomaton.h"

void IDAutomaton::S0(const std::string& input) {
    if (isalpha(input[index])) {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void IDAutomaton::S1(const std::string& input) {
    if (isalnum(input[index])) {
        inputRead++;
        index++;
        S2(input);
    }
    else {
        return;
    }
}

void IDAutomaton::S2(const std::string& input) {
    if (isalnum(input[index])) {
        inputRead++;
        index++;
        S2(input);
    }
    else {
        return;
    }
}