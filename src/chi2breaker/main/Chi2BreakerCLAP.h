#ifndef __Chi2Breaker_Command_Line_Arguments__
#define __Chi2Breaker_Command_Line_Arguments__

#include <stdbool.h>

typedef struct Chi2BreakerParametersStruct {
  char* inFilename;
  char* alphFilename;
  char* outFilename;
  char* freqFilename;
  int keyLength;
  bool showHelp;
} Chi2BreakerParameters;

void initDecoderParameters(Chi2BreakerParameters* c2bp);

// ===========================================================================

int processCommandLine(int argc, char *argv[], Chi2BreakerParameters* parameters) ;

int getChi2BreakerClapError(const int errorCode, char* line, const int lineLim);

#endif
