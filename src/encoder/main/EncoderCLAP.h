#ifndef __Encoder_Command_Line_Arguments__
#define __Encoder_Command_Line_Arguments__

#include <stdbool.h>

typedef struct EncoderParametersStruct {
  char* inFilename;
  char* alphFilename;
  char* outFilename;
  char* key;
  bool showHelp;
} EncoderParameters;

void initEncoderParameters(EncoderParameters* ep);

// ===========================================================================

int processCommandLine(int argc, char *argv[], EncoderParameters* parameters) ;

int getEncoderClapError(const int errorCode, char* line, const int lineLim);

#endif
