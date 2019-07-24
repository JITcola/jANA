#include "Evaluator.h"

#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <cstdio>
#include <gmp.h>
#include <mpfr.h>

#include "EvaluatorTemplate.h"
#include "ModIn.h"
#include "ModOut.h"
#include "Module.h"
#include "ModuleType.h"
#include "FunctionGenerator.h"
#include "Delay.h"


Evaluator::Evaluator(EvaluatorTemplate evaluatorTemplate)
{
    modulePtrs.reserve(evaluatorTemplate.moduleRecords.size());
    modOutDependencies.reserve(
        evaluatorTemplate.jobInfo.modOutDependencyIds.size());

    isMultiprecision = 
        evaluatorTemplate.jobInfo.precision == "double" ? false : true;
    multiprecisionBits = evaluatorTemplate.jobInfo.multiprecisionBits;
    sampleRate = evaluatorTemplate.jobInfo.sampleRate;
    currentSample = static_cast<long int>(0);
    
    /* Initialize time vector. */
    if (evaluatorTemplate.jobInfo.precision == "double")
        for (long int i = 0; 
             i < evaluatorTemplate.jobInfo.numberOfSamples; 
             ++i) {
            double newTime = static_cast<double>(i) / 
                static_cast<double>(evaluatorTemplate.jobInfo.sampleRate);
            time.push_back(SampleValue(newTime));
        }
    else {
        for (long int i = 0; 
             i < evaluatorTemplate.jobInfo.numberOfSamples; 
             ++i)
            time.push_back(SampleValue(true, 
                evaluatorTemplate.jobInfo.multiprecisionBits)); 
        mpfr_t sampleNumber;
        mpfr_t sampleRate;
        mpfr_init2 (sampleNumber, 
            static_cast<mpfr_prec_t>(
            evaluatorTemplate.jobInfo.multiprecisionBits));
        mpfr_init2 (sampleRate, 
            static_cast<mpfr_prec_t>(
            evaluatorTemplate.jobInfo.multiprecisionBits));
        mpfr_set_si (sampleRate, 
            static_cast<long int>(
            evaluatorTemplate.jobInfo.sampleRate),
            MPFR_RNDN);
        for (long int i = 0; 
             i < evaluatorTemplate.jobInfo.numberOfSamples; 
             ++i) {
            mpfr_set_si (sampleNumber, i, MPFR_RNDN);
            mpfr_div (time[i].multiValue, sampleNumber, sampleRate, 
                      MPFR_RNDN);
        }
        mpfr_clear (sampleNumber);
        mpfr_clear (sampleRate);
    }

    /* Create modulation map. */
    std::map<int, ModIn*> modInIdMap;
    std::map<int, ModOut*> modOutIdMap;
    std::map<int, int> modInToModOutMap;

    /* Import ModOut dependencies. */
    for (int id: evaluatorTemplate.jobInfo.modOutDependencyIds) {
        modOutDependencies.push_back(modOutFromId(id));
        modOutIdMap.insert({id, &modOutDependencies.back()});
    }

    /* Create modules and register ModIns, ModOuts, modInToModOutMap info. */
    for (ModuleRecord& moduleRecord: evaluatorTemplate.moduleRecords) {
        if (Module::moduleTypeFromString(moduleRecord.moduleType) ==
            ModuleType::FunctionGenerator) {
            auto newFunctionGeneratorPtr {
                std::make_unique<FunctionGenerator>(
                    isMultiprecision,
                    multiprecisionBits,
                    time,
                    moduleRecord
                )
            };
            modulePtrs.push_back(std::move(newFunctionGeneratorPtr));
        } else if (Module::moduleTypeFromString(moduleRecord.moduleType) ==
                   ModuleType::Delay) {
            auto newDelayPtr {
                std::make_unique<Delay>(
                    isMultiprecision,
                    multiprecisionBits,
                    time,
                    moduleRecord
                )
            };
            modulePtrs.push_back(std::move(newDelayPtr));
        } else 
             std::cerr << "Failed to create modulePtrs." << std::endl;
        for (auto dependency: moduleRecord.dependencies) {
            modInIdMap.insert({
                dependency.first.second, 
                &(modulePtrs.back()->getModIn(dependency.first.first))});
            modInToModOutMap.insert({
                dependency.first.second, 
                dependency.second});
        }
        for (auto product: moduleRecord.products) {
            modOutIdMap.insert({
                product.second, 
                &(modulePtrs.back()->getModOut(product.first))});
            (modulePtrs.back()->getModOut(
                product.first)).isComputed = true;
        }
    }

    /* Connect ModIns to ModOuts. */

    for (auto modPair: modInToModOutMap)
        modInIdMap[modPair.first]->source =
            modOutIdMap[modPair.second];

}

void Evaluator::evaluate(void)
{
    for (long int i = 0; i < time.size(); ++i)
        computeNextSample();
    freeResources();
    exportModOutProducts();
}

void Evaluator::computeNextSample()
{
    for (auto& modulePtr: modulePtrs)
        modulePtr->computeNextSample();
}

void Evaluator::freeResources(void)
{
    mpfr_free_cache ();
}

void Evaluator::exportModOutProducts(void)
{
    return;
}

ModOut Evaluator::modOutFromId(int id)
{
    return ModOut {}; // TODO: actually write this method
}
