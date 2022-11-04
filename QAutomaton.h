#ifndef QAUTOMATON_H
#define QAUTOMATON_H

#include "Automaton.h"

class QAutomaton : public Automaton
{
public:
    QAutomaton() : Automaton(TokenType::Q_MARK) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif // QAUTOMATON_H

