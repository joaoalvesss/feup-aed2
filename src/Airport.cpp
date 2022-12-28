#include "../headers/Airport.h"
#include <sstream>
#include <vector>

Airport* Airport::readLine(const std::string& line) {
    std::string code, name, city, country, word;
    double lat, lon;
    std::istringstream stream(line);
    std::vector<std::string> words;

    while (getline(stream, word, ',')) {
        words.push_back(word);
    }
    if (words.size() != 6)
        return nullptr;
    code = words.at(0);
    name = words.at(1);
    city = words.at(2);
    country = words.at(3);
    lat = stod(words.at(4));
    lon = stod(words.at(5));

    return new Airport(code, name, city, country, lat, lon);
}