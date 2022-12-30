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
    //graph->dfs(true, "CDG");
    //graph->helperPrint();
    //std::cout << graph->dist("SJZ", "LIS") << std::endl;
    Airport airport1 = Airport("RTM","Rotterdam","Rotterdam","Netherlands",51.956944,4.437222);
    Airport airport2 = Airport("YZV","Sept Iles","Sept-iles","Canada",50.223333,-66.265556);
    //std::cout << utils::haversine(airport1, airport2) << endl;
    //graph->bfsWithDist("CDG");
    //graph->minPath("OPO", "PXO");
    graph->distKm(airport1.getCode(), airport2.getCode());
}