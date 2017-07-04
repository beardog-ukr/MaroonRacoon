#include "FileUtils.h"

#include <stdio.h> //fgetc, fopen
#include <stdlib.h> // malloc
#include <string.h> //strlen

enum FileUtilsErrorCodes {
  FUEC_FAILED_READ =1
};

// ===========================================================================

int readFullFile(const char* const filename, char* buf, const int bufLimit) {
  FILE* fp;
  fp = fopen(filename, "r");
  if (fp == NULL) {
    return FUEC_FAILED_READ;
  }

  char* lineBuf = malloc(bufLimit) ;
  int currentBufLength = 0;

  while ( (fgets(lineBuf, bufLimit, fp) != NULL) ) {
    int realLineLen = strlen(lineBuf);
    if (lineBuf[realLineLen-1]=='\n') {
      lineBuf[realLineLen-1] ='\0';
      realLineLen--;
    }
    if( (currentBufLength + realLineLen) < (bufLimit-1) ) {
      strcpy( &buf[currentBufLength], lineBuf);
      currentBufLength += realLineLen;
    }
    else {
      break;
    }
  }

  //printf("Got line <%s>\n", buf);

  free(lineBuf);
  fclose(fp);
  return 0;
}

// ===========================================================================
