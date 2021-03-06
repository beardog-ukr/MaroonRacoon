#ifndef __Frequency_Info__
#define __Frequency_Info__

#include <stdbool.h> //bool

typedef struct FrequencyInfoStruct {
  char* symbols;
  double* frequencies;
  int n; //number of elements
  double defaultFreq;
} FrequencyInfo;

FrequencyInfo* createFrequencyInfo(void) ;
FrequencyInfo* freeFrequencyInfo(FrequencyInfo* finfo) ;

int loadFrequencyInfoFile(const char* const filename, FrequencyInfo* finfo);
int loadOneFrequencyInfoLine(const char* const line, char* sp, double* dp);

int getFrequencyInfoLoaderError(const int errorCode, char* line, const int lineLim);
void printFrequencyInfoLoaderError(const int errorCode);

double getFrequency(const char symbol, const FrequencyInfo* const info) ;

#endif
