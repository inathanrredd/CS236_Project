#include "Parser.h"
#include <iostream>


Parser::Parser(std::vector<Token*> copy) {
    tokens = copy;
    index = 0;
    parsingStage = "";
    First_schemeList = {"ID"};
    First_factList = {"ID"};
    First_ruleList = {"ID"};
    First_queryList = {"ID"};
    First_idList = {"COMMA"};
    First_stringList = {"COMMA"};
    First_predicateList = {"COMMA"};
    First_parameterList = {"COMMA"};
    tempSchemes = {};
    tempFacts = {};
    tempQueries = {};
    tempRules = {};
    tempRulePreds = {};
    tempDomain = {};
}

Parser::~Parser() {

}

void Parser::printTokens() {
    std::string str;
    for (auto each: tokens ) {
        each->printTokenType();
    }
}

void Parser::Parse() {
    try {
        datalog = datalogProgram();
//        std::cout << "Success!" << std::endl;
//        std::cout << datalog->toString() << std::endl;
    } catch (Token* error) {
        std::cout << "Failure!" << std::endl;
        std::cout << "  " << error->printTokenToString() << std::endl;
    }
}

DatalogProgram* Parser::datalogProgram() {
//    datalogProgram	->	SCHEMES COLON scheme schemeList FACTS COLON factList RULES COLON ruleList QUERIES COLON query queryList EOF
    DatalogProgram* datalog = new DatalogProgram();
    match("SCHEMES");
    parsingStage = "SCHEMES";

    match("COLON");
    scheme();
    schemeList();

    match("FACTS");
    parsingStage = "FACTS";
    match("COLON");
    factList();

    match("RULES");
    parsingStage = "RULES";
    match("COLON");
    ruleList();

    match("QUERIES");
    parsingStage = "QUERIES";
    match("COLON");
    query();
    queryList();
    datalog->setSchemes(tempSchemes);
    datalog->setFacts(tempFacts,tempDomain);
    datalog->setQueries(tempQueries);
    datalog->setRules(tempRules);
    return datalog;
}

void Parser::schemeList() {
    if (inList(First_schemeList)) {
        scheme();
        schemeList();
    }
    else {
        return;
    }
}

void Parser::factList() {
    if(inList(First_factList)) {
        fact();
        factList();
    }
    else {
        return;
    }
}

void Parser::ruleList() {
    if(inList(First_ruleList)) {
        rule();
        ruleList();
    }
    else {
        return;
    }
}

void Parser::queryList() {
    if (inList(First_queryList)) {
        query();
        queryList();
    }
    else if (tokens[index]->tokenType()=="EOF") {
        return;
    }
    else {
        throw tokens[index];
    }
}

void Parser::scheme() {
    Predicate* pred = new Predicate(tokens[index]->getValue());
    match("ID");
    match("LEFT_PAREN");
    pred->addParameter(tokens[index]->getValue());
    match("ID");
    pred = idList(pred);
    match("RIGHT_PAREN");
    tempSchemes.emplace_back(pred);
    return;
}

void Parser::fact() {
    Predicate* pred = new Predicate(tokens[index]->getValue());
    match("ID");
    match("LEFT_PAREN");
    pred->addParameter(tokens[index]->getValue());
    tempDomain.emplace(tokens[index]->getValue());
    match("STRING");
    pred = stringList(pred);
    match("RIGHT_PAREN");
    match("PERIOD");
    tempFacts.emplace_back(pred);
}

void Parser::rule() {
    headPredicate();
    match("COLON_DASH");
    parsePredicate();
    predicateList();
    match("PERIOD");
    Rule* rule = new Rule(tempRulePreds);
    tempRules.emplace_back(rule);
    while (!tempRulePreds.empty()) {
        tempRulePreds.erase(tempRulePreds.begin());
    }
}

void Parser::query() {
    parsePredicate();
    match("Q_MARK");
}

void Parser::headPredicate() {
    Predicate* pred = new Predicate(tokens[index]->getValue());
    match("ID");
    match("LEFT_PAREN");
    pred->addParameter(tokens[index]->getValue());
    match("ID");
    pred = idList(pred);
    match("RIGHT_PAREN");
    tempRulePreds.emplace_back(pred);
}

void Parser::parsePredicate() {
    Predicate* pred = new Predicate(tokens[index]->getValue());
    match("ID");
    match("LEFT_PAREN");
    pred = parameter(pred);
    pred = parameterList(pred);
    match("RIGHT_PAREN");
    if (parsingStage == "QUERIES") {
        tempQueries.emplace_back(pred);
    }
    if (parsingStage == "RULES") {
        tempRulePreds.emplace_back(pred);
    }
}

void Parser::predicateList() {
    if(inList(First_predicateList)) {
        match("COMMA");
        parsePredicate();
        predicateList();
    }
    else {
        return;
    }
}

Predicate* Parser::parameterList(Predicate* pred) {
    if (inList(First_parameterList)) {
        match("COMMA");
        pred = parameter(pred);
        parameterList(pred);
    }
    else {
        return pred;
    }
    return pred;
}
Predicate* Parser::stringList(Predicate* pred) {
    if (inList(First_stringList)) {
        match("COMMA");
        pred->addParameter(tokens[index]->getValue());
        tempDomain.emplace(tokens[index]->getValue());
        match("STRING");
        stringList(pred);
    }
    else {
        return pred;
    }
    return pred;
}
Predicate* Parser::idList(Predicate* pred) {
    if(inList(First_idList)) {
        match("COMMA");
        pred->addParameter(tokens[index]->getValue());
        match("ID");
        idList(pred);
    }
    else {
        return pred;
    }
    return pred;
}
Predicate* Parser::parameter(Predicate* pred) {

    if (tokens[index]->tokenType() == "STRING") {
        bool constant = true;
        pred->addParameter(tokens[index]->getValue(), constant);
        match("STRING");
    }
    else {
        bool constant = false;
        pred->addParameter(tokens[index]->getValue(), constant);
        match("ID");
    }
    return pred;
}

void Parser::match(std::string str) {
    if (str == tokens[index]->tokenType()) {
//        std::cout << "Matched successfully: " << str << std::endl;
        index++;
        return;
    }
    else {
        throw tokens[index]; //Look up how to throw the right exception for this
    }
}

bool Parser::inList(std::vector<std::string> first) {
    for (auto each:first) {
        if (each == tokens[index]->tokenType()) {
            return true;
        }
    }
    return false;
}

DatalogProgram* Parser::getProgram() {
    return datalog;
}