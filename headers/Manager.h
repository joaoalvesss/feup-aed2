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
};
#endif
