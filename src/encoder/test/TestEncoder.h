#ifndef __TEST_Encoder__
#define __TEST_Encoder__

#include <stdbool.h>
#include "AlphabetTransform.h"

//char encodeOneChar(const AlphabetTransform* at,
//                    const char* key, const int keyLen,
//                    const int keyPos, const char symbol) ;
bool tst_encodeOneChar_A(char* errorBuf, const int errorBufLim);

//void encodeLine(const AlphabetTransform* at, char* line,
//                const char* key, const int keyLen, const int startPos,
//                char* result, const int resultLimit) ;
bool tst_encodeLine_A(char* errorBuf, const int errorBufLim);

#endif
