#include "Dsp.h"

#include <cmath>
#include <gmp.h>
#include <mpfr.h>

using namespace std;

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
    for (long int i = 0; i < signal.size(); ++i)
        if (i % divisor == 0)
            result.push_back(signal[i]);
    return result;
}

vector<SampleValue> Dsp::iDft(const vector<SampleValue> response)
{
    vector<SampleValue> result;
    if (response.size() == 0)
        return result;
    if (response[0].isMultiprecision) {
        mpfr_t coeff, i_multi, k_multi, response_multi, size_multi, pi_multi;
        mpfr_inits2 (static_cast<mpfr_prec_t>(
                     response[0].multiprecisionBits),
                     coeff, i_multi, k_multi, response_multi,
                     size_multi, pi_multi, static_cast<mpfr_ptr>(0));
        mpfr_set_si (size_multi, response.size(), MPFR_RNDN);
        mpfr_const_pi (pi_multi, MPFR_RNDN);
        for (int i = 0; i < response.size(); ++i) {
            mpfr_set_si (coeff, 0, MPFR_RNDN);
            mpfr_set_si (i_multi, i, MPFR_RNDN);
            for (int k = 0; k < response.size(); ++k) {
                mpfr_set_si (k_multi, k, MPFR_RNDN);
                mpfr_set (response_multi, response[k].multiValue, MPFR_RNDN);

                mpfr_mul (k_multi, k_multi, i_multi, MPFR_RNDN);
                mpfr_mul_si (k_multi, k_multi, 2, MPFR_RNDN);
                mpfr_mul (k_multi, k_multi, pi_multi, MPFR_RNDN);
                mpfr_div (k_multi, k_multi, size_multi, MPFR_RNDN);
                mpfr_cos (k_multi, k_multi, MPFR_RNDN);
                mpfr_mul (response_multi, response_multi, k_multi, MPFR_RNDN);
                mpfr_add (coeff, coeff, response_multi, MPFR_RNDN);
            }
            mpfr_div (coeff, coeff, size_multi, MPFR_RNDN);
            char* str;
            mpfr_asprintf (&str, "%Re", coeff);
            std::string valueString {str};
            mpfr_free_str (str);
            result.push_back(SampleValue(true, response[0].multiprecisionBits,
                                         valueString));
        }
        mpfr_clears (coeff, i_multi, k_multi, response_multi, size_multi,
                     pi_multi, static_cast<mpfr_ptr>(0));
    } else
        for (int i = 0; i < response.size(); ++i) {
            double coeff = 0;
            for (int k = 0; k < response.size(); ++k)
                coeff += response[k].doubleValue *
                         cos((2*k*i*pi)/response.size());
            coeff /= response.size();
            result.push_back(SampleValue(coeff));
        }
    return result;
}