#ifndef PARAMETER_H
#define PARAMETER_H

#include <string>

class Parameter {
public:
    std::string name;

    virtual std::string getValueAsString() = 0;

    Parameter() = default;
    Parameter(std::string name) : name {name} {}
};

#endif
