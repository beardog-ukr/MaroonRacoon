#ifndef __Decoder_Command_Line_Arguments__
#define __Decoder_Command_Line_Arguments__

#include <stdbool.h>

typedef struct DecoderParametersStruct {
  char* inFilename;
  char* alphFilename;
  char* outFilename;
  char* key;
  bool showHelp;
} DecoderParameters;

void initDecoderParameters(DecoderParameters* ep);

// ===========================================================================

int processCommandLine(int argc, char *argv[], DecoderParameters* parameters) ;

int getDecoderClapError(const int errorCode, char* line, const int lineLim);
void printDecoderClapError(const int errCode) ;


#endif
