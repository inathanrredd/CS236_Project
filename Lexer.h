#ifndef LEXER_H
#define LEXER_H
#include <vector>
#include "Automaton.h"
#include "Token.h"

class Lexer
{
private:
    std::vector<Automaton*> automata;
    std::vector<Token*> tokens;

    void CreateAutomata();

    // TODO: add any other private methods here (if needed)
    int line_num;
    int maxRead;
    Automaton* maxAutomaton;
    int inputRead;
    Token* newToken;

public:
    Lexer();
    ~Lexer();

    void Run(std::string& input);
    std::vector<Token*> getTokens();
    
    // TODO: add other public methods here

};

#endif // LEXER_H

