#include "../headers/Manager.h"
#include "../headers/Airport.h"

Manager::Manager() {
    std::vector<std::string> airports = utils::file::readCsv("./resources/airports.csv");
    this->network = new Graph(airports.size());
    for (std::string line: airports) {
        Airport* ap = Airport::readLine(line);
    }


}