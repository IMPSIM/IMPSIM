/* ------------------------------------------------------------------ */
/* movasc-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Move the pen to absolute screen coordinates (s,t) on the screen
|     of the graphic display device.
|
|     Access:
|       (void) movasc(real s, real t);
|     real s,i-Desired horizontal coordinate in screen units from the
|       left screen edge.
|     real t,i-Desired vertical   coordinate in screen units from the
|       bottom of the screen.
|
|     Error Conditions:
|       If coordinates outside of the screen window boundaries are spec-
|     ified, they are brought within the screen window by use of the min
|     and max functions.
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
  void movasc(real s, real t)
#else
  void movasc(s, t)
  real s, t;
#endif
{
  lspen = FALSE;
  wrpenc(s, t);
  return;
}
