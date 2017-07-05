#ifndef __Breaker_Command_Line_Arguments__
#define __Breaker_Command_Line_Arguments__

#include <stdbool.h>

typedef struct BreakerParametersStruct {
  char* inFilename;
  char* alphFilename;
  char* outFilename;
  char* fiFilename;
  bool showHelp;
} BreakerParameters;

// ===========================================================================

int processCommandLine(int argc, char *argv[], BreakerParameters* parameters) ;

int getBreakerClapError(const int errorCode, char* line, const int lineLim);

#endif
