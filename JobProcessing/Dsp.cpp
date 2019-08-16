#include "Dsp.h"

#include <cmath>
#include <gmp.h>
#include <mpfr.h>

using namespace std;

vector<SampleValue> Dsp::lpf(const vector<SampleValue>& signal,
                             const int sampleRate,
                             const int cutoff)
{
    const int taps = 256;
    vector<SampleValue> result;
    if (signal.size() == 0)
        return result;
    int n {static_cast<int>(floor((taps*cutoff)/((double)sampleRate)))};
    vector<SampleValue> response;
    if (signal[0].isMultiprecision) {
        for (int i = 0; i <= n; ++i)
            response.push_back(SampleValue(true,
                                           signal[0].multiprecisionBits,
                                           "1.0"));
        for (int i = n+1; i <= (taps-n-1); ++i)
            response.push_back(SampleValue(true,
                                           signal[0].multiprecisionBits,
                                           "0.0"));
        for (int i = taps-n; i < taps; ++i)
            response.push_back(SampleValue(true,
                                           signal[0].multiprecisionBits,
                                           "1.0"));
    } else {
        for (int i = 0; i <= n; ++i)
            response.push_back(SampleValue(1));
        for (int i = n+1; i <= (taps-n-1); ++i)
            response.push_back(SampleValue(0));
        for (int i = taps-n; i < taps; ++i)
            response.push_back(SampleValue(1));
    }
    vector<SampleValue> coeffs = iDft(response);
    if (signal[0].isMultiprecision) {
        mpfr_t sampleValue, signalValue;
        mpfr_inits2 (static_cast<mpfr_prec_t>(signal[0].multiprecisionBits),
                     sampleValue,
                     signalValue,
                     static_cast<mpfr_ptr>(0));
        for (long int i = 0; i < signal.size(); ++i) {
            mpfr_set_si (sampleValue, 0, MPFR_RNDN);
            if (i < taps-1) {
                for (long int j = 0; j <= i; ++j) {
                    mpfr_set (signalValue, signal[j].multiValue, MPFR_RNDN);
                    mpfr_mul (signalValue, signalValue,
                              coeffs[taps - 1 - i + j].multiValue, MPFR_RNDN);
                    mpfr_add (sampleValue, sampleValue, signalValue,
                              MPFR_RNDN);
                }
            } else {
                for (long int j = i - (taps-1); j <= i; ++j) {
                    mpfr_set (signalValue, signal[j].multiValue, MPFR_RNDN);
                    mpfr_mul (signalValue, signalValue,
                              coeffs[taps - 1 - i + j].multiValue, MPFR_RNDN);
                    mpfr_add (sampleValue, sampleValue, signalValue,
                              MPFR_RNDN);
                }
            }
            char* str;
            mpfr_asprintf (&str, "%Re", sampleValue);
            std::string valueString {str};
            mpfr_free_str (str);
            result.push_back(SampleValue(true, signal[0].multiprecisionBits,
                                         valueString));

        }
        mpfr_clears (sampleValue, signalValue, static_cast<mpfr_ptr>(0));
    } else
        for (long int i = 0; i < signal.size(); ++i) {
            double sampleValue = 0;
            if (i < taps-1) {
                for (long int j = 0; j <= i; ++j)
                    sampleValue = sampleValue +
                                  signal[j].doubleValue *
                                  coeffs[taps - 1 - i + j].doubleValue;
            } else {
                for (long int j = i - (taps-1); j <= i; ++j)
                    sampleValue = sampleValue +
                                  signal[j].doubleValue *
                                  coeffs[taps - 1 - i + j].doubleValue;
            }
            result.push_back(SampleValue(sampleValue));
        }

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
        mpfr_t *result_array = new mpfr_t[response.size()];
        if (!result_array)
            return result;
        for (int i = 0; i < response.size(); ++i)
            mpfr_init2 (result_array[i],
                        static_cast<mpfr_prec_t>(
                        response[0].multiprecisionBits));
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
            mpfr_set (result_array[i], coeff, MPFR_RNDN);
        }
        mpfr_t divisor;
        mpfr_init2 (divisor,
                    static_cast<mpfr_prec_t>(
                    response[0].multiprecisionBits));
        mpfr_set_si (divisor, 0, MPFR_RNDN);
        for (int i = 0; i < response.size(); ++i)
            mpfr_add (divisor, divisor, result_array[i], MPFR_RNDN);
        for (int i = 0; i < response.size(); ++i)
            mpfr_div (result_array[i], result_array[i], divisor, MPFR_RNDN);
        for (int i = 0; i < response.size(); ++i) {
            char* str;
            mpfr_asprintf (&str, "%Re", result_array[i]);
            std::string valueString {str};
            mpfr_free_str (str);
            result.push_back(SampleValue(true, response[0].multiprecisionBits,
                                         valueString));
        }
        for (int i = 0; i < response.size(); ++i)
            mpfr_clear (result_array[i]);
        delete[] result_array;
        mpfr_clears (coeff, i_multi, k_multi, response_multi, size_multi,
                     pi_multi, static_cast<mpfr_ptr>(0));
    } else {
        for (int i = 0; i < response.size(); ++i) {
            double coeff = 0;
            for (int k = 0; k < response.size(); ++k)
                coeff += response[k].doubleValue *
                         cos((2*k*i*pi)/response.size());
            coeff /= response.size();
            result.push_back(SampleValue(coeff));
        }
        double total = 0;
        for (auto sample: result)
            total += sample.doubleValue;
        for (long int i = 0; i < result.size(); ++i)
            result[i].doubleValue /= total;
    }
    return result;
}
