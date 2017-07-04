#include "FrequencyInfo.h"

#include <errno.h>
#include <stdbool.h> //bool
#include <stdio.h> //fgetc, fopen
#include <stdlib.h> // malloc
#include <string.h> //strlen

// ===========================================================================

enum PreprocessorErrorCodes {
  FIEC_FAILED_READ_FILE =1,
  FIEC_FILE_FORMAT,
  FIEC_FILE_FORMAT_DUPLICATE_KEYS,
  FIEC_FILE_FORMAT_DOUBLE_VALUE_CONV
};

// ===========================================================================

int getFrequencyInfoLoaderError(const int errorCode, char* line, const int lineLim) {
  int result =0;
  switch (errorCode) {
    case FIEC_FAILED_READ_FILE:
      snprintf(line, lineLim, "Failed to read frequency info file\n");
    break;
    case FIEC_FILE_FORMAT:
      snprintf(line, lineLim, "Incorrect format of the frequency info file\n");
    break;
    case FIEC_FILE_FORMAT_DUPLICATE_KEYS:
      snprintf(line, lineLim, "Incorrect format of the frequency info file: one of the keys appear twice\n");
    break;
    case FIEC_FILE_FORMAT_DOUBLE_VALUE_CONV:
      snprintf(line, lineLim, "Incorrect format of the frequency info file: one of the values is not double\n");
    break;

    default:
      result =1;
  }

  return result ;
}

// ===========================================================================

void printFrequencyInfoLoaderError(const int errorCode){
  const int ebs = 1024;
  char errbuf[ebs];
  if ( getFrequencyInfoLoaderError(errorCode, errbuf, ebs) ==0) {
    fprintf(stderr, "%s\n", errbuf);
  }
  else {
    fprintf(stderr, "Unknown internal error (frequency info, %u)\n", errorCode);
  }
}

// ===========================================================================

FrequencyInfo* createFrequencyInfo()  {
  FrequencyInfo* result = malloc(sizeof (FrequencyInfo) );
  result->symbols = 0;
  result->frequencies =0;
  result->n =0;
  return result;
}

// ===========================================================================

FrequencyInfo* freeFrequencyInfo(FrequencyInfo* finfo) {
  if (finfo==0) {
    return 0;
  }

  free(finfo->symbols);
  free(finfo->frequencies);

  free(finfo);

  return 0;
}

// ===========================================================================

int loadOneFrequencyInfoLine(char* line, char* sp, double* dp){
  if (line==0) {
    return FIEC_FILE_FORMAT;
  }

  int lineLen = strlen(line);
  if (lineLen<3) {
    return FIEC_FILE_FORMAT;
  }

  if (line[1]!= ' ') {
    return FIEC_FILE_FORMAT;
  }

  *sp = line[0];
  *dp = strtod(&line[2],0);
  if (errno!=0) {// does not work for some reason
    return FIEC_FILE_FORMAT_DOUBLE_VALUE_CONV;
  }

  return 0;
}

// ===========================================================================

int loadFrequencyInfoFile(const char* filename, FrequencyInfo* finfo) {
  FILE* fp;
  fp = fopen(filename, "r");
  if (fp == NULL) {
    // printf("Failed to read %s \n", filename);
    return FIEC_FAILED_READ_FILE;
  }

  const int bufSize = 300;
  char buf[bufSize] ;
  const int elementsLimit = 200;
  double frequencies[elementsLimit];
  char symbols[elementsLimit];

  int ecounter = 0;
  int result =0;
  while ( (result==0) && ( fgets(buf, bufSize, fp) != NULL ) ) {
    buf[bufSize] = '\0' ;
    result = loadOneFrequencyInfoLine(buf, &symbols[ecounter], &frequencies[ecounter]);
    ecounter++;
  }

  fclose(fp) ;

  if (result==0) {
    finfo->symbols = realloc(finfo->symbols, ecounter) ;
    finfo->frequencies = realloc(finfo->frequencies, ecounter*(sizeof(double)) ) ;

    for (int i=0; i<ecounter; i++) {
      finfo->symbols[i] = symbols[i] ;
      finfo->frequencies[i] = frequencies[i] ;
    }

    finfo->n = ecounter;
  }

  return result;
}

// ===========================================================================

double getFrequency(const char symbol, FrequencyInfo* info) {
  for (int i=0; i<info->n; i++) {
    if (info->symbols[i]==symbol) {
      return info->frequencies[i];
    }
  }

  //bad, not found
  return -1.0;
}

// ===========================================================================
