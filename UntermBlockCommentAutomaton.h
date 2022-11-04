#ifndef UDBLOCKCOMMENTAUTOMATON_H
#define UDBLOCKCOMMENTAUTOMATON_H

#include "Automaton.h"

class UDBlockCommentAutomaton : public Automaton
{
public:
    UDBlockCommentAutomaton() : Automaton(TokenType::UNDEFINED) {}  // Call the base constructor

    void S0(const std::string& input);
    void S1(const std::string& input);
    void S2(const std::string& input);
    void S3(const std::string& input);

};

#endif // UDBLOCKCOMMENTAUTOMATON_H

