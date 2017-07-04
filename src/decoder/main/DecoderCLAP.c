#include "DecoderCLAP.h"
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
  EC_MISSED_ARGUMENT_KEY,
  EC_MISSED_IN ,
  EC_MISSED_OUT,
  EC_MISSED_ALPH,
  EC_MISSED_KEY,
  EC_UNKNOWN_OPTION,
  EC_MORE_ARGUMENTS
};

// ===========================================================================

int getDecoderClapError(const int errorCode, char* line, const int lineLim) {
  int result = 0;
  switch (errorCode) {
    case EC_MISSED_ARGUMENT:
      snprintf(line, lineLim, "Missed argument for some option\n");
    break;

    case EC_MISSED_ARGUMENT_ALPH:
      snprintf(line, lineLim, "Missed argument for -a (or --aplh) option\n");
    break;
    case EC_MISSED_ARGUMENT_IN:
      snprintf(line, lineLim, "Missed argument for -i option\n");
    break;
    case EC_MISSED_ARGUMENT_OUT:
      snprintf(line, lineLim, "Missed argument for -o option\n");
    break;
    case EC_MISSED_ARGUMENT_KEY:
      snprintf(line, lineLim, "Missed argument for -k (--key) option\n");
    break;

    case EC_MISSED_ALPH:
      snprintf(line, lineLim, "Missed alphabet file name (-a or --aplh option)\n");
    break;
    case EC_MISSED_IN:
      snprintf(line, lineLim, "Missed input file name (-i or --in option)\n");
    break;
    case EC_MISSED_OUT:
      snprintf(line, lineLim, "Missed output file name (-o or --out option)\n");
    break;
    case EC_MISSED_KEY:
      snprintf(line, lineLim, "Missed key string (-k or --key option)\n");
    break;

    case EC_UNKNOWN_OPTION:
      snprintf(line, lineLim, "Received unknown option\n");
    break;

    case EC_MORE_ARGUMENTS:
      snprintf(line, lineLim, "This program should not receive non-option arguments\n");
    break;

    default:
      result =1;
  }

  return result;
}

// ===========================================================================

void printDecoderClapError(const int errCode) {
  const int ebs = 1024;
  char errbuf[ebs];
  if ( getDecoderClapError(errCode, errbuf, ebs) ==0) {
    fprintf(stderr, "%s\n", errbuf);
  }
  else {
    fprintf(stderr, "Unknown internal error (decoder, %u)\n", errCode);
  }
}

// ===========================================================================

int processCommandLine(int argc, char *argv[], DecoderParameters* parameters) {
  parameters->showHelp = false;
  parameters->inFilename =0 ;
  parameters->outFilename =0 ;
  parameters->alphFilename =0;
  parameters->key =0;

  static struct option long_options[] = {
    {"in",     required_argument, 0,  'i' },
    {"out",    required_argument, 0,  'o' },
    {"alph",   required_argument, 0,  'a' },
    {"key",    required_argument, 0,  'k' },
    {"help",   no_argument,       0,  'h'},
    {0,        0,                 0,  0 }
  };

  int opt;
  int option_index = 0;
  while ((opt = getopt_long(argc, argv, ":i:o:a:k:h", long_options, &option_index )) != -1) {
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
      case 'k':
        if (looksLikeOption(optarg)) {
          return EC_MISSED_ARGUMENT_KEY;
        }
        parameters->key = optarg;
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

  if ( parameters->alphFilename ==0) {
    return EC_MISSED_ALPH;
  }
  if ( parameters->inFilename ==0) {
    return EC_MISSED_IN;
  }
  if ( parameters->outFilename ==0) {
    return EC_MISSED_OUT;
  }
  if ( parameters->key ==0) {
    return EC_MISSED_KEY;
  }

  return 0;
}

// ===========================================================================
