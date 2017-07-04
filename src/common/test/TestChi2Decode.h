#ifndef __TEST_Chi2_Decode__
#define __TEST_Chi2_Decode__

#include <stdbool.h>

//=============================================================================
//double calculateChi2ForCoset(char* const coset, const int shiftValue,
//                             AlphabetTransform* at, FrequencyInfo* finfo)
bool tst_calculateChi2ForCoset_A(char* errorBuf, const int errorBufLim);

//=============================================================================
//char decodeChi2ForCoset(char* const coset, AlphabetTransform* at, FrequencyInfo* finfo) {
bool tst_decodeChi2ForCoset_A(char* errorBuf, const int errorBufLim);


#endif
