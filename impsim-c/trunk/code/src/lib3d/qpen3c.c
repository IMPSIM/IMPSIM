/* ------------------------------------------------------------------ */
/* qpen3c-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Return the current 3D coordinates of the graphic pen.
|
|     Access:
|       (void) qpen3c(real *x, real *y, real *z, real *w);
|     real *x,o-The 3D x-coordinate of the graphic pen.
|     real *y,o-The 3D y-coordinate of the graphic pen.
|     real *z,o-The 3D z-coordinate of the graphic pen.
|     real *w,o-The 3D homogeneous coordinate of the graphic pen.
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
  void qpen3c(real *x, real *y, real *z, real *w)
#else
  void qpen3c(x, y, z, w)
  real *x, *y, *z, *w;
#endif
{
  real x2, y2;
 
  qpen2c(&x2, &y2);
  x2to3c(x2, y2, 0.0, 1.0, &x3pen, &y3pen, &z3pen, &w3pen);
  *x = x3pen;
  *y = y3pen;
  *z = z3pen;
  *w = w3pen;
  l3pen = TRUE;
  return;
}
