#ifndef __TEST_Chi2_Decode__
#define __TEST_Chi2_Decode__

#include <stdbool.h>

//=============================================================================
//int readCosetFromLine(char * const line,
//                      const int cosetIndex, const int cosetNumber,
//                      char* resultBuf, const int resultLen);
//basic usage
bool tst_readCosetFromLine_A(char* errorBuf, const int errorBufLim);
//short line
bool tst_readCosetFromLine_B(char* errorBuf, const int errorBufLim);

//=============================================================================
//int readCosetFromFile(FILE* filename,
//                      const int cosetIndex, const int cosetNumber,
//                      char* resultBuf, const int resultLen);
bool test_readCosetFromFile_basic(char* errorBuf, const int errorBufLim);

//=============================================================================
//char getShiftedCosetSymbol(const char basic, AlphabetTransform* const at, const int shift);
bool tst_getShiftedCosetSymbol_A(char* errorBuf, const int errorBufLim);
bool tst_getShiftedCosetSymbol_B(char* errorBuf, const int errorBufLim);

//=============================================================================
//double calculateChi2ForCoset(char* const coset, const int shiftValue,
//                             AlphabetTransform* at, FrequencyInfo* finfo)
bool tst_calculateChi2ForCoset_A(char* errorBuf, const int errorBufLim);

//=============================================================================
//char decodeChi2ForCoset(char* const coset, AlphabetTransform* at, FrequencyInfo* finfo) {
bool tst_decodeChi2ForCoset_A(char* errorBuf, const int errorBufLim);


#endif
