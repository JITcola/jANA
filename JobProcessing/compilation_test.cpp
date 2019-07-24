#include <vector>
#include <iostream>
#include <string>
#include <cstdio>
#include <gmp.h>
#include <mpfr.h>

#include "JobFileReader.h"
#include "Evaluator.h"
#include "EvaluatorTemplate.h"
#include "FunctionGenerator.h"
#include "Delay.h"
#include "SampleValue.h"
#include "ModuleType.h"

int main(void)
{
    JobFileReader reader;
    EvaluatorTemplate evaluatorTemplate;
    evaluatorTemplate = reader.readJobFile(2);
    evaluatorTemplate.jobInfo.precision = "multiprecision";
    evaluatorTemplate.jobInfo.multiprecisionBits = 512;
    Evaluator evaluator {evaluatorTemplate};
    for (auto& modulePtr: evaluator.modulePtrs) {
        if (modulePtr->moduleType == ModuleType::FunctionGenerator) {
            std::cout << "frequency -> "
                      << ((modulePtr->getModIn("frequency")).source != nullptr ?
                         (modulePtr->getModIn("frequency")).source->name :
                         "nullptr")
                      << std::endl;
            std::cout << "phase -> "
                      << ((modulePtr->getModIn("phase")).source != nullptr ?
                         (modulePtr->getModIn("phase")).source->name :
                         "nullptr")
                      << std::endl;
            std::cout << "level -> "
                      << ((modulePtr->getModIn("level")).source != nullptr ?
                         (modulePtr->getModIn("level")).source->name :
                         "nullptr")
                      << std::endl;
        } else if (modulePtr->moduleType == ModuleType::Delay) {
            std::cout << "input -> "
                      << ((modulePtr->getModIn("input")).source != nullptr ?
                         (modulePtr->getModIn("input")).source->name :
                         "nullptr")
                      << std::endl;
            std::cout << "time -> "
                      << ((modulePtr->getModIn("time")).source != nullptr ?
                         (modulePtr->getModIn("time")).source->name :
                         "nullptr")
                      << std::endl;
            std::cout << "feedback -> "
                      << ((modulePtr->getModIn("feedback")).source != nullptr ?
                         (modulePtr->getModIn("feedback")).source->name :
                         "nullptr")
                      << std::endl;
            std::cout << "level -> "
                      << ((modulePtr->getModIn("level")).source != nullptr ?
                         (modulePtr->getModIn("level")).source->name :
                         "nullptr")
                      << std::endl;
        } else {
            std::cout << "Unknown ModuleType" << std::endl;
        }
        std::cout << "***" << std::endl;
    }

//    mpfr_out_str (stdout, 10, 0, evaluator.time[44099].multiValue, MPFR_RNDN);
    return 0;
}
