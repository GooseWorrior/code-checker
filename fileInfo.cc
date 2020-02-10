#include "fileInfo.h"

using std::smatch;
using std::regex;
using std::regex_search;
using std::string;
using std::endl;

// scan() goes through a program file and identifies "TODO"s and different finds of comments 
// using regular expression searching. It updates "theInfo" accordingly
void fileInfo::scan() {
    bool leftMatch = false, commentLine = false, blockLine = false, singleLine = false;
    string str, temp;
    smatch m1, m2;
    regex sComment(SC);
    regex bCommentLeft(BCL), bCommentRight(BCR);
    while (getline(source, str)) {
        commentLine = false;
        blockLine = false;
        singleLine = false;
        while (!str.empty()) {
            if (leftMatch) { // first check if a block comment end if a block comment has started
                regex_search(str, m1, bCommentRight); 
                blockLine = true;
                commentLine = true;
                if (!m1.empty()) { // the previous block comment end and we proceed with rest of the string
                    temp = m1.prefix().str();
                    countTODO(temp); // TODOs are counted in the comment segments 
                    str = m1.suffix().str();
                } else { // this line is within a block comment
                    countTODO(str); // TODOs are counted in the comment segments
                    break; 
                }
                theInfo[BLOCK]++;
                leftMatch = false;
            } else { // if a block comment hasn't started
                regex_search(str, m1, sComment);  // look for single comments and the start of block comments at the same time
                regex_search(str, m2, bCommentLeft);
                int pos1 = str.size(), pos2 = str.size();
                if (!m1.empty()) pos1 = m1.position(0);
                if (!m2.empty()) pos2 = m2.position(0);
                if (pos1 < pos2) { // if the single comment appears first, ignore the block comment
                    singleLine = true;
                    commentLine = true;
                    temp = m1.suffix().str();
                    countTODO(temp);
                    break;
                } else if (pos1 > pos2){ // if the block comment appears first, ignore the single comment
                    commentLine = true;
                    leftMatch = true;
                    blockLine = true;
                    str = m2.suffix().str();
                    countTODO(str);
                } else { // if neither of them appears, we are done with this line
                    break;
                }
                // we loop in case of finding a start of a block comment to handle several blocks in the same line
            } 
        }
        theInfo[CLINE] += commentLine;
        theInfo[BCLINE] += blockLine;
        theInfo[SCLINE] += singleLine;
        theInfo[LINE]++;
    }
}

// countTODO(str) count "TODO"s and update str
void fileInfo::countTODO(string & str) {
    smatch m;
    regex todo("TODO");
    while (regex_search(str, m, todo)) {
        if (!m.empty()) theInfo[TODO]++;
        str = m.suffix().str();
    }
}

// loadLanguage(list) load language setting (comments notations) 
void fileInfo::loadLanguage(const std::vector<string> list) {
    if (list.size() != 3) return;
    SC = list[0];
    BCL = list[1];
    BCR = list[2];
}

// print() print scanning result to "output"
void fileInfo::print() {
    output << "Total # of lines: " << theInfo[LINE] << endl;
    output << "Total # of comment lines: " << theInfo[CLINE] << endl;
    output << "Total # of single line comments: " << theInfo[SCLINE] << endl;
    output << "Total # of comment lines within block comments: " << theInfo[BCLINE] << endl;
    output << "Total # of block line comments: " << theInfo[BLOCK] << endl;
    output << "Total # of TODO’s: " << theInfo[TODO] << endl;
}