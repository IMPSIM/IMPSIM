/* ------------------------------------------------------------------ */
/* qbitc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Test whether the nbit bit of a word is set to one.
|
|     Access:
|       test = (int) qbitc(int nbit, void *word)
|     int   nbit,i-Bit position of the bit to be tested.
|     void *word,i-Word in which bit is to be tested.
|     int   test,o-Logical result of test.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       For specification of nbit, bits are numbered from zero to NBITS,
|     with the lesser significant bits being numbered with smaller
|     values of nbit.
|       If nbit >= NBITS, then qbitc returns test = FALSE.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

#include "..\libcad\libcad.h"
#ifdef ANSI
  int qbitc(int nbit, void *word)
#else
  int qbitc(nbit, word)
  int   nbit;
  void *word;
#endif
{
  unsigned long *iword;

  iword = (unsigned long *) word;
  if (nbit >= NBITS) {
    return(FALSE);
  } else {
    return(((1 << nbit) & *iword) > 0);
  }
}
