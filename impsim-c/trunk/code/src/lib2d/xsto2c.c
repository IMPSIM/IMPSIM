/* ------------------------------------------------------------------ */
/* xsto2c-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Transform a given point from screen to 2D coordinates.
|
|     Access:
|       (void) xsto2c(real s, real t, real *x2, real *y2);
|     real  s, i-The horizontal screen coordinate of the point.
|     real  t, i-The vertical   screen coordinate of the point.
|     real *x2,o-The horizontal 2D coordinate of the point.
|     real *y2,o-The vertical   2D coordinate of the point.
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
  void xsto2c(real s, real t, real *x2, real *y2)
#else
  void xsto2c(s, t, x2, y2)
  real s, t, *x2, *y2;
#endif
{
  *x2 = (s - x20) / x2scal;
  *y2 = (t - y20) / y2scal;
  return;
}
