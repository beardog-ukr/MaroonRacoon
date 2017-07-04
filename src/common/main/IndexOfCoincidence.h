#ifndef __Index_Of_Coincidence__
#define __Index_Of_Coincidence__

#include "AlphabetTransform.h"

double calculateIndexOfCoincidence(const char* const line,
                                   const AlphabetTransform* const at);

// Guesses key length with IoC.
// line is encrypted text
// returns best key length guess
int guessKeyLengthIOC(const char* const line,const AlphabetTransform* const at);

#endif
