#include <iostream>
#include <string>

#include "JobFileReader.h"
#include "EvaluatorTemplate.h"

int main(void)
{
    JobFileReader reader;
    EvaluatorTemplate evaluatorTemplate;
    evaluatorTemplate = reader.readJobFile(2);

    std::cout << evaluatorTemplate.moduleRecords.size() << std::endl;
    for (auto record: evaluatorTemplate.moduleRecords) {
        for (auto parameter: record.parameters)
            std::cout << parameter.first << std::endl;
        std::cout << "***" << std::endl;
    }

    return 0;
}
