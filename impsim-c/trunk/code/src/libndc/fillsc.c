/* ------------------------------------------------------------------ */
/* fillsc-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Fill a polygon defined by NDC coordinates.
|
|     Access:
|       (void) fillsc(int n, real s[], real t[]);
|     int n,i-Number of vertices in the polygon.
|     real s[],i-Horizontal NDC coordinates of polygon vertices.
|     real t[],i-Vertical   NDC coordinates of polygon vertices.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       fillsc() assumes that all incoming vertices are ordered either
|     clockwise or counter-clockwise.  It automatically closes the poly-
|     gon before filling.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void fillsc(int n, real s[], real t[])
#else
  void fillsc(n, s, t)
  int  n;
  real s[], t[];
#endif
{
# include "..\libcad\devic.h"
# include "..\libcad\screnc.h"
# ifdef __WATCOMC__
#   include <graph.h>
    struct _wxycoord pts[MXPOLY];
# else
#   include "xglblc.h"
    XPoint pts[MXPOLY];
# endif
  int j, npts;
 
  if (dspdvc == DT_GRAPHIC) {
    npts = min(n, MXPOLY);
#   ifdef __WATCOMC__
      for (j=0; j<npts; j++) {
        pts[j].wx = s[j];
        pts[j].wy = t[j];
      }
      _polygon_wxy(_GFILLINTERIOR, npts, &pts);
#   else
      for (j=0; j<npts; j++) {
        AbstoPix(pts[j].x, pts[j].y, s[j], t[j]);
      }
      XFillPolygon(dsp, pixmap, fill_gc, pts, npts, Nonconvex,
        CoordModeOrigin);
      pix_drwn = TRUE;
#   endif
    lspen = TRUE;
    l2pen = FALSE;
    l3pen = FALSE;
    spen = max(min(s[0], smax), smin);
    tpen = max(min(t[0], tmax), tmin);
  }
  return;
}
