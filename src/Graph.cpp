#include <stack>
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

std::list<Airport> Graph::bfsMinPath(const std::string& sourceAirport, const std::string& targetAirport){
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
                    std::list<Airport> path;
                    std::string node = adj.dest;

                    while (node != sourceAirport) {
                        path.push_front(*nodes[node].airport);
                        node = preNode[node];
                    }
                    path.push_front(*nodes[sourceAirport].airport);
                    return path;
                }
                queue.push(adj.dest);
            }
        }
    }
    return {};
}

std::pair<std::vector<Airport>, std::vector<std::string>> Graph::bfsMinPathAirline(const std::string &sourceAirport, const std::string &targetAirport, const std::vector<std::string>& wantedAirlines) {
    std::queue<std::string> queue;
    std::unordered_map<std::string, std::string> preNode;
    std::unordered_map<std::string, std::string> preFlight;


    setAllNodesToUnvisited();
    queue.push(sourceAirport);
    nodes[sourceAirport].visited = true;

    while (!queue.empty()) {
        std::string curr = queue.front();
        queue.pop();
        for(const auto &adj : nodes[curr].adj) {
            if (!nodes[adj.dest].visited && std::count(wantedAirlines.begin(), wantedAirlines.end(),adj.airlineCode) == 1) {
                preNode[adj.dest] = curr;
                preFlight[adj.dest] = adj.airlineCode;
                nodes[adj.dest].visited = true;

                if(adj.dest == targetAirport) {
                    std::vector<Airport> path;
                    std::vector<std::string> airlines;
                    std::string node = adj.dest;

                    while (node != sourceAirport) {
                        path.insert(path.begin(), *nodes[node].airport);
                        airlines.insert(airlines.begin(), preFlight[node]);
                        node = preNode[node];
                    }
                    path.insert(path.begin(), *nodes[sourceAirport].airport);
                    airlines.emplace_back(" ");
                    return {path, airlines};
                }
                queue.push(adj.dest);
            }
        }
    }
    return {};
}

