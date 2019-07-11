#include "JobInfo.h"

#include <string>
#include <vector>

JobInfo::JobInfo(std::string precision, int multiprecisionBits, int sampleRate,
                 int renderLength, std::vector<int> modOutDependencyIds, 
                 std::vector<int> modOutProductIds)
    : precision {precision}, multiprecisionBits {multiprecisionBits}, 
      sampleRate {sampleRate}, renderLength {renderLength}, 
      modOutDependencyIds {modOutDependencyIds}, 
      modOutProductIds {modOutProductIds} 
{
    numberOfSamples = static_cast<long int>(sampleRate) * 
                      static_cast<long int>(renderLength);
}
