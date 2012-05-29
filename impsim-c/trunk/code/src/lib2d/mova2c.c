/* ------------------------------------------------------------------ */
/* mova2c-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Move the pen to given absolute 2D coordinates (x2, y2).
|
|     Access:
|       (void) mova2c(real x2, real y2);
|     real x2,i-The horizontal 2D coordinate of the new pen location.
|     real y2,i-The vertical   2D coordinate of the new pen location.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void mova2c(real x2, real y2)
#else
  void mova2c(x2, y2)
  real x2, y2;
#endif
{
  real s, t;
 
  x2tosc(x2, y2, &s, &t);
  movasc(s, t);
  x2pen = x2;
  y2pen = y2;
  l2pen = TRUE;
  l3pen = FALSE;
  return;
}
