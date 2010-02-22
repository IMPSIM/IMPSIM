/* ------------------------------------------------------------------ */
/* pnta3c-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Place a visible point at given 3D coordinates (x, y, z, w).
|
|     Access:
|       (void) pnta3c(real x, real y, real z, real w);
|     real x,i-The 3D x-coordinate of the desired point.
|     real y,i-The 3D y-coordinate of the desired point.
|     real z,i-The 3D z-coordinate of the desired point.
|     real w,i-The 3D homogeneous coordinate of the desired point.
|
|     Error Conditions:
|       If coordinates outside the current page or screen windows are
|     specified, the point will not appear.
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
  void pnta3c(real x, real y, real z, real w)
#else
  void pnta3c(x, y, z, w)
  real x, y, z, w;
#endif
{
  mova3c(x, y, z, w);
  drwa3c(x, y, z, w);
  return;
}
