#ifndef __TEST_Frequency_Info__
#define __TEST_Frequency_Info__

#include <stdbool.h> //bool
#include "FrequencyInfo.h"

//int loadFrequencyInfoFile(const char* filename, FrequencyInfo* finfo);
bool tst_loadFrequencyInfoFile_A(char* errorBuf, const int errorBufLim);

//int loadOneLine(char* line, char* sp, double* dp);
bool tst_loadOneFrequencyInfoLine_A(char* errorBuf, const int errorBufLim);

//double getFrequency(const char symbol, FrequencyInfo* info) ;
bool tst_getFrequency_A(char* errorBuf, const int errorBufLim);


#endif
