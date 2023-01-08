#include <string>
#include <vector>

#ifndef PROJETO_AED_2_AIRLINE_H
#define PROJETO_AED_2_AIRLINE_H


class Airline{
    std::string code, name, callsign, country;
    std::vector<std::string> destinations;

public:

    /**
     * Constructor of an Airline
     * @param code
     * @param name
     * @param callsign
     * @param country
     */
    Airline(std::string code, std::string name, std::string callsign, std::string country);

    /**
     * @return airline code
     */
    const std::string& getAirlineCode() const { return this->code; }

    /**
     * @param line
     * @return a pointer to the airline presented in the csv line given
     * Complexity O(n)
     */
    static Airline* readLine(const std::string& line);
};
#endif
