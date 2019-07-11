#include <iostream>
#include <string>

#include "JobFileReader.h"
#include "EvaluatorTemplate.h"

int main(void)
{
    JobFileReader reader;
    EvaluatorTemplate template;
    template = reader.readJobFile(2);
    return 0;
}
