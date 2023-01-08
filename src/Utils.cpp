#include <fstream>
#include <cmath>
#include "../headers/Utils.h"
#include "../headers/Airport.h"

vector<std::string> utils::file::readCsv(const std::string& fileName) {
    ifstream openFile(fileName);
    vector<string> elements;
    string line;

    if (!openFile.is_open()) return elements;

    openFile.ignore(500, '\n');

    while(getline(openFile, line))
        elements.push_back(line);

    return elements;
}

double utils::haversine(const Airport& airport1, const Airport& airport2){
    double dLat = (airport2.getLat() - airport1.getLat()) * M_PI / 180.0;
    double dLon = (airport2.getLon() - airport1.getLon()) * M_PI / 180.0;

    double Lat1air = (airport1.getLat()) * M_PI / 180.0;
    double Lat2air = (airport2.getLat()) * M_PI / 180.0;

    double x = pow(sin(dLat / 2),2) +
               pow(sin(dLon / 2), 2) *
               cos(Lat1air) * cos(Lat2air);
    double rad = 6371;
    double c = 2 * asin(sqrt(x));
    return round(rad * c);
}