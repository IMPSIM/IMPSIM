/* ------------------------------------------------------------------ */
/* ldnanc-01 Jan 00:06 May 06
|     (C)Copyright, JJU Research, 2000-2006.
|
|     Description:
|       Set the NaN (Not a Number) pattern into a word of memory.
|
|     Access:
|       (void) ldnanc(void *word)
|     void *word,i-The word into which NaN is to be set.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The bit-pattern used for NaN is the same as the long int pattern
|     defined as INDEF in libcad.h.
|       Once set, the value of word can be tested by isnan(word) or
|     isnanc(&word) to see if it still has the value of INDEF.  Thus,
|     this pattern can be used to identify undefined values in memory.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

#include "..\libcad\libcad.h"
#ifdef ANSI
  void ldnanc(void *word)
#else
  void ldnanc(word)
  void *word;
#endif
{
  unsigned long *iword;

  iword  = (unsigned long *) word;
  *iword = INDEF;
  return;
}
