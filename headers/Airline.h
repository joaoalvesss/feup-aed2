#include <string>
#include <vector>

#ifndef PROJETO_AED_2_AIRLINE_H
#define PROJETO_AED_2_AIRLINE_H


class Airline{
    std::string code, name, callsign, country;
    std::vector<std::string> destinations;

public:
    Airline(std::string code, std::string name, std::string callsign, std::string country);
    const std::string& getAirlineCode() const { return this->code; }
    const std::string& getAirlineName() const { return this->name; }
    const std::string& getAirlineCallsign() const { return this->callsign; }
    const std::string& getAirlineCountry() const { return this->country; }
    static Airline* readLine(const std::string& line);
    void print();
};
#endif
