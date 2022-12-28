#ifndef PROJETO_AED_2_FLIGHT_H
#define PROJETO_AED_2_FLIGHT_H

#include "utils.h"
#include <sstream>
#include <vector>

class Flight {
    std::string sourceAirportCode, targetAirportCode, airlineCode;
    std::vector<std::string> flights;

    public:
    Flight(const std::string& sac, const std::string& tac, const std::string& code);

    const std::string& getSourceAirportCode() const {
        return sourceAirportCode;
    }

    const std::string& getTargetAirportCode() const {
        return targetAirportCode;
    }

    const std::string& getAirlineCode() const {
        return airlineCode;
    }

    Flight* readLine(const std::string& line);
};

#endif //PROJETO_AED_2_FLIGHT_H