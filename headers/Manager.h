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
     * prints the possible airlines for a specific path
     * @param path
     */
    void printAirlinesForPath(std::vector<Airport>& path);
    /**
     * prints the possible airlines for a specific path using only the wantedAirlines
     * @param path
     * @param wantedAirlines
     */
    void printAirlinesForPathExcluding(std::vector<Airport>& path, std::vector<std::string>& wantedAirlines);
    /**
     * Uses bfsMinPath to print the minimum path (path with less flights) from an airport to another
     * @param start (starting Airport code)
     * @param target (target Airport code)
     */
    void printMinPath();
    /**
     * asks the user for a starting and a target airport
     * prints all the best paths from start to target
     */
    void printBestPaths();
    /**
     * asks the user for a starting airport and a target airport
     * asks the user for the list of airlines to be used
     * prints all the best paths from start to target using only the airlines in list
     */
    void printBestPathsExcludingAirlines();
    /**
     * Prints the following information about an airport (by user input)
     * - How many flights from the airport
     * - From how many different air companies
     * - To how many different destinations (different airports)
     * - To how many different countries
     * Note: if the airport doesn't exist, it warns the user about it
     */
    void printAirportGeneralInfo();
    /**
     * Asks the user to input an airport code and a max number of flights
     * Then prints the following information about that airport:
     * - How many airports, cities, and countries are reachable with that max number of flights
     * Note: if the airport doesn't exist, it warns the user about it
     */
    void printAirportInfoMaxFlights();
    /**
     * Uses bfsMinPathAirlines to print the minimum number of
     * flights between two airports (by user input)
     */
    void printMinPathAirlines();
    /**
     * Prints the total number of flights from an airport
     * @param airPortCode
     */
    void printNumOfOutgoingFlights(const std::string& airPortCode);
    /**
     * Prints the total number of air companies that have flights
     * from an airport
     * @param airPortCode
     */
    void printNumAirCompanies(const std::string& airPortCode);

    /**
     * Prints the number of different airports (different destinations)
     * that we can get to from an airport directly (1 flight)
     * @param airPortCode
     */
    void printNumAirports(const std::string& airPortCode);

    /**
     * Prints the number of countries
     * that we can get from an airport directly (1 flight)
     * @param airPortCode
     */
    void printNumCountries(const std::string& airPortCode);
    /**
     * Prints the number of airports that are reachable from airPortCode
     * with a maxFlights maximum number of flights
     * @param airPortCode
     * @param maxFlights
     * Complexity = O(V + E)
     */
    void printReachableAirports(const std::string &airPortCode, int maxFlights);
    /**
     * @param airportCode
     * @param maxFlights
     * @return a list of airports that we can reach from airportCode having a maxFlights number of flights
     * Complexity = O(V + E)
     */
    std::list<Airport> getReachableAirports(const std::string& airportCode, int maxFlights);
    /**
     * Prints the number of countries that are reachable from airPortCode
     * with a maxFlights maximum number of flights
     * @param airPortCode
     * @param maxFlights
     * Complexity = O(V + E)
     */
    void printReachableCountries(const std::string &airPortCode, int maxFlights);

    /**
     * @param airportCode
     * @param maxFlights
     * @return a set of countries that we can reach from airportCode having a maxFlights number of flights
     * Complexity = O(V + E)
     */
    std::set<std::string> getReachableCountries(const std::string& airportCode, int maxFlights);
    /**
     * prints the number of cities reachable from the airport with airportCode within maxFlights
     * @param airPortCode
     * @param maxFlights
     * Complexity = O (V + E)
     */
    void printReachableCities(const std::string &airPortCode, int maxFlights);
    /**
     * @param airportCode
     * @param maxFlights
     * @return
     * Complexity = O (V + E)
     */
    std::set<std::string> getReachableCities(const std::string& airportCode, int maxFlights);
    /**
     * Checks if an airport exists by its code
     * @param airportCode
     * @return true if airport exists, false if not
     * Complexity = O(V)
     */
    bool checkIfAirportExists(const std::string& airportCode);
    /**
     * 
     */
    void travelByCities();
    void travelByCoords();
};
#endif
