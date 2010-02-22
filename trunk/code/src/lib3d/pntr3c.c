/* ------------------------------------------------------------------ */
/* pntr3c-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Place a visible point at (dx, dy, dz, w) relative 3D coordinates
|     from the current pen location.
|
|     Access:
|       (void) pntr3c(real dx, real dy, real dz, real w);
|     real dx,i-The 3D x-coordinate from the pen to the point.
|     real dy,i-The 3D y-coordinate from the pen to the point.
|     real dz,i-The 3D z-coordinate from the pen to the point.
|     real w, i-The 3D homogeneous coordinate of the increment.
|
|     Error Conditions:
|       If the values specified produce a point location outside of the
|     current page or screen windows, the point will not appear.
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
  void pntr3c(real dx, real dy, real dz, real w)
#else
  void pntr3c(dx, dy, dz, w)
  real dx, dy, dz, w;
#endif
{
  movr3c(dx, dy, dz, w);
  drwr3c(0.0, 0.0, 0.0, 1.0);
  return;
}
