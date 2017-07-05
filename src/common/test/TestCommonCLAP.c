#include "TestCommonCLAP.h"
#include "CommonCLAP.h"

#include <stdio.h>

// ===========================================================================
//Test for
//bool looksLikeOption(char* const sample)
bool tst_looksLikeOption_A(char* errorBuf, const int errorBufLim) {
  const char* s1 = "-option"  ;
  bool b1 = looksLikeOption(s1);
  if (b1!=true) {
    snprintf(errorBuf, errorBufLim,"tst_looksLikeOption_A: %s", s1);
    return false;
  }

  const char* s4 = ""  ;
  bool b4 = looksLikeOption(s4);
  if (b4!=true) {
    snprintf(errorBuf, errorBufLim,"tst_looksLikeOption_A: <empty string>");
    return false;
  }

  const char* s3 = "option"  ;
  bool b3 = looksLikeOption(s3);
  if (b3!=false) {
    snprintf(errorBuf, errorBufLim, "tst_looksLikeOption_A: %s", s3);
    return false;
  }

  const char* s2 = "--option"  ;
  bool b2 = looksLikeOption(s2);
  if (b2!=true) {
    snprintf(errorBuf, errorBufLim,"tst_looksLikeOption_A: %s", s2);
    return false;
  }

  return true;
}


// ===========================================================================
