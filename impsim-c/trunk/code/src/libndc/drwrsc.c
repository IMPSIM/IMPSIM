/* ------------------------------------------------------------------ */
/* drwrsc-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Draw a visible line through (ds,dt) relative screen units start-
|     ing from the current pen location on the display screen.
|
|     Access:
|       (void) drwrsc(real ds, real dt);
|     real ds,i-Horizontal projection of the line in screen units to the
|       right, starting from the current pen location.
|     real dt,i-Vertical projection of the line in screen units upward,
|       starting from the current pen location.
|
|     Error Conditions:
|       If absolute coordinates outside of the screen window boundaries
|     occur, they are brought within the screen window by use of the min
|     and max functions.
|       A dash pattern for the line may be defined by a preceeding call
|     to dashc().  If not, a solid line will be drawn.
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
  void drwrsc(real ds, real dt)
#else
  void drwrsc(ds, dt)
  real ds, dt;
#endif
{
  real s, t;
 
  s = spen + ds;
  t = tpen + dt;
  drwasc(s, t);
  return;
}
