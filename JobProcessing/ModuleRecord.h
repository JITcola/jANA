#ifndef MODULERECORD_H
#define MODULERECORD_H

#include <string>
#include <vector>
#include <utility>

class ModuleRecord {
public:
    std::string moduleType;
    std::vector<std::pair<std::string, std::string>> parameters;
    std::vector<std::pair<std::pair<std::string, int>, int>> dependencies;
};

#endif
