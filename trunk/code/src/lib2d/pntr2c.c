/* ------------------------------------------------------------------ */
/* pntr2c-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Place a visible point at (dx2, dy2) relative 2D coordinates from
|     the current pen location.
|
|     Access:
|       (void) pntr2c(real dx2, real dy2);
|     real dx2,i-The relative 2D horizontal distance from the pen to the
|       point.
|     real dy2,i-The relative 2D vertical   distance from the pen to the
|       point.
|
|     Error Conditions:
|       If the values specified produce a point location outside of the
|     current screen window, the point will not appear.
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
  void pntr2c(real dx2, real dy2)
#else
  void pntr2c(dx2, dy2)
  real dx2, dy2;
#endif
{
  movr2c(dx2, dy2);
  drwr2c(0.0, 0.0);
  return;
}
