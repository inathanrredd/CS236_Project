#ifndef UNTERMSTRINGAUTOMATON_H
#define UNTERMSTRINGAUTOMATON_H

#include "Automaton.h"

class UntermStringAutomaton : public Automaton
{
public:
    UntermStringAutomaton() : Automaton(TokenType::UNDEFINED) {}  // Call the base constructor

    void S0(const std::string& input);
    void S1(const std::string& input);
    void S2(const std::string& input);

};

#endif // UNTERMSTRINGAUTOMATON_H

