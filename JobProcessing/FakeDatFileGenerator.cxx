#include <fstream>
#include <gmp.h>
#include <mpfr.h>

using namespace std;

int main(void)
{
    ofstream os {"ModOut11.dat"};

    os << "ModOut ID: 11" << endl
       << "Precision: multiprecision" << endl
       << "Multiprecision bits: 64" << endl
       << "Sample rate: 384000" << endl
       << "Length: 5" << endl
       << "Data:" << endl;

    mpfr_t currentSample;
    mpfr_init2 (currentSample, static_cast<mpfr_prec_t>(64));
    long int sampleRate {384000};
    long int numSamples {384000 * 5};
    for (long int i = 0; i < numSamples; ++i) {
        mpfr_set_si (currentSample, i, MPFR_RNDN);
        mpfr_div_si (currentSample, currentSample, sampleRate, MPFR_RNDN);
        mpfr_sin (currentSample, currentSample, MPFR_RNDN); 
        char* str;
        mpfr_asprintf (&str, "%Re", currentSample);
        string valueString {str};
        mpfr_free_str (str);
        os << valueString << endl;
    }

    mpfr_clear (currentSample);
    mpfr_free_cache ();

    return 0;
}




