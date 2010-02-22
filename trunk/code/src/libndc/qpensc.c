/* ------------------------------------------------------------------ */
/* qpensc-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Return the current screen coordinates of the graphic pen.
|
|     Access:
|       (void) qpensc(real *s, real *t, int *lpen);
|     real *s,o-Horizontal coordinate of the pen measured in screen
|       units from the left edge of the graphic display screen.
|     real *t,o-Vertical   coordinate of the pen measured in screen
|       units from the bottom edge of the graphic display screen.
|     int *lpen,o-Flag set to TRUE when graphic pen is down.
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
  void qpensc(real *s, real *t, int *lpen)
#else
  void qpensc(s, t, lpen)
  real *s, *t;
  int  *lpen;
#endif
{
  *s    = spen;
  *t    = tpen;
  *lpen = lspen;
  return;
}
