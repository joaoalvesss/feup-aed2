#include <string>
#include <vector>

#ifndef PROJETO_AED_2_UTILS_H
#define PROJETO_AED_2_UTILS_H
using namespace std;

namespace utils::file {
    std::vector<std::string> readCsv(const std::string& fileName);
}
#endif //PROJETO_AED_2_UTILS_H