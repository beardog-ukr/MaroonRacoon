#ifndef __Decoder__
#define __Decoder__

#include <stdbool.h>

#include "AlphabetTransform.h"

//
int performDecoding(const char* inFilename, const char* outFilename,
                    const char* key, const AlphabetTransform* at) ;

#endif
