#ifndef __Coset_Functions__
#define __Coset_Functions__

#include <stdbool.h> //bool
#include <stdio.h> // FILE*

#include "AlphabetTransform.h"
#include "FrequencyInfo.h"

int readCosetFromLine(const char* const line,
                      const int cosetIndex, const int cosetNumber,
                      char* resultBuf, const int resultLen);

char getShiftedCosetSymbol(const char basic, const AlphabetTransform* const at,
                          const int shift);

#endif
