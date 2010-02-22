/* ------------------------------------------------------------------ */
/* x2tosc-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Transform a given point from 2D to screen coordinates.
|
|     Access:
|       (void) x2tosc(real x2, real y2, real *s, real *t);
|     real  x2,i-The horizontal 2D coordinate of the point.
|     real  y2,i-The vertical   2D coordinate of the point.
|     real *s, o-The horizontal screen coordinate of the point.
|     real *t, o-The vertical   screen coordinate of the point.
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
  void x2tosc(real x2, real y2, real *s, real *t)
#else
  void x2tosc(x2, y2, s, t)
  real x2, y2, *s, *t;
#endif
{
  *s = x2 * x2scal + x20;
  *t = y2 * y2scal + y20;
  return;
}
