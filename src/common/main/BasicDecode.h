#ifndef __Basic_Decode__
#define __Basic_Decode__

#include "AlphabetTransform.h"

// returns decoded char or '\0' on failure
char decodeOneChar(const AlphabetTransform* const at,
                    const char* const key, const int keyLen,
                    const int keyPos, const char symbol) ;

//
void decodeLine(const AlphabetTransform* const at, const char* const line,
                const char* const key, const int keyLen, const int startPos,
                char* result, const int resultLimit) ;
//
//
int performDecoding(const char* const inFilename, const char* const outFilename,
                    const char* const key, const AlphabetTransform* const at) ;

#endif
