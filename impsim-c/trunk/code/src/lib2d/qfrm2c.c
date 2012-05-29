/* ------------------------------------------------------------------ */
/* qfrm2c-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Return the current 2D window boundaries to the user.
|
|     Access:
|       (void) qfrm2c(real *x2mn, real *y2mn, real *x2mx, real *y2mx);
|     real *x2mn,o-The minimum 2D horizontal coordinate allowed.
|     real *y2mn,o-The minimum 2D vertical   coordinate allowed.
|     real *x2mx,o-The maximum 2D horizontal coordinate allowed.
|     real *y2mx,o-The maximum 2D vertical   coordinate allowed.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       The screen window boundaries may be changed at will by calling
|     fram2c().
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void qfrm2c(real *x2mn, real *y2mn, real *x2mx, real *y2mx)
#else
  void qfrm2c(x2mn, y2mn, x2mx, y2mx)
  real *x2mn, *y2mn, *x2mx, *y2mx;
#endif
{
  *x2mn = x2min;
  *y2mn = y2min;
  *x2mx = x2max;
  *y2mx = y2max;
  return;
}
