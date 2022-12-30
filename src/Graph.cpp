#include  "../headers/Graph.h"
#include "../headers/Utils.h"
#include  <queue>
#include <algorithm>
#include <set>

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
static vector<std::string> airportsPassed; // TEMP
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

void Graph::setAllNodesToUnvisited(){
    for(auto& node: nodes)
        node.second.visited = false;
}

/*void Graph::bfsWithDist(const std::string& AirportCode) {
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
*/
int Graph::dist(const std::string& AirportCode1, const std::string& AirportCode2) {
    bfsWithDist(AirportCode1);
    int distance = nodes[AirportCode2].dist;
    return distance;
}

// TODO
/*void Graph::minPath(const std::string& sourceAirport){ // Dijkstra minimum path
    setAllNodesToUnvisited();
    nodes[sourceAirport].dist = 0;
    nodes[sourceAirport].visited = true;

    if(!nodes[sourceAirport].storeMinPaths.empty())
        nodes[sourceAirport].storeMinPaths.clear();

    nodes[sourceAirport].storeMinPaths.push_back(*(nodes.find(sourceAirport)->second.airport));

    std::set<std::pair<std::string,double>> keeper;
    for (auto &node: nodes)
        keeper.insert({node.first, node.second.dist});

    while(!keeper.empty()){
        std::string aux = keeper.begin()->first;
        keeper.erase(keeper.begin());
        nodes[sourceAirport].visited = true;

        for(auto &nod        std::list<Airport> storeMinPaths; // list to use into minPath function
e : nodes[aux].adj){

        }
    }*/
void Graph::resetGraph(const std::string &start) {
    for(auto& node: nodes) {
        node.second.visited = false;
        node.second.airport->getCode() == start ? node.second.dist = 0 : node.second.dist = INT32_MAX;
    }
}
void Graph::bfsWithDist(const std::string &sourceAirport) {
    resetGraph(sourceAirport);

    queue<std::string> q; // queue of unvisited nodes
    q.push(sourceAirport);

    nodes.find(sourceAirport)->second.visited = true;

    while (!q.empty()) {
        std::string u = q.front(); q.pop();

        for (const auto& e : nodes[u].adj) {  // para cada edge
            std::string w = e.dest;
            if (!nodes[w].visited) { // se não tiver sido visitada
                nodes[w].dist = nodes[u].dist + 1;  // adiciona a distancia
                q.push(w);
                nodes[w].previousNode = u;  // adiciona o previous node
                nodes[w].visited = true;
            }
        }
    }
}
//TODO
void Graph::minPath(const std::string &sourceAirport, const std::string& targetAirport) {
    vector<std::string> rpath;
    vector<std::string> path = {sourceAirport};
    Node start = nodes.find(targetAirport)->second;
    while(start.airport->getCode() != sourceAirport){
        rpath.push_back(start.airport->getCode());
        start = nodes.find(start.previousNode)->second;
    }
    for (auto it = rpath.rbegin(); it != rpath.rend(); it++)
        path.push_back(*it);

    for (const std::string& s : path)
        cout << s << " -> ";
}


// TEMP
void Graph::helperPrint() {
    //minPath("CDG");
}
