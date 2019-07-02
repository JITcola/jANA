#include <iostream>
#include <chrono>

#include <stdio.h>
#include <gmp.h>
#include <mpfr.h>

#define PRECISION 512 

int main(void)
{
    mpfr_t sampleRate, two, pi, frequency, multiplier;
    mpfr_t *result;
    result = (mpfr_t *)malloc(sizeof(mpfr_t) * 109375000);

    using namespace std::chrono;
    auto t0 = high_resolution_clock::now();

    mpfr_inits2 (PRECISION, sampleRate, two, pi, frequency,
                 multiplier, (mpfr_ptr) 0);

    mpfr_set_str (sampleRate, "44100", 10, MPFR_RNDN);
    mpfr_set_str (two, "2", 10, MPFR_RNDN);
    mpfr_const_pi (pi, MPFR_RNDN);
    mpfr_set_str (frequency, "300", 10, MPFR_RNDN);
    mpfr_mul (multiplier, two, pi, MPFR_RNDN);
    mpfr_mul (multiplier, multiplier, frequency, MPFR_RNDN);
    mpfr_div (multiplier, multiplier, sampleRate, MPFR_RNDN);

    mpfr_out_str (stdout, 10, 0, sampleRate, MPFR_RNDN);
    printf("\n");
    mpfr_out_str (stdout, 10, 0, pi, MPFR_RNDN);
    printf("\n");
    mpfr_out_str (stdout, 10, 0, two, MPFR_RNDN);
    printf("\n");
    mpfr_out_str (stdout, 10, 0, frequency, MPFR_RNDN);
    printf("\n");
    mpfr_out_str (stdout, 10, 0, multiplier, MPFR_RNDN);
    printf("\n");

    for (int i = 0; i < 109375000; ++i) {
        mpfr_init2 (result[i], PRECISION);
        mpfr_set_ui (result[i], i, MPFR_RNDN);
        mpfr_mul (result[i], multiplier, result[i], MPFR_RNDN);
        mpfr_sin (result[i], result[i], MPFR_RNDN);
    }

    mpfr_out_str (stdout, 10, 0, result[11000], MPFR_RNDN);
    printf("\n");
    mpfr_out_str (stdout, 10, 0, result[43000], MPFR_RNDN);
    printf("\n");

    mpfr_clears (sampleRate, two, pi, frequency, multiplier,
                 (mpfr_ptr) 0);
    for (int i = 0; i < 109375000; ++i)
        mpfr_clear (result[i]);
    mpfr_free_cache ();

    auto t1 = high_resolution_clock::now();
    std::cout << duration_cast<milliseconds>(t1-t0).count() << "msec\n";

    return 0;
}
