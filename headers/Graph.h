#ifndef PROJETO_AED_2_GRAPH_H
#define PROJETO_AED_2_GRAPH_H

#include  "Airport.h"
#include "Flight.h"
#include <algorithm>
#include <limits>
#include  <unordered_map>
#include  <list>
#include  <queue>
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
        //std::string previousNode;
        std::list<Airport> storeMinPath; // list to use into minPath function
    };

    int n;                                        // Graph size (vertices are numbered from 1 to n)
    bool hasDir;                                 // false: undirected; true: directed
    std::unordered_map<std::string, Node> nodes; // The list of nodes being represented

public:
    // Constructor: nr nodes and direction (default: directed)
    explicit Graph(int nodes, bool dir = true);

    // Add edge from source to destination with a certain weight
    void addEdge(const Flight* flight);
    void addNode(Airport* airport);

    // Depth-First Search: example implementation
    void dfs(bool setAllVisitedToFalse, const std::string& AirportCode);
    // Breadth-First Search: example implementation
    void bfs(const std::string& AirportCode);
    void bfsWithDist(const std::string& AirportCode); // min value
    int dist(const std::string& AirportCode1, const std::string& AirportCode2);
    void setAllNodesToUnvisited();
    void resetGraph(const std::string& start);
    void minPath(const std::string& sourceAirport);
    void DijkstraAlgorithm(const std::string& sourceAirport);
    
    void helperPrint();

};
#endif
