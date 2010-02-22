/* ------------------------------------------------------------------ */
/* wrpenc-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Generate output for absolute screen coordinates (s,t) with the
|     the pen either up or down according to the value of lspen.
|
|     Access:
|       (void) wrpenc(ral s, real t);
|     real s,i-Horizontal NDC coordinate of the line termination point.
|     real t,i-Vertical   NDC coordinate of the line termination point.
|
|     Error Conditions:
|       If coordinates outside of the screen window boundaries are spec-
|     ified, they are brought within the screen window by use of the
|     min and max functions.
|
|     Comments:
|       This routine is not intended for use by the applications
|     programmer; it is a service routine for use in subprograms within
|     the libcad library.
|       The display device must have been defined by a previous call to
|     devic().
|       If lspen = FALSE on entry into wrpenc, an invisible line will be
|     drawn; otherwise, a solid visible line will be drawn.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void wrpenc(real s, real t)
#else
  void wrpenc(s, t)
  real s, t;
#endif
{
# ifdef __WATCOMC__
#   include <graph.h>
# else
#   include "xglblc.h"
    int x1, y1, x2, y2;
# endif
  real ss, tt;
 
/* Bound the s,t values to the nearest on-screen position. */
  ss = max( min( s, smax), smin);
  tt = max( min( t, tmax), tmin);
 
/* Draw the line. */
  if (dspdvc == DT_GRAPHIC) {
    if (lsmode && lspen) {
#     ifdef __WATCOMC__
        _moveto_w(spen,tpen);
        _lineto_w(ss,tt);
#     else
        AbstoPix(x1, y1, spen, tpen);
        AbstoPix(x2, y2, ss, tt);
        if ((x1 == x2) && (y1 == y2)) {
          XDrawPoint(dsp, pixmap, line_gc, x1, y1);
        } else {
          XDrawLine(dsp, pixmap, line_gc, x1, y1, x2, y2);
        }
        pix_drwn = TRUE;
#     endif
    }
  }
 
/* Reset the variables in common storage. */
  lsmode= TRUE;
  lspen = TRUE;
  l2pen = FALSE;
  l3pen = FALSE;
  spen  = ss;
  tpen  = tt;
  return;
}
