#include "Dsp.h"

vector<SampleValue> Dsp::lpf(const vector<SampleValue>& signal,
                             const int sampleRate,
                             const int cutoff)
{
    vector<SampleValue> result;
    return result;
}

vector<SampleValue> Dsp::padUp(const vector<SampleValue>& signal,
                               const int multiplier)
{
    vector<SampleValue> result;
    for (long int i = 0; i < signal.size(); ++i) {
        result.push_back(signal[i]);
        for (long int j = 1; j < multiplier; ++j)
            if (signal[i].isMultiprecision)
                result.push_back(SampleValue(true,
                                             signal[i].multiprecisionBits,
                                             "0.0"));
            else
                result.push_back(SampleValue(0.0));
    }
    return result;
}

vector<SampleValue> Dsp::decimate(const vector<SampleValue>& signal,
                                  const int divisor)
{
    vector<SampleValue> result;
    return result;
}

vector<SampleValue> Dsp::iDft(const vector<SampleValue> response)
{
    vector<SampleValue> result;
    return result;
}
