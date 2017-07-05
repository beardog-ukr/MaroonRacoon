#include "TestAlphabetTransform.h"
#include "AlphabetTransform.h"

#include <stdio.h> //printf, fgetc, fopen, snprintf
#include <string.h> //strcmp
#include <stdlib.h> // malloc

// ===========================================================================
//bool checkKey(const AlphabetTransform* const at, const char* const key);
bool tst_checkKey_A(char* errorBuf, const int errorBufLim) {
  AlphabetTransform at ;
  at.basic = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  at.n=26;
  //
  char* k1 = "G";
  if (checkKey(&at, k1)!=true) {
    snprintf(errorBuf, errorBufLim, "%s: bad for \"%s\"", __func__, k1);
    return false;
  }

  if (checkKey(&at, "BOO")!=true) {
    snprintf(errorBuf, errorBufLim, "%s: bad for \"BOO\"", __func__);
    return false;
  }

  if (checkKey(&at, "")!=false) {
    snprintf(errorBuf, errorBufLim, "%s: bad for \"empty string\"", __func__);
    return false;
  }

  if (checkKey(&at, "Baaa")!=false) {
    snprintf(errorBuf, errorBufLim, "%s: bad for \"Baaa\"", __func__);
    return false;
  }

  return true;
}

// ===========================================================================
