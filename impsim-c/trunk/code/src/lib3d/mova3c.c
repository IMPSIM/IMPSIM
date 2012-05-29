/* ------------------------------------------------------------------ */
/* mova3c-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Move the pen to given absolute 3D coordinates (x, y, z, w).
|
|     Access:
|       (void) mova3c(real x, real y, real z, real w);
|     real x,i-The 3D x-coordinate of the new pen location.
|     real y,i-The 3D y-coordinate of the new pen location.
|     real z,i-The 3D z-coordinate of the new pen location.
|     real w,i-The 3D homogeneous coordinate of the new pen location.
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
  void mova3c(real x, real y, real z, real w)
#else
  void mova3c(x, y, z, w)
  real x, y, z, w;
#endif
{
  real temp1, temp2, w2, x2, y2, z2, zero;
 
  x3to2c(x, y, z, w, &x2, &y2, &z2, &w2);
  zero = min(x2scal, y2scal) * stzero;
  if (fabs(w2) <= zero) w2 = sign(zero, w2);
  temp1 = x2 / w2;
  temp2 = y2 / w2;
  mova2c(temp1, temp2);
  x3pen = x;
  y3pen = y;
  z3pen = z;
  w3pen = w;
  l3pen = TRUE;
  return;
}
