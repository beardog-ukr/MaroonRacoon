#ifndef __Encoder__
#define __Encoder__

#include <stdbool.h>

#include "AlphabetTransform.h"

// Transforms file to the form where only allowed letters are used
int performEncoding(const char* inFilename, const char* outFilename,
                    const char* key, const AlphabetTransform* at) ;

//int lineToHext(char* line, char* result, int resultLen);

#endif
