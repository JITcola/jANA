#ifndef JOBINFO_H
#define JOBINFO_H

#include <string>
#include <vector>

class JobInfo {
public:
    std::string precision;
    int multiprecisionBits;
    int sampleRate;
    int renderLength;
    long int numberOfSamples;
    std::vector<int> jobModOutDependencyIds;
    std::vector<int> jobModOutProductIds;
};

#endif

