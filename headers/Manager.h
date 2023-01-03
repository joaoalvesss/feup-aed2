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
    void printMinPath();
    void printMinPathOptions();
    /**
     * Uses bfsMinPathAirlines to print the minimum number of
     * flights between two airports (by user input)
     */
    void printMinPathAirlines();
    /**
     * Prints the total number of flights of an airport (by user input)
     */
    void printNumOfFlights();
    /**
     * Prints the total number of air companies that have flights
     * from an airport (by user input)
     */
    void printNumAirCompanies();
    /**
     *
     */
    void printNumDestinations();
    void printNumCountries();
};
#endif
