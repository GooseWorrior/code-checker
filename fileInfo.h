#ifndef FILEINFO_H
#define FILEINFO_H

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>

enum TYPE { // assign each index of "theInfo" with a name
    LINE = 0,
    CLINE,
    SCLINE,
    BLOCK, 
    BCLINE,
    TODO
}; 

class fileInfo {
    int theInfo[6];
    std::string BCR, BCL, SC;
    std::istream & source;  // can be attached to different input when initializing
    std::ostream & output;  // can be attached to different output when initializing
    public:
        fileInfo(std::istream & i, std::ostream & o): source{i}, output{o} { 
            for (auto & i : theInfo) i = 0;
        } 
        fileInfo(): source{std::cin}, output{std::cout} { 
            for (auto & i : theInfo) i = 0;
        } 
        void reset() { for (auto & i : theInfo) i = 0; } 
        void scan();
        void print();
        void countTODO(std::string & str);
        void loadLanguage(const std::vector<std::string> list);

};

#endif