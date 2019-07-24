#ifndef OPTIONPARAMETER_H
#define OPTIONPARAMETER_H

#include <string>

#include "Parameter.h"

class OptionParameter : public Parameter {
public:
    std::string value;

    std::string getValueAsString() {return value;}

    OptionParameter();
    OptionParameter(std::string name, std::string value)
        : Parameter(name), 
          value {value} {}
};

#endif
