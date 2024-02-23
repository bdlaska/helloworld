#include <iostream>
#include "file_search.h"

int main() {
    std::string filename;
    std::cout << "Enter the file name to search: ";
    std::cin >> filename;

    FileSearch::searchFile(filename);

    return 0;
}
