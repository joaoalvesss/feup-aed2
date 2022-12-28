#include  "../headers/Graph.h"
#include "../headers/Utils.h"
#include  <queue>

Graph::Graph(int nodes, bool dir) {
    this->n = nodes;
    this->hasDir = dir;
}

void Graph::addNode(Airport* airport) {
    nodes.insert({airport->getCode(), {airport, {}, false}});
}

void Graph::addEdge(const Flight* flight){
    auto sourceAirport = nodes.find(flight->getSourceAirportCode());
    auto targetAirport = nodes.find(flight->getTargetAirportCode());
    const std::string& airlineCode = flight->getAirlineCode();

    if(sourceAirport == targetAirport || sourceAirport == nodes.end() || targetAirport == nodes.end()) return;

    double distance = utils::haversine(sourceAirport->second.airport->getLat(), sourceAirport->second.airport->getLon(), targetAirport->second.airport->getLat(), targetAirport->second.airport->getLon());
    sourceAirport->second.adj.push_back({flight->getSourceAirportCode(), airlineCode, distance});
}

void Graph::bfs(const std::string& AirportCode){
    setAllNodesToUnvisited();

    std::queue<std::string> queue;
    nodes[AirportCode].visited = true;
    queue.push(AirportCode);

    while (!queue.empty()) {
        std::string aux = queue.front();
        queue.pop();

        Node auxNode = nodes.at(aux);
        for(const auto &adj : auxNode.adj) {
            if (!nodes[adj.dest].visited) {
                nodes[adj.dest].visited = true;
                queue.push(adj.dest);
            }
        }
    }
}

void Graph::dfs(bool setAllVisitedToFalse, const std::string& AirportCode){
    if(setAllVisitedToFalse) // just a controller
        setAllNodesToUnvisited();
    cout << AirportCode;
    nodes[AirportCode].visited = true;
    for (const auto& adj : nodes[AirportCode].adj) {
        std::string aux = adj.dest;
        if (!nodes[aux].visited)
            dfs(false, aux);
    }
}

void Graph::setAllNodesToUnvisited(){
    for(auto& node: nodes) node.second.visited = false;
}