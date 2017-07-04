#ifndef __TEST_Index_Of_Coincidence__
#define __TEST_Index_Of_Coincidence__

#include <stdbool.h>

#include "AlphabetTransform.h"

//double calculateIndexOfCoincidence(const char* const line,
//                                   const AlphabetTransform* const at);
bool tst_calculateIndexOfCoincidence_A(char* errorBuf, const int errorBufLim);


//int guessKeyLengthIOC(const char* const line,const AlphabetTransform* const at);
bool tst_guessKeyLengthIOC_A(char* errorBuf, const int errorBufLim);

#endif
