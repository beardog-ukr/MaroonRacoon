#include "TestChi2Decode.h"
#include "Chi2Decode.h"

#include <stdio.h> //printf, fgetc, fopen, snprintf
#include <string.h> //strcmp
#include <stdlib.h> // malloc

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

  const char* line = "WWBQCUOBSW";
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

  const char* line = "NIBFOPDVWTZ";
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
