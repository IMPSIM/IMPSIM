/* ------------------------------------------------------------------ */
/* ishftc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Perform a bit by bit logical left shift of the bit pattern
|     stored in a word by a given number of bits, filling with zero bits
|     on the right.
|
|     Access:
|       ireslt = (unsigned long) ishftc(void *iword, int ibits)
|     void         *iword,i- Bit pattern to be shifted.
|     int           ibits,i- Number of bits to be shifted through.
|     unsigned long ireslt,o-Resulting bit pattern.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       No integer overflow condition will result, as might occur if
|     multiplication by 2**ibits were used instead.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

#include "..\libcad\libcad.h"
#ifdef ANSI
  unsigned long ishftc(void *iword, int ibits)
#else
  ishftc(iword, ibits)
  void *iword;
  int   ibits;
#endif
{
  unsigned long result, word;

  word   = *((unsigned long *) iword);
  result = word << ibits;
  return(result);
}
