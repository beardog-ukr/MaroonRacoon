#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "AlphabetTransform.h"
#include "BasicDecode.h"
#include "DecoderCLAP.h"

// ===========================================================================

void performAction(DecoderParameters* pp) {
  int execResult = 0;
  AlphabetTransform* atRules = createAlphabetTransform();

  execResult = loadAlphabetFile(pp->alphFilename, atRules);

  if (!execResult) {
    execResult = performDecoding(pp->inFilename, pp->outFilename, pp->key, atRules  );
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
  DecoderParameters dp;
  int pclr = processCommandLine(argc, argv, &dp) ; //

  if (pclr) {
    printDecoderClapError(pclr);
    return 1;
  }

  // printf("Working in from %s\n", dp.inFilename);
  // printf("Working out to %s\n", dp.outFilename);
  // printf("Alphabet will be loaded from %s\n", dp.alphFilename);
  // printf("Key is \"%s\"\n", dp.key);


  performAction(&dp) ;

  return 0;
}

// ===========================================================================
