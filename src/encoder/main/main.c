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
    // printf("Got rules:\n");
    // printf("basic         : %s\n", atRules->basic);
    // printf("transformation: %s\n", atRules->transformation);
    // printf("transConfirm  : %s\n", atRules->transConfirm);
    if (!checkKey(atRules, pp->key)) {
      printf("Error: Key \"%s\" does not conform alphabet\n", pp->key);
      execResult = 1;
    }
  }

  if (!execResult) {
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

  if (ep.showHelp) {
    printf("vi_encoder accepts following command line options:\n");
    printf("  -i or --in sets input file name\n");
    printf("  -o or --out sets file name to store result\n");
    printf("  -a or --aplh is a name of the file defining alphabet\n" );
    printf("  -k or --key defines key\n" );
    printf("all parameters are mandatory\n");
    return 0;
  }

  // printf("Working in from %s\n", ep.inFilename);
  // printf("Working out to %s\n", ep.outFilename);
  // printf("Alphabet will be loaded from %s\n", ep.alphFilename);
  // printf("Key is \"%s\"\n", ep.key);


  performAction(&ep) ;

  return 0;
}

// ===========================================================================
