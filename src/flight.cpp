#include "flight.h"

Flight::Flight(const std::string &sac, const std::string &tac, const std::string &code) : sourceAirportCode(sac), targetAirportCode(tac), airlineCode(code) {
    flights = utils::file::readCsv("./resources/flights.csv");
}

Flight* Flight::readLine(const std::string &line) {
    std::string sac, tac, code, word;
    std::vector<std::string> words;
    std::stringstream stream(line);

    while (getline(stream, word, ','))
        words.push_back(word);

    if(words.size() != 3)
        return nullptr;

    sac = words.at(0);
    tac = words.at(1);
    code = words.at(2);
    return new Flight(sac, tac, code);
    }