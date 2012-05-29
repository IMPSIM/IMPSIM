/* ------------------------------------------------------------------ */
/* drwr3c-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Draw a visible line segment through (dx, dy, dz, w) relative 3D
|     coordinate increments from the current pen location.
|
|     Access:
|       (void) drwr3c(real dx, real dy, real dz, real w);
|     real dx,i-The 3D relative x-increment to draw through.
|     real dy,i-The 3D relative y-increment to draw through.
|     real dz,i-The 3D relative z-increment to draw through.
|     real w, i-The 3D homogeneous coordinate of this increment.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       The line segment to be drawn is clipped to fit within the cur-
|     rent screen window.
|       The line segment will be drawn as solid visible, or with the
|     pattern defined by the most recent call to dashc().
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void drwr3c(real dx, real dy, real dz, real w)
#else
  void drwr3c(dx, dy, dz, w)
  real dx, dy, dz, w;
#endif
{
  real x, y, z, h;
 
  if (! l3pen) {
    if (! l2pen) {
      xsto2c(spen, tpen, &x2pen, &y2pen);
      l2pen = TRUE;
    }
    x2to3c(x2pen, y2pen, 0.0, 1.0, &x3pen, &y3pen, &z3pen, &w3pen);
    l3pen = TRUE;
  }
  x = x3pen * w + dx * w3pen;
  y = y3pen * w + dy * w3pen;
  z = z3pen * w + dz * w3pen;
  h = w * w3pen;
  drwa3c(x, y, z, h);
  return;
}
