/* ------------------------------------------------------------------ */
/* qsclsc-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Return the horizontal and vertical scale factors for the current
|     graphic display device.
|
|     Access:
|       (void) qsclsc(real *sscal, real *tscal);
|     real *sscal,o-Current horizontal scale factor (pixels per screen).
|     real *tscal,o-Current vertical   scale factor (pixels per screen).
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void qsclsc(real *sscal, real *tscal)
#else
  void qsclsc(sscal, tscal)
  real *sscal, *tscal;
#endif
{
  *sscal = sscale;
  *tscal = tscale;
  return;
}
