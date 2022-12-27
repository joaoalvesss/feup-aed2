#include <fstream>
#include "utils.h"

vector<std::string> utils::file::readCsv(const std::string& fileName) {
    ifstream openFile(fileName);
    vector<string> elements;
    string line;

    if (!openFile.is_open()) return elements;

    openFile.ignore(INT32_MAX, '\n');

    while(getline(openFile, line))
        elements.push_back(line);

    return elements;
}