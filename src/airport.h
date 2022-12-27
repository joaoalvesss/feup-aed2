#ifndef PROJETO_AED_2_FLIGHT_H
#define PROJETO_AED_2_FLIGHT_H

#include <iostream>
#include <string>

class Airport {
    std::string code, name, city, country;
    double lat, lon;

public:
    Airport(const std::string& code, const std::string& name, const std::string& city, const std::string& country, const double lat, const double lon) : code(code), name(name), city(city), country(country), lat(lat), lon(lon){}
    
};

#endif