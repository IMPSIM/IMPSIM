/* ------------------------------------------------------------------ */
/* isnanc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Test a word of memory for the NaN (Not a Number) pattern.
|
|     Access:
|       lflag = (int) isnanc(void *word);
|     void *word,i-The word which is to be tested.
|     int   lflag,o-Flag set TRUE if word has content of NaN.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The bit-pattern used for NaN is the same as the long int pattern
|     defined as INDEF in libcad.h.
|       Once initialized (by ldnanc), the value of word can be tested by
|     isnanc(word) or isnanc(&word) to see if it still has the value of
|     INDEF. Thus, this pattern can be used to identify undefined values
|     in memory.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

#include "..\libcad\libcad.h"
#ifdef ANSI
  int isnanc(void *word)
#else
  int isnanc(word)
  void *word;
#endif
{
  int           result;
  unsigned long iword;

  iword = *((unsigned long *) word);
  if (iword == INDEF){
    result = TRUE;
  } else {
    result = FALSE;
  }
  return(result);
}
