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
/* dqcamc-01 Jan 00:29 Jun 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Form the derivative of the Q operator for a cam joint.
|
|     Access:
|       (void) dqcamc(int nivar, int njvar, real phi[3], real u, real v,
|         real du, real dv, ddu, ddv, real Q[6]);
|     int  nivar, i-Number of the variable within the joint.
|     int  njvar, i-Number of the variable of the derivative.
|     real phi[3],i-Values of the joint variables of the joint.
|     real u,     i-Value of the cam u profile function.
|     real v,     i-Value of the cam v profile function.
|     real du,    i-Value of cam u profile function first derivative.
|     real dv,    i-Value of cam v profile function first derivative.
|     real ddu,   i-Value of cam u profile function second derivative.
|     real ddv,   i-Value of cam v profile function second derivative.
|     real dQ[6], o-Derivative of the Q operator.
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
  void dqcamc(int nivar, int njvar, real phi[3], real u, real v,
    real du, real dv, real ddu, real ddv, real dQ[6])
#else
  void dqcamc(nivar, njvar, phi, u, v, du, dv, ddu, ddv, dQ)
  int  nivar, njvar;
  real phi[3], u, v, du, dv, ddu, ddv, dQ[6];
#endif
{
  int i;
  real ctheta, denom, dtheta, stheta, theta;

  for (i=0; i<6; i++) dQ[i] = 0.0;
  theta  = atan2(u, v);
  stheta = sin(theta);
  ctheta = cos(theta);
  denom  = du * ctheta + dv * stheta;
  if (fabs(denom) < System.zero) denom = sign(System.zero, denom);
  dtheta = (-ddu * stheta * ddv * ctheta) / denom;
  switch (nivar) {
  case 0:
    switch (njvar) {
    case 0:
      dQ[0] = ((( u - phi[1]) * ctheta + v * stheta) * dtheta + dv) *
        dtheta - ddu * ctheta - ddv * stheta;
      dQ[1] = (((-u - phi[1]) * stheta + v * ctheta) * dtheta - du +
        du * ctheta + dv * stheta) * dtheta;
      break;
    case 1:
      dQ[0] = -stheta * dtheta;
      dQ[1] =  ctheta * dtheta;
    }
    break;
  case 1:
    switch (njvar) {
    case 0:
      dQ[0] =  stheta * dtheta;
      dQ[1] = -ctheta * dtheta;
    }
  }
  return;
}
