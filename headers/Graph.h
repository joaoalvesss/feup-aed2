#ifndef PROJETO_AED_2_GRAPH_H
#define PROJETO_AED_2_GRAPH_H

#include "Airport.h"
#include "Flight.h"
#include <algorithm>
#include <limits>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <queue>
#include <set>

class Graph {
    struct Edge {
        std::string dest;       // destination node
        std::string airlineCode;
        double distance;        // distance between two airports
    };

    struct Node {
        Airport* airport;
        std::list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        bool visited;       // As the node been visited on a search?
        int dist;
        double distanceKm;    // Distance to other nodes
        std::list<Airport> storeMinPath; // list to use into minPath function
    };

    int n;                                        // Graph size (vertices are numbered from 1 to n)
    bool hasDir;                                 // false: undirected; true: directed
    std::unordered_map<std::string, Node> nodes; // The list of nodes being represented

public:
    explicit Graph(int nodes, bool dir = true);
    void addEdge(const Flight* flight);
    void addNode(Airport* airport);

    // Depth-First Search: example implementation
    void dfs(bool setAllVisitedToFalse, const std::string& AirportCode);
    /**
     * Uses Breadth-First Search to return a list with the min path from one airport to another
     * @param start (starting Airport code)
     * @param target (target Airport code)
     * @return a list of Airports
     */
    std::list<Airport> bfsMinPath(const std::string& start, const std::string& target);
    std::list<Airport> bfsMinPathAirline(const std::string& start, const std::string& target, const std::vector<std::string>& wantedAirlines);
    int dist(const std::string& AirportCode1, const std::string& AirportCode2);

    void setAllNodesToUnvisited();
    void resetGraph(const std::string& start);

    int getNumOfFlights(const std::string& airportCode);
    int getNumAirCompanies(const std::string& airportCode);
    int getNumDestinations(const std::string& airportCode);
    int getNumFlightsFromCountries(const std::string& airportCode);
    int getNumReachableAirports(const std::string& airportCode, int maxFlights); // kind of bfs
    int getNumReachableCities(const std::string& airportCode, int maxFlights); // kind of bfs
    int getNumReachableCountries(const std::string& airportCode, int maxFlights); // kind of bfs

    // Feito pelo João
    // void DijkstraAlgorithm(const std::string& sourceAirport);
    // double distKm(const std::string& AirportCode1, const std::string& AirportCode2);

    // Feitos pelo Rama
    // void DijkstraAlgorithm2(const std::string& sourceAirport);
    // void printMinimumPath(const std::string &sourceAirport, const std::string &destAirport);

};

#endif
