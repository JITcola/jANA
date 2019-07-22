#include "Module.h"

#include <string>
#include "ModuleType.h"

ModuleType Module::moduleTypeFromString(std::string moduleTypeString)
{
    if (moduleTypeString == "FunctionGenerator")
        return ModuleType::FunctionGenerator;
    else if (moduleTypeString == "Delay")
        return ModuleType::Delay;
    else
        return ModuleType::NullModuleType;
}
