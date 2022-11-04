//
// Created by nathan on 10/21/22.
//

#ifndef PROJECT_0_MAIN_HEADER_H
#define PROJECT_0_MAIN_HEADER_H
#include <vector>
#include <string>

class Header {
private:
    std::vector<std::string> attributes;
public:
    Header();
    Header(std::vector<std::string> atts);
    ~Header();
    std::string printAllAttributes();
    std::vector<std::string> getVecAttributes();
    std::string printAttributeAt(int index);
    void setAllAttributes(std::vector<std::string> vec);
    void setAttributeAt(int index);

};


#endif //PROJECT_0_MAIN_HEADER_H
