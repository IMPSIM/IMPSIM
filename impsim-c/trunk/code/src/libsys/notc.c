/* ------------------------------------------------------------------ */
/* notc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Form the bit by bit logical complement of the bit pattern stored
|     in a word.
|
|     Access:
|       ireslt = (unsigned long) notc(void *word)
|     void *word,i-Bit pattern to be complemented.
|     unsigned long ireslt,o-Resulting bit pattern.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

#include "..\libcad\libcad.h"
#ifdef ANSI
  unsigned long notc(void *word)
#else
  unsigned long notc(word)
  void *word;
#endif
{
  unsigned long *iword;

  iword = (unsigned long *) word;
  return(~(*iword));
}
