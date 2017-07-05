#ifndef __Encoder__
#define __Encoder__

#include <stdbool.h>

#include "AlphabetTransform.h"

char encodeOneChar(const AlphabetTransform* const at,
                    const char* const key, const int keyLen,
                    const int keyPos, const char symbol) ;

void encodeLine(const AlphabetTransform* at, const char* const line,
                const char* const key, const int keyLen, const int startPos,
                char* result, const int resultLimit) ;

// Transforms file to the form where only allowed letters are used
int performEncoding(const char* const inFilename, const char* const outFilename,
                    const char* const key, const AlphabetTransform* const at) ;

//int lineToHext(char* line, char* result, int resultLen);

#endif
