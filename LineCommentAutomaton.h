#ifndef LINECOMMENTAUTOMATON_H
#define LINECOMMENTAUTOMATON_H

#include "Automaton.h"

class LineCommentAutomaton : public Automaton
{
public:
    LineCommentAutomaton() : Automaton(TokenType::COMMENT) {}  // Call the base constructor

    void S0(const std::string& input);
    void S1(const std::string& input);

};

#endif // LINECOMMENTAUTOMATON_H

