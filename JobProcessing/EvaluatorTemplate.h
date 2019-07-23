#ifndef EVALUATORTEMPLATE_H
#define EVALUATORTEMPLATE_H

#include <vector>
#include <string>

#include "ModuleRecord.h"
#include "JobInfo.h"

class EvaluatorTemplate {
public:
    std::vector<ModuleRecord> moduleRecords;
    JobInfo jobInfo;
};

#endif
