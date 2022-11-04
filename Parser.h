#ifndef PARSER_H
#define PARSER_H
#include <vector>
#include "Token.h"
#include "DatalogProgram.h"


class Parser
{
private:
    std::vector<Token*> tokens;
    bool inList(std::vector<std::string> first);
    void printTokens();
    DatalogProgram* datalogProgram();
    DatalogProgram* datalog;
    void factList();
    void ruleList();
    void queryList();
    void scheme();
    void fact();
    void rule();
    void query();
    void schemeList();
    void headPredicate();
    void parsePredicate();
    void predicateList();
    Predicate* parameterList(Predicate* pred);
    Predicate* stringList(Predicate* pred);
    Predicate* idList(Predicate* pred);
    Predicate* parameter(Predicate* pred);
    void match(std::string str);
    int index;
    std::string parsingStage;
    std::vector<std::string> First_schemeList;
    std::vector<std::string> First_factList;
    std::vector<std::string> First_ruleList;
    std::vector<std::string> First_queryList;
    std::vector<std::string> First_idList;
    std::vector<std::string> First_stringList;
    std::vector<std::string> First_predicateList;
    std::vector<std::string> First_parameterList;
    std::vector<Predicate*> tempSchemes;
    std::vector<Predicate*> tempFacts;
    std::vector<Predicate*> tempQueries;
    std::vector<Predicate*> tempRulePreds;
    std::vector<Rule*> tempRules;
    std::set<std::string> tempDomain;
public:
    Parser(std::vector<Token*> copy);
    ~Parser();

    void Parse();
    DatalogProgram* getProgram();




};

#endif