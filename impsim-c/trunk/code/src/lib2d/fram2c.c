/* ------------------------------------------------------------------ */
/* fram2c-01 Jan 00:07 Jul 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Set the 2D window boundaries and the 2D to screen transform-
|     ation parameters to fit the current screen window.
|
|     Access:
|       (void) fram2c(real x2mn, real y2mn, real x2mx, real y2mx);
|     real x2mn,i-Minimum allowable horizontal 2D coordinate value.
|     real y2mn,i-Minimum allowable vertical   2D coordinate value.
|     real x2mx,i-Maximum allowable horizontal 2D coordinate value.
|     real y2mx,i-Maximum allowable vertical   2D coordinate value.
|
|     Error Conditions:
|       If x2mx = x2mn and y2mx = y2mn, an error message is printed and
|     no further action is taken.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       First the horizontal and vertical 2D to screen scale factors
|     are set such that (x2mx - x2mn) scales to fit the current screen
|     width and (y2mx - y2mn) scales to fit the current screen height.
|       If x2mx = x2mn then the horizontal 2D to screen scale factor is
|     set from (y2mx - y2mn) to produce a rigid body transformation from
|     2D to screen.
|       If y2mx = y2mn then the vertical 2D to screen scale factor is
|     set from (x2mx - x2mn) to produce a rigid body transformation from
|     2D to screen.
|       Next the 2D to screen translation parameters are set such that
|     the midrange values (x2mx + x2mn)/2 and (y2mx + y2mn)/2 transform
|     to the center of the current screen window.
|       Finally, with the transformation parameters set, the 2D window
|     boundaries are reset to match the current screen boundaries.
|       The final 2D window boundaries may be found by calling qfrm2c().
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void fram2c(real x2mn, real y2mn, real x2mx, real y2mx)
#else
  void fram2c(x2mn, y2mn, x2mx, y2mx)
  real x2mn, y2mn, x2mx, y2mx;
#endif
{
  real ds, dt, dx2, dy2;
 
/* Check for a null 2D window. */
  if (( fabs(x2mx - x2mn) * x2scal < stzero)
    && (fabs(y2mx - y2mn) * y2scal < stzero)) {
    textc("Error: Null 2D window area.", TRUE);
 
/* Find 2D and screen heights and widths. */
  } else {
    ds = max(smax - smin, stzero);
    dt = max(tmax - tmin, stzero);
    x2max = max(x2mn, x2mx);
    x2min = min(x2mn, x2mx);
    y2max = max(y2mn, y2mx);
    y2min = min(y2mn, y2mx);
    dx2 = x2max - x2min;
    dy2 = y2max - y2min;
 
/* Check for and adjust a null 2D height or width. */
    if (fabs(dx2 * x2scal) < stzero) {
      dx2 = dy2 * ds / (aspect * dt);
    } else if (fabs(dy2 * y2scal) < stzero){
      dy2 = dx2 * aspect * dt / ds;
    }
 
/* Set the 2D to screen scale factors. */
    x2scal = ds / dx2;
    y2scal = dt / dy2;
 
/* Set the 2D to screen translation terms. */
    x20 = 0.5 * (smax + smin - (x2max + x2min) * x2scal);
    y20 = 0.5 * (tmax + tmin - (y2max + y2min) * y2scal);
 
/* Reset the 2D boundaries to fit the screen window. */
    x2max = (smax - x20) / x2scal;
    x2min = (smin - x20) / x2scal;
    y2max = (tmax - y20) / y2scal;
    y2min = (tmin - y20) / y2scal;
 
/* Lift the pen if outside of the window. */
    if (l2pen) lspen = (x2pen >= x2min) && (x2pen <= x2max)
                    && (y2pen >= y2min) && (y2pen <= y2max);
  }
  l2pen = FALSE;
  l3pen = FALSE;
  return;
}
