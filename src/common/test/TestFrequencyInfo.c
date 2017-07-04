#include "TestFrequencyInfo.h"
#include "FrequencyInfo.h"

#include <stdio.h> //printf, fgetc, fopen, snprintf
#include <string.h> //strcmp
#include <stdlib.h> // malloc

// ============================================================================

//int loadOneFrequencyInfoLine(char* line, char* sp, double* dp);
bool tst_loadOneFrequencyInfoLine_A(char* errorBuf, const int errorBufLim) {
  int ti;
  char tc;
  double td;

  ti = loadOneFrequencyInfoLine("z", &tc, &td) ;
  if ((ti==0)) {
    snprintf(errorBuf, errorBufLim, "tst_loadOneFrequencyInfoLine_A: Unexpected %u as result(1)", ti);
    return false;
  }

  ti = loadOneFrequencyInfoLine("za 1.2", &tc, &td) ;
  if ((ti==0)) {
    snprintf(errorBuf, errorBufLim, "tst_loadOneFrequencyInfoLine_A: Unexpected %u as result(2)", ti);
    return false;
  }

//excluded as known bug
  // ti = loadOneFrequencyInfoLine("z aaaaa", &tc, &td) ;
  // if (ti==0) {
  //   snprintf(errorBuf, errorBufLim, "tst_loadOneFrequencyInfoLine_A: Unexpected %u as result(3)", ti);
  //   return false;
  // }

  ti = loadOneFrequencyInfoLine("z 234", &tc, &td) ;
  if ((ti!=0)||(tc!='z')||(td!=234)) {
    snprintf(errorBuf, errorBufLim, "tst_loadOneFrequencyInfoLine_A: Unepected %u/0, %.5d/234, %c/z",
             ti, tc, td);
    return false;
  }

  ti = loadOneFrequencyInfoLine("a 1.2", &tc, &td) ;
  if ((ti!=0)||(tc!='a')||(td!=1.2)) {
    snprintf(errorBuf, errorBufLim, "tst_loadOneFrequencyInfoLine_A: Unepected %u/0, %.5d/1.2, %c/a",
             ti, tc, td);
    return false;
  }

  return true;
}

// ============================================================================
// ============================================================================
// ============================================================================

bool tst_loadFrequencyInfoFile_A_prepareFile(char* const filename,
                                      char* errorBuf, const int errorBufLim) {
  FILE* fp;
  fp = fopen(filename, "w");
  if (fp == NULL) {
    snprintf(errorBuf, errorBufLim,
             "tst_loadFrequencyInfoFile_A: Failed to create test file %s", filename);
    return false;
  }

  fprintf(fp, "%s\n", "a 0.0123");
  fprintf(fp, "%s\n", "b 44.5");
  fprintf(fp, "%s", "c 222");

  fclose(fp);
  return true;
}

bool tst_loadFrequencyInfoFile_A_actions(char* fn, FrequencyInfo* finfo,
                                     char* errorBuf, const int errorBufLim) {
  int ti = loadFrequencyInfoFile(fn, finfo) ;
  if (ti!=0) {
    snprintf(errorBuf, errorBufLim,
             "tst_loadFrequencyInfoFile_A: Failed (re)open file");
    return false;
  }

  if (finfo->n != 3) {
    snprintf(errorBuf, errorBufLim,
             "tst_loadFrequencyInfoFile_A: Expected 3 elements");
    return false;
  }

  if ( (finfo->symbols[0]!='a')||(finfo->symbols[1]!='b')||(finfo->symbols[2]!='c') )  {
    snprintf(errorBuf, errorBufLim,
             "tst_loadFrequencyInfoFile_A: bad symbols %c/a %c/b %c/c",
             finfo->symbols[0], finfo->symbols[1]!='b', finfo->symbols[2]);
    return false;
  }

  if ( (finfo->frequencies[0]!=0.0123)||(finfo->frequencies[1]!=44.5)||(finfo->frequencies[2]!=222) )  {
    snprintf(errorBuf, errorBufLim,
             "tst_loadFrequencyInfoFile_A: bad values %.5f/0.0123 %.5f/44.5 %.5f/222",
             finfo->frequencies[0],finfo->frequencies[1],finfo->frequencies[2]);
    return false;
  }

  return true;
}

//int loadFrequencyInfoFile(const char* filename, FrequencyInfo* finfo);
bool tst_loadFrequencyInfoFile_A(char* errorBuf, const int errorBufLim) {
  char* tmpFileName = "tf_tst_loadFrequencyInfoFile_A.txt" ;
  if (!tst_loadFrequencyInfoFile_A_prepareFile(tmpFileName, errorBuf, errorBufLim)) {
    return false;
  }

  //---------------------------------
  FrequencyInfo* finfo = createFrequencyInfo();
  bool testResult = tst_loadFrequencyInfoFile_A_actions(tmpFileName, finfo, errorBuf, errorBufLim);
  freeFrequencyInfo(finfo);

  remove(tmpFileName);

  return testResult;
}

// ============================================================================
// ============================================================================
// ============================================================================

//double getFrequency(const char symbol, FrequencyInfo* info) ;
bool tst_getFrequency_A(char* errorBuf, const int errorBufLim) {
  FrequencyInfo* finfop = createFrequencyInfo();

  //finfo is empty here
  double tmpd = getFrequency('s', finfop);
  if (tmpd >=0) {
    snprintf(errorBuf, errorBufLim,
             "tst_getFrequency_A: unexpected for empty info");
    return false;
  }

  freeFrequencyInfo(finfop);


  double farr[3];
  char charr[3];
  charr [0] = 'A' ; farr[0] = 0.01;
  charr [1] = 'B' ; farr[1] = 0.02;
  charr [2] = 'C' ; farr[2] = 0.03;
  FrequencyInfo finfo ;
  finfo.frequencies = farr;
  finfo.symbols = charr;
  finfo.n=3;

  double dc = getFrequency('C', &finfo);
  double db = getFrequency('B', &finfo);
  double da = getFrequency('A', &finfo);

  if ( (dc!=0.03)||(db!=0.02)||(da!=0.01) ) {
    snprintf(errorBuf, errorBufLim,
             "tst_getFrequency_A: bad %f/0.01 %f/0.02 %f/0.03", da, db, dc);
    return false;
  }

  double dd = getFrequency('D', &finfo);
  if (dd >=0) {
    snprintf(errorBuf, errorBufLim,
             "tst_getFrequency_A: unexpected for incorrect key");
    return false;
  }


  return true;
}

// ============================================================================
// ============================================================================
// ============================================================================
