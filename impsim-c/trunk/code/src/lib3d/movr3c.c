/* ------------------------------------------------------------------ */
/* movr3c-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Move the pen by (dx, dy, dz, w) 3D units from its current
|     location.
|
|     Access:
|       (void) movr3c(real dx, real dy, real dz, real w);
|     real dx,i-The relative 3D x-coordinate of the pen movement.
|     real dy,i-The relative 3D y-coordinate of the pen movement.
|     real dz,i-The relative 3D z-coordinate of the pen movement.
|     real w, i-The 3D homogeneous coordinate for this increment.
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
  void movr3c(real dx, real dy, real dz, real w)
#else
  void movr3c(dx, dy, dz, w)
  real dx, dy, dz, w;
#endif
{
  real w3, x3, y3, z3;
 
  if ( ! l3pen) {
    if ( ! l2pen) {
      xsto2c(spen, tpen, &x2pen, &y2pen);
      l2pen = TRUE;
    }
    x2to3c(x2pen, y2pen, 0.0, 1.0, &x3pen, &y3pen, &z3pen, &w3pen);
    l3pen = TRUE;
  }
  x3 = x3pen * w + w3pen * dx;
  y3 = y3pen * w + w3pen * dy;
  z3 = z3pen * w + w3pen * dz;
  w3 = w3pen* w;
  mova3c(x3, y3, z3, w3);
  return;
}
