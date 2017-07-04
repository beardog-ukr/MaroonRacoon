#include "TestCommonCLAP.h"
#include "CommonCLAP.h"

#include <stdio.h>

// ===========================================================================
//Test for
//bool looksLikeOption(char* const sample)
bool test_looksLikeOption_basic() {
  char* s1 = "-option"  ;
  bool b1 = looksLikeOption(s1);
  if (b1!=true) {
    printf("test_looksLikeOption_basic: %s\n", s1);
    return false;
  }

  char* s4 = ""  ;
  bool b4 = looksLikeOption(s4);
  if (b4!=true) {
    printf("test_looksLikeOption_basic: <empty string>\n");
    return false;
  }

  char* s3 = "option"  ;
  bool b3 = looksLikeOption(s3);
  if (b3!=false) {
    printf("test_looksLikeOption_basic: %s\n", s3);
    return false;
  }

  char* s2 = "--option"  ;
  bool b2 = looksLikeOption(s2);
  if (b2!=true) {
    printf("test_looksLikeOption_basic: %s\n", s2);
    return false;
  }

  return true;
}


// ===========================================================================
