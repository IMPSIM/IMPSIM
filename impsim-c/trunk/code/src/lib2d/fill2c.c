/* ------------------------------------------------------------------ */
/* fill2c-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       A polygon filling routine for 2D level graphics.
|
|     Access:
|       (void) fill2c(int n, real x2[], real y2[]);
|     int  n,   i-Number of vertices in the polygon.
|     real x2[],i-Horizontal 2D coordinates of polygon vertices.
|     real y2[],i-Vertical   2D coordinates of polygon vertices.
|
|     Error Conditions:
|       If coordinates outside of the current screen window boundaries
|     are specified, they are clipped to fit the screen window.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       fillsc() assumes that all incoming vertices are ordered either
|     clockwise or counter-clockwise.  It automatically closes the
|     polygon before filling.
|       It is assumed that the polygon to be filled contains up to 
|     MXPOLY = 72 vertices.  If more than MXPOLY vertices are entered,
|     the first MXPOLY vertices are used as the polygon.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void fill2c(int n, real x2[], real y2[])
#else
  void fill2c(n, x2, y2)
  int  n;
  real x2[], y2[];
#endif
{
  int  i, iclip, index;
  real s[MXPOLY], t[MXPOLY], slast, tlast, snext, tnext, s1, t1, s2, t2;
 
/* Transform and clip 2D coordinates to fit the screen window. */
  index = 1;
  x2tosc(x2[0], y2[0], &slast, &tlast);
  if ((slast >= smin) && (slast <= smax) && (tlast >= tmin) &&
    (tlast <= tmax)) {
    index = 1;
    s[0] = slast;
    t[0] = tlast;
  }
  for (i=1; i < n; i++) {
    x2tosc(x2[i], y2[i], &snext, &tnext);
    clipsc(slast, tlast, snext, tnext, &s1, &t1, &s2, &t2, &iclip);
    if (iclip != 4) {
      if (iclip & 1) {
        if (index >= MXPOLY) break;
        s[index] = s1;
        t[index] = t1;
        index++;
      }
      if (index >= MXPOLY) break;
      s[index] = s2;
      t[index] = t2;
      index++;
    }
    slast = snext;
    tlast = tnext;
  }
  fillsc(index, s, t);
  return;
}
