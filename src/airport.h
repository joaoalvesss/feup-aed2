#ifndef PROJETO_AED_2_FLIGHT_H
#define PROJETO_AED_2_FLIGHT_H

#include <sstream>

class Flight {
    std::string sourceAirportCode, targetAirportCode, airlineCode;

public:
    const std::string& getSourceAirportCode() const {
        return sourceAirportCode;
    }

    const std::string& getTargetAirportCode() const {
        return targetAirportCode;
    }

    const std::string& getAirlineCode() const {
        return airlineCode;
    }
};

#endif //PROJETO_AED_2_FLIGHT_H
