/* ------------------------------------------------------------------ */
/* qfrmsc-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Return to the calling program the current boundaries of the
|     screen window of the graphic display device.
|
|     Access:
|       (void) qfrmsc(real *smn, real *tmn, real *smx, real *tmx);
|     real *smn,o-Horizontal screen coordinate of the left   edge of the
|       screen window.
|     real *tmn,o-Vertical   screen coordinate of the bottom edge of the
|       screen window.
|     real *smx,o-Horizontal screen coordinate of the right  edge of the
|       screen window.
|     real *tmx,o-Vertical   screen coordinate of the top    edge of the
|       screen window.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       The screen window boundaries may be changed at will by calling
|     framsc().
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void qfrmsc(real *smn, real *tmn, real *smx, real *tmx)
#else
  void qfrmsc(smn, tmn, smx, tmx)
  real *smn, *tmn, *smx, *tmx;
#endif
{
  *smn = smin;
  *tmn = tmin;
  *smx = smax;
  *tmx = tmax;
  return;
}
