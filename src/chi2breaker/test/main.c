#include <stdbool.h> //bool
#include <stdio.h> //printf
#include <stdlib.h>
#include <unistd.h>

//#include "TestChi2Breaker.h"

// ===========================================================================
// ===========================================================================
// ===========================================================================

int main(int argc, char *argv[]) {
  printf("Starting \"Chi2Breaker\" tests\n");

  int testCounter =0;
  int failedCounter =0;
  // bool ter ;//test execution result

  // const int errorMessageLimit = 2048;
  // char errorMessageBuf[errorMessageLimit];

  // //---------------------------------------------------------------------------
  // //
  // ter = tst_readFullFile_A(&errorMessageBuf[0], errorMessageLimit);
  // if (!ter) {
  //   failedCounter++;
  //   printf("F: %s\n", errorMessageBuf);
  // }
  // testCounter++;

  //---------------------------------------------------------------------------
  printf("Finished \"Chi2Breaker\" testing\n");
  if (failedCounter>0) {
    printf("Failed %u/%u \"Chi2Breaker\" tests\n", failedCounter, testCounter);
  }
  else {
    printf("All %u \"Chi2Breaker\" tests successfully passed\n", testCounter);
  }
  return 0;
}

// ===========================================================================
