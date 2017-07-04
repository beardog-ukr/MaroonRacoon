#ifndef __Chi2_Decode__
#define __Chi2_Decode__

#include <stdbool.h> //bool

#include "AlphabetTransform.h"
#include "FrequencyInfo.h"

double calculateChi2ForCoset(char* const coset, const int shiftValue,
                     const AlphabetTransform* at, const FrequencyInfo* finfo);

char decodeChi2ForCoset(char* const coset,
                      const AlphabetTransform* at, const FrequencyInfo* finfo);

#endif
