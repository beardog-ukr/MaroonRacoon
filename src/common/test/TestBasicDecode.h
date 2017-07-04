#ifndef __TEST_Basic_Decode__
#define __TEST_Basic_Decode__

#include <stdbool.h>
#include "AlphabetTransform.h"

//char decodeOneChar(const AlphabetTransform* at,
//                    const char* key, const int keyLen,
//                    const int keyPos, const char symbol) ;
bool tst_decodeOneChar_A(char* errorBuf, const int errorBufLim);

//void decodeLine(const AlphabetTransform* at, char* line,
//                const char* key, const int keyLen, const int startPos,
//                char* result, const int resultLimit) ;
bool tst_decodeLine_A(char* errorBuf, const int errorBufLim);

//
//int performDecoding(const char* inFilename, const char* outFilename,
//                    const char* key, const AlphabetTransform* at) ;
// ---- function is too complicated to be tested

#endif
