/* ------------------------------------------------------------------ */
/* x3to2c-01 Jan 00:05 Jul 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Transform a point from 3D to 2D homogeneous coordinates.
|
|     Access:
|       (void) x3to2c(real x3, real y3, real z3, real w3, real *x2,
|         real *y2, real *z2, real *w2);
|     real  x3,i-The 3D x-coordinate of the point.
|     real  y3,i-The 3D y-coordinate of the point.
|     real  z3,i-The 3D z-coordinate of the point.
|     real  w3,i-The 3D homogeneous coordinate of the point.
|     real *x2,o-The 2D x-coordinate of the point.
|     real *y2,o-The 2D y-coordinate of the point.
|     real *z2,o-The 2D z-coordinate of the point.
|     real *w2,o-The 2D homogeneous coordinate of the point.
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
  void x3to2c(real x3, real y3, real z3, real w3, real *x2, real *y2,
    real *z2, real *w2)
#else
  void x3to2c(x3, y3, z3, w3, x2, y2, z2, w2)
  real x3, y3, z3, w3, *x2, *y2, *z2, *w2;
#endif
{
  *x2  = x3to2[0][0] * x3 + x3to2[0][1] * y3 + x3to2[0][2] * z3
       + x3to2[0][3] * w3;
  *y2  = x3to2[1][0] * x3 + x3to2[1][1] * y3 + x3to2[1][2] * z3
       + x3to2[1][3] * w3;
  *z2  = x3to2[2][0] * x3 + x3to2[2][1] * y3 + x3to2[2][2] * z3
       + x3to2[2][3] * w3;
  *w2  = x3to2[3][0] * x3 + x3to2[3][1] * y3 + x3to2[3][2] * z3
       + x3to2[3][3] * w3;
  *x2 -= 0.5 * (x2max + x2min) * eyeinv * *z2;
  *y2 -= 0.5 * (y2max + y2min) * eyeinv * *z2;
  *w2 -=                         eyeinv * *z2;
  return;
}
