#include "Chi2Breaker.h"
#include "Chi2Decode.h"

#include <stdbool.h> //bool
#include <stdio.h> //fgetc, fopen
#include <stdlib.h> // malloc
#include <string.h> //strlen

enum Chi2BreakerErrorCodes {
  C2EC_FAILED_READ_SOURCE ,
  C2EC_FAILED_WRITE_RESULT,
  C2EC_EMPTY_KEY
};

//static const char PECM_FAILED_READ_ALPHABET[] = "Failed to read alphabet file\n";

// ===========================================================================

int performChi2Break(const char* inFilename, const char* outFilename,
                 const int keyLength,
                 const AlphabetTransform* at, const FrequencyInfo* finfo) {
  int result =0;

  return result;
}

// ===========================================================================
