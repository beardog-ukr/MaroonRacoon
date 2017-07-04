#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "Preprocessor.h"
#include "PreprocessorCLAP.h"

// ===========================================================================

void performAction(PreprocessorParameters* pp) {
  int execResult = 0;
  AlphabetTransform* atRules = createAlphabetTransform();

  execResult = loadAlphabetFile(pp->alphFilename, atRules);

  if (!execResult) {
    printf("Got rules:\n");
    printf("basic         : %s\n", atRules->basic);
    printf("transformation: %s\n", atRules->transformation);
    printf("transConfirm  : %s\n", atRules->transConfirm);

    execResult = preprocessFiles(pp->inFilename, pp->outFilename, atRules  );
  }

  if (execResult!=0) {
    printf("Failed something %u\n", execResult);
  }

  atRules = freeAlphabetTransform(atRules);
}

// ===========================================================================

int main(int argc, char *argv[])
{
  PreprocessorParameters pp;
  int pcar = processCommandLine(argc, argv, &pp) ;

  if (pcar) {
    printError(pcar);
    return 1;
  }

  printf("Working in from %s\n", pp.inFilename);
  printf("Working out to %s\n", pp.outFilename);

  performAction(&pp) ;

  return 0;
}

// ===========================================================================
