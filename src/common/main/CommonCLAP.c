#include "CommonCLAP.h"

#include <string.h> //strlen
#include <stdio.h>

// ===========================================================================

bool looksLikeOption(const char* const sample){
  if (sample==0) {
    return true;
  }

  if (strlen(sample)==0) { //really should be undefined
    return true;
  }

  if ( (sample!=0) &&(sample[0]=='-')  ) {
    return true;
  }

  return false;
}

// ===========================================================================

void printClapError(const int errCode,  int (*getErrorStr)(const int, char* , const int  )) {
  const int ebs = 1024;
  char errbuf[ebs];
  if ( getErrorStr(errCode, errbuf, ebs) ==0) {
    fprintf(stderr, "%s\n", errbuf);
  }
  else {
    fprintf(stderr, "Unknown internal error (%u)\n", errCode);
  }
}
