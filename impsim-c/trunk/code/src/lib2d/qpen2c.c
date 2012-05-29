/* ------------------------------------------------------------------ */
/* qpen2c-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Return the current 2D coordinates of the graphic pen.
|
|     Access:
|       (void) qpen2c(real *x2, real *y2);
|     real *x2,o-Current 2D horizontal coordinate of the graphic pen.
|     real *y2,o-Current 2D vertical   coordinate of the graphic pen.
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
  void qpen2c(real *x2, real *y2)
#else
  void qpen2c(x2, y2)
  real *x2, *y2;
#endif
{
  real s, t;
 
  qpensc(&s, &t, &lspen);
  xsto2c(s, t, &x2pen, &y2pen);
  l2pen = TRUE;
  l3pen = FALSE;
  *x2 = x2pen;
  *y2 = y2pen;
  return;
}
