#ifndef __COMMON_CLAP__
#define __COMMON_CLAP__

//CLAP is "command line arguments processor"

#include <stdbool.h>

bool looksLikeOption(const char* const sample);

void printClapError(const int errCode, int (*getErrorStr)(const int, char* , const int));

#endif
