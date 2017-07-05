#include <stdio.h> //printf
#include <stdlib.h>

#include "TestEncoder.h"

// ===========================================================================

void runTest(int* totalCounter, int* failedCounter,
             char* errorBuf, const int errorBufLim,
             bool (*tst_func)(char* , const int )){
  //
  bool tmpboo = tst_func(errorBuf, errorBufLim);
  if (!tmpboo) {
    (*failedCounter)++;
    printf("F: %s\n", errorBuf);
  }
  (*totalCounter)++;
}

// ===========================================================================
// ===========================================================================

int main(int argc, char *argv[]) {
  printf("Starting \"Encoder\" tests\n");

  int testCounter =0;
  int failedCounter =0;

  const int errorMessageLimit = 2048;
  char errorMessageBuf[errorMessageLimit];
  errorMessageBuf[0] = '\0';

  runTest(&testCounter, &failedCounter, &errorMessageBuf[0], errorMessageLimit,
          tst_encodeOneChar_A);

  runTest(&testCounter, &failedCounter, &errorMessageBuf[0], errorMessageLimit,
          tst_encodeLine_A);
          
  //---------------------------------------------------------------------------
  printf("Finished \"Encoder\" testing\n");
  if (failedCounter>0) {
    printf("Failed %u/%u \"Encoder\" tests\n", failedCounter, testCounter);
  }
  else {
    printf("All %u \"Encoder\" tests successfully passed\n", testCounter);
  }
  return 0;
}

// ===========================================================================
