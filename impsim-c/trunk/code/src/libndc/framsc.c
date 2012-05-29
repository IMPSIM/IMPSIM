/* ------------------------------------------------------------------ */
/* framsc-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Set the graphic display device screen window boundaries for sub-
|     sequent graphic mode commands.
|
|     Access:
|       (void) framsc(real s1, real t1, real s2, real t2);
|     real s1,i-Minimum allowable horizontal screen coordinate value.
|     real t1,i-Minimum allowable vertical   screen coordinate value.
|     real s2,i-Maximum allowable horizontal screen coordinate value.
|     real t2,i-Maximum allowable vertical   screen coordinate value.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       For equal min and max boundary values in either direction, the
|     max boundary value is increased by one pixel.
|       The graphic screen window boundaries may be changed at will by
|     calling framsc().  Before the first call, the screen window bound-
|     aries are coincident with the edges of the graphic display screen.
|       All of the calling parameters must have values between 0.0 and
|     1.0.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void framsc(real s1, real t1, real s2, real t2)
#else
  void framsc(s1, t1, s2, t2)
  real s1, t1, s2, t2;
#endif
{
/* Set the screen window within hardware limits. */
  smin = min( max(0.0, min(s1, s2)), 1.0);
  tmin = min( max(0.0, min(t1, t2)), 1.0);
  smax = max( min(1.0, max(s1, s2)), 0.0);
  tmax = max( min(1.0, max(t1, t2)), 0.0);
  if (smax <= smin) smax = smin + stzero;
  if (tmax <= tmin) tmax = tmin + stzero;
 
/* Reset the 2-D window to match. */
  x2min = (smin - x20) / x2scal;
  y2min = (tmin - y20) / y2scal;
  x2max = (smax - x20) / x2scal;
  y2max = (tmax - y20) / y2scal;
 
/* Raise the graphic pen if outside of the new window. */
  lspen = (spen >= smin) && (spen <= smax) && (tpen >= tmin)
    && (tpen <= tmax);
  return;
}
