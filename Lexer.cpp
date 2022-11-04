#include "Lexer.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "AddAutomaton.h"
#include "CommaAutomaton.h"
#include "FactsAutomaton.h"
#include "BlockCommentAutomaton.h"
#include "IDAutomaton.h"
#include "LineCommentAutomaton.h"
#include "LPAutomaton.h"
#include "MultiplyAutomaton.h"
#include "PeriodAutomaton.h"
#include "QAutomaton.h"
#include "QueriesAutomaton.h"
#include "RPAutomaton.h"
#include "RulesAutomaton.h"
#include "SchemesAutomaton.h"
#include "StringAutomaton.h"
#include "UntermStringAutomaton.h"
#include "UntermBlockCommentAutomaton.h"
#include <cctype>
#include <iostream>

Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
    // TODO: need to clean up the memory in `automata` and `tokens`
    for (unsigned int i=0; i<tokens.size();i++) {
        delete tokens[i];
        tokens[i] = nullptr;
    }
    for (unsigned int i=0; i<automata.size();i++) {
        delete automata[i];
        automata[i] = nullptr;
    }
}

void Lexer::CreateAutomata() {
    automata.push_back(new ColonAutomaton());
    automata.push_back(new ColonDashAutomaton());
    automata.push_back(new AddAutomaton());
    automata.push_back(new CommaAutomaton());
    automata.push_back(new FactsAutomaton());
    automata.push_back(new SchemesAutomaton());
    automata.push_back(new BlockCommentAutomaton());
    automata.push_back(new LineCommentAutomaton());
    automata.push_back(new LPAutomaton());
    automata.push_back(new MultiplyAutomaton());
    automata.push_back(new PeriodAutomaton());
    automata.push_back(new QAutomaton());
    automata.push_back(new QueriesAutomaton());
    automata.push_back(new RPAutomaton());
    automata.push_back(new RulesAutomaton());
    automata.push_back(new StringAutomaton());
    automata.push_back(new IDAutomaton());
    automata.push_back(new UntermStringAutomaton());
    automata.push_back(new UDBlockCommentAutomaton());

}

void Lexer::Run(std::string& input) {

    line_num = 1;
    while (input.size() > 0) {
        maxRead = 0;
        maxAutomaton = automata[0];

        while (std::isspace(input[0])) {
            if (input[0] == '\n') {
                line_num++;
            }
            if (std::isspace(input[0])) {
                input.erase(input.begin());
            }
        }
        if (input.size()==0) {
            break;
        }

        for (unsigned int i = 0; i < automata.size(); i++ ) {
            inputRead = automata[i]->Start(input);
            if (inputRead > maxRead) {
                maxRead = inputRead;
                maxAutomaton = automata[i];
            }
        }

        if (maxRead > 0) {
            newToken = maxAutomaton->CreateToken(input.substr(0,maxRead), line_num);
            line_num += maxAutomaton->NewLinesRead();
            if (newToken->tokenType() != "COMMENT") {
                tokens.emplace_back(newToken);
            }

        } else {
            maxRead = 1;
            newToken = new Token(TokenType::UNDEFINED, input.substr(0,maxRead), line_num);
            tokens.emplace_back(newToken);
        }

        for (int i = 0; i < maxRead; i++) {
            input.erase(input.begin());
        }
    }
    newToken = new Token(TokenType::END_OF_FILE,"", line_num);
    tokens.emplace_back(newToken);
//    for (unsigned int i=0; i<tokens.size(); i++) {
//        tokens[i]->printToken();
//    }
//    std::cout << "Total Tokens = " << tokens.size();

}

std::vector<Token*> Lexer::getTokens() {
    return tokens;
}