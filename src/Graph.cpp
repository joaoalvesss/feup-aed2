#include  "../headers/Graph.h"
#include "../headers/Utils.h"
#include "../headers/Airline.h"

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
                    airlines.push_back(" ");
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
    //bfsWithDist(AirportCode1);
    int distance = nodes[AirportCode2].dist;
    return distance;
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

// DEVEM ESTAR ALGUNS TROCADOS TROCADOS BRUH
int Graph::getNumOfFlights(const std::string& airportCode){ // certo, I guess
    return (int) nodes[airportCode].adj.size();
}

int Graph::getNumAirCompanies(const std::string& airportCode) { // certo, I guess
    std::set<std::string> count;
    for (const auto& edge : nodes[airportCode].adj){
        if(count.find(edge.airlineCode) == count.end())
            count.insert(edge.airlineCode);
    }
    return (int) count.size();
}

int Graph::getNumDestinations(const std::string& airportCode){ // certo, I guess
    std::set<std::string> destinations;
    for (const auto& edge : nodes[airportCode].adj){
        if(destinations.find(edge.dest) == destinations.end())
            destinations.insert(edge.dest);
    }
    return (int) destinations.size();
}

int Graph::getNumFlightsFromCountries(const std::string &airportCode) { // certo, I guess
    std::set<std::string> countries;

    for (const auto& complete_node : nodes) {
        Node node = complete_node.second;
        for (const auto& edge : node.adj) {
            if (edge.dest == airportCode) {
                if (node.airport->getCountry() != nodes[airportCode].airport->getCountry()
                    and countries.find(node.airport->getCountry()) == countries.end())
                    countries.insert(node.airport->getCountry());
            }
        }
    }
    return (int) countries.size();
}


int Graph::getNumReachableAirports(const std::string& airportCode, int maxFlights){ // por verificar
    std::queue<std::string> queue;
    queue.push(airportCode);
    nodes[airportCode].visited = true;
    int numReachable = 1;

    while (!queue.empty()){
        std::string current = queue.front();
        queue.pop();

        for (const auto& edge : nodes[current].adj) {
            if (!nodes[edge.dest].visited) {
                queue.push(edge.dest);
                nodes[edge.dest].visited = true;
                numReachable++;
            }
        }
        if (nodes[current].dist > maxFlights)
            break;
    }
    return numReachable;
}

int Graph::getNumReachableCountries(const std::string& airportCode, int maxFlights){ // por verificar
    std::queue<std::string> queue;
    queue.push(airportCode);
    nodes[airportCode].visited = true;
    std::unordered_set<std::string> countries;
    countries.insert(nodes[airportCode].airport->getCountry());

    while (!queue.empty()) {
        std::string current = queue.front();
        queue.pop();

        for (const auto& edge : nodes[current].adj){
            if (!nodes[edge.dest].visited){
                if(countries.find(nodes[airportCode].airport->getCountry()) == countries.end()){
                    countries.insert(nodes[airportCode].airport->getCountry());
                    queue.push(edge.dest);
                }
                nodes[edge.dest].visited = true;
            }
        }
        if (nodes[current].dist > maxFlights)
            break;
    }
    return (int) countries.size();
}
int Graph::getNumReachableCities(const std::string& airportCode, int maxFlights){ // por verificar
    return 0;
}