#ifndef PROJETO_AED_2_UTILS_H
#define PROJETO_AED_2_UTILS_H

#include <string>
#include <vector>
#include "Airport.h"

using namespace std;

namespace utils {
    namespace file {
        std::vector<std::string> readCsv(const std::string &fileName);
    }
    double haversine(const Airport& airport1, const Airport& airport2);
}
#endif