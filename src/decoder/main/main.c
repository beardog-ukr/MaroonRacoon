#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "AlphabetTransform.h"
#include "BasicDecode.h"
#include "CommonCLAP.h"
#include "DecoderCLAP.h"

// ===========================================================================

void performAction(DecoderParameters* pp) {
  int execResult = 0;
  AlphabetTransform* atRules = createAlphabetTransform();

  execResult = loadAlphabetFile(pp->alphFilename, atRules);

  if (!execResult) {
    if (!checkKey(atRules, pp->key)) {
      printf("Error: Key \"%s\" does not conform alphabet\n", pp->key);
      execResult = 1;
    }
  }

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
    printClapError(pclr, getDecoderClapError);
    return 1;
  }

  // printf("Working in from %s\n", dp.inFilename);
  // printf("Working out to %s\n", dp.outFilename);
  // printf("Alphabet will be loaded from %s\n", dp.alphFilename);
  // printf("Key is \"%s\"\n", dp.key);
  if (dp.showHelp) {
    printf("vi_decoder accepts following command line options:\n");
    printf("  -i or --in sets input file name\n");
    printf("  -o or --out sets file name to store result\n");
    printf("  -a or --alph is a name of the file defining alphabet\n" );
    printf("  -k or --key defines key\n" );
    printf("all parameters are mandatory\n");
    return 0;
  }

  performAction(&dp) ;

  return 0;
}

// ===========================================================================
