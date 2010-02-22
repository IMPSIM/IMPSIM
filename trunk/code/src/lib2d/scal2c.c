/* ------------------------------------------------------------------ */
/* scal2c-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Magnify the current 2D to screen scale by the given factors,
|     holding the center of the current view stationary.
|
|     Access:
|       (void) scal2c(real x2scl, real y2scl);
|     real x2scl,i-The desired horizontal magnification factor.
|     real y2scl,i-The desired vertical   magnification factor.
|
|     Error Conditions:
|       If both x2scl and y2scl are zero, then an error message is given
|     and no further action is taken.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       If x2scl = 0 then the horizontal 2D to screen scale factor is
|     set from y2scl to produce a rigid body transformation from 2D to
|     screen.
|       If y2scl = 0 then the vertical 2D to screen scale factor is set
|     from x2scl to produce a rigid body transformationfrom 2D to
|     screen.
|       Next the 2D to screen translation parameters are set such that
|     the midrange values (x2mx + x2mn) / 2 and (y2mx + y2mn) / 2 trans-
|     form to the center of the current screen window.
|       Finally, with the transformation parameters set, the 2D window
|     boundaries are reset to match the current screen boundaries.
|       The current 2D to screen scale factors can be obtained at will
|     by use of qscl2c().
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void scal2c(real x2scl, real y2scl)
#else
  void scal2c(x2scl, y2scl)
  real x2scl, y2scl;
#endif
{
  if ((x2scl == 0.0) && (y2scl == 0.0)) {
    textc("Error: Null 2D scale factors ignored.", TRUE);
  } else {
    x2scal = x2scl * x2scal;
    y2scal = y2scl * y2scal;
    if (x2scal == 0.0) x2scal = y2scal * aspect;
    if (y2scal == 0.0) y2scal = x2scal / aspect;
    x20 = 0.5 * ((x2max + x2min) * x2scal - smax - smin);
    y20 = 0.5 * ((y2max + y2min) * y2scal - tmax - tmin);
    xsto2c(smin, tmin, &x2min, &y2min);
    xsto2c(smax, tmax, &x2max, &y2max);
    if (l2pen) lspen = (x2pen >= x2min) && (x2pen <= x2max)
                    && (y2pen >= y2min) && (y2pen <= y2max);
    l2pen = FALSE;
    l3pen = FALSE;
  }
  return;
}
