#include "TestFileUtils.h"
#include "FileUtils.h"

#include <stdio.h> //printf, fgetc, fopen, snprintf
#include <string.h> //strcmp
#include <stdlib.h> // malloc

// ===========================================================================

bool test_readFullFile_A_pf(char* const filename, char* errorBuf, const int errorBufLim) {
  FILE* fp;
  fp = fopen(filename, "w");
  if (fp == NULL) {
    snprintf(errorBuf, errorBufLim,
             "test_readFullFile_A: Failed to create test file %s", filename);
    return false;
  }

  fprintf(fp, "%s\n", "aaaaa");
  fprintf(fp, "%s\n", "b");
  fprintf(fp, "%s", "cc");

  fclose(fp);
  return true;
}

bool test_readFullFile_A_a(char* const filename, char* errorBuf, const int errorBufLim) {
  const int bSize = 100;
  char c0[bSize];
  readFullFile(filename, &c0[0], bSize);
  char* e0 = "aaaaabcc";
  if (strcmp(c0, e0)!=0) {
    snprintf(errorBuf, errorBufLim,
             "test_readFullFile_A: Failed read file 0: %s/%s", c0, e0);
    return false;
  }

  return true;
}

//int readFullFile(char* const filename, char* buf, const int bufLimit);
bool tst_readFullFile_A(char* errorBuf, const int errorBufLim) {
  //
  char* tmpFileName = "tf_tst_readFullFile_A.txt" ;
  if (!test_readFullFile_A_pf(tmpFileName, errorBuf, errorBufLim)) {
    return false;
  }

  bool testResult = test_readFullFile_A_a(tmpFileName, errorBuf, errorBufLim);

  remove(tmpFileName);

  return testResult;
}

// ===========================================================================
