/* ------------------------------------------------------------------ */
/* pntasc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Place a visible point at screen coordinates (s,t) on the graphic
|     display device.
|
|     Access:
|       (void) pntasc(real s, real t);
|     real s,i-Desired horizontal coordinate of the point in screen
|       units to the right of the graphic display screen left edge.
|     real t,i-Desired vertical   coordinate of the point in screen
|       units up from the bottom of the graphic display screen.
|
|     Error Conditions:
|       If coordinates outside of the screen window boundaries are spec-
|     ified, they are brought within the screen window by use of the
|     min and max functions.
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
  void pntasc(real s, real t)
#else
  void pntasc(s, t)
  real s, t;
#endif
{
  movasc(s, t);
  drwasc(s, t);
  return;
}
