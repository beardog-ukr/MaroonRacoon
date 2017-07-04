#include <stdio.h> //printf

#include "TestBasicDecode.h"
#include "TestChi2Decode.h"
#include "TestCommonCLAP.h"
#include "TestCosetFunctions.h"
#include "TestFileUtils.h"
#include "TestFrequencyInfo.h"
#include "TestIndexOfCoincidence.h"

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
// ===========================================================================

int main(int argc, char *argv[]) {
  printf("Starting \"Common\" tests\n");

  int testCounter =0;
  int failedCounter =0;

  const int errorMessageLimit = 2048;
  char errorMessageBuf[errorMessageLimit];
  errorMessageBuf[0] = '\0';

  runTest(&testCounter, &failedCounter, &errorMessageBuf[0], errorMessageLimit,
          tst_looksLikeOption_A);

  runTest(&testCounter, &failedCounter, &errorMessageBuf[0], errorMessageLimit,
          tst_readCosetFromLine_A);
  runTest(&testCounter, &failedCounter, &errorMessageBuf[0], errorMessageLimit,
          tst_readCosetFromLine_B);

  //----- this one is known bug
  // runTest(&testCounter, &failedCounter, &errorMessageBuf[0], errorMessageLimit,
          // test_readCosetFromFile_basic);

  runTest(&testCounter, &failedCounter, &errorMessageBuf[0], errorMessageLimit,
          tst_getShiftedCosetSymbol_A);

  runTest(&testCounter, &failedCounter, &errorMessageBuf[0], errorMessageLimit,
          tst_getShiftedCosetSymbol_B);

  runTest(&testCounter, &failedCounter, &errorMessageBuf[0], errorMessageLimit,
          tst_calculateChi2ForCoset_A  );

  runTest(&testCounter, &failedCounter, &errorMessageBuf[0], errorMessageLimit,
          tst_decodeChi2ForCoset_A);

  //---------------------------------------------------------------------------
  runTest(&testCounter, &failedCounter, &errorMessageBuf[0], errorMessageLimit,
          tst_loadOneFrequencyInfoLine_A);

  runTest(&testCounter, &failedCounter, &errorMessageBuf[0], errorMessageLimit,
          tst_loadFrequencyInfoFile_A);

  runTest(&testCounter, &failedCounter, &errorMessageBuf[0], errorMessageLimit,
          tst_getFrequency_A);

  // --------------------------------------------------------------------------
  runTest(&testCounter, &failedCounter, &errorMessageBuf[0], errorMessageLimit,
          tst_readFullFile_A);

  // -------------------------------------------------------------------------
  runTest(&testCounter, &failedCounter, &errorMessageBuf[0], errorMessageLimit,
          tst_calculateIndexOfCoincidence_A);

  runTest(&testCounter, &failedCounter, &errorMessageBuf[0], errorMessageLimit,
          tst_guessKeyLengthIOC_A);

  // -------------------------------------------------------------------------
  runTest(&testCounter, &failedCounter, &errorMessageBuf[0], errorMessageLimit,
          tst_decodeOneChar_A);
  runTest(&testCounter, &failedCounter, &errorMessageBuf[0], errorMessageLimit,
          tst_decodeLine_A);


  printf("Finished \"Common\" testing\n");
  if (failedCounter>0) {
    printf("Failed %u/%u \"Common\" tests\n", failedCounter, testCounter);
  }
  else {
    printf("All %u \"Common\" tests successfully passed\n", testCounter);
  }
  return 0;
}

// ===========================================================================
