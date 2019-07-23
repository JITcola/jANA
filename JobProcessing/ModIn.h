#ifndef MODIN_H
#define MODIN_H

#include <string>

#include "ModOut.h"
#include "SampleValue.h"

class ModIn {
public:
    std::string name;
    ModOut* source;

    ModIn() 
        : name {"Unnamed ModIn"}, source {nullptr} {}
    ModIn(std::string name)
        : name {name}, source {nullptr} {}
    ModIn(std::string name, ModOut* source)
        : name {name}, source {source} {}
};

#endif
