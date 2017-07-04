#ifndef __Basic_Decode__
#define __Basic_Decode__

#include "AlphabetTransform.h"

// returns decoded char or '\0' on failure
char decodeOneChar(const AlphabetTransform* at,
                    const char* key, const int keyLen,
                    const int keyPos, const char symbol) ;

//
void decodeLine(const AlphabetTransform* at, char* line,
                const char* key, const int keyLen, const int startPos,
                char* result, const int resultLimit) ;
//
//
int performDecoding(const char* inFilename, const char* outFilename,
                    const char* key, const AlphabetTransform* at) ;

#endif
