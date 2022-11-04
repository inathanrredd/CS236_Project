#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"
#include <fstream>
#include <iostream>

int main(int argc, char** argv) {

    Lexer* lexer = new Lexer();


    std::string input;
    std::string str;
    std::string filename = argv[1];
    std::ifstream inFile;
    inFile.open(filename);
    if (!inFile.is_open()) {
        std::cout << "Could not open file" << std::endl;
    }
    else {
        while (getline(inFile, str)) {
            input += str;
            input += "\n";
        }
    }
    inFile.close();
    lexer->Run(input);
    std::vector<Token*> tokenOutput = lexer->getTokens();
    Parser* parser = new Parser(tokenOutput);
    parser->Parse();
    Interpreter* interpreter = new Interpreter(parser->getProgram());
    interpreter->interpret();
    delete lexer;
    delete parser;
    delete interpreter;

    return 0;
}