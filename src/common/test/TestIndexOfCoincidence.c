#include "TestIndexOfCoincidence.h"
#include "IndexOfCoincidence.h"

#include <stdio.h> //printf, fgetc, fopen, snprintf

//=============================================================================

//double calculateIndexOfCoincidence(const char* const line,
//                                   const AlphabetTransform* const at);
bool tst_calculateIndexOfCoincidence_A(char* errorBuf, const int errorBufLim) {
  AlphabetTransform at;
  at.basic = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  at.n=26;

  //both examples values in this function came from
  //http://www.cs.mtu.edu/~shene/NSF-4/Tutorial/VIG/Vig-IOC.html

  const char* c1 = "THEREARETWOWAYSOFCONSTRUCTINGASOFTWAREDESIGNONEWAY"
                   "ISTOMAKEITSOSIMPLETHATTHEREAREOBVIOUSLYNODEFICIENC"
                   "IESANDTHEOTHERWAYISTOMAKEITSOCOMPLICATEDTHATTHEREA"
                   "RENOOBVIOUSDEFICIENCIESTHEFIRSTMETHODISFARMOREDIFF"
                   "ICULT" ;

  double ioc = calculateIndexOfCoincidence(c1, &at) ;
  double expectedIoc = 0.068101;
  double diff = expectedIoc >ioc ? (expectedIoc-ioc) : (ioc-expectedIoc);
  if ( diff > 0.001 ) {
    snprintf(errorBuf, errorBufLim,
             "%s: diff %f for %f/%f", __func__, diff, ioc, expectedIoc);
    return false;
  }

  const char* c2 = "VVQGYTVVVKALURWFHQACMMVLEHUCATWFHHIPLXHVUWSCIGINCM"
             "UHNHQRMSUIMHWZODXTNAEKVVQGYTVVQPHXINWCABASYYMTKSZR"
             "CXWRPRFWYHXYGFIPSBWKQAMZYBXJQQABJEMTCHQSNAEKVVQGYT"
             "VVPCAQPBSLURQUCVMVPQUTMMLVHWDHNFIKJCPXMYEIOCDTXBJW"
             "KQGAN" ;

  ioc = calculateIndexOfCoincidence(c2, &at) ;
  expectedIoc = 0.041989;
  diff = expectedIoc >ioc ? (expectedIoc-ioc) : (ioc-expectedIoc);
  if ( diff > 0.001 ) {
    snprintf(errorBuf, errorBufLim,
             "%s: diff %f for %f/%f", __func__, diff, ioc, expectedIoc);
    return false;
  }

  const char* c3 = "ABCDEFHIJ" ;
  ioc = calculateIndexOfCoincidence(c3, &at) ;
  expectedIoc = 0.0; // unique letters will give IoC ==0
                    // since thre are no two equal letters
  diff = expectedIoc >ioc ? (expectedIoc-ioc) : (ioc-expectedIoc);
  if ( diff > 0.001 ) {
    snprintf(errorBuf, errorBufLim,
             "%s: diff %f for %f/%f", __func__, diff, ioc, expectedIoc);
    return false;
  }

  //finally
  return true;
}

//=============================================================================

//int guessKeyLengthIOC(const char* const line,const AlphabetTransform* const at);
bool tst_guessKeyLengthIOC_A(char* errorBuf, const int errorBufLim) {
  AlphabetTransform at;
  at.basic = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  at.n=26;

  //both examples values in this function came from
  // http://www.cs.mtu.edu/~shene/NSF-4/Tutorial/VIG/Vig-IOC-Len.html

  const char* c1 = "VVQGYTVVVKALURWFHQACMMVLEHUCATWFHHIPLXHVUWSCIGINCM"
             "UHNHQRMSUIMHWZODXTNAEKVVQGYTVVQPHXINWCABASYYMTKSZR"
             "CXWRPRFWYHXYGFIPSBWKQAMZYBXJQQABJEMTCHQSNAEKVVQGYT"
             "VVPCAQPBSLURQUCVMVPQUTMMLVHWDHNFIKJCPXMYEIOCDTXBJW"
             "KQGAN" ;

  int gl = guessKeyLengthIOC(c1, &at) ;
  int expectedGl = 8;
  if ( gl != expectedGl ) {
    snprintf(errorBuf, errorBufLim,
             "%s: bad %u/%u", __func__, gl, expectedGl);
    return false;
  }

  return true;
}

//=============================================================================
