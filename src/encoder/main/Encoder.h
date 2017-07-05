#ifndef __Encoder__
#define __Encoder__

#include <stdbool.h>

#include "AlphabetTransform.h"

char encodeOneChar(const AlphabetTransform* at,
                    const char* key, const int keyLen,
                    const int keyPos, const char symbol) ;

void encodeLine(const AlphabetTransform* at, char* line,
                const char* key, const int keyLen, const int startPos,
                char* result, const int resultLimit) ;

// Transforms file to the form where only allowed letters are used
int performEncoding(const char* inFilename, const char* outFilename,
                    const char* key, const AlphabetTransform* at) ;

//int lineToHext(char* line, char* result, int resultLen);

#endif
