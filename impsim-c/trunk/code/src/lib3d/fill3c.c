/* ------------------------------------------------------------------ */
/* fill3c-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       A polygon filling routine for 3D level graphics.
|
|     Access:
|       (void) fill3c(real xpnt[], real ypnt[], real zpnt[],
|         real wpnt[], int n)
|     real xpnt[n],i-The 3D x-coordinates of polygon vertices.
|     real ypnt[n],i-The 3D y-coordinates of polygon vertices.
|     real zpnt[n],i-The 3D z-coordinates of polygon vertices.
|     real wpnt[n],i-The 3D w-coordinates of polygon vertices.
|     int  n,      i-Number of vertices in the polygon.
|
|     Error Conditions:
|       It is assumed that the polygon to be filled contains less than
|     MXPOLY=72 vertices.  If more than MXPOLY vertices are entered, the
|     first MXPOLY vertices are used as the polygon.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       fill3c() assumes that all incoming vertices are ordered either
|     clockwise or counter-clockwise.  It automatically closes the poly-
|     gon before filling.
|       If coordinates outside of the current 2D window boundaries are
|     specified, they are clipped to fit the 2D window.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void fill3c(real xpnt[], real ypnt[], real zpnt[], real wpnt[], int n)
#else
  void fill3c(xpnt, ypnt, zpnt, wpnt, n)
  real xpnt[], ypnt[], zpnt[], wpnt[];
  int  n;
#endif
{
  int  i, iclip, index;
  real s[MXPOLY], t[MXPOLY], xlast, ylast, zlast, wlast, x2, y2, z2, w2,
    x21, y21, z21, x22, y22, z22;
 
/* Transform and clip 2D coordinates to fit the 2D window. */
  x3to2c(xpnt[0], ypnt[0], zpnt[0], wpnt[0], &xlast, &ylast, &zlast,
    &wlast);
  iclip = clip2c(xlast, ylast, zlast, wlast, xlast, ylast, zlast, wlast,
    &x21, &y21, &z21, &x22, &y22, &z22);
  index = 0;
  if (!(iclip & 2)) {
    s[0] = x22 * x2scal + x20;
    t[0] = y22 * y2scal + y20;
    index = 1;
  }
  for (i=2; i<=n; i++) {
    x3to2c(xpnt[i-1], ypnt[i-1], zpnt[i-1], wpnt[i-1], &x2, &y2, &z2,
      &w2);
    iclip = clip2c(xlast, ylast, zlast, wlast, x2, y2, z2, w2, &x21,
      &y21, &z21, &x22, &y22, &z22);
    if (iclip != 4) {
      if (iclip & 1) {
        if (index >= MXPOLY) goto _3;
        s[index] = x21 * x2scal + x20;
        t[index] = y21 * y2scal + y20;
        index++;
      }
      if (index >= MXPOLY) goto _3;
      s[index] = x22 * x2scal + x20;
      t[index] = y22 * y2scal + y20;
      index++;
    }
    xlast = x2;
    ylast = y2;
    zlast = z2;
    wlast = w2;
  }
_3:
  fillsc(index, s, t);
  return;
}
