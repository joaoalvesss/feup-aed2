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



void Manager::print() {
    travelByCities();
}

void Manager::printAirlinesPath(std::vector<Airport>& path) {
    std::string target = path.back().getCode();
    std::vector<std::vector<std::string>> airl;
    if (path.empty()) {
        std::cout << "There's no path in between those 2 airports\n";
        return;
    }
    for (int i = 0; i < path.size() - 1; i++) {
        Airport source = path[i];
        Airport dest = path[i + 1];
        vector<std::string> helper;

        for (const auto& ad : this->graph->getNode(source.getCode()).adj)
            if (ad.dest == dest.getCode())
                helper.push_back(ad.airlineCode);
        airl.push_back(helper);
    }

    for (auto p : path) {
        if (p.getCode() == target)
            std::cout << p.getName() << " (" << p.getCode() << ")" << std::endl;
        else
            std::cout << p.getName() << " (" << p.getCode() << ")" << " -----> ";
    }
    size_t max = 0;
    for (const auto& a : airl)
        if (a.size() > max)
            max = a.size();
    for (auto& a : airl)
        while(a.size() != max)
            a.emplace_back("   ");
    for (int i = 0; i < max; i++) {
        ostringstream out;

        for (int j = 0; j< airl.size(); j++) {
            out << std::string(path[j].getName().length() + 8, ' ') << airl[j][i] << "   ";
        }
        std::cout << out.str() << std::endl;
    }
}

void Manager::printMinPath() {
    std::string start, target;
    std::cout << "\n\tPlease indicate the origin airport's code: ";
    (std::cin >> start).ignore().clear();
    if (!checkIfAirportExists(start)) {
        std::cout << "This airport doesn't exist: " << start << std::endl;
        return;
    }

    std::cout << "\tPlease indicate the destiny airport's code: ";
    (std::cin >> target).ignore().clear();
    if (!checkIfAirportExists(target)) {
        std::cout << "This airport doesn't exist: " << start << std::endl;
        return;
    }

    std::vector<Airport> path = graph->bfsMinPath(start, target);
    std::vector<std::vector<std::string>> airl;
    if (path.empty()) {
        std::cout << "There's no path in between those 2 airports\n";
        return;
    }


    for (int i = 0; i < path.size() - 1; i++) {
        Airport source = path[i];
        Airport dest = path[i + 1];
        vector<std::string> helper;

        for (const auto& ad : this->graph->getNode(source.getCode()).adj)
            if (ad.dest == dest.getCode())
                helper.push_back(ad.airlineCode);
        airl.push_back(helper);
    }

    for (auto p : path) {
        if (p.getCode() == target)
            std::cout << p.getName() << " (" << p.getCode() << ")" << std::endl;
        else
            std::cout << p.getName() << " (" << p.getCode() << ")" << " -----> ";
    }
    size_t max = 0;
    for (const auto& a : airl)
        if (a.size() > max)
            max = a.size();
    for (auto& a : airl)
        while(a.size() != max)
            a.emplace_back("   ");
    for (int i = 0; i < max; i++) {
        ostringstream out;

        for (int j = 0; j< airl.size(); j++) {
            out << std::string(path[j].getName().length() + 8, ' ') << airl[j][i] << "   ";
        }
        std::cout << out.str() << std::endl;
    }


}
void Manager::printMinPathAirlines() {
    std::string start, target, airline = " ";
    std::vector<std::string> wantedAirlines;
    std::cout << "\n\tPlease indicate the origin airport's code: ";
    (std::cin >> start).ignore().clear();
    if (!checkIfAirportExists(start)) {
        std::cout << "This airport doesn't exist: " << start << std::endl;
        return;
    }
    std::cout << "\tPlease indicate the destiny airport's code: ";
    (std::cin >> target).ignore().clear();
    if (!checkIfAirportExists(target)) {
        std::cout << "This airport doesn't exist: " << start << std::endl;
        return;
    }

    std::cout << "\tPlease indicate the desired airlines codes:" << std::endl;
    std::cout << "\n\t Type DONE when finished" << std::endl;
    while ( airline != "DONE") {
        std::cout << "\t> ";
        std::cin >> airline;
        std::transform(airline.begin(), airline.end(), airline.begin(), ::toupper);
        if (airline != "DONE")
            wantedAirlines.push_back(airline);
    }
    std::cout << '\n';

    for (const std::string& airlineCode : wantedAirlines) {
        if (airlines.count(airlineCode) == 0) {
            std::cout << "This Airline doesn't exist: " << airlineCode << std::endl;
            return;
        }
    }

    std::vector<Airport> path = graph->bfsMinPathAirline(start, target, wantedAirlines);
    std::vector<std::vector<std::string>> airl;

    printAirlinesPath(path);
   /* if (path.empty()) {
        std::cout << "There's no path in between those 2 airports\n";
        return;
    }

    for (int i = 0; i < path.size() - 1; i++) {
        Airport source = path[i];
        Airport dest = path[i + 1];
        vector<std::string> helper;

        for (const auto& ad : this->graph->getNode(source.getCode()).adj)
            if (ad.dest == dest.getCode() && std::find(wantedAirlines.begin(), wantedAirlines.end(), ad.airlineCode) != wantedAirlines.end())
                helper.push_back(ad.airlineCode);
        airl.push_back(helper);
    }
    for (auto p : path) {
        if (p.getCode() == target)
            std::cout << p.getName() << " (" << p.getCode() << ")" << std::endl;
        else
            std::cout << p.getName() << " (" << p.getCode() << ")" << " -----> ";
    }
    size_t max = 0;
    for (const auto& a : airl)
        if (a.size() > max)
            max = a.size();
    for (auto& a : airl)
        while(a.size() != max)
            a.emplace_back("   ");
        for (int i = 0; i < max; i++) {
            ostringstream out;

            for (int j = 0; j< airl.size(); j++) {
                out << std::string(path[j].getName().length() + 8, ' ') << airl[j][i] << "   ";
            }
            std::cout << out.str() << std::endl;
    }
*/
}

