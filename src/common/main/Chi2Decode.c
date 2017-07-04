#include "Chi2Decode.h"

#include <float.h> //DBL_MAX
#include <stdbool.h> //bool
#include <stdio.h> //fgetc, fopen
#include <stdlib.h> // malloc
#include <string.h> //strlen



enum PreprocessorErrorCodes777 {
  DEC_FAILED_READ_SOURCE ,
  DEC_FAILED_WRITE_RESULT,
  DEC_EMPTY_KEY
};

//static const char PECM_FAILED_READ_ALPHABET[] = "Failed to read alphabet file\n";

// ===========================================================================

int readCosetFromLine(char * const line,
                      const int cosetIndex, const int cosetNumber,
                      char* resultBuf, const int resultLen){
  const int lineLen = strlen(line) ;

  int ci = cosetIndex;
  int ri=0;
  while ( (ci<lineLen)&&(ri<(resultLen-1)) ) {
    resultBuf[ri] = line[ci];
    ci += cosetNumber ;
    ri++;
  }

  resultBuf[ri] = '\0' ;

  return 0;
}

// ===========================================================================
// This function is not really implemented
int readCosetFromFile(FILE* fp, const int cosetIndex, const int cosetNumber,
                      char* resultBuf, const int resultLimit){
  const int bufSize = 8192;
  char* lineBuf = malloc(bufSize);
  const int lineCountMax = 400;
  const int fullBufSize = lineCountMax*bufSize;
  char* fullBuf = malloc(fullBufSize); //

  // int cosetLinePos =0;
  // int fullBufLength =0;
  //
  // while ( (fgets(lineBuf, bufSize, fp) != NULL) && (fullBufLength < fullBufSize) ) {
  //   lineBuf[bufSize-1]='\0';
  //   int currentBufLength = strlen(buf);
  //   if(currentBufLength>0) {
  //     strcpy( &fullBuf[fullBufLen], lineBuf);
  //     fullBufLength += currentBufLength;
  //   }
  // }
  //
  // printf("Got line <%s>", fullBufLen);
  //
  // if (strlen(buf)>lineShift) {
  //     readCosetFromLine(&buf[lineShift], cosetIndex, cosetNumber, ccBuf, bufSize);
  //     const int ccLen= strlen(ccBuf) ;
  //     int nclp = cosetLinePos + ccLen ;
  //     if ((nclp+1)<cosetMaxSize) {
  //       strcpy( &fullCoset[cosetLinePos], ccBuf);
  //       cosetLinePos += ccLen;
  //     }
  //     else {
  //       break;
  //     }
  //   }
  // }

  free(lineBuf);
  free(fullBuf);

  // strncpy(resultBuf, fullCoset, resultLimit);

  return 0;
}

// ===========================================================================

char getShiftedCosetSymbol(const char ch, const AlphabetTransform* const at,
                          const int shift){
  int chPos = findAlphabetPos(at->basic, ch) ;
  int resultPos = chPos -shift;
  if (resultPos <0) {
    resultPos = at->n + resultPos ;
  }

  if ((resultPos>=0)&&(resultPos<at->n)) {
    return at->basic[resultPos];
  }
  else {
    return '\0' ;
  }
}

// ===========================================================================

double calculateChi2ForCoset(char* const coset, const int shiftValue,
                     const AlphabetTransform* at, const FrequencyInfo* finfo) {
  int* counters = malloc(at->n * (sizeof (int)));
  double* actualFreq = malloc(at->n * (sizeof (double)));
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
  free(actualFreq);

  return chi2;
}

// ===========================================================================

char decodeChi2ForCoset(char* const coset,
                    const AlphabetTransform* at, const FrequencyInfo* finfo) {
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
