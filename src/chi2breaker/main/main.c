#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "AlphabetTransform.h"
#include "FrequencyInfo.h"
#include "Chi2Breaker.h"
#include "Chi2BreakerCLAP.h"

// ===========================================================================

void performAction(Chi2BreakerParameters pp) {
  int execResult = 0;
  AlphabetTransform* atRules =  createAlphabetTransform();

  execResult = loadAlphabetFile(pp.alphFilename, atRules);
  if (execResult!=0) {
    freeAlphabetTransform(atRules);
    return;
  }

  FrequencyInfo* finf = createFrequencyInfo();
  execResult = loadFrequencyInfoFile(pp.freqFilename, finf) ;
  if (execResult!=0) {
    printFrequencyInfoLoaderError(execResult) ;
    freeFrequencyInfo(finf);
    freeAlphabetTransform(atRules);
    return;
  }

  execResult = performChi2Break(pp.inFilename, pp.outFilename,
                                pp.keyLength, atRules, finf);
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
  Chi2BreakerParameters c2bp;
  int pclr = processCommandLine(argc, argv, &c2bp) ; //

  if (pclr) {
    printChi2BreakerClapError(pclr);
    return 1;
  }

  performAction(c2bp) ;

  return 0;
}

// ===========================================================================
