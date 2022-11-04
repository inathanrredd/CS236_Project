#ifndef RPAUTOMATON_H
#define RPAUTOMATON_H

#include "Automaton.h"

class RPAutomaton : public Automaton
{
public:
    RPAutomaton() : Automaton(TokenType::RIGHT_PAREN) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif // RPAUTOMATON_H

