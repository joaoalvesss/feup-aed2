#ifndef PROJETO_AED_2_AIRPORT_H
#define PROJETO_AED_2_AIRPORT_H

#include <string>
#include <iostream>

class Airport {
    std::string code, name, city, country;
    double lat, lon;

public:
    /**
     * Airport default constructor
     */
    Airport();

    /**
     * Airport constructor
     * @param code
     * @param name
     * @param city
     * @param country
     * @param lat
     * @param lon
     */
    Airport(std::string code, std::string name, std::string city, std::string country, const double lat, const double lon) : code(std::move(code)), name(std::move(name)), city(std::move(city)), country(std::move(country)), lat(lat), lon(lon){}

    /**
     *
     * @return airport code
     */
    std::string getCode() {return code;}

    /**
     *
     * @return  airport name
     */
    std::string getName() {return name;}

    /**
     *
     * @return airport city
     */
    std::string getCity() {return city;}

    /**
     *
     * @return airport country
     */
    std::string getCountry() {return country;}

    /**
     *
     * @return airport latitude
     */
    double getLat() const {return lat;}

    /**
     *
     * @return airport longitude
     */
    double getLon() const {return lon;}

    /**
     *
     * @param line
     * @return a pointer to the airline presented in the csv line given
     * Complexity O(n)
     */
    static Airport* readLine(const std::string& line);
};

#endif