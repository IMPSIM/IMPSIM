/* ------------------------------------------------------------------ */
/* ldbitc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Set bit number nbit of a word to one.
|
|     Access:
|       (void) ldbitc(int nbit, void *word)
|     int   nbit,i-Bit position of the bit to be set.
|     void *word,i/o-Word in which bit is to be set.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       For specification of nbit, bits are numbered from zero to NBITS
|     with the less significant bits being numbered with smaller values
|     of nbit.
|       If nbit >= NBITS, the number of bits in a single word, then no
|     action is taken.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

#include "..\libcad\libcad.h"
#ifdef ANSI
  void ldbitc(int nbit, void *word)
#else
  void ldbitc(nbit, word)
  int   nbit;
  void *word;
#endif
{
  unsigned long *iword;

  iword = (unsigned long *) word;
  if (nbit < NBITS) *iword |= (1 << nbit);
  return;
}
