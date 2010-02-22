/* ------------------------------------------------------------------ */
/* x3ndcc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Find the 3D to 2D transformataion matrix from the orientation
|     angles.
|
|     Access:
|       (void) x3ndcc(real scl32, real x20, real y20, real *theta,
|         real *phi, real x32[3][4])
|     real scl32,i-3D to 2D scale factor.
|     real x20,  i-Horizontal 2D coordinate of the 3D origin.
|     real y20,  i-Vertical   2D coordinate of the 3D origin.
|     real *theta,i/o-Angle of rotation about the vertical   3D axis.
|     real *phi,  i/o-Angle of rotation about the horizontal 2D axis.
|     real x32[3][4],o-3D to 2D transformation matrix.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       This is a service utility routine for the floating horizon
|     algorithm of srfacu.  It should not be called directly by the
|     applications program.
|       Note that x32[3][4] is stored in row-major (C) rather than
|     column-major (Fortran) order.
|       The display device must have been defined by a previous call to
|     devic.
|       The angle *theta is converted if needed to an equivalent angle
|     between 0.0 and 2.0*PI.  The angle *phi is modified if needed to
|     be bounded between 0.0 and PI/2.0.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void x3ndcc(real scl32, real x20, real y20, real *theta, real *phi,
    real x32[3][4])
#else
  void x3ndcc(scl32, x20, y20, theta, phi, x32)
  real scl32, x20, y20, *theta, *phi, x32[3][4];
#endif
{
# define TWOPI (2.0*PI)
  real cphi, sphi, ctheta, stheta;
 
  *phi = max(min(*phi, PI/2.0), 0.0);
  cphi = cos(*phi);
  sphi = sin(*phi);
  if (*theta >= TWOPI) *theta -= TWOPI;
  if (*theta <    0.0) *theta += TWOPI;
  ctheta = cos(*theta);
  stheta = sin(*theta);
  x32[0][0] =       scl32        *  stheta;
  x32[0][1] =       scl32        *  ctheta;
  x32[0][2] =               0.0;
  x32[0][3] = x20 - scl32        * (stheta + ctheta) / 2.0;
  x32[1][0] =     - scl32 * sphi *  ctheta;
  x32[1][1] =       scl32 * sphi *  stheta;
  x32[1][2] =       scl32 * cphi;
  x32[1][3] = y20 - scl32 * sphi * (stheta - ctheta) / 2.0;
  x32[2][0] =       scl32 * cphi *  ctheta;
  x32[2][1] =     - scl32 * cphi *  stheta;
  x32[2][2] =       scl32 * sphi;
  x32[2][3] =     - scl32 * cphi * (stheta - ctheta) / 2.0;
  return;
# undef TWOPI
}
