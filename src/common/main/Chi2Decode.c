#include "Chi2Decode.h"
#include "CosetFunctions.h"

#include <float.h> //DBL_MAX
#include <stdbool.h> //bool
#include <stdio.h> //fgetc, fopen
#include <stdlib.h> // malloc
#include <string.h> //strlen

// ===========================================================================

double calculateChi2ForCoset(const char* const coset, const int shiftValue,
                     const AlphabetTransform* at, const FrequencyInfo*const  finfo) {
  int* counters = malloc(at->n * (sizeof (int)));
  //double* actualFreq = malloc(at->n * (sizeof (double)));
  for(int i=0; i< at->n; i++) {
    counters[i] = 0;
  }

  const int cosetLen = strlen(coset) ;

  for(int i=0; i<cosetLen; i++ ) {
    char shiftedChar = getShiftedCosetSymbol(coset[i], at, shiftValue);
    int scp = findAlphabetPos(at->basic, shiftedChar);
    if ( (scp>=0)&&(scp<at->n)  ) {
      counters[scp]++;
    }
  }

  double chi2 =0;
  const double cosetLenD = cosetLen ;
  for(int i=0; i< at->n; i++) {
    double actualFreq = counters[i] / cosetLenD;
    double knownFreq = getFrequency(at->basic[i], finfo);
    double akDiff = actualFreq-knownFreq ;
    chi2 += (akDiff*akDiff)/knownFreq;
  }

  free(counters);
  //free(actualFreq);

  return chi2;
}

// ===========================================================================

char decodeChi2ForCoset(const char* const coset,
  const AlphabetTransform* const at, const FrequencyInfo* const finfo) {
  char result = '\0' ;
  double resultValue = DBL_MAX;
  for(int i=0; i<at->n; i++) {
    double currentChi2 = calculateChi2ForCoset(coset, i, at, finfo);
    if (resultValue > currentChi2) {
      result = at->basic[i];
      resultValue = currentChi2;
    }
  }

  return result ;
}

// ===========================================================================
