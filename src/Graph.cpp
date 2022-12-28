#include  "../headers/Graph.h"
#include  "../headers/Flight.h"
#include  <queue>

void Graph::addEdge(const Flight flight){

}

Graph::Graph(int nodes, bool dir) {
    this->n = nodes;
    this->hasDir = dir;
}

void Graph::addNode(const std::string& AirportCode, Airport* airport) {
    nodes.insert({AirportCode, {airport, {}, false}});
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