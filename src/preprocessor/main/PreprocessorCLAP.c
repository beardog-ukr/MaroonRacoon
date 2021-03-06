#include "PreprocessorCLAP.h"
#include "CommonCLAP.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>

// ===========================================================================

enum ErrorCodes {
  EC_MISSED_ARGUMENT =1,
  EC_MISSED_ARGUMENT_IN ,
  EC_MISSED_ARGUMENT_OUT,
  EC_MISSED_ARGUMENT_ALPH,
  EC_MISSED_IN ,
  EC_MISSED_OUT,
  EC_MISSED_ALPH,
  EC_UNKNOWN_OPTION,
  EC_MORE_ARGUMENTS
};

// ===========================================================================

int processCommandLine(const int argc, char * const argv[],
                       PreprocessorParameters* parameters) {
  parameters->showHelp = false;
  parameters->inFilename =0 ;
  parameters->outFilename =0 ;
  parameters->alphFilename =0;

  static struct option long_options[] = {
    {"in",     required_argument, 0,  'i' },
    {"out",    required_argument, 0,  'o' },
    {"alph",   required_argument, 0,  'a' },
    {"help",  no_argument,       0,  'h'},
    {0,         0,                0,  0 }
  };

  int opt;
  int option_index = 0;
  while ((opt = getopt_long(argc, argv, ":i:o:a:h", long_options, &option_index )) != -1) {
    switch (opt) {
      case 'i':
        if (looksLikeOption(optarg)) {
          return EC_MISSED_ARGUMENT_IN;
        }
        parameters->inFilename = optarg;
      break;
      case 'o':
        if (looksLikeOption(optarg)) {
          return EC_MISSED_ARGUMENT_OUT;
        }
        parameters->outFilename = optarg;
      break;
      case 'a':
        if (looksLikeOption(optarg)) {
          return EC_MISSED_ARGUMENT_OUT;
        }
        parameters->alphFilename = optarg;
      break;

      case 'h':
        //printf("Option \"h\" processed\n");
        parameters->showHelp = true;
      break;

      case ':':
        return EC_MISSED_ARGUMENT;
      break;

      case '?':
      default:
        printf("unknown option %s (%s)\n", argv[optind], optarg);
        return EC_UNKNOWN_OPTION;
    }
  }

  if (optind>argc) {
    return EC_MORE_ARGUMENTS;
  }

  if (parameters->showHelp) {
    return 0; //no need to perform other checks
  }

  if ( parameters->alphFilename ==0) {
    return EC_MISSED_ALPH;
  }
  if ( parameters->inFilename ==0) {
    return EC_MISSED_IN;
  }
  if ( parameters->outFilename ==0) {
    return EC_MISSED_OUT;
  }

  return 0;
}

// ===========================================================================

void printError(int errorCode) {
  switch (errorCode) {
    case EC_MISSED_ARGUMENT:
      fprintf(stderr, "Missed argument for some option\n");
    break;

    case EC_MISSED_ARGUMENT_ALPH:
      fprintf(stderr, "Missed argument for -a (or --aplh) option\n");
    break;
    case EC_MISSED_ARGUMENT_IN:
      fprintf(stderr, "Missed argument for -i option\n");
    break;
    case EC_MISSED_ARGUMENT_OUT:
      fprintf(stderr, "Missed argument for -o option\n");
    break;

    case EC_MISSED_ALPH:
      fprintf(stderr, "Missed alphabet file name (-a or --aplh option)\n");
    break;
    case EC_MISSED_IN:
      fprintf(stderr, "Missed input file name (-i or --in option)\n");
    break;
    case EC_MISSED_OUT:
      fprintf(stderr, "Missed output file name (-o or --out option)\n");
    break;

    case EC_UNKNOWN_OPTION:
      fprintf(stderr, "Received unknown option\n");
    break;

    case EC_MORE_ARGUMENTS:
      fprintf(stderr, "This program should not receive non-option arguments\n");
    break;
  }
}


// ===========================================================================
