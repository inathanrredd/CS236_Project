#include "UntermStringAutomaton.h"

void UntermStringAutomaton::S0(const std::string& input) {
    if (input[index] == '\'') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void UntermStringAutomaton::S1(const std::string& input) {
    if (input[index] == '\0') {
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
    else if (input[index] == EOF) {
        return; //I may have to count the eof as a character and inputRead++
    }
    else {
        inputRead++;
        index++;
        S1(input);

    }
}

void UntermStringAutomaton::S2(const std::string& input) {
    if (input[index] == '\'') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}