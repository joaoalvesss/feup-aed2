#ifndef PROJETO_AED_2_UTILS_H
#define PROJETO_AED_2_UTILS_H

#include <string>
#include <vector>
#include "Airport.h"

using namespace std;

namespace utils {
    namespace file {
        /**
         * @param fileName
         * @return
         * Complexity O(n)
         */
        std::vector<std::string> readCsv(const std::string &fileName);
    }

    /**
     * @param airport1
     * @param airport2
     * @return real distance between two airports in kilometers
     * Complexity O(1)
     */
    double haversine(const Airport& airport1, const Airport& airport2);
}
#endif