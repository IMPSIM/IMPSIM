/* ------------------------------------------------------------------ */
/* ldnblc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       This routine sets the four least significant bits of a word
|     to a bit pattern corresponding to a specified integer.
|
|     Access:
|       (void) ldnblc(int intger, void *word);
|     int   intger,i-Integer bit pattern to be set.
|     void *word,i/o-Word to be modified.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       Only the four least significant bits of word are changed.
|       intger should be greater than or equal to zero and less than 16;
|     if not, it is treated modulo 16.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

#include "..\libcad\libcad.h"
#ifdef ANSI
  void ldnblc(int intger, void *word)
#else
  void ldnblc(intger, word)
  int   intger;
  void *word;
#endif
{
  int i, j; 

  for (j=0, i=LSBREL; j<4; i++, j++){
    if (intger & (1 << j)) {
      ldbitc(i, word);
    } else {
      clbitc(i, word);
    }
  }
  return;
}
