#include <iostream>
#include <string>

#include "JobInfo.h"

int main(void)
{
    std::string precision {"test"};
    int multiprecisionBits {0};
    int sampleRate {10};
    int renderLength {2};
    std::vector<int> modOutDependencyIds;
    modOutDependencyIds.push_back(0);
    std::vector<int> modOutProductIds;
    modOutProductIds.push_back(0);
    JobInfo jobInfo(precision, multiprecisionBits, sampleRate,
                    renderLength, modOutDependencyIds,
                    modOutProductIds);
    std::cout << jobInfo.precision << "\n" << jobInfo.multiprecisionBits << "\n"
              << jobInfo.sampleRate << "\n" << jobInfo.renderLength << "\n"
              << jobInfo.numberOfSamples << "\n" << jobInfo.modOutDependencyIds[0] << "\n"
              << jobInfo.modOutProductIds[0] << std::endl;

    return 0;
}
