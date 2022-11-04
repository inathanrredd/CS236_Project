#ifndef LPAUTOMATON_H
#define LPAUTOMATON_H

#include "Automaton.h"

class LPAutomaton : public Automaton
{
public:
    LPAutomaton() : Automaton(TokenType::LEFT_PAREN) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif // LPAUTOMATON_H

