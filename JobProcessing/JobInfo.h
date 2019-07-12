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
    std::vector<int> modOutDependencyIds;
    std::vector<int> modOutProductIds;

    JobInfo() = default;
    JobInfo(std::string precision, int multiprecisionBits, int sampleRate,
            int renderLength, std::vector<int> modOutDependencyIds, 
            std::vector<int> modOutProductIds);
};

#endif

