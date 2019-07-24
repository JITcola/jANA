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
    evaluatorTemplate = reader.readJobFile(3);
    evaluatorTemplate.jobInfo.precision = "multiprecision";
    evaluatorTemplate.jobInfo.multiprecisionBits = 100;
    Evaluator evaluator {evaluatorTemplate};
    for (auto& modulePtr: evaluator.modulePtrs) {
        if (modulePtr->moduleType == ModuleType::FunctionGenerator) {
            std::cout << "initLevel value: "
                      << (modulePtr->getParameter("initLevel")).getValueAsString()
                      << std::endl;
        } else if (modulePtr->moduleType == ModuleType::Delay) {
            std::cout << "initLevel value: "
                      << (modulePtr->getParameter("initLevel")).getValueAsString()
                      << std::endl;
        } else {
            std::cout << "Unknown ModuleType" << std::endl;
        }
        std::cout << "***" << std::endl;
    }

//    mpfr_out_str (stdout, 10, 0, evaluator.time[44099].multiValue, MPFR_RNDN);
    return 0;
}
