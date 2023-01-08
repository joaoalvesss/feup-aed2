#include "../headers/Airline.h"
#include "../headers/Utils.h"

#include <iostream>
#include <utility>
#include <sstream>


Airline::Airline(string code, string name, string callsign, string country) {
    this->code = std::move(code);
    this->name = std::move(name);
    this->callsign = std::move(callsign);
    this->country = std::move(country);
}

Airline* Airline::readLine(const std::string &line) {
    std::string code, name, callsign, country, word;
    std:vector<std::string> words;
    std::istringstream stream(line);
    while(getline(stream, word, ','))
        words.push_back(word);
    if (words.size() != 4)
        return nullptr;
    code = words.at(0);
    name = words.at(1);
    callsign = words.at(2);
    country = words.at(3);
    return new Airline(code, name, callsign, country);
}
