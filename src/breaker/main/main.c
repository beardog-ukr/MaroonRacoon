#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#include "Breaker.h"
#include "BreakerCLAP.h"

// ===========================================================================

void performAction(BreakerParameters pp) {
  int execResult = 0;
  AlphabetTransform* atRules =  createAlphabetTransform();

  execResult = loadAlphabetFile(pp.alphFilename, atRules);
  if (execResult!=0) {
    freeAlphabetTransform(atRules);
    return;
  }

  FrequencyInfo* finf = createFrequencyInfo();
  execResult = loadFrequencyInfoFile(pp.fiFilename, finf) ;
  if (execResult!=0) {
    printFrequencyInfoLoaderError(execResult) ;
    freeFrequencyInfo(finf);
    freeAlphabetTransform(atRules);
    return;
  }

  execResult = performBreak(pp.inFilename, pp.outFilename, atRules, finf);
  if (execResult!=0) {
    printf("Failed something %u\n", execResult);
  }

  freeAlphabetTransform(atRules);
  freeFrequencyInfo(finf);
}

// ===========================================================================
// ===========================================================================
// ===========================================================================

int main(int argc, char *argv[]) {
  BreakerParameters bp;
  int pclr = processCommandLine(argc, argv, &bp) ; //

  if (pclr) {
    printBreakerClapError(pclr);
    return 1;
  }

  performAction(bp) ;

  return 0;
}

// ===========================================================================
