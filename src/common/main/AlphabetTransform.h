#ifndef __Alphabet_Transform__
#define __Alphabet_Transform__

typedef struct AlphabetTransformStruct {
  char* basic;
  char* transformation;
  char* transConfirm;
  int n;// number of symbols in the alphabet (26 for english)
} AlphabetTransform;

AlphabetTransform* createAlphabetTransform() ;
AlphabetTransform* freeAlphabetTransform(AlphabetTransform* at) ;

int loadAlphabetFile(const char* filename, AlphabetTransform* at);
int getAlphabetLoaderError(const int errorCode, char* line, const int lineLim);
void printAlphabetLoaderError(const int errorCode);

int findAlphabetPos(const char* row, const char sample) ;
char transformOneChar(const AlphabetTransform* at, const char symbol) ;
void convertLine(const AlphabetTransform* at, char* line,
                 char* result, const int resultLimit) ;

#endif