void Graph::dfs(bool setAllVisitedToFalse, const std::string& AirportCode){
    if(setAllVisitedToFalse)
        setAllNodesToUnvisited();

    nodes.find(AirportCode)->second.visited = true;

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

std::vector<Airport*> Graph::shortestPaths (const std::string& node, const std::string& end, int depth, std::vector<Airport*>path = {}) {
    path.push_back(nodes[node].airport);
    if (node == end)
         return path;
    else {
        for (auto adj : nodes[node].adj) {
            if (nodes[adj.dest].dist < depth && nodes[adj.dest].dist == nodes[node].dist + 1){
                shortestPaths(adj.dest, end, depth, path);
            }
        }
    }
    return {};
}




// ESTAS DUAS FUNÇÕES FAZEM MIN PATH PARA A MENOR DISTANCIA
// PODEMOS ADICIONAR COMO EXTRA
/*
void Graph::DijkstraAlgorithm2(const std::string& sourceAirport) {
    // Set the distance of the source node to 0 and all other nodes to infinity
    for (auto &[key, node]: nodes) {
        if (node.airport->getCode() == sourceAirport) {
            node.distanceKm = 0;
        } else {
            node.distanceKm = std::numeric_limits<double>::infinity();
            node.previousNode = "";
        }
    }

    // Create a priority queue to store the nodes that still need to be processed
    std::priority_queue<std::pair<double, std::string>, std::vector<std::pair<double, std::string>>, std::greater<>> pq;
    pq.emplace(0, sourceAirport);

    // Process nodes in the queue until it is empty
    while (!pq.empty()) {
        auto [distance, airportCode] = pq.top();
        pq.pop();

        // Skip the node if it has already been processed
        if (nodes[airportCode].visited) continue;
        nodes[airportCode].visited = true;

        // Update the distance and previous node of the neighboring nodes
        for (const auto &edge: nodes[airportCode].adj) {
            const std::string &destAirportCode = edge.dest;
            double distance = edge.distance;
            if (nodes[destAirportCode].distanceKm > distance + nodes[airportCode].distanceKm) {
                nodes[destAirportCode].distanceKm = distance + nodes[airportCode].distanceKm;
                nodes[destAirportCode].previousNode = airportCode;
                pq.emplace(nodes[destAirportCode].distanceKm, destAirportCode);
            }
        }
    }
}

void Graph::printMinimumPath(const std::string &sourceAirport, const std::string &destAirport) {
    // Run Dijkstra's algorithm to find the minimum distance and previous nodes
    DijkstraAlgorithm2(sourceAirport);

    // Print the minimum path by starting at the destination airport and following the previous nodes back to the source airport
    std::string currentAirport = destAirport;
    while (currentAirport != sourceAirport) {
         std::cout << currentAirport << " <- ";
         currentAirport = nodes[currentAirport].previousNode;
     }
     std::cout << sourceAirport << std::endl;
 }
 */

/*
void Graph::DijkstraAlgorithm(const std::string& sourceAirport) { // Dijkstra minimum path
    nodes[sourceAirport].distanceKm = 0;
    nodes[sourceAirport].storeMinPath.push_back(*(nodes.find(sourceAirport)->second.airport));

    std::queue<std::pair<std::string, double>> helper;
    setAllNodesToUnvisited();

    for (auto &node: nodes) {
        if (sourceAirport != node.first) {
            node.second.distanceKm = (double) INT32_MAX;
            helper.push({node.first, node.second.distanceKm});
            continue;
        }
        helper.push({node.first, node.second.distanceKm});
    }

    while (!helper.empty()) {
        std::string aux = helper.front().first;
        helper.pop();

        for (auto &node: nodes[aux].adj) {
            double newDistance = nodes[aux].distanceKm + node.distance;

            if(newDistance < nodes[node.dest].distanceKm){
                nodes[node.dest].storeMinPath.clear();

                for(const Airport& airport : nodes[aux].storeMinPath)
                    nodes[node.dest].storeMinPath.push_back(airport);

                nodes[node.dest].distanceKm = nodes[aux].distanceKm + node.distance;
                nodes[node.dest].storeMinPath.push_back(*(nodes[node.dest].airport));
                helper.push({node.dest, node.distance + nodes[aux].distanceKm});
            }
        }
    }
}

double Graph::distKm(const std::string& AirportCode1, const std::string& AirportCode2){
    DijkstraAlgorithm(AirportCode2);
    return nodes[AirportCode1].distanceKm;
}
*/


//    -------------------------------------------- Estatistica --------------------------------
// DEVEM ESTAR ALGUNS TROCADOS TROCADOS BRUH

std::list<Airport> Graph::getNumReachableAirports(const std::string& airportCode, int maxFlights){ // MAL
    bfs(airportCode);
    std::list<Airport> airports;

    for(const auto& node : nodes){
        if(node.second.airport->getCode() == airportCode) continue;
        if(node.second.dist <= maxFlights) airports.push_back(*(node.second.airport));
    }
    return airports;
}

std::set<std::string> Graph::getNumReachableCountries(const std::string& airportCode, int maxFlights){ // MAL
    bfs(airportCode);
    std::set<std::string> countries;

    for(const auto& node : nodes){
        if(node.second.airport->getCountry() == nodes[airportCode].airport->getCountry()) continue;
        if(countries.find(node.second.airport->getCountry()) != countries.end()) continue;
        if(node.second.dist <= maxFlights) countries.insert(node.second.airport->getCountry());
    }
    return countries;
}

std::set<std::pair<std::string,std::string>> Graph::getNumReachableCities(const std::string& airportCode, int maxFlights){ // MAL
    bfs(airportCode);
    std::set<std::pair<std::string,std::string>> cities;

    for(const auto& node : nodes){
        if(node.second.airport->getCity() == nodes[airportCode].airport->getCity()) continue;
        if(cities.find({node.second.airport->getCity(), node.second.airport->getCountry()}) != cities.end()) continue;
        if(node.second.dist <= maxFlights) cities.insert({node.second.airport->getCity(), node.second.airport->getCountry()});
    }
    return cities;
}


void Graph::printShortestPaths(const std::string& start, const std::string& end) {
    // Run the breadth-first search to find the shortest path from the start airport to the end airport
    bfs(start);
    // Get the destination node
    Graph::Node endNode = nodes[end];
    // If the destination node has a distance of -1, it is unreachable from the start airport
    if (endNode.dist == -1) {
        std::cout << "There is no path from " << start << " to " << end << "." << std::endl;
        return;
    }
    // The shortest paths are the ones that have the same minimum distance as the destination node
    int minDistance = endNode.dist;
    std::vector<std::vector<std::string>> shortestPaths;
    for (const auto& node : nodes) {
        if (node.second.dist == minDistance) {
            shortestPaths.push_back(node.second.storeMinPath);
        }
    }
    // Print the shortest paths
    std::cout << "The shortest path(s) from " << start << " to " << end << " are:" << std::endl;
    for (const auto& path : shortestPaths) {
        for (const auto& airportCode : path) {
            std::cout << airportCode << " ";
        }
        std::cout << std::endl;
    }
}