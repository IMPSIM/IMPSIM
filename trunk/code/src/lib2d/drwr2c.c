/* ------------------------------------------------------------------ */
/* drwr2c-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Draw a visible line segment through (dx2, dy2) relative 2D
|     coordinates from the current pen location.
|
|     Access:
|       (void) drwr2c(real dx2, real dy2)
|     real dx2,i-The horizontal relative 2D coordinate to draw through.
|     real dy2,i-The vertical   relative 2D coordinate to draw through.
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
  void drwr2c(real dx2, real dy2)
#else
  void drwr2c(dx2, dy2)
  real dx2, dy2;
#endif
{
  real x2, y2;
 
  if (! l2pen) {
    xsto2c(spen, tpen, &x2pen, &y2pen);
    l2pen = TRUE;
  }
  x2 = x2pen + dx2;
  y2 = y2pen + dy2;
  drwa2c(x2, y2);
  return;
}
