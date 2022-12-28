#ifndef PROJETO_AED_2_MANAGER_H
#define PROJETO_AED_2_MANAGER_H

#include <unordered_map>
#include "flight.h"
#include "airport.h"
#include "airline.h"
#include "graph.h"


class Manager {
    Graph* network;
    std::unordered_map<int,Flight> flights;

};
#endif //PROJETO_AED_2_MANAGER_H
