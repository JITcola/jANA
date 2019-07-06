#include <iostream>
#include "la_jitco_jana_ParallelRendererJobProcessor.h"

JNIEXPORT void JNICALL Java_la_jitco_jana_ParallelRendererJobProcessor_computeExternalDependencyOuts
  (JNIEnv *, jobject)
{
    std::cout << "Did it work?\n";
}
