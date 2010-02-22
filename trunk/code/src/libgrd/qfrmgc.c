/* ------------------------------------------------------------------ */
/* qfrmgc-01 Jan 00:23 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Return to the calling program the current boundaries of the
|     graph window of the graphic display device.
|
|     Access:
|       (void) qfrmgc(real *sgmn, real *tgmn, real *sgmx, real *tgmx);
|     real *smn,o-Horizontal screen coordinate of the left   edge of the
|       graph window.
|     real *tmn,o-Vertical   screen coordinate of the bottom edge of the
|       graph window.
|     real *smx,o-Horizontal screen coordinate of the right  edge of the
|       graph window.
|     real *tmx,o-Vertical   screen coordinate of the top    edge of the
|       graph window.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       The graph window boundaries may be changed at will by calling
|     framgc().
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void qfrmgc(real *sgmn, real *tgmn, real *sgmx, real *tgmx)
#else
  void qfrmgc(sgmn, tgmn, sgmx, tgmx)
  real *sgmn, *tgmn, *sgmx, *tgmx;
#endif
{
  *sgmn = sgmin;
  *tgmn = tgmin;
  *sgmx = sgmax;
  *tgmx = tgmax;
  return;
}
