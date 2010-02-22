/* ------------------------------------------------------------------ */
/* clbitc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Set the specified bit of a word to zero.
|
|     Access:
|       (void) clbitc(int nbit, void *word)
|     int   nbit,i-Bit position of the bit to be cleared.
|     void *word,i/o-Word in which bit is to be cleared.
|
|     Error Conditions:
|       If nbit >= NBITS, then no action is taken.
|
|     Comments:
|       For specification of nbit, bits are numbered from zero to a
|     maximum, with the lesser significant bits being numbered with
|     smaller values of nbit.  The lowest bit has nbit=0.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

#include "..\libcad\libcad.h"
#ifdef ANSI
  void clbitc(int nbit, void *word)
#else
  void clbitc(nbit, word)
  int   nbit;
  void *word;
#endif
{
  unsigned long int *iword;
    
  iword = (unsigned long int *) word;
  if (nbit < NBITS) *iword &= ~(1 << nbit);
  return;
}
