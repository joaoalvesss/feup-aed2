#ifndef PROJETO_AED_2_FLIGHT_H
#define PROJETO_AED_2_FLIGHT_H

#include <vector>
#include <string>
#include <sstream>
#include <iostream>

class Flight {
    std::string sourceAirportCode, targetAirportCode, airlineCode;

public:
    Flight(std::string  sac, std::string  tac, std::string  code);

    const std::string& getSourceAirportCode() const {return sourceAirportCode;}
    const std::string& getTargetAirportCode() const {return targetAirportCode;}
    const std::string& getAirlineCode() const {return airlineCode;}
    static Flight* readLine(const std::string& line);
    void print();
};

#endif