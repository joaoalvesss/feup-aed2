#ifndef PROJETO_AED_2_GRAPH_H
#define PROJETO_AED_2_GRAPH_H

#include <list>
#include <vector>
#include <queue>
#include <iostream>
#include <string>

using namespace std;

class Graph {
    struct Edge {
        string dest;   // destination node
        string airlineCode;
        double distance; // distance between two airports
    };

    struct Node {
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        bool visited;   // As the node been visited on a search?
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirected; true: directed
    vector<Node> nodes; // The list of nodes being represented

public:
    // Constructor: nr nodes and direction (default: undirected)
    Graph(int nodes, bool dir = true);

    // Add edge from source to destination with a certain weight
    void addEdge(int src, int dest);
    void addNode();

    // Depth-First Search: example implementation
    void dfs(int v);

    // Breadth-First Search: example implementation
    int bfs(int v);

    // ----- Functions to implement in this class -----
    int distance(int a, int b);
    int diameter();
};
#endif //PROJETO_AED_2_GRAPH_H
