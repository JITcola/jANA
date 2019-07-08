#include <iostream>
#include <filesystem>
#include <string>
#include <vector>

void processJob(int jobId);

int main(void)
{
    processJob(2);
    return 0;
}

void processJob(int jobId)
{
    int id {-1};
    std::string precision {""};
    std::string multiprecisionBits {""};
    std::string sampleRate {""};
    std::vector<int> externalModOutDependencies;
    std::vector<int> externalModInDependencies;    
}
