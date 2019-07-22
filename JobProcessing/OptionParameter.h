#ifndef OPTIONPARAMETER_H
#define OPTIONPARAMETER_H

#include <string>

#include "Parameter.h"

class OptionParameter : public Parameter {
public:
    std::string value;

    OptionParameter();
    OptionParameter(std::string name, std::string value)
        : Parameter(name) { this->value = value; }
};

#endif
