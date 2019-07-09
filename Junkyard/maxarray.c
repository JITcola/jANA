#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <mpfr.h>
#include <stdint.h>

#define PRECISION 512

int main(void)
{
    mpfr_t *result = malloc(sizeof(mpfr_t) * 10000000);

    for (int i = 0; i < 10000000; ++i) {
        mpfr_init2 (result[i], PRECISION);
    }

    for (int i = 0; i < 10000000; ++i) {
        mpfr_clear (result[i]);
    }

    mpfr_free_cache();

    free(result);
    printf("%lu\n", SIZE_MAX);

    return 0;
}
