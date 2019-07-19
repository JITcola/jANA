#ifndef EVALUATORTEMPLATE_H
#define EVALUATORTEMPLATE_H

#include <vector>

#include "ModuleRecord.h"
#include "JobInfo.h"
#include "Evaluator.h"
#include "ModOut.h"

class EvaluatorTemplate {
public:
    std::vector<ModuleRecord> moduleRecords;
    JobInfo jobInfo;

    Evaluator createEvaluator(void);

private:
    ModOut modOutFromId(int id);
};

#endif