/*void Manager::printMinPathAirlines() {
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
*/ // printMinPathAirlines não apagar - Pedro

//TODO
void Manager::printMinPathOptions() {

}

void Manager::printAirportGeneralInfo() {
    std::string airPortCode;
    std::cout << "\n\tPlease indicate airport's code: ";
    (std::cin >> airPortCode).ignore().clear();
    if (Manager::checkIfAirportExists(airPortCode)) {
        Manager::printNumOfOutgoingFlights(airPortCode);
        Manager::printNumAirCompanies(airPortCode);
        Manager::printNumAirports(airPortCode);
        Manager::printNumCountries(airPortCode);
    }
    else {
        std::cout << "\n\tAirport " << airPortCode << " doesn't exist";
    }
}

void Manager::printAirportInfoMaxFlights() {
    std::string airPortCode;
    std::cout << "\n\tPlease indicate airport's code: ";
    (std::cin >> airPortCode).ignore().clear();

    int maxFlights;
    std::cout << "\n\tPlease indicate the maximum number of flights: ";
    (std::cin >> maxFlights).ignore().clear();

    if (checkIfAirportExists(airPortCode)) {
        Manager::printReachableAirports(airPortCode, maxFlights);
        Manager::printReachableCities(airPortCode, maxFlights);
        Manager::printReachableCountries(airPortCode, maxFlights);
    }
    else {
        std::cout << "\n\tAirport " << airPortCode << " doesn't exist";
    }
}

void Manager::printNumOfOutgoingFlights(std::string airPortCode){
    std::cout << "\tNumber of Flights: " << graph->getNode(airPortCode).adj.size() << std::endl;
}

void Manager::printNumAirCompanies(std::string airPortCode) {
    std::set<std::string> count;
    for (const auto& edge : graph->getNode(airPortCode).adj){
        if(count.find(edge.airlineCode) == count.end())
            count.insert(edge.airlineCode);
    }
    std::cout << "\tNumber of Air Companies: " << count.size() << std::endl;
}

void Manager::printNumAirports(std::string airPortCode) {
    std::set<std::string> destinations;
    for (const auto& edge : graph->getNode(airPortCode).adj){
        if(destinations.find(edge.dest) == destinations.end())
            destinations.insert(edge.dest);
    }
    std::cout << "\tNumber of Destinations: " << destinations.size() << std::endl;
}

void Manager::printNumCountries(std::string airPortCode) {
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
    std::cout << "\tNumber of Countries: " << countries.size() << std::endl;
}

void Manager::printReachableAirports(const std::string &airPortCode, int maxFlights) {
    std::list<Airport> airportList = Manager::getReachableAirports(airPortCode, maxFlights);
    std::cout << "\t    Number of Airports reachable with " << maxFlights << " flights: " <<  airportList.size() << std::endl;
}

