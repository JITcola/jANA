#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cmath>
#include <gmp.h>
#include <mpfr.h>

#include "JobFileReader.h"
#include "Evaluator.h"
#include "EvaluatorTemplate.h"
#include "FunctionGenerator.h"
#include "Delay.h"
#include "SampleValue.h"
#include "ModuleType.h"
#include "DatFileReader.h"
#include "Dsp.h"

int main(void)
{

/*    

    JobFileReader reader;
    EvaluatorTemplate evaluatorTemplate;
    evaluatorTemplate = reader.readJobFile(3);
    evaluatorTemplate.jobInfo.precision = "multiprecision";
    evaluatorTemplate.jobInfo.multiprecisionBits = 64;
    Evaluator evaluator {evaluatorTemplate};

    for (auto& modulePtr: evaluator.modulePtrs) {
        if (modulePtr->moduleType == ModuleType::FunctionGenerator) {
            std::cout << "initLevel value: "
                      << (modulePtr->getParameter("initLevel")).getValueAsString()
                      << std::endl;
        } else if (modulePtr->moduleType == ModuleType::Delay) {
            std::cout << "initLevel value: "
                      << (modulePtr->getParameter("initLevel")).getValueAsString()
                      << std::endl;
        } else {
            std::cout << "Unknown ModuleType" << std::endl;
        }
        std::cout << "***" << std::endl;
    }

    DatFileReader datFileReader;
    datFileReader.getData(11);
    for (auto value: datFileReader.data)
        std::cout << value.to_string() << '\n';

    std::cout << "************************\n";

    std::vector<SampleValue> v1, v2;
    v1.push_back(SampleValue(true, 256, "1.2834832"));
    v1.push_back(SampleValue(true, 256, "2.813838289"));
    v1.push_back(SampleValue(true, 256, "0.82918353"));
    v2 = Dsp::padUp(v1, 3);
    for (auto value: v2)
        std::cout << value.to_string() << '\n';
    v1 = Dsp::decimate(v2, 3);
    std::cout << "*************************\n";
    for (auto value: v1)
        std::cout << value.to_string() << '\n';
    std::vector<SampleValue> v3, v4;
    v3.push_back(SampleValue(true, 256, "1.0"));
    v3.push_back(SampleValue(true, 256, "0.0"));
    v3.push_back(SampleValue(true, 256, "1.0"));
    v3.push_back(SampleValue(true, 256, "0.0"));
    v3.push_back(SampleValue(true, 256, "1.0"));
    v3.push_back(SampleValue(true, 256, "1.0"));
    v3.push_back(SampleValue(true, 256, "1.0"));
    v4 = Dsp::iDft(v3);
    for (auto value: v4)
        std::cout << value.to_string() << '\n';


    std::cout << datFileReader.modOutId << std::endl
              << datFileReader.isMultiprecision << std::endl;


    mpfr_out_str (stdout, 10, 0, evaluator.time[44099].multiValue, MPFR_RNDN);

*/

    std::vector<SampleValue> signal;
    std::vector<SampleValue> filtered;

    for (long int i = 0; i < 44100; ++i)
        signal.push_back(SampleValue(sin(2*Dsp::pi*3000*i/44100.0)));
    filtered = Dsp::lpf(signal, 44100, 1000);
    std::ofstream sigFile {"sigFile.dat"};
    std::ofstream filterFile {"filterFile.dat"};
    for (auto value: signal)
        sigFile << value.to_string() << '\n';
    for (auto value: filtered)
        filterFile << value.to_string() << '\n';
    sigFile.close();
    filterFile.close();

    std::vector<SampleValue> signalMulti;
    std::vector<SampleValue> filteredMulti;

    for (long int i = 0; i < 44100; ++i) {
        mpfr_t sampleValue;
        mpfr_t pi_multi;
        mpfr_inits2 (static_cast<mpfr_prec_t>(256), sampleValue, pi_multi,
                     static_cast<mpfr_ptr>(0));
        mpfr_set_si (sampleValue, 2, MPFR_RNDN);
        mpfr_const_pi (pi_multi, MPFR_RNDN);
        mpfr_mul (sampleValue, sampleValue, pi_multi, MPFR_RNDN);
        mpfr_mul_si (sampleValue, sampleValue, 3000, MPFR_RNDN);
        mpfr_mul_si (sampleValue, sampleValue, i, MPFR_RNDN);
        mpfr_div_si (sampleValue, sampleValue, 44100, MPFR_RNDN);
        mpfr_sin (sampleValue, sampleValue, MPFR_RNDN);
        char* str;
        mpfr_asprintf (&str, "%Re", sampleValue);
        std::string valueString {str};
        mpfr_free_str (str);
        signalMulti.push_back(SampleValue(true, 256, valueString));
        mpfr_clears (sampleValue, pi_multi, static_cast<mpfr_ptr>(0));
    }

    filteredMulti = Dsp::lpf(signalMulti, 44100, 1000);
    std::ofstream sigMultiFile {"sigMultiFile.dat"};
    std::ofstream filterMultiFile {"filterMultiFile.dat"};
    for (auto value: signalMulti)
        sigMultiFile << value.to_string() << '\n';
    for (auto value: filteredMulti)
        filterMultiFile << value.to_string() << '\n';
    sigMultiFile.close();
    filterMultiFile.close();

    return 0;
}
