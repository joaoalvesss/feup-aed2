#include "../headers/Manager.h"
#include "../headers/Utils.h"

Manager::Manager() {
    std::vector<std::string> airports = utils::file::readCsv("./resources/airports.csv");
    std::vector<std::string> flights = utils::file::readCsv("./resources/flights.csv");
    std::vector<std::string> airlines = utils::file::readCsv("./resources/airlines.csv");
    this->graph = new Graph((int) airports.size());

    for (const std::string& line: airports){
        Airport* ap = Airport::readLine(line);
        this->graph->addNode(ap);
    }

    for (const std::string& line : flights){
        Flight* fl = Flight::readLine(line);
        this->graph->addEdge(fl);
    }
}

void Manager::print(){
    graph->dfs(true, "");
}