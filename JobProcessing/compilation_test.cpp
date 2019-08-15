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
#include "DatFileReader.h"
#include "Dsp.h"

int main(void)
{
    JobFileReader reader;
    EvaluatorTemplate evaluatorTemplate;
    evaluatorTemplate = reader.readJobFile(3);
    evaluatorTemplate.jobInfo.precision = "multiprecision";
    evaluatorTemplate.jobInfo.multiprecisionBits = 64;
    Evaluator evaluator {evaluatorTemplate};

    /*
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

    DatFileReader datFileReader;
    datFileReader.getData(11);
    for (auto value: datFileReader.data)
        std::cout << value.to_string() << '\n';

    std::cout << "************************\n";
    */

    std::vector<SampleValue> v1, v2;
    v1.push_back(SampleValue(true, 256, "1.2834832"));
    v1.push_back(SampleValue(true, 256, "2.813838289"));
    v1.push_back(SampleValue(true, 256, "0.82918353"));
    v2 = Dsp::padUp(v1, 3);
    for (auto value: v2)
        std::cout << value.to_string() << '\n';
    v1 = Dsp::decimate(v2, 3);
    std::cout << "*************************\n";
    for (auto value: v1)
        std::cout << value.to_string() << '\n';
    std::vector<SampleValue> v3, v4;
    v3.push_back(SampleValue(true, 256, "1.0"));
    v3.push_back(SampleValue(true, 256, "0.0"));
    v3.push_back(SampleValue(true, 256, "1.0"));
    v3.push_back(SampleValue(true, 256, "0.0"));
    v3.push_back(SampleValue(true, 256, "1.0"));
    v3.push_back(SampleValue(true, 256, "1.0"));
    v3.push_back(SampleValue(true, 256, "1.0"));
    v4 = Dsp::iDft(v3);
    for (auto value: v4)
        std::cout << value.to_string() << '\n';


/*
    std::cout << datFileReader.modOutId << std::endl
              << datFileReader.isMultiprecision << std::endl;
*/


//    mpfr_out_str (stdout, 10, 0, evaluator.time[44099].multiValue, MPFR_RNDN);
    return 0;
}
