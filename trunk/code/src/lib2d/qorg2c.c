/* ------------------------------------------------------------------ */
/* qorg2c-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Return the screen coordinates of the origin of the 2D coordinate
|     system.
|
|     Access:
|       (void) qorg2c(real *s0, real *t0);
|     real *s0,o-The horizontal screen coordinate of the 2D origin.
|     real *t0,o-The vertical   screen coordinate of the 2D origin.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       Realignment of the 2D coordinate system relative to the screen
|     may take place by calls fram2c() and/or slid2c().
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void qorg2c(real *s0, real *t0)
#else
  void qorg2c(s0, t0)
  real *s0, *t0;
#endif
{
  *s0 = x20;
  *t0 = y20;
  return;
}
