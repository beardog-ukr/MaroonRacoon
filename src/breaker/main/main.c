#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#include "Breaker.h"
#include "CommonCLAP.h"
#include "CommonCLAP.h"
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
    printClapError(pclr, getBreakerClapError);
    return 1;
  }

  if (bp.showHelp) {
    printf("vi_breaker accepts following command line options:\n");
    printf("  -i or --in sets input file name\n");
    printf("  -o or --out sets file name to store result\n");
    printf("  -a or --alph is a name of the file defining alphabet\n" );
    printf("  -f or --fi is a name of the file defining letter frequency\n" );
    printf("all parameters are mandatory\n");
    return 0;
  }

  performAction(bp) ;

  return 0;
}

// ===========================================================================
