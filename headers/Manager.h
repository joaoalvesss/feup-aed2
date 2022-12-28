#ifndef PROJETO_AED_2_MANAGER_H
#define PROJETO_AED_2_MANAGER_H

#include <unordered_map>
#include "Flight.h"
#include "Airport.h"
#include "Airline.h"
#include "Graph.h"


class Manager {
    Graph* network;
    std::unordered_map<int,Flight> flights;
    Manager();
};
#endif //PROJETO_AED_2_MANAGER_H
