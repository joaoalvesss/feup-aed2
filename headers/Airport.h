#ifndef PROJETO_AED_2_AIRPORT_H
#define PROJETO_AED_2_AIRPORT_H

#include <string>

class Airport {
    std::string code, name, city, country;
    double lat, lon;

public:
    Airport(std::string code, std::string name, std::string city, std::string country, const double lat, const double lon) : code(std::move(code)), name(std::move(name)), city(std::move(city)), country(std::move(country)), lat(lat), lon(lon){}
    std::string getCode() {return code;}
    std::string getName() {return name;}
    std::string getCity() {return city;}
    std::string getCountry() {return country;}
    double getLat() const {return lat;}
    double getLon() const {return lon;}
    static Airport* readLine(const std::string&);
};

#endif