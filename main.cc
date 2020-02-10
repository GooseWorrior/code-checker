#include "fileInfo.h"

#define cvs const std::vector<std::string>
 
cvs C {"//", "/\\*", "\\*/"};
cvs Python {"#", "$a", "$aS"};  // $a means it doesn't match anything
cvs Java {"//", "/\\*", "\\*/"}; 

int main (int argc, char * argv[]) {
    fileInfo file{std::cin, std::cout};
    file.reset();
    file.loadLanguage(C); // Can have other language setting
    file.scan();
    file.print();
}