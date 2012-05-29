/* ------------------------------------------------------------------ */
/* drwasc-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Draw a visible line from the current pen location to coordinates
|     (s,t) on the graphic display screen.
|
|     Access:
|       (void) drwasc(real s, real t);
|     real s,i-Horizontal coordinate of the line termination point in
|       screen units from the left screen edge.
|     real t,i-Vertical   coordinate of the line termination point in
|       screen units from the bottom of the screen.
|
|     Error Conditions:
|       If coordinates outside of the screen window boundaries are spec-
|     ified, they are brought within the screen window by use of the
|     min and max functions.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       A dash pattern for the line may be defined by a preceeding call
|     to dashc().  If not, a solid line will be drawn.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void drwasc(real s, real t)
#else
  void drwasc(s, t)
  real s, t;
#endif
{
  static real sdash = 0.0, tdash = 0.0;
  real diag, dist, dx, dy, part, x, y;
 
/* Draw the line. */
  if (dspdvc == DT_GRAPHIC) {
 
/* Move to the start of line if necessary. */
    if (!(lsmode && lspen)) movasc(spen, tpen);
 
/* Generate any required software dash pattern. */
    if (idash > 9) {
      if (ndash < 1) {
        lspen = FALSE;
        ndash = 1 - ndash;
      } else if (ndash > 1) {
        if ((sdash != spen) || (tdash != tpen)) {
          ldash  = -1;
          dshseg = 0.0;
        }
        x  = spen;
        y  = tpen;
        dx = s - spen;
        dy = t - tpen;
        diag = sqrt(dx * dx + dy * dy);
        dist = diag;
_2:     if (dshseg <= stzero){
          ldash  = (ldash + 1) % ndash;
          dshseg = fabs(dshtbl[ldash]);
        }
        if (dshseg < dist){
          part = dshseg / diag;
          x += dx * part;
          y += dy * part;
 
/* Draw the dash or space. */
          if (dshtbl[ldash] <= 0.0) lspen = FALSE;
          wrpenc(x, y);
          dist  -= dshseg;
          ldash  = (ldash + 1) % ndash;
          dshseg = fabs(dshtbl[ldash]);
          goto _2;
        }
        if (dshtbl[ldash] <= 0.0) lspen = FALSE;
        dshseg -= dist;
        sdash  = s;
        tdash  = t;
      }
    }
 
/* Draw the final line. */
    wrpenc(s, t);
  }
  return;
}
