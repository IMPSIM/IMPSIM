/* ------------------------------------------------------------------ */
/* x2to3c-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Transform a point from 2D to 3D homogeneous coordinates.
|
|     Access:
|       (void) x2to3c(real x2, real y2, real z2, real w2, real *x3,
|         real *y3, real *z3, real *w3);
|     real  x2,i-The 2D x-coordinate of the point.
|     real  y2,i-The 2D y-coordinate of the point.
|     real  z2,i-The 2D z-coordinate of the point.
|     real  w2,i-The 2D homogeneous coordinate of the point.
|     real *x3,o-The 3D x-coordinate of the point.
|     real *y3,o-The 3D y-coordinate of the point.
|     real *z3,o-The 3D z-coordinate of the point.
|     real *w3,o-The 3D homogeneous coordinate of the point.
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
  void x2to3c(real x2, real y2, real z2, real w2, real *x3, real *y3,
    real *z3, real *w3)
#else
  void x2to3c(x2, y2, z2, w2, x3, y3, z3, w3)
  real x2, y2, z2, w2, *x3, *y3, *z3, *w3;
#endif
{
  real w, x, y, z;
 
  x   = x2 + 0.5 * (x2max + x2min) * eyeinv * z2;
  y   = y2 + 0.5 * (y2max + y2min) * eyeinv * z2;
  z   = z2;
  w   = w2 + eyeinv * z2;
  *x3 = x2to3[0][0]*x + x2to3[0][1]*y + x2to3[0][2]*z + x2to3[0][3]*w;
  *y3 = x2to3[1][0]*x + x2to3[1][1]*y + x2to3[1][2]*z + x2to3[1][3]*w;
  *z3 = x2to3[2][0]*x + x2to3[2][1]*y + x2to3[2][2]*z + x2to3[2][3]*w;
  *w3 = x2to3[3][0]*x + x2to3[3][1]*y + x2to3[3][2]*z + x2to3[3][3]*w;
  return;
}
