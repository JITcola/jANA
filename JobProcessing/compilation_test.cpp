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

int main(void)
{
    JobFileReader reader;
    EvaluatorTemplate evaluatorTemplate;
    evaluatorTemplate = reader.readJobFile(5);
    evaluatorTemplate.jobInfo.precision = "multiprecision";
    evaluatorTemplate.jobInfo.multiprecisionBits = 512;
    Evaluator evaluator {evaluatorTemplate};
    for (auto& modulePtr: evaluator.modulePtrs) {
        std::cout << "frequency (" << (modulePtr->getModIn("frequency")).name << ") -> ";
        if ((modulePtr->getModIn("frequency")).source != nullptr)
            std::cout << (modulePtr->getModIn("frequency")).source->name;
        else
            std::cout << "nullptr";
        std::cout << std::endl;
        std::cout << "phase (" << (modulePtr->getModIn("phase")).name << ") -> ";
        if ((modulePtr->getModIn("phase")).source != nullptr)
            std::cout << (modulePtr->getModIn("phase")).source->name;
        else
            std::cout << "nullptr";
        std::cout << std::endl;
        std::cout << "level (" << (modulePtr->getModIn("level")).name << ") -> ";
        if ((modulePtr->getModIn("level")).source != nullptr)
            std::cout << (modulePtr->getModIn("level")).source->name;
        else
            std::cout << "nullptr";
        std::cout << std::endl;
        std::cout << "***" << std::endl;
    }

//    mpfr_out_str (stdout, 10, 0, evaluator.time[44099].multiValue, MPFR_RNDN);
    return 0;
}
