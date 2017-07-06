#ifndef __Breaker__
#define __Breaker__

#include "AlphabetTransform.h"
#include "FrequencyInfo.h"
//
int performBreak(const char* const inFilename, const char* const outFilename,
                 const AlphabetTransform* const at,
                 const FrequencyInfo* const finfo) ;

void printBreakerError(const int errorCode);

#endif
