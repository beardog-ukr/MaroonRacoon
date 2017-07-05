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

  if (c2bp.showHelp) {
    printf("vi_ci2breaker accepts following command line options:\n");
    printf("  -i or --in sets input file name\n");
    printf("  -o or --out sets file name to store result\n");
    printf("  -a or --aplh is a name of the file defining alphabet\n" );
    printf("  -f or --fi is a name of the file defining letter frequency\n" );
    printf("  -k or --key defines key length (integer)\n" );
    printf("all parameters are mandatory\n");
    return 0;
  }

  performAction(c2bp) ;

  return 0;
}

// ===========================================================================
