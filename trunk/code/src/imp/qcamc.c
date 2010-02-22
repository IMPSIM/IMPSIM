/* ------------------------------------------------------------------ */
/* cpypbl-01 Jan 84:11 Jul 09                                          |
|     (C) Copyright, JJU Research, 1984-2009.                          |
|                                                                      |
|     This material is released under the terms of the                 |
|     GNU General Public License, version 3 (GNU GPLv3).               |
|     The full text of that license is available from the 'IMPSim'     |
|     project site on Google Code.                                     |
|                                                                      |
|     This initial release of 'IMPSim' is equivalent to the            |
|     IMP Integrated Mechanisms Program (IMP-2009) and is released     |
|     with the full approval of JJU Research of Madison, WI.           |
|                                                                      |
* ------------------------------------------------------------------- */
/* ------------------------------------------------------------------ */
/* qcamc-01 Jan 00:29 Jun 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Form the derivative operator for a cam joint.
|
|     Access:
|       (void) qcamc(int njvar, real phi[3], real u, real v, real du,
|         real dv, ddu, ddv, real Q[6]);
|     int  njvar, i-Number of the variable within the joint.
|     real phi[3],i-Values of the joint variables of the joint.
|     real u,     i-Value of the cam u profile function.
|     real v,     i-Value of the cam v profile function.
|     real du,    i-Value of cam u profile function first derivative.
|     real dv,    i-Value of cam v profile function first derivative.
|     real ddu,   i-Value of cam u profile function second derivative.
|     real ddv,   i-Value of cam v profile function second derivative.
|     real Q[6],  o-Derivative operator for that joint variable.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void qcamc(int njvar, real phi[3], real u, real v, real du, real dv,
    real ddu, real ddv, real Q[6])
#else
  void qcamc(njvar, phi, u, v, du, dv, ddu, ddv, Q)
  int  njvar;
  real phi[2], u, v, du, dv, ddu, ddv, Q[6];
#endif
{
  int i;
  real ctheta, denom, dtheta, stheta, theta;

  for (i=0; i<6; i++) {
    Q[i] = 0.0;
  }
  theta  = atan2(du, dv);
  stheta = sin(theta);
  ctheta = cos(theta);
  switch (njvar) {
  case 0:
    denom = du * ctheta + dv * stheta;
    if (fabs(denom) < System.zero) denom = sign(System.zero, denom);
    dtheta = (-ddu * stheta * ddv * ctheta) / denom;
    Q[0] = ((u - phi[1]) * stheta + v - v * ctheta) * dtheta -
      du * ctheta - dv * stheta;
    Q[1] = ((u + phi[1]) * ctheta - u + v * stheta) * dtheta;
    Q[5] = dtheta;
    break;
  case 1:
    Q[0] = -ctheta;
    Q[1] = -stheta;
    break;
  case 2:
    Q[2] = 1.0;
  }
  return;
}
