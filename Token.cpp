#include "Token.h"
#include <iostream>

Token::Token(TokenType type, std::string description, int line) {
    // TODO: initialize all member variables
    Type = typeToString(type);
    Description = description;
    Line = line;
}

std::string Token::typeToString(TokenType type) {
    switch (type) {
        case TokenType::COLON: return "COLON"; break;
        case TokenType::COLON_DASH: return "COLON_DASH"; break;
        case TokenType::END_OF_FILE: return "EOF"; break;
        case TokenType::UNDEFINED: return "UNDEFINED"; break;
        case TokenType::ADD: return "ADD"; break;
        case TokenType::FACTS: return "FACTS"; break;
        case TokenType::COMMA: return "COMMA"; break;
        case TokenType::COMMENT: return "COMMENT"; break;
        case TokenType::ID: return "ID"; break;
        case TokenType::LEFT_PAREN: return "LEFT_PAREN"; break;
        case TokenType::MULTIPLY: return "MULTIPLY"; break;
        case TokenType::PERIOD: return "PERIOD"; break;
        case TokenType::Q_MARK: return "Q_MARK"; break;
        case TokenType::QUERIES: return "QUERIES"; break;
        case TokenType::RIGHT_PAREN: return "RIGHT_PAREN"; break;
        case TokenType::RULES: return "RULES"; break;
        case TokenType::SCHEMES: return "SCHEMES"; break;
        case TokenType::STRING: return "STRING"; break;

    }
    return "ERROR";
}

void Token::printToken() {
    std::cout << "(" << Type << ",\"" << Description << "\"," << Line << ")" << std::endl;
}

void Token::printLastToken() {
    std::cout << "(" << Type << ",\"" << Description << "\"," << Line << ")";
}

void Token::printTokenType() {
    std::cout << Type << std::endl;
}

std::string Token::getValue() {
    return Description;
}

std::string Token::tokenType() {
    return Type;
}

std::string Token::printTokenToString() {
    std::string str = "(" + Type + ",\"" + Description + "\"," + std::to_string(Line) + ")";
    return str;
}