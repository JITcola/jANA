#ifndef PARAMETER_H
#define PARAMETER_H

#include <string>

class Parameter {
public:
    std::string name;

    Parameter() = default;
    Parameter(std::string name) : name {name} {}
};

#endif
