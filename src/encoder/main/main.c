#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "AlphabetTransform.h"
#include "Encoder.h"
#include "EncoderCLAP.h"

// ===========================================================================

void performAction(EncoderParameters* pp) {
  int execResult = 0;
  AlphabetTransform* atRules = createAlphabetTransform();

  execResult = loadAlphabetFile(pp->alphFilename, atRules);

  if (!execResult) {
    printf("Got rules:\n");
    printf("basic         : %s\n", atRules->basic);
    printf("transformation: %s\n", atRules->transformation);
    printf("transConfirm  : %s\n", atRules->transConfirm);

    execResult = performEncoding(pp->inFilename, pp->outFilename,
                                 pp->key, atRules  );
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
  EncoderParameters ep;
  int pclr = processCommandLine(argc, argv, &ep) ; //

  if (pclr) {
    printEncoderClapError(pclr);
    return 1;
  }

  printf("Working in from %s\n", ep.inFilename);
  printf("Working out to %s\n", ep.outFilename);
  printf("Alphabet will be loaded from %s\n", ep.alphFilename);
  printf("Key is \"%s\"\n", ep.key);


  performAction(&ep) ;

  return 0;
}

// ===========================================================================
