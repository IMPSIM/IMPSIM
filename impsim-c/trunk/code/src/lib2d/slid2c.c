/* ------------------------------------------------------------------ */
/* slid2c-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Translate the 2D coordinate system by (dx2, dy2) 2D units rela-
|     tive to the screen.
|
|     Access:
|       (void) slid2c(real dx2, real dy2);
|     real dx2,i-The relative 2D horizontal distance to slide through.
|     real dy2,i-The relative 2D vertical   distance to slide through.
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
  void slid2c(real dx2, real dy2)
#else
  void slid2c(dx2, dy2)
  real dx2, dy2;
#endif
{
  x20 += dx2 * x2scal;
  y20 += dy2 * y2scal;
  xsto2c(smin, tmin, &x2min, &y2min);
  xsto2c(smax, tmax, &x2max, &y2max);
  if (l2pen) lspen = (x2pen >= x2min) && (x2pen <= x2max)
                  && (y2pen >= y2min) && (y2pen <= y2max);
  l2pen = FALSE;
  l3pen = FALSE;
  return;
}
