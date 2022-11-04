#include "StringAutomaton.h"

void StringAutomaton::S0(const std::string& input) {
    if (input[index] == '\'') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void StringAutomaton::S1(const std::string& input) {
    if (input[index] == '\0') {
        Serr();
        return;
    }
    if (input[index] == '\n') {
        newLines++;
    }
    if (input[index] == '\'') {
        inputRead++;
        index++;
        S2(input);
    }
    else {
        inputRead++;
        index++;
        S1(input);
    }
}

void StringAutomaton::S2(const std::string& input) {
    if (input[index] == '\0') {
        Serr();
        return;
    }
    if (input[index] == '\'') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        return;
    }
}