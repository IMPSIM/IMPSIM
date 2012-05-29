/* ------------------------------------------------------------------ */
/* drwa2c-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Draw a visible line segment from the current pen location to
|     absolute 2D coordinates (x2, y2).
|
|     Access:
|       (void) drwa2c(real x2, real y2);
|     real x2,i-The horizontal 2D coordinate of the end of the line.
|     real y2,i-The vertical   2D coordinate of the end of the line.
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
  void drwa2c(real x2, real y2)
#else
  void drwa2c(x2, y2)
  real x2, y2;
#endif
{
  real s0, t0, s1, t1, s2, t2, sf, tf;
  int iclip;
 
  if (l2pen) {
    x2tosc(x2pen, y2pen, &s0, &t0);
  } else {
    s0 = spen;
    t0 = tpen;
  }
  x2tosc(x2, y2, &sf, &tf);
  clipsc(s0, t0, sf, tf, &s1, &t1, &s2, &t2, &iclip);
  if (iclip == 4) {
    lspen = FALSE;
  } else {
    if(!(lsmode && lspen) || (iclip & 1))movasc(s1, t1);
    drwasc(s2, t2);
    if (iclip >= 2) lspen = FALSE;
  }
  x2pen = x2;
  y2pen = y2;
  l2pen = TRUE;
  l3pen = FALSE;
  return;
}
