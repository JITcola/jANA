#include <iostream>
#include <string>

#include "JobFileReader.h"
#include "EvaluatorTemplate.h"

int main(void)
{
    JobFileReader reader;
    EvaluatorTemplate evaluatorTemplate;
    evaluatorTemplate = reader.readJobFile(5);
    return 0;
}
