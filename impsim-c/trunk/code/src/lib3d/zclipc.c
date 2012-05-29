/* ------------------------------------------------------------------ */
/* zclipc-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Set the 2D z-clipping boundaries for visibility of transformed
|     3D graphics.
|
|     Access:
|       (void) zclipc(real z2mn, real z2mx)
|     real z2mn,i-Minimum desired visible z (perpendicular to screen).
|     real z2mx,i-Maximum desired visible z (perpendicular to screen).
|
|     Error Conditions:
|       If z2mn or z2mx or both are larger than the current distance
|     from the screen to the viewer's eye, this is not an error, but
|     points behind the viewer's eye will not be visible since clipping
|     is also performed with a plane at the viewer's eye.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       The z2mn and z2mx values are measured in 2D units along a line
|     perpendicular to the screen with positive values measured toward
|     the viewer's eye and negative values behind the screen.
|       If zclipc() is not called, the values z2mn=-99999.0 and z2mx=
|     99999.0 are used for z-limits on visibility.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void zclipc(real z2mn, real z2mx)
#else
  void zclipc(z2mn, z2mx)
  real z2mn, z2mx;
#endif
{
  z2min = min(z2mn, z2mx);
  z2max = max(z2mn, z2mx);
  return;
}
