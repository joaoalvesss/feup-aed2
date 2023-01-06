#ifndef PROJETO_AED_2_GRAPH_H
#define PROJETO_AED_2_GRAPH_H

#include "Airport.h"
#include "Flight.h"
#include <algorithm>
#include <limits>
#include <cctype>
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
        std::vector<std::string> storeMinPath; // list to use into minPath function
    };

    int n;                                        // Graph size (vertices are numbered from 1 to n)
    std::unordered_map<std::string, Node> nodes; // The list of nodes being represented

public:
    explicit Graph(int nodes);
    void addEdge(const Flight* flight);
    void addNode(Airport* airport);
    Node& getNode(const std::string &airPortCode) {return nodes[airPortCode];}
    bool airportExists(const std::string& airportCode);

    int getGraphSize();
    std::unordered_map<std::string, Node> getAllNodes() { return this->nodes; }

    void dfs(bool setAllVisitedToFalse, const std::string& AirportCode);
    void bfs(const std::string& AirportCode);

    /**
     * Uses Breadth-First Search to return a list with the min path from one airport to another
     * @param start (starting Airport code)
     * @param target (target Airport code)
     * @return a list of Airports
     */
    std::vector<Airport> bfsMinPath(const std::string& start, const std::string& target);
    // não fazer a documentacao ainda
    std::vector<Airport> bfsMinPathAirline(const std::string& start, const std::string& target, const std::vector<std::string>& wantedAirlines);

    /**
     * sets all nodes to unvisited
     */
    void setAllNodesToUnvisited();
    /**
     *
     * @param airportCode
     * @param maxFlights
     * @return list of Airports reachable from airport with airportCode within maxFlights number of flights
     */
    std::list<Airport> getReachableAirports(const std::string& airportCode, int maxFlights);
    /**
     *
     * @param airportCode
     * @param maxFlights
     * @return set of pairs of type <city, country> reachable from the airport with airportCode within maxFlights number of flights
     *
     */
    std::set<std::pair<std::string,std::string>> getReachableCities(const std::string& airportCode, int maxFlights);
    /**
     *
     * @param airportCode
     * @param maxFlights
     * @return set of countries reachable from the airport with airportCode within maxFlights number of flights
     */
    std::set<std::string> getReachableCountries(const std::string& airportCode, int maxFlights);

    std::list<std::string> findAirportsByCoords(double latitude, double longitude);
    std::list<std::string> findAirportsByCity(const std::string& city);
    

    // Feito pelo João
    // void DijkstraAlgorithm(const std::string& sourceAirport);
    // double distKm(const std::string& AirportCode1, const std::string& AirportCode2);

    // Feitos pelo Rama
    // void DijkstraAlgorithm2(const std::string& sourceAirport);
    // void printMinimumPath(const std::string &sourceAirport, const std::string &destAirport);

    void printShortestPaths(const std::string &start, const std::string &end);
};
#endif
