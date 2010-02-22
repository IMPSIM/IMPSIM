/* ------------------------------------------------------------------ */
/* pntrsc-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Plot a visible point at (ds,dt) relative screen coordinates from
|     the current pen location on the screen of the graphic display
|     device.
|
|     Access:
|       (void) pntrsc(real ds, real dt);
|     real ds,i-Desired horizontal coordinate of the point, measured in
|       screen units to the right of the current pen location.
|     real dt,i-Desired vertical   coordinate of the point, measured in
|       screen units upward from the current pen location.
|
|     Error Conditions:
|       If absolute coordinates outside of the screen window boundaries
|     occur, they are brought within the screen window by use of the min
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
  void pntrsc(real ds, real dt)
#else
  void pntrsc(ds, dt)
  real ds, dt;
#endif
{
  real s, t;
 
  s = spen + ds;
  t = tpen + dt;
  pntasc(s, t);
  return;
}
