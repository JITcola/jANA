#include <iostream>
#include <chrono>
#include <cstdio>
#include <cmath>

int main(void)
{
    double sampleRate, two, pi, frequency, multiplier;
    double result[44100];

    using namespace std::chrono;
    auto t0 = high_resolution_clock::now();

    sampleRate = 44100;
    two = 2;
    pi = M_PI;
    frequency = 300;
    multiplier = two * pi * frequency / sampleRate;

    printf("%f", sampleRate);
    printf("\n");
    printf("%f", pi);
    printf("\n");
    printf("%f", two);
    printf("\n");
    printf("%f", frequency);
    printf("\n");
    printf("%f", multiplier);
    printf("\n");

    for (int i = 0; i < 44100; ++i) {
        result[i] = i;
        result[i] *= multiplier;
        result[i] = sin(result[i]);
    }

    printf("%f", result[11000]);
    printf("\n");
    printf("%f", result[43000]);
    printf("\n");

    auto t1 = high_resolution_clock::now();
    std::cout << duration_cast<milliseconds>(t1-t0).count() << "msec\n";

    return 0;
}
