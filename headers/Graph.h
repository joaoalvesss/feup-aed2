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

    std::unordered_map<std::string, Node> getAllNodes() { return this->nodes; }

    /**
     * BFS setting the distance from the node whose Airport has airportCode
     * @param AirportCode
     * Complexity = O(V + E)
     */
    void bfs(const std::string& AirportCode);

    /**
     * Uses Breadth-First Search to return a list with the min path from one airport to another
     * @param start (starting Airport code)
     * @param target (target Airport code)
     * @return a list of Airports
     * Complexity = O(V + E)
     */
    std::vector<Airport> bfsMinPath(const std::string& start, const std::string& target);

    /**
     * Uses BFS to return a list with a minimal path from one airport to another
     * @param start
     * @param target
     * @param wantedAirlines
     * @return list of Airports (path)
     * Complexity = O(V + E)
     */
    std::vector<Airport> bfsMinPathAirline(const std::string& start, const std::string& target, const std::vector<std::string>& wantedAirlines);

    /**
     * sets all nodes to unvisited
     * Complexity = O (V)
     */
    void setAllNodesToUnvisited();
    /**
     *
     * @param start
     * @param target
     * @return all possible minimal paths from start to target
     * Complexity = O(V + E)
     */
    std::vector<std::vector<Airport>> findBestPaths(const std::string& start, const std::string& target);
    /**
     * dfs to support findBestPaths
     * stores in paths all minimal paths possible
     * @param start
     * @param target
     * @param path
     * @param paths
     * Complexity = O(V + E)
     */
    void dfsBestPaths(const std::string& start, const std::string& target, std::vector<Airport>& path, std::vector<std::vector<Airport>>& paths);
    /**
     *
     * @param start
     * @param target
     * @param wantedAirlines
     * @return all minimal possible paths from start to target using only airlines in wantedAirlines
     * Complexity = O(V + E)
     */
    std::vector<std::vector<Airport>> findBestPathsAirlines(const std::string& start, const std::string& target, std::vector<std::string> wantedAirlines);
    /**
     * dfs to support findBestPathsAirlines
     * stores in paths all minimal paths possible
     * @param start
     * @param target
     * @param path
     * @param paths
     * @param wantedAirlines
     * Complexity = O(V + E)
     */
    void dfsBestPathsAirlines(const std::string& start, const std::string& target, std::vector<Airport>& path, std::vector<std::vector<Airport>>& paths, std::vector<std::string> wantedAirlines);

    /**
     * @param latitude
     * @param longitude
     * @return list of airport within a radius of 80km of the coordinates that were given
     * Complexity = O(V)
     */
    std::list<std::string> findAirportsByCoords(double latitude, double longitude);

    /**
     * @param city
     * @return list of airports that exist in a city
     * O (V)
     */
    std::list<std::string> findAirportsByCity(const std::string& city);
    

};
#endif
