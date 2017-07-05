#include "TestBasicDecode.h"
#include "BasicDecode.h"

#include <stdbool.h> //bool
#include <stdio.h> //fgetc, fopen
#include <stdlib.h> // malloc
#include <string.h> //strlen

// ===========================================================================

//char decodeOneChar(const AlphabetTransform* at,
//                    const char* key, const int keyLen,
//                    const int keyPos, const char symbol) ;
bool tst_decodeOneChar_A(char* errorBuf, const int errorBufLim) {
  AlphabetTransform at ;
  at.basic = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  at.n=26;

  const char* key = "BOY" ;
  const int keyLen= 3;

  //example values came from
  //http://www.cs.mtu.edu/~shene/NSF-4/Tutorial/VIG/Vig-Recover.html

  char ch = decodeOneChar(&at, key, keyLen, 0, 'N' );
  char expCh = 'M';
  if (expCh!=ch) {
    snprintf(errorBuf, errorBufLim,"%s: chars %c/%c", __func__, ch, expCh);
    return false;
  }

  ch = decodeOneChar(&at, key, keyLen, 20, 'J' );
  expCh = 'L';
  if (expCh!=ch) {
    snprintf(errorBuf, errorBufLim,"%s: chars %c/%c", __func__, ch, expCh);
    return false;
  }

  ch = decodeOneChar(&at, key, keyLen, 0, '%' );
  expCh = '\0';
  if (expCh!=ch) {
    snprintf(errorBuf, errorBufLim,"%s: chars %c/%c", __func__, ch, expCh);
    return false;
  }

  return true;
}

// ===========================================================================

//void decodeLine(const AlphabetTransform* at, char* line,
//                const char* key, const int keyLen, const int startPos,
//                char* result, const int resultLimit) ;
bool tst_decodeLine_A(char* errorBuf, const int errorBufLim) {
  AlphabetTransform at ;
  at.basic = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  at.n=26;

    //example values came from
  //http://www.cs.mtu.edu/~shene/NSF-4/Tutorial/VIG/Vig-Recover.html
  const char* key = "BOY" ;
  int keyLen= 3;
  const char* line = "NWAIWEBBRFQFOCJPUGDOJVBGWSPTWRZ";
  char decoded[100];

  decodeLine(&at, line, key, keyLen, 0, &decoded[0], 100) ;
  const char* expDecoded = "MICHIGANTECHNOLOGICALUNIVERSITY" ;
  if (strcmp(&decoded[0], expDecoded)!=0 ) {
    snprintf(errorBuf, errorBufLim,"%s: lines %s/%s", __func__, decoded, expDecoded);
    return false;
  }

  line = "CDEFGHI";
  key = "C";
  keyLen = 1;
  expDecoded = "ABCDEFG" ;
  decodeLine(&at, line, key, keyLen, 0, &decoded[0], 100) ;
  if (strcmp(&decoded[0], expDecoded)!=0 ) {
    snprintf(errorBuf, errorBufLim,"%s: lines %s/%s", __func__, decoded, expDecoded);
    return false;
  }

  return true;
}

// ===========================================================================
