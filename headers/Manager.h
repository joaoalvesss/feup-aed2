#ifndef PROJETO_AED_2_MANAGER_H
#define PROJETO_AED_2_MANAGER_H

#include "Flight.h"
#include "Airport.h"
#include "Airline.h"
#include "Graph.h"

#include <unordered_map>

class Manager {
    Graph* graph;
    std::unordered_map<std::string,Airline*> airlines;
public:
    Manager();
    void print();
    /**
     * Uses bfsMinPath to print the minimum path (path with less flights) from an airport to another
     * @param start (starting Airport code)
     * @param target (target Airport code)
     */
    void printAirlinesPath(std::vector<Airport>& path);
    void printMinPath();
    void printMinPathOptions();
    /**
     * Uses bfsMinPathAirlines to print the minimum number of
     * flights between two airports (by user input)
     */
    void printMinPathAirlines();
    /**
     * Prints the total number of flights from an airport (by user input)
     */
    void printNumOfOutgoingFlights();
    /**
     * Prints the total number of air companies that have flights
     * from an airport (by user input)
     */
    void printNumAirCompanies();
    /**
     * Prints the number of different airports (different destinations)
     * that we can get to from an airport (by user input) directly (1 flight)
     */
    void printNumAirports();
    /**
     * Prints the number of countries
     * that we can get from an airport (by user input) directly (1 flight)
     */
    void printNumCountries();
    void printReachableAirports();
    /**
     * @param airportCode
     * @param maxFlights
     * @return a list of airports that we can reach from airportCode having a maxFlights number of flights
     */
    std::list<Airport> getReachableAirports(const std::string& airportCode, int maxFlights);
    /**
     * @param airportCode
     * @param maxFlights
     * @return a list of countries that we can reach from airportCode having a maxFlights number of flights
     */
    std::set<std::string> getReachableCountries(const std::string& airportCode, int maxFlights);
    std::set<std::pair<std::string,std::string>> getReachableCities(const std::string& airportCode, int maxFlights);

    std::vector<std::string> travelByCities(const std::string& sourceCity, const std::string& targetCity);
    std::vector<std::string> travelByCoords();
};
#endif
