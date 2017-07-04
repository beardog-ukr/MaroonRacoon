#ifndef __Preprocessor_Command_Line_Arguments__
#define __Preprocessor_Command_Line_Arguments__

#include <stdbool.h>

typedef struct PreprocessorParametersStruct {
  char* inFilename;
  char* alphFilename;
  char* outFilename;
  bool showHelp;
} PreprocessorParameters;

// ===========================================================================

int processCommandLine(const int argc, char * const argv[], 
                       PreprocessorParameters* parameters) ;

void printError(int errorCode);


#endif
