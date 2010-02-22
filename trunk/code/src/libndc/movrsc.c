/* ------------------------------------------------------------------ */
/* movrsc-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Move the graphic pen through (ds,dt) relative screen units
|     starting from the current pen location on the screen of the
|     graphic display device.
|
|     Access:
|       (void) movrsc(real ds, real dt)
|     real ds,i-Desired horizontal pen movement to the right, in screen
|       units from the current pen location.
|     real dt,i-Desired vertical pen movement upward, in screen units
|       from the current pen location.
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
  void movrsc(real ds, real dt)
#else
  void movrsc(ds, dt)
  real ds, dt;
#endif
{
  real s, t;
 
  s = spen + ds;
  t = tpen + dt;
  movasc(s, t);
  return;
}
