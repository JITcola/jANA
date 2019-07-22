#include <vector>
#include <iostream>
#include <string>
#include <cstdio>
#include <gmp.h>
#include <mpfr.h>

#include "JobFileReader.h"
#include "EvaluatorTemplate.h"
#include "FunctionGenerator.h"
#include "Delay.h"
#include "SampleValue.h"

int main(void)
{
    JobFileReader reader;
    EvaluatorTemplate evaluatorTemplate;
    evaluatorTemplate = reader.readJobFile(2);
    evaluatorTemplate.jobInfo.precision = "multiprecision";
    evaluatorTemplate.jobInfo.multiprecisionBits = 512;
    std::cout << evaluatorTemplate.moduleRecords[0].moduleType << std::endl;
    std::vector<SampleValue> time;
    FunctionGenerator newFunctionGenerator {true, 
                                            evaluatorTemplate.jobInfo.multiprecisionBits,
                                            time,
                                            evaluatorTemplate.moduleRecords[0]};

    Evaluator evaluator;
    evaluator = evaluatorTemplate.createEvaluator();
    std::cout << evaluatorTemplate.moduleRecords.size() << std::endl;
    for (auto record: evaluatorTemplate.moduleRecords) {
        for (auto parameter: record.parameters)
            std::cout << parameter.first << std::endl;
        std::cout << "***" << std::endl;
    }

    mpfr_out_str (stdout, 10, 0, evaluator.time[44099].multiValue, MPFR_RNDN);
    return 0;
}
