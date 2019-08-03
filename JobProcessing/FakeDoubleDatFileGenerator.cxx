#include <fstream>
#include <cmath>
#include <limits>
#include <gmp.h>
#include <mpfr.h>

using namespace std;

int main(void)
{
    ofstream os {"ModOut12.dat"};

    os.precision(numeric_limits<double>::max_digits10);
    os << "ModOut ID: 12" << endl
       << "Precision: double" << endl
       << "Multiprecision bits: 64" << endl
       << "Sample rate: 384000" << endl
       << "Length: 5" << endl
       << "Data:" << endl;

    double sampleRate {384000};
    long int numSamples {384000 * 5};
    for (long int i = 0; i < numSamples; ++i)
        os << sin(i/sampleRate) << '\n';

    return 0;
}




