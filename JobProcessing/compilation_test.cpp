#include <iostream>
#include <string>

#include "JobInfo.h"
#include "ModuleRecord.h"
#include "EvaluatorTemplate.h"
#include "SampleValue.h"

using namespace std::literals::string_literals;

int main(void)
{
    JobInfo jobInfo;
    ModuleRecord moduleRecord;
    EvaluatorTemplate evaluatorTemplate;
    SampleValue sampleValue1;
    SampleValue sampleValue2(2.718);
    SampleValue sampleValue3(true, 256);
    SampleValue sampleValue4(true, 1024, "2.718"s);
    
    mpfr_free_cache ();
    std::cout << "Compilation successful" << std::endl;

    return 0;
}
