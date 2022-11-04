#include "LineCommentAutomaton.h"

void LineCommentAutomaton::S0(const std::string& input) {
    if (input[index] == '#') {
        inputRead++;
        index++;
        if (input[index] == '|') {
            Serr();
            return;
        }
        else {
            S1(input);
        }
    }
    else {
        Serr();
    }
}

void LineCommentAutomaton::S1(const std::string& input) {
    if (input[index] == '\n' || input[index] == '\0') {
        return;
    }

    else {
        inputRead++;
        index++;
        S1(input);
    }
}