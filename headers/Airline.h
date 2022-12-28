#include <string>
#include <vector>

#ifndef PROJETO_AED_2_AIRLINE_H
#define PROJETO_AED_2_AIRLINE_H

using namespace std;

class Airline{
    string code, name, callsign, country;
    vector<string> destinations;

public:
    Airline(string code, string name, string callsign, string country);
    const string& getAirlineCode() const { return this->code; }
    const string& getAirlineName() const { return this->name; }
    const string& getAirlineCallsign() const { return this->callsign; }
    const string& getAirlineCountry() const { return this->country; }
    void print();
};
#endif
