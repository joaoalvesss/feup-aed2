#include "../headers/Flight.h"


Flight::Flight(std::string sac, std::string tac, std::string code) : sourceAirportCode(std::move(sac)), targetAirportCode(std::move(tac)), airlineCode(std::move(code)) {
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