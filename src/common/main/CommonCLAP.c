#include "CommonCLAP.h"

#include <string.h> //strlen

// ===========================================================================

bool looksLikeOption(char* const sample){
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
