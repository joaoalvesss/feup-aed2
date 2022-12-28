#include <fstream>
#include <cmath>
#include "../headers/Utils.h"

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

double utils::haversine(double lat1, double lon1, double lat2, double lon2){
    // distance between locations by coords
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;

    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    double a = pow(sin(dLat / 2), 2) * pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}