#ifndef __Chi2_Decode__
#define __Chi2_Decode__

#include <stdbool.h> //bool
#include <stdio.h> // FILE*


#include "AlphabetTransform.h"
#include "FrequencyInfo.h"

int readCosetFromLine(char* const line,
                      const int cosetIndex, const int cosetNumber,
                      char* resultBuf, const int resultLen);

int readCosetFromFile(FILE* filename,
                      const int cosetIndex, const int cosetNumber,
                      char* resultBuf, const int resultLen);

char getShiftedCosetSymbol(const char basic, AlphabetTransform* const at,
                          const int shift);

double calculateChi2ForCoset(char* const coset, const int shiftValue,
                             AlphabetTransform* at, FrequencyInfo* finfo);

char decodeChi2ForCoset(char* const coset, AlphabetTransform* at, FrequencyInfo* finfo);


//
int performDecoding777(const char* inFilename, const char* outFilename,
                    const char* key, const AlphabetTransform* at) ;

#endif
