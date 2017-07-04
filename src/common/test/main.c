#include <stdio.h> //printf
#include <stdlib.h>
#include <unistd.h>

#include "TestChi2Decode.h"
#include "TestCommonCLAP.h"
#include "TestFileUtils.h"
#include "TestFrequencyInfo.h"

// ===========================================================================
// ===========================================================================
// ===========================================================================

int main(int argc, char *argv[]) {
  printf("Starting tests\n");

  int testCounter =0;
  int failedCounter =0;
  bool ter ;//test execution result

  const int errorMessageLimit = 2048;
  char errorMessageBuf[errorMessageLimit];

  ter = test_looksLikeOption_basic();
  if (!ter) {
    failedCounter++;
    printf("F: test_looksLikeOption_basic()\n");
  }
  testCounter++;

  //-----
  ter = test_readCosetFromLine_basic();
  if (!ter) {
    failedCounter++;
    printf("F: test_readCosetFromLine_basic()\n");
  }
  testCounter++;

  //-----
  ter = test_readCosetFromLine_short();
  if (!ter) {
    failedCounter++;
    printf("F: %s\n", errorMessageBuf);
  }
  testCounter++;

  //-----
  // ter = test_readCosetFromFile_basic(&errorMessageBuf[0], errorMessageLimit);
  // if (!ter) {
  //   failedCounter++;
  //   printf("F: %s\n", errorMessageBuf);
  // }
  // testCounter++;

  ter = tst_getShiftedCosetSymbol_A(&errorMessageBuf[0], errorMessageLimit);
  if (!ter) {
    failedCounter++;
    printf("F: %s\n", errorMessageBuf);
  }
  testCounter++;

  ter = tst_getShiftedCosetSymbol_B(&errorMessageBuf[0], errorMessageLimit);
  if (!ter) {
    failedCounter++;
    printf("F: %s\n", errorMessageBuf);
  }
  testCounter++;

  ter = tst_calculateChi2ForCoset_A(&errorMessageBuf[0], errorMessageLimit);
  if (!ter) {
    failedCounter++;
    printf("F: %s\n", errorMessageBuf);
  }
  testCounter++;

  ter = tst_decodeChi2ForCoset_A(&errorMessageBuf[0], errorMessageLimit);
  if (!ter) {
    failedCounter++;
    printf("F: %s\n", errorMessageBuf);
  }
  testCounter++;

  //---------------------------------------------------------------------------
  //
  ter = tst_loadOneFrequencyInfoLine_A(&errorMessageBuf[0], errorMessageLimit);
  if (!ter) {
    failedCounter++;
    printf("F: %s\n", errorMessageBuf);
  }
  testCounter++;

  ter = tst_loadFrequencyInfoFile_A(&errorMessageBuf[0], errorMessageLimit);
  if (!ter) {
    failedCounter++;
    printf("F: %s\n", errorMessageBuf);
  }
  testCounter++;

  ter = tst_getFrequency_A(&errorMessageBuf[0], errorMessageLimit);
  if (!ter) {
    failedCounter++;
    printf("F: %s\n", errorMessageBuf);
  }
  testCounter++;

  // --------------------------------------------------------------------------
  ter = tst_readFullFile_A(&errorMessageBuf[0], errorMessageLimit);
  if (!ter) {
    failedCounter++;
    printf("F: %s\n", errorMessageBuf);
  }
  testCounter++;

  printf("Finished testing\n");
  if (failedCounter>0) {
    printf("Failed %u/%u\n", failedCounter, testCounter);
  }
  else {
    printf("All %u tests successfully passed\n", testCounter);
  }
  return 0;
}

// ===========================================================================
