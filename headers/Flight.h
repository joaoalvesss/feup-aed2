#ifndef PROJETO_AED_2_FLIGHT_H
#define PROJETO_AED_2_FLIGHT_H

#include <vector>
#include <string>
#include <sstream>
#include <iostream>

class Flight {
    std::string sourceAirportCode, targetAirportCode, airlineCode;

public:
    /**
     * Constructor
     * @param sac
     * @param tac
     * @param code
     */
    Flight(std::string  sac, std::string  tac, std::string  code);

    /**
     * @return source airport code
     */
    const std::string& getSourceAirportCode() const {return sourceAirportCode;}

    /**
    * @return target airport code
    */
    const std::string& getTargetAirportCode() const {return targetAirportCode;}

    /**
    * @return airline code
    */
    const std::string& getAirlineCode() const {return airlineCode;}

    /**
    * @param line
    * @return a pointer to the flight presented in the csv line given
    * Complexity O(n)
    */
    static Flight* readLine(const std::string& line);
};

#endif