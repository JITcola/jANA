#include <iostream>
#include <string>
#include <cstdio>
#include <gmp.h>
#include <mpfr.h>

#include "JobFileReader.h"
#include "EvaluatorTemplate.h"

int main(void)
{
    JobFileReader reader;
    EvaluatorTemplate evaluatorTemplate;
    evaluatorTemplate = reader.readJobFile(2);
    evaluatorTemplate.jobInfo.precision = "multiprecision";
    evaluatorTemplate.jobInfo.multiprecisionBits = 512;
    Evaluator evaluator;
    evaluator = evaluatorTemplate.createEvaluator();

    std::cout << evaluatorTemplate.moduleRecords.size() << std::endl;
    for (auto record: evaluatorTemplate.moduleRecords) {
        for (auto parameter: record.parameters)
            std::cout << parameter.first << std::endl;
        std::cout << "***" << std::endl;
    }

    mpfr_out_str (stdout, 10, 0, evaluator.time[88200].multiValue, MPFR_RNDN);

    return 0;
}
