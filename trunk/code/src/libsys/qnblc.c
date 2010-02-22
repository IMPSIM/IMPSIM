/* ------------------------------------------------------------------ */
/* qnblc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       This routine finds the four least significant bits of a word
|     and returns the bit pattern as an integer.
|
|     Access:
|       intger = (int) qnblc(void *word);
|     void *word,i-Word with bits to be found.
|     int intger,o-Integer bit pattern found from word.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       Only the four least significant bits of word are found.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

#include "..\libcad\libcad.h"
#ifdef ANSI
  int qnblc(void *word)
#else
  int qnblc(word)
  void *word;
#endif
{
  int i, intger, j; 

  intger = 0;
  for (j=0, i=LSBREL; j<4; i++, j++) {
    if (qbitc(i, word)) intger |= 1 << j;
  }
  return(intger);
}
