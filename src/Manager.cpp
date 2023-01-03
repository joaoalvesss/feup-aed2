#include "../headers/Manager.h"
#include "../headers/Utils.h"


Manager::Manager() {
    std::vector<std::string> airports = utils::file::readCsv("../resources/airports.csv");
    std::vector<std::string> flights = utils::file::readCsv("../resources/flights.csv");
    std::vector<std::string> als = utils::file::readCsv("../resources/airlines.csv");
    this->graph = new Graph((int) airports.size());

    for (const std::string& line: airports){
        Airport* ap = Airport::readLine(line);
        this->graph->addNode(ap);
    }

    for (const std::string& line : flights){
        Flight* fl = Flight::readLine(line);
        this->graph->addEdge(fl);
    }

    for (const std::string& line : als) {
        Airline* al = Airline::readLine(line);
        this->airlines.insert({al->getAirlineCode(),al});
    }
}

void Manager::print(){
    for(auto& airport : graph->getNumReachableCountries("ETD", 1))
        std::cout << airport << endl;
    std::cout << graph->getNumReachableCountries("ETD", 1).size() << endl;

}

void Manager::printMinPath() {
    std::string start, target;
    std::cout << "\n\tPlease indicate the origin airport's code: ";
    (std::cin >> start).ignore().clear();
    std::cout << "\tPlease indicate the destiny airport's code: ";
    (std::cin >> target).ignore().clear();
    std::list<Airport> path = graph->bfsMinPath(start, target);
    for(Airport p : path){
        if (p.getCode() != target)
            std::cout << p.getName() << " (" << p.getCode() << ") --> ";
        else
            std::cout << p.getName() << " (" << p.getCode() << ")" << std::endl;

    }

}
void Manager::printMinPathAirlines() {
    std::string start, target;
    std::cout << "\n\tPlease indicate the origin airport's code: ";
    (std::cin >> start).ignore().clear();
    std::cout << "\tPlease indicate the destiny airport's code: ";
    (std::cin >> target).ignore().clear();
    vector<Airport> path = graph->bfsMinPathAirline(start, target, {"TAP", "VOZ"}).first;
    vector<std::string> airlines = graph->bfsMinPathAirline(start, target, {"TAP", "VOZ"}).second;
    ostringstream out;
    for(int i = 0; i < path.size(); i++) {
        Airport p = path[i];
        std::string a = airlines[i];
        if (p.getCode() != target) {
            std::cout << p.getName() << " (" << p.getCode() << ")" << " -----> ";
            out << std::string(p.getName().length() + 8, ' ') << a << "   ";;
        } else {
            std::cout << p.getName() << " (" << p.getCode() << ")" << std::endl;
            std::cout << out.str();
        }
    }
}

void Manager::printMinPathOptions() {
    this->graph->printShortestPaths("OPO", "TBU");
}

void Manager::printNumOfFlights(){
    std::string airPortCode;
    std::cout << "\n\tPlease indicate airport's code: ";
    (std::cin >> airPortCode).ignore().clear();
    std::cout << "\tNumber of Flights: " << graph->getNode(airPortCode).adj.size();
}

void Manager::printNumAirCompanies() {
    std::string airPortCode;
    std::cout << "\n\tPlease indicate airport's code: ";
    (std::cin >> airPortCode).ignore().clear();
    std::set<std::string> count;
    for (const auto& edge : graph->getNode(airPortCode).adj){
        if(count.find(edge.airlineCode) == count.end())
            count.insert(edge.airlineCode);
    }
    std::cout << "\tNumber of Air Companies: " << count.size();
}

void Manager::printNumDestinations() {
    std::string airPortCode;
    std::cout << "\n\tPlease indicate airport's code: ";
    (std::cin >> airPortCode).ignore().clear();
    std::set<std::string> destinations;
    for (const auto& edge : graph->getNode(airPortCode).adj){
        if(destinations.find(edge.dest) == destinations.end())
            destinations.insert(edge.dest);
    }
    std::cout << "\tNumber of Destinations: " << destinations.size();
}

void Manager::printNumCountries() {
    std::string airPortCode;
    std::cout << "\n\tPlease indicate airport's code: ";
    (std::cin >> airPortCode).ignore().clear();
    std::set<std::string> countries;

    for (const auto& complete_node : graph->getAllNodes()) {
        for (const auto& edge : complete_node.second.adj) {
            if (edge.dest == airPortCode) {
                if (complete_node.second.airport->getCountry() != graph->getAllNodes()[airPortCode].airport->getCountry()
                    and countries.find(complete_node.second.airport->getCountry()) == countries.end())
                    countries.insert(complete_node.second.airport->getCountry());
            }
        }
    }
    std::cout << "\tNumber of Countries: " << countries.size();
}



