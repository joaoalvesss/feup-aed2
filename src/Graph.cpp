#include <stack>
#include <utility>
#include  "../headers/Graph.h"
#include "../headers/Utils.h"
#include "../headers/Airline.h"


Graph::Graph(int nodes) {
    this->n = nodes;
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


void Graph::bfs(const std::string& AirportCode) {
    setAllNodesToUnvisited();

    for (auto& node : nodes)
        node.second.dist = -1;

    queue<std::string> q;
    q.push(AirportCode);
    nodes[AirportCode].dist = 0;
    nodes[AirportCode].visited = true;

    while (!q.empty()) {
        std::string u = q.front(); q.pop();

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

void Graph::setAllNodesToUnvisited(){
    for(auto& node: nodes)
        node.second.visited = false;
}


std::vector<Airport> Graph::bfsMinPath(const std::string& sourceAirport, const std::string& targetAirport){
    std::queue<std::string> queue;
    std::unordered_map<std::string, std::string> preNode;

    setAllNodesToUnvisited();
    queue.push(sourceAirport);
    nodes[sourceAirport].visited = true;

    while (!queue.empty()) {
        std::string curr = queue.front();
        queue.pop();
        for(const auto &adj : nodes[curr].adj) {
            if (!nodes[adj.dest].visited) {
                preNode[adj.dest] = curr;
                nodes[adj.dest].visited = true;

                if(adj.dest == targetAirport){
                    std::vector<Airport> path;
                    std::string node = adj.dest;

                    while (node != sourceAirport) {
                        path.insert(path.begin(),*nodes[node].airport);
                        node = preNode[node];
                    }
                    path.insert(path.begin(),*nodes[sourceAirport].airport);
                    return path;
                }
                queue.push(adj.dest);
            }
        }
    }
    return {};
}

std::vector<Airport> Graph::bfsMinPathAirline(const std::string& sourceAirport, const std::string& targetAirport, const std::vector<std::string>& wantedAirlines){
    std::queue<std::string> queue;
    std::unordered_map<std::string, std::string> preNode;

    setAllNodesToUnvisited();
    queue.push(sourceAirport);
    nodes[sourceAirport].visited = true;

    while (!queue.empty()) {
        std::string curr = queue.front();
        queue.pop();
        for(const auto &adj : nodes[curr].adj) {
            if (!nodes[adj.dest].visited && std::find(wantedAirlines.begin(), wantedAirlines.end(),adj.airlineCode) != wantedAirlines.end()) {
                preNode[adj.dest] = curr;
                nodes[adj.dest].visited = true;

                if(adj.dest == targetAirport){
                    std::vector<Airport> path;
                    std::string node = adj.dest;

                    while (node != sourceAirport) {
                        path.insert(path.begin(), *nodes[node].airport);
                        node = preNode[node];
                    }
                    path.insert(path.begin(),*nodes[sourceAirport].airport);
                    return path;
                }
                queue.push(adj.dest);
            }
        }
    }
    return {};
}


void Graph::dfsBestPaths(const string &start, const string &target, vector<Airport> &path, vector<vector<Airport>>& paths) {

    path[nodes[start].dist] = *nodes[start].airport;

    if (start == target) {
        paths.push_back(path);
        return;
    }
    nodes[start].visited = true;
    std::vector<std::string> destsUsed;
    for (auto &e: nodes[start].adj) {
        string next = e.dest;
        if (!nodes[next].visited && nodes[next].dist == nodes[start].dist + 1 && nodes[next].dist < path.size() && std::find(destsUsed.begin(), destsUsed.end(), next) == destsUsed.end()) {
            dfsBestPaths(next, target, path, paths);
            destsUsed.push_back(next);
        }
    }
    nodes[start].visited = false;
}

vector<vector<Airport>> Graph::findBestPaths(const std::string &start, const std::string &target) {
    bfs(start);

    if (nodes[target].dist == -1) {
        cout << "No path found" << endl;
        return {};
    }
    setAllNodesToUnvisited();

    vector<Airport> path (nodes[target].dist + 1);
    vector<std::vector<Airport>> paths;
    dfsBestPaths(start, target, path, paths);

    return paths;
}


void Graph::dfsBestPathsAirlines(const string &start, const string &target, vector<Airport> &path,
                                 vector<vector<Airport>> &paths,
                                 vector<string> wantedAirlines) {

    path[nodes[start].dist] = *nodes[start].airport;

    if (start == target) {
        paths.push_back(path);
        return;
    }
    nodes[start].visited = true;
    std::vector<std::string> destsUsed;
    for (auto &e: nodes[start].adj) {
        string next = e.dest;
        if (!nodes[next].visited && nodes[next].dist == nodes[start].dist + 1 && nodes[next].dist < path.size() && std::find(destsUsed.begin(), destsUsed.end(), next) == destsUsed.end() && find(wantedAirlines.begin(), wantedAirlines.end(), e.airlineCode) != wantedAirlines.end()) {
            dfsBestPathsAirlines(next, target, path, paths, wantedAirlines);
            destsUsed.push_back(next);
        }
    }
    nodes[start].visited = false;
}

vector<vector<Airport>> Graph::findBestPathsAirlines(const std::string &start, const std::string &target,
                                                     std::vector<std::string> wantedAirlines) {
    bfs(start);

    if (nodes[target].dist == -1) {
        cout << "No path found" << endl;
        return {};
    }
    setAllNodesToUnvisited();

    vector<Airport> path (nodes[target].dist  + 1);
    vector<vector<Airport>> paths;

    dfsBestPathsAirlines(start, target, path, paths, std::move(wantedAirlines));

    return paths;
}


std::list<std::string> Graph::findAirportsByCoords(double latitude, double longitude){ // use coords to find near airports
    std::list<std::string> airports;
    Airport aux = Airport("AUX", "AUX", "AUX", "AUX", latitude, longitude);

    for(const auto& node : nodes)
        if((utils::haversine(aux, *(node.second.airport))) < 80)
            airports.push_back(node.first);

    if(airports.empty())
        cout << "There's no airports in range in the coordinates: { " << latitude << ", " << longitude << " }" << endl;
    return airports;
}

std::list<std::string> Graph::findAirportsByCity(const std::string& city){ // use city name to find airports in the city
    std::list<std::string> airports;

    for (auto& node : nodes) {
        if(node.second.airport->getCity() == city)
            airports.push_back(node.first);
    }
    if(airports.empty())
        cout << "There's no airport in this city: " << city << endl;
    return airports;
}
