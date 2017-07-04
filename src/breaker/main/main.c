#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "AlphabetTransform.h"
//#include "X2Decode.h"
#include "BreakerCLAP.h"

// ===========================================================================

void performAction(BreakerParameters pp) {
  int execResult = 0;
  AlphabetTransform* atRules = createAlphabetTransform();

  execResult = loadAlphabetFile(pp.alphFilename, atRules);

  if (!execResult) {
    printf("Got rules:\n");
    printf("basic         : %s\n", atRules->basic);
    printf("transformation: %s\n", atRules->transformation);
    printf("transConfirm  : %s\n", atRules->transConfirm);

//    execResult = performDecoding(pp->inFilename, pp->outFilename,
//                                 pp->key, atRules  );
  }
  //
  if (execResult!=0) {
    printf("Failed something %u\n", execResult);
  }

  atRules = freeAlphabetTransform(atRules);
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

  printf("Working in from %s\n", bp.inFilename);
  printf("Working out to %s\n", bp.outFilename);
  printf("Alphabet will be loaded from %s\n", bp.alphFilename);
  printf("Key length supposed to be \"%u\"\n", bp.key);


  performAction(bp) ;

  return 0;
}

// ===========================================================================