std::list<Airport> Manager::getReachableAirports(const std::string& airportCode, int maxFlights){
    graph->bfs(airportCode);
    std::list<Airport> airports;

    for(const auto& node : graph->getAllNodes())
        if (node.second.dist <= maxFlights && node.second.dist > 0)
            airports.push_back(*(node.second.airport));

    return airports;
}

void Manager::printReachableCountries(const std::string &airPortCode, int maxFlights) {
    std::set<std::string> countries = Manager::getReachableCountries(airPortCode, maxFlights);
    std::cout << "\tNumber of Countries reachable with " << maxFlights << " flights: " <<  countries.size() << std::endl;
}

std::set<std::string> Manager::getReachableCountries(const std::string& airportCode, int maxFlights){
    graph->bfs(airportCode);
    std::set<std::string> countries;

    for(const auto& node : graph->getAllNodes()){
        if(countries.find(node.second.airport->getCountry()) != countries.end()) continue;
        if(node.second.dist <= maxFlights && node.second.dist > 0) countries.insert(node.second.airport->getCountry());
    }
    return countries;
}

void Manager::printReachableCities(const std::string &airPortCode, int maxFlights) {
    std::set<std::pair<std::string,std::string>> cities = Manager::getReachableCities(airPortCode, maxFlights);
    std::cout << "\tNumber of Cities reachable with " << maxFlights << " flights: " <<  cities.size() << std::endl;
}

// MAL
std::set<std::pair<std::string,std::string>> Manager::getReachableCities(const std::string& airportCode, int maxFlights){
    graph->bfs(airportCode);
    std::set<std::pair<std::string,std::string>> cities; // city and country

    for(const auto& node : graph->getAllNodes()){
        if(node.second.airport->getCity() == graph->getAllNodes()[airportCode].airport->getCity()) continue;
        if(cities.find({node.second.airport->getCity(), node.second.airport->getCountry()}) != cities.end()) continue;
        if(node.second.dist <= maxFlights) cities.insert({node.second.airport->getCity(), node.second.airport->getCountry()});
    }
    return cities;
}


void Manager::travelByCities() {
    std::string sourceCity, targetCity;
    std::cout << "\n\tPlease indicate the starting city: ";
    (std::cin >> sourceCity).ignore().clear();
    std::cout << "\n\tPlease indicate the target city: ";
    (std::cin >> targetCity).ignore().clear();
    std::list<std::string> sourceAirports = this->graph->findAirportsByCity(sourceCity);
    std::list<std::string> targetAirports = this->graph->findAirportsByCity(targetCity);
    std::vector<Airport> airports;
    std::vector<std::string> res;
    size_t minSize = INT8_MAX;

    for (std::string &air1: sourceAirports) {
        for (std::string &air2: targetAirports) {
            if ((graph->bfsMinPath(air1, air2).size()) < minSize) {
                airports = graph->bfsMinPath(air1, air2);
                minSize = graph->bfsMinPath(air1, air2).size();
            }
        }
    }

    printAirlinesPath(airports);
}

void Manager::travelByCoords(){
    double lat1, lon1, lat2, lon2;
    std::cout << "\n\tPlease indicate the starting latitude: ";
    (std::cin >> lat1).ignore().clear();
    std::cout << "\n\tPlease indicate the starting longitude: ";
    (std::cin >> lon1).ignore().clear();

    std::cout << "\n\tPlease indicate the target latitude: ";
    (std::cin >> lat2).ignore().clear();
    std::cout << "\n\tPlease indicate the target longitude: ";
    (std::cin >> lon2).ignore().clear();
    std::list<std::string> sourceAirports = this->graph->findAirportsByCoords(lat1, lon1);
    std::list<std::string> targetAirports = this->graph->findAirportsByCoords(lat2, lon2);
    std::vector<Airport> airports;
    std::vector<std::string> res;
    size_t minSize = INT8_MAX;

    for(std::string& air1 : sourceAirports){
        for(std::string& air2 : targetAirports){
            if((graph->bfsMinPath(air1, air2).size()) < minSize){
                airports = graph->bfsMinPath(air1, air2);
                minSize = graph->bfsMinPath(air1, air2).size();
            }
        }
    }

    printAirlinesPath(airports);
}

bool Manager::checkIfAirportExists(const std::string &airportCode) {
    if (graph->getAllNodes().count(airportCode) == 1)
        return true;
    return false;
}

//43.282900,17.845878, 37.245667,-93.388639