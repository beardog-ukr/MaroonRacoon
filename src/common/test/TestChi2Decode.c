#include "TestChi2Decode.h"
#include "Chi2Decode.h"

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

bool test_readCosetFromFile_basic_prepareFile(char* const filename,
                                      char* errorBuf, const int errorBufLim) {
  FILE* fp;
  fp = fopen(filename, "w");
  if (fp == NULL) {
    snprintf(errorBuf, errorBufLim,
             "test_readCosetFromFile_basic: Failed to create test file %s", filename);
    return false;
  }

  fprintf(fp, "%s\n", "abcdabcdabcdabcda");
  fprintf(fp, "%s\n", "bcdab");
  fprintf(fp, "%s", "cdabcdabcdabc");
  //so full text is abcdabcdabcdabcdabcdabcdabcdabcdabc

  fclose(fp);
  return true;
}

bool test_readCosetFromFile_basic_actions(FILE* fp,
                                     char* errorBuf, const int errorBufLim) {
  const int cbSize = 100;
  char c0[cbSize];
  readCosetFromFile(fp, 0, 4, &c0[0], cbSize);
  char* e0 = "aaaaaaaaa";
  if (strcmp(c0, e0)!=0) {
    snprintf(errorBuf, errorBufLim,
             "test_readCosetFromFile_basic: Failed read coset 0: %s/%s", c0, e0);
    return false;
  }



  return true;
}

//int readCosetFromFile(FILE* filename,
//                      const int cosetIndex, const int cosetNumber,
//                      char* resultBuf, const int resultLen);
bool test_readCosetFromFile_basic(char* errorBuf, const int errorBufLim) {
  char* tmpFileName = "tf_test_readCosetFromFile_basic.txt" ;
  if (!test_readCosetFromFile_basic_prepareFile(tmpFileName, errorBuf, errorBufLim)) {
    return false;
  }

  //---------------------------------
  FILE* fp;
  fp = fopen(tmpFileName, "r");
  if (fp == NULL) {
    snprintf(errorBuf, errorBufLim,
             "test_readCosetFromFile_basic: Failed to (re)open test file %s", tmpFileName);
    return false;
  }

  bool testResult = test_readCosetFromFile_basic_actions(fp, errorBuf, errorBufLim);

  fclose(fp);
  remove(tmpFileName);

  return testResult;
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
void tst_calculateChi2ForCoset_prepareFI(FrequencyInfo* finfo) {
  finfo->n=26;
  finfo->symbols = realloc(finfo->symbols, finfo->n*sizeof(char));
  finfo->frequencies = realloc(finfo->frequencies, finfo->n*sizeof(double));

  finfo->symbols[ 0]= 'A'; finfo->frequencies[ 0] =  0.0815 ;
  finfo->symbols[ 1]= 'B'; finfo->frequencies[ 1] =  0.0144 ;
  finfo->symbols[ 2]= 'C'; finfo->frequencies[ 2] =  0.0276 ;
  finfo->symbols[ 3]= 'D'; finfo->frequencies[ 3] =  0.0379 ;
  finfo->symbols[ 4]= 'E'; finfo->frequencies[ 4] =  0.1311 ;
  finfo->symbols[ 5]= 'F'; finfo->frequencies[ 5] =  0.0292 ;
  finfo->symbols[ 6]= 'G'; finfo->frequencies[ 6] =  0.0199 ;
  finfo->symbols[ 7]= 'H'; finfo->frequencies[ 7] =  0.0526 ;
  finfo->symbols[ 8]= 'I'; finfo->frequencies[ 8] =  0.0635 ;
  finfo->symbols[ 9]= 'J'; finfo->frequencies[ 9] =  0.0013 ;
  finfo->symbols[10]= 'K'; finfo->frequencies[10] =  0.0042 ;
  finfo->symbols[11]= 'L'; finfo->frequencies[11] =  0.0339 ;
  finfo->symbols[12]= 'M'; finfo->frequencies[12] =  0.0254 ;
  finfo->symbols[13]= 'N'; finfo->frequencies[13] =  0.0710 ;
  finfo->symbols[14]= 'O'; finfo->frequencies[14] =  0.0800 ;
  finfo->symbols[15]= 'P'; finfo->frequencies[15] =  0.0198 ;
  finfo->symbols[16]= 'Q'; finfo->frequencies[16] =  0.0012 ;
  finfo->symbols[17]= 'R'; finfo->frequencies[17] =  0.0683 ;
  finfo->symbols[18]= 'S'; finfo->frequencies[18] =  0.0610 ;
  finfo->symbols[19]= 'T'; finfo->frequencies[19] =  0.1047 ;
  finfo->symbols[20]= 'U'; finfo->frequencies[20] =  0.0246 ;
  finfo->symbols[21]= 'V'; finfo->frequencies[21] =  0.0092 ;
  finfo->symbols[22]= 'W'; finfo->frequencies[22] =  0.0154 ;
  finfo->symbols[23]= 'X'; finfo->frequencies[23] =  0.0017 ;
  finfo->symbols[24]= 'Y'; finfo->frequencies[24] =  0.0198 ;
  finfo->symbols[25]= 'Z'; finfo->frequencies[25] =  0.0008 ;
}
//double calculateChi2ForCoset(char* const coset, const int shiftValue,
//                             AlphabetTransform* at, FrequencyInfo* finfo)
bool tst_calculateChi2ForCoset_A(char* errorBuf, const int errorBufLim) {
  FrequencyInfo* fi = createFrequencyInfo();
  tst_calculateChi2ForCoset_prepareFI(fi) ;

  AlphabetTransform at ;
  at.basic = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  at.n=26;

  //example line and values came from
  //http://www.cs.mtu.edu/~shene/NSF-4/Tutorial/VIG/Vig-Recover.html

  char* line = "WWBQCUOBSW";
  double lineChi2 = calculateChi2ForCoset(line, 0, &at, fi) ;
  double expectedChi2 = 17.0130;
  double diff = expectedChi2 -lineChi2;
  if ( (diff*diff) > 0.001 ) {
    snprintf(errorBuf, errorBufLim,
             "tst_calculateChi2ForCoset_A: chi2 %f/%f", lineChi2, expectedChi2);
    freeFrequencyInfo(fi);
    return false;
  }

  lineChi2 = calculateChi2ForCoset(line, 1, &at, fi) ;
  expectedChi2 = 10.8557;
  diff = expectedChi2 -lineChi2;
  if ( (diff*diff) > 0.00000001 ) {
    snprintf(errorBuf, errorBufLim,
             "tst_calculateChi2ForCoset_A: chi2 %f/%f", lineChi2, expectedChi2);
    freeFrequencyInfo(fi);
    return false;
  }

  freeFrequencyInfo(fi);
  return true;
}

//=============================================================================
//char decodeChi2ForCoset(char* const coset, AlphabetTransform* at, FrequencyInfo* finfo) {
bool tst_decodeChi2ForCoset_A(char* errorBuf, const int errorBufLim) {
  FrequencyInfo* fi = createFrequencyInfo();
  tst_calculateChi2ForCoset_prepareFI(fi) ;

  AlphabetTransform at ;
  at.basic = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  at.n=26;

  //example line and values came from
  //http://www.cs.mtu.edu/~shene/NSF-4/Tutorial/VIG/Vig-Recover.html

  char* line = "NIBFOPDVWTZ";
  char ch = decodeChi2ForCoset(line, &at, fi) ;
  char expCh = 'B';
  if ( expCh != ch ) {
    snprintf(errorBuf, errorBufLim,
             "tst_calculateChi2ForCoset_A: chars %c/%c", ch, expCh);
    freeFrequencyInfo(fi);
    return false;
  }

  line = "WWBQCUOBSW";
  ch = decodeChi2ForCoset(line, &at, fi) ;
  expCh = 'O';
  if ( expCh != ch ) {
    snprintf(errorBuf, errorBufLim,
             "tst_calculateChi2ForCoset_A: chars %c/%c", ch, expCh);
    freeFrequencyInfo(fi);
    return false;
  }

  line = "AERFJGJGPR";
  ch = decodeChi2ForCoset(line, &at, fi) ;
  expCh = 'Y';
  if ( expCh != ch ) {
    snprintf(errorBuf, errorBufLim,
             "tst_calculateChi2ForCoset_A: chars %c/%c", ch, expCh);
    freeFrequencyInfo(fi);
    return false;
  }

  //finally
  freeFrequencyInfo(fi);
  return true;
}
