/* ------------------------------------------------------------------ */
/* iandc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Form the bit by bit logical and of the bit patterns stored in
|     two words.
|
|     Access:
|       ireslt = (unsigned long) iandc(void *iword1, void *iword2);
|     void *iword1,i-First word bit pattern.
|     void *iword2,i-Second word bit pattern.
|     unsigned long ireslt,o-Resulting word bit pattern.
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
  unsigned long iandc(void *iword1, void *iword2)
#else
  unsigned long iandc(iword1, iword2)
  void *iword1, *iword2;
#endif
{
  unsigned long result, word1, word2;

  word1 = *((unsigned long *) iword1);
  word2 = *((unsigned long *) iword2);
  result = word1 & word2;
  return(result);
}
