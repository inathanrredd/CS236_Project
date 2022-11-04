#ifndef TOKEN_H
#define TOKEN_H
#include <string>

enum class TokenType {
    COLON,
    COLON_DASH,
    ADD,
    FACTS,
    COMMA,
    COMMENT,
    ID,
    LEFT_PAREN,
    MULTIPLY,
    PERIOD,
    Q_MARK,
    QUERIES,
    RIGHT_PAREN,
    RULES,
    SCHEMES,
    STRING,
    UNDEFINED,
    END_OF_FILE
};

class Token
{
private:
    std::string Type;
    std::string Description;
    int Line;

public:
    Token(TokenType type, std::string description, int line);

    std::string typeToString(TokenType type);

    void printToken();
    void printLastToken();
    void printTokenType();
    std::string tokenType();
    std::string printTokenToString();
    std::string getValue();
};

#endif // TOKEN_H

