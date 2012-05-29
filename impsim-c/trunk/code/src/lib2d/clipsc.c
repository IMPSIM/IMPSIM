/* ------------------------------------------------------------------ */
/* clipsc-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Clip a screen coordinate straight line segment to fit within the
|     screen boundaries.
|
|     Access:
|       (void) clipsc(real s0, real t0, real sf, real tf, real *s1,
|         real *t1, real *s2, real *t2, int *iclip);
|     real  s0,i-The horizontal screen coordinate of the beginning of
|       the original line segment.
|     real  t0,i-The vertical   screen coordinate of the beginning of
|       the original line segment.
|     real  sf,i-The horizontal screen coordinate of the final point of
|       the original line segment.
|     real  tf,i-The vertical   screen coordinate of the final point of
|       the original line segment.
|     real *s1,o-The horizontal screen coordinate of the beginning of
|       the clipped line segment.
|     real *t1,o-The vertical   screen coordinate of the beginning of
|       the clipped line segment.
|     real *s2,o-The horizontal screen coordinate of the end point of
|       the clipped line segment.
|     real *t2,o-The vertical   screen coordinate of the end point of
|       the clipped line segment.
|     int *iclip,o-A flag indicating the extent of clipping:
|       iclip = 0 for no clipping,
|       iclip = 1 for clipping of (s0, t0),
|       iclip = 2 for clipping of (sf, tf),
|       iclip = 3 for clipping of both points,
|       iclip = 4 if the entire line segment is outside of the window.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       This routine is not intended for use by the applications pro-
|     grammer; it is a service routine for use in subprograms within the
|     graphics library.
|       The display device must have been defined by a previous call to
|     devic().
|       The graphic screen window boundaries may be changed at will by
|     calling framsc().
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void clipsc(real s0, real t0, real sf, real tf, real *s1, real *t1,
    real *s2, real *t2, int *iclip)
#else
  void clipsc(s0, t0, sf, tf, s1, t1, s2, t2, iclip)
  real s0, t0, sf, tf, *s1, *t1, *s2, *t2;
  int *iclip;
#endif
{
  real s, t;
 
  *s1 = s0;
  *t1 = t0;
  *s2 = sf;
  *t2 = tf;
  *iclip = 0;
  do {
    if (*s1 < smin) {
      if (*s2 < smin) {
        *iclip = 4;
        return;
      }
      s = smin;
    } else {
      if (*s1 <= smax) break;
      if (*s2 > smax) {
        *iclip = 4;
        return;
      }
      s = smax;
    }
    *t1 += (s - *s1) * (*t2 - *t1) / (*s2 - *s1);
    *s1  = s;
    *iclip = 1;
  } while (FALSE);
  do {
    if (*s2 < smin) {
      s = smin;
    } else {
      if (*s2 <= smax) break;
      s = smax;
    }
    *t2 = (s - *s1) * (*t2 - *t1) / (*s2 - *s1) + *t1;
    *s2 = s;
    *iclip |= 2;
  } while (FALSE);
  do {
    if (*t1 < tmin) {
      if (*t2 < tmin) {
        *iclip = 4;
        return;
      }
      t = tmin;
    } else {
      if (*t1 <= tmax) break;
      if (*t2 > tmax) {
        *iclip = 4;
        return;
      }
      t=tmax;
    }
    *s1 += (t - *t1) * (*s2 - *s1) / (*t2 - *t1);
    *t1  = t;
    *iclip |= 1;
  } while (FALSE);
  if (*t2 < tmin) {
    t = tmin;
  } else {
    if (*t2 <= tmax) return;
    t = tmax;
  }
  *s2 = (t - *t1) * (*s2 - *s1) / (*t2 - *t1) + *s1;
  *t2 = t;
  *iclip |= 2;
  return;
}
