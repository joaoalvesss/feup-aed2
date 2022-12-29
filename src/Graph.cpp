#include  "../headers/Graph.h"
#include "../headers/Utils.h"
#include  <queue>
#include <algorithm>

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

    double distance = utils::haversine(*(sourceAirport->second.airport), *(targetAirport->second.airport));
    sourceAirport->second.adj.push_back({flight->getTargetAirportCode(), airlineCode, distance});
}

void Graph::bfs(const std::string& AirportCode){
    setAllNodesToUnvisited();

    std::queue<std::string> queue;
    nodes[AirportCode].visited = true;
    queue.push(AirportCode);

    while (!queue.empty()) {
        std::string aux = queue.front();
        queue.pop();
        cout << aux;
        Node auxNode = nodes.at(aux);
        for(const auto &adj : auxNode.adj) {
            if (!nodes[adj.dest].visited) {
                nodes[adj.dest].visited = true;
                queue.push(adj.dest);
            }
        }
    }
}
// static vector<std::string> airportsPassed;
void Graph::dfs(bool setAllVisitedToFalse, const std::string& AirportCode){
    if(setAllVisitedToFalse)// just a controller
        setAllNodesToUnvisited();

    nodes.find(AirportCode)->second.visited = true;
    // std::cout << AirportCode << endl; // print
    // airportsPassed.push_back(AirportCode); // test

    for (const auto& adj : nodes.find(AirportCode)->second.adj) {
        std::string aux = adj.dest;
        if (!nodes.find(aux)->second.visited)
            dfs(false, aux);
    }
}

/*void Graph::helperPrint() {
    std::cout << airportsPassed.size() << " |-| " << nodes.size() << std::endl;
    vector<std::string> ap = airportsPassed;
    for (const auto &e : nodes) {
        if (!std::count(ap.begin(), ap.end(), e.second.airport->getCode()))
            std::cout << e.second.airport->getCode() << std::endl;
    }
}*/

void Graph::setAllNodesToUnvisited(){
    for(auto& node: nodes)
        node.second.visited = false;
}

void Graph::bfsWithDist(const std::string& AirportCode) {
    setAllNodesToUnvisited();
    for(auto& node : nodes)
        node.second.dist = -1;

    nodes.find(AirportCode)->second.dist = 0;
    queue<std::string> q; // queue of unvisited nodes
    q.push(AirportCode);
    nodes.find(AirportCode)->second.visited = true;
    while (!q.empty()) { // while there are still unvisited nodes
        std::string u = q.front(); q.pop();
        // show node order
        //cout << u << " ";
        for (const auto& e : nodes[u].adj) {
            std::string w = e.dest;
            if (!nodes[w].visited) {
                nodes[w].dist = nodes[u].dist + 1;
                q.push(w);
                nodes[w].visited = true;
            }
        }
    }
}

int Graph::dist(const std::string& AirportCode1, const std::string& AirportCode2) {
    bfsWithDist(AirportCode1);
    int distance = nodes[AirportCode2].dist;
    return distance;
}
