/* ------------------------------------------------------------------ */
/* drwa3c-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Draw a visible line segment from the current pen location to
|     absolute 3D coordinates (x, y, z, w).
|
|     Access:
|       drwa3c(x, y, z, w);
|     real x,i-The 3D x-coordinate of the end point of the line.
|     real y,i-The 3D y-coordinate of the end point of the line.
|     real z,i-The 3D z-coordinate of the end point of the line.
|     real w,i-The 3D homogeneous coordinate of the end point of the
|       line.
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
  void drwa3c(real x, real y, real z, real w)
#else
  void drwa3c(x, y, z, w)
  real x, y, z, w;
#endif
{
  int  iclip;
  real z2pen, w2pen, w2, x2, y2, z2, x21, y21, z21, x22, y22, z22, s1,
    t1, s2, t2;
 
  if (l3pen) {
    x3to2c(x3pen, y3pen, z3pen, w3pen, &x2pen, &y2pen, &z2pen, &w2pen);
  } else {
    if (! l2pen) {
      xsto2c(spen, tpen, &x2pen, &y2pen);
      l2pen = TRUE;
    }
    z2pen = 0.0;
    w2pen = 1.0;
  }
  x3to2c(x, y, z, w, &x2, &y2, &z2, &w2);
  iclip = clip2c(x2pen, y2pen, z2pen, w2pen, x2, y2, z2, w2, &x21, &y21,
    &z21, &x22, &y22, &z22);
  if (iclip == 4) {
    lspen = FALSE;
  } else {
    if (!(lsmode && lspen) || (iclip & 1)) {
      x2tosc(x21, y21, &s1, &t1);
      movasc(s1, t1);
    }
    x2tosc(x22, y22, &s2, &t2);
    drwasc(s2, t2);
    if (iclip >= 2) lspen = FALSE;
  }
  x2pen = x22;
  y2pen = y22;
  l2pen = TRUE;
  x3pen = x;
  y3pen = y;
  z3pen = z;
  w3pen = w;
  l3pen = TRUE;
  return;
}
