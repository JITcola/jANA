#ifndef DSP_H
#define DSP_H

#include <vector>
#include "SampleValue.h"

using namespace std;

class Dsp {
public:
    static vector<SampleValue> lpf(const vector<SampleValue>& signal,
                                   const int sampleRate,
                                   const int cutoff);
    static vector<SampleValue> padUp(const vector<SampleValue>& signal,
                                     const int multiplier);
    static vector<SampleValue> decimate(const vector<SampleValue>& signal,
                                        const int divisor);

private:
    static vector<SampleValue> iDft(const vector<SampleValue> response);    
};

#endif
