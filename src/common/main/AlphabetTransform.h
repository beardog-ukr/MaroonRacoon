#ifndef __Alphabet_Transform__
#define __Alphabet_Transform__

#include <stdbool.h>

typedef struct AlphabetTransformStruct {
  char* basic;
  char* transformation;
  char* transConfirm;
  int n;// number of symbols in the alphabet (26 for english)
} AlphabetTransform;

AlphabetTransform* createAlphabetTransform(void) ;
AlphabetTransform* freeAlphabetTransform(AlphabetTransform* at) ;

int loadAlphabetFile(const char* filename, AlphabetTransform* at);
int getAlphabetLoaderError(const int errorCode, char* line, const int lineLim);
void printAlphabetLoaderError(const int errorCode);

//--------
// Seaches for given char in the row. Usually gets called with at->basic.
//returns int position in the row or -1 if nothing found
int findAlphabetPos(const char* row, const char sample) ;

//--------
char transformOneChar(const AlphabetTransform* at, const char symbol) ;
void convertLine(const AlphabetTransform* at, char* line,
                 char* result, const int resultLimit) ;

//---------
// Checks if key conform to alphabet rules (if all the key symbols are allowed
// in the alphabet)
// returns true if all is ok
bool checkKey(const AlphabetTransform* const at, const char* const key);

#endif
