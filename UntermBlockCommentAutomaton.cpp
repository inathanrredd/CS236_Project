#include "UntermBlockCommentAutomaton.h"

void UDBlockCommentAutomaton::S0(const std::string& input) {
    if (input[index] == '#') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void UDBlockCommentAutomaton::S1(const std::string& input) {
    if (input[index] == '|') {
        inputRead++;
        index++;
        S2(input);
    }
    else {
        Serr();
    }
}

void UDBlockCommentAutomaton::S2(const std::string& input) {
    if (input[index] == '\0') {
        return;
    }
    if (input[index] == '\n') {
        newLines++;
    }
    if (input[index] == '|') {
        inputRead++;
        index++;
        S3(input);
    }
    else {
        inputRead++;
        index++;
        S2(input);
    }
}

void UDBlockCommentAutomaton::S3(const std::string& input) {
    if (input[index] == '\0') {
        return;
    }
    if (input[index] == '\n') {
        newLines++;
    }
    if (input[index] == '#') {
        Serr();
    }
    else {
        inputRead++;
        index++;
        S2(input);
    }
}