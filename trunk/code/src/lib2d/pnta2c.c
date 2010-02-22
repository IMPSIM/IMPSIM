/* ------------------------------------------------------------------ */
/* pnta2c-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Place a visible point at given 2D coordinates (x2, y2).
|
|     Access:
|       (void) pnta2c(real x2, real y2);
|     real x2,i-The desired horizontal 2D coordinate of the point.
|     real y2,i-The desired vertical   2D coordinate of the point.
|
|     Error Conditions:
|       If coordinates outside the current screen window are specified,
|     the point will not appear.
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
  void pnta2c(real x2, real y2)
#else
  void pnta2c(x2, y2)
  real x2, y2;
#endif
{
  mova2c(x2, y2);
  drwa2c(x2, y2);
  return;
}
