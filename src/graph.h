#ifndef PROJETO_AED_2_GRAPH_H
#define PROJETO_AED_2_GRAPH_H
#include "airport.h"

#include <iostream>
#include <string>
#include <list>

class Graph {

    struct Edge {
        std::string edge;
        std::string flightCode;
        double distance;
    };

    struct Node {
        Airport* Airport;
        std::list<Edge> adj;
        bool visited;
    };
};

#endif //PROJETO_AED_2_GRAPH_H
