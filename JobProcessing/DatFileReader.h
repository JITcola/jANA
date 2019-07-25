#ifndef DATFILEREADER_H
#define DATFILEREADER_H

#include <vector>
#include "SampleValue.h"

class DatFileReader {
public:
    int modOutId;
    bool isMultiprecision;
    int multiprecisionBits;
    int sampleRate;
    int length;
    std::vector<SampleValue> data;

    void getData(int modOutId);
};

#endif
