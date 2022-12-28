#ifndef PROJETO_AED_2_UTILS_H
#define PROJETO_AED_2_UTILS_H

#include <string>
#include <vector>

using namespace std;

namespace utils {
    namespace file {
        std::vector<std::string> readCsv(const std::string &fileName);
    }
    double haversine(double lat1, double lon1, double lat2, double lon2);
}
#endif