/* ------------------------------------------------------------------ */
/* qscl2c-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Return the current 2D to screen scale factors.
|
|     Access:
|       (void) qscl2c(real *x2scl, real *y2scl);
|     real *x2scl,o-The current horizontal 2D to screen scale factor.
|     real *y2scl,o-The current vertical   2D to screen scale factor.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       The 2D to screen scale factors can be changed at will by calling
|     scal2c().
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void qscl2c(real *x2scl, real *y2scl)
#else
  void qscl2c(x2scl, y2scl)
  real *x2scl, *y2scl;
#endif
{
  *x2scl = 1.0 / x2scal;
  *y2scl = 1.0 / y2scal;
  return;
}
