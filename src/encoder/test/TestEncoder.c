#include "TestEncoder.h"
#include "Encoder.h"

#include <stdbool.h> //bool
#include <stdio.h> //fgetc, fopen
#include <stdlib.h> // malloc
#include <string.h> //strlen

// ===========================================================================

//char encodeOneChar(const AlphabetTransform* at,
//                    const char* key, const int keyLen,
//                    const int keyPos, const char symbol) ;
bool tst_encodeOneChar_A(char* errorBuf, const int errorBufLim) {
  AlphabetTransform at ;
  at.basic = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  at.n=26;

  const char* key = "BOY" ;
  const int keyLen= 3;

  //example values came from
  //http://www.cs.mtu.edu/~shene/NSF-4/Tutorial/VIG/Vig-Recover.html

  char ch = encodeOneChar(&at, key, keyLen, 0, 'M' );
  char expCh = 'N';
  if (expCh!=ch) {
    snprintf(errorBuf, errorBufLim,"%s: chars %c/%c", __func__, ch, expCh);
    return false;
  }

  ch = encodeOneChar(&at, key, keyLen, 20, 'L' );
  expCh = 'J';
  if (expCh!=ch) {
    snprintf(errorBuf, errorBufLim,"%s: chars %c/%c", __func__, ch, expCh);
    return false;
  }

  ch = encodeOneChar(&at, key, keyLen, 0, '%' );
  expCh = '\0';
  if (expCh!=ch) {
    snprintf(errorBuf, errorBufLim,"%s: chars %c/%c", __func__, ch, expCh);
    return false;
  }

  return true;
}

// ===========================================================================
//void encodeLine(const AlphabetTransform* at, char* line,
//                const char* key, const int keyLen, const int startPos,
//                char* result, const int resultLimit) ;
bool tst_encodeLine_A(char* errorBuf, const int errorBufLim) {
  AlphabetTransform at ;
  at.basic = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  at.n=26;

    //example values came from
  //http://www.cs.mtu.edu/~shene/NSF-4/Tutorial/VIG/Vig-Recover.html
  char* key = "BOY" ;
  int keyLen= 3;
  char* line = "MICHIGANTECHNOLOGICALUNIVERSITY";
  char encoded[100];

  encodeLine(&at, line, key, keyLen, 0, &encoded[0], 100) ;
  char* expEncoded = "NWAIWEBBRFQFOCJPUGDOJVBGWSPTWRZ" ;
  if (strcmp(&encoded[0], expEncoded)!=0 ) {
    snprintf(errorBuf, errorBufLim,"%s: lines %s/%s", __func__, encoded, expEncoded);
    return false;
  }

  //THERE ARETW OWAYS OFCON STRUC TINGA SOFTW AREDE SIGN
  line = "ONEWAYISTOMAKEITSOSIMPLETHATTHEREAREOBVIOUSLYNODEFICIENCIES";
  key = "COMPUTER";
  keyLen = 8;

  encodeLine(&at, line, key, keyLen, 44, &encoded[0], 100) ;
  expEncoded = "IGINCMUHNHQRMSUIMHWZODXTNAEKVVQGYTVVQPHXINWCABASYYMTKSZRCXW" ;
  if (strcmp(&encoded[0], expEncoded)!=0 ) {
    snprintf(errorBuf, errorBufLim,"%s: lines %s/%s", __func__, encoded, expEncoded);
    return false;
  }

  line = "ABCDEFG";
  key = "C";
  keyLen = 1;

  encodeLine(&at, line, key, keyLen, 0, &encoded[0], 100) ;
  expEncoded = "CDEFGHI" ;
  if (strcmp(&encoded[0], expEncoded)!=0 ) {
    snprintf(errorBuf, errorBufLim,"%s: lines %s/%s", __func__, encoded, expEncoded);
    return false;
  }

  return true;
}

// ===========================================================================
