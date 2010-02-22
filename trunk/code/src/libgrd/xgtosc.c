/* ------------------------------------------------------------------ */
/* xgtosc-01 Jan 00:23 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Transform the grid coordinates (x,y) of a point to its screen
|     coordinates (s,t).
|
|     Access:
|       (void) xgtosc(real x, real y, real *s, real *t);
|     real  x,i-Horizontal grid coordinate value to be transformed.
|     real  y,i-Vertical   grid coordinate value to be transformed.
|     real *s,o-Transformed horizontal screen coordinate value.
|     real *t,o-Transformed vertical   screen coordinate value.
|
|     Error Conditions:
|       If routine gridc has specified a log axis and x (or y) is a non-
|     positive value, then the max of x (or y) and ZERO is used instead.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       The transformation parameters from to screen coordinates must
|     have been defined by a previous call to gridc().
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void xgtosc(real x, real y, real *s, real *t)
#else
  void xgtosc(x, y, s, t)
  real x, y, *s, *t;
#endif
{
  real p, q;
 
  p = x;
  if ((kgrid & 1) != 0) p = log( max(p, ZERO));
  *s = min( max(pscale * p + p0, sgmin), sgmax);
  q = y;
  if (kgrid / 2 != 0) q = log( max(q, ZERO));
  *t = min( max(qscale * q + q0, tgmin), tgmax);
  return;
}
