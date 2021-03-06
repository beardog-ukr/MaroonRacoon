#ifndef __Chi2_Breaker__
#define __Chi2_Breaker__

#include <stdbool.h>

#include "AlphabetTransform.h"
#include "FrequencyInfo.h"

//
int performChi2Break(const char* const inFilename, const char* const outFilename,
                 const int keyLength,
                 const AlphabetTransform* at, const FrequencyInfo* finfo) ;

#endif
