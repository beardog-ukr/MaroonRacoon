#include "TestCosetFunctions.h"
#include "CosetFunctions.h"

#include <stdio.h> //printf, fgetc, fopen, snprintf
#include <string.h> //strcmp
#include <stdlib.h> // malloc

// ===========================================================================
//Test for
//int readCosetFromLine(char * const line,
//                      const int cosetIndex, const int cosetNumber,
//                      char* resultBuf, const int resultLen);
bool tst_readCosetFromLine_A(char* errorBuf, const int errorBufLim){
  char* line = "RSTCSJLSLRSLFELGWLFIISIKRMGL";

  const int bSize = 1024;

  char b0[bSize];
  readCosetFromLine(line, 0, 3, b0, bSize);
  char* c0 = "RCLRFGFSRL" ;
  if (strcmp(c0, b0)!=0) {
    snprintf(errorBuf, errorBufLim,
             "tst_readCosetFromLine_A: %s != %s", b0, c0);
    return false;
  }

  char b1[bSize];
  readCosetFromLine(line, 1, 3, b1, bSize);
  char* c1 = "SSSSEWIIM" ;
  if (strcmp(c1, b1)!=0) {
    snprintf(errorBuf,errorBufLim,"tst_readCosetFromLine_A: %s != %s", b1, c1);
    return false;
  }

  char b2[bSize];
  readCosetFromLine(line, 2, 3, b2, bSize);
  char* c2 = "TJLLLLIKG" ;
  if (strcmp(c2, b2)!=0) {
    snprintf(errorBuf, errorBufLim,"tst_readCosetFromLine_A: %s != %s", b2, c2);
    return false;
  }

  return true;
}


// ===========================================================================
//Test for
//int readCosetFromLine(char * const line,
//                      const int cosetIndex, const int cosetNumber,
//                      char* resultBuf, const int resultLen);
bool tst_readCosetFromLine_B(char* errorBuf, const int errorBufLim){
  char* line = "RS";

  const int bSize = 1024;

  char b0[bSize];
  readCosetFromLine(line, 0, 3, b0, bSize);
  char* c0 = "R" ;
  if (strcmp(c0, b0)!=0) {
    snprintf(errorBuf, errorBufLim,
             "tst_readCosetFromLine_B: %s != %s", b0, c0);
    return false;
  }

  char b1[bSize];
  readCosetFromLine(line, 1, 3, b1, bSize);
  char* c1 = "S" ;
  if (strcmp(c1, b1)!=0) {
    snprintf(errorBuf, errorBufLim,
             "tst_readCosetFromLine_B: %s != %s", b1, c1);
    return false;
  }

  char b2[bSize];
  readCosetFromLine(line, 2, 3, b2, bSize);
  //char* c2 = "" ; third cosed should appear enmpty
  if (strlen(b2)!=0) {
    snprintf(errorBuf, errorBufLim,
             "tst_readCosetFromLine_B: zz \"%s\"", b2);
    return false;
  }

  return true;
}

// ===========================================================================

//char getShiftedCosetSymbol(const char basic, AlphabetTransform* const at, const int shift);
bool tst_getShiftedCosetSymbol_A(char* errorBuf, const int errorBufLim) {
  AlphabetTransform at;
  at.basic = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  at.n=26;

  //test sample comes from http://www.cs.mtu.edu/~shene/NSF-4/Tutorial/VIG/Vig-Recover.html
  char* seq = "WWBQCUOBSW" ;
  const int seqLen = strlen(seq);
  char shiftedSeq[seqLen+1] ;
  shiftedSeq[seqLen] = '\0' ;

  for (int i=0; i<seqLen; i++) {
    shiftedSeq[i] = getShiftedCosetSymbol(seq[i], &at, 1);
  }

  char* expSeq = "VVAPBTNARV";
  if (strcmp(shiftedSeq, expSeq)!=0) {
    snprintf(errorBuf, errorBufLim,
             "tst_getShiftedCosetSymbol_A: bad shift result %s/%s", shiftedSeq, expSeq);
    return false;
  }

  return true ;
}

bool tst_getShiftedCosetSymbol_B(char* errorBuf, const int errorBufLim) {
  AlphabetTransform at;
  at.basic = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  at.n=26;

  char* seq = "ABCDEF" ;
  const int seqLen = strlen(seq);
  char shiftedSeq[seqLen+1] ;
  shiftedSeq[seqLen] = '\0' ;

  for (int i=0; i<seqLen; i++) {
    shiftedSeq[i] = getShiftedCosetSymbol(seq[i], &at, 4);
  }

  char* expSeq = "WXYZAB";
  if (strcmp(shiftedSeq, expSeq)!=0) {
    snprintf(errorBuf, errorBufLim,
             "tst_getShiftedCosetSymbol_A: bad shift result %s/%s", shiftedSeq, expSeq);
    return false;
  }

  return true ;
}

// ===========================================================================
