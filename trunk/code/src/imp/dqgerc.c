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
/* dqgerc-01 Jan 00:19 Jun 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Form the derivative of the Q operator for a specified gear
|     joint variable with respect to a specified joint variable.
|
|     Access:
|       (void) dqgerc(int ijv, int jjv, real phi, real ratio,
|         real helix, real cd, real dQ[6]);
|     int  ijv,   i-number of the Q operator within the joint.
|     int  jjv,   i-number of the joint variable of the derivative.
|     real phi[3],i-Joint variables of the gear joint.
|     real ratio, i-Gear ratio of the gear joint.
|     real helix, i-Helix angle of the gear joint.
|     real cd,    i-Center to center distance of the gear joint.
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
  void dqgerc(int ijv, int jjv, real phi[3], real ratio, real helix,
    real cd, real dQ[6])
#else
  void dqgerc(ijv, jjv, phi, ratio, helix, cd, dQ)
  int  ijv, jjv;
  real phi[3], ratio, helix, cd, dQ[6];
#endif
{
  int i;
  real cdist, dcos, denom, factor;

  for (i=0; i<6; i++) dQ[i] = 0.0;
  cdist = cd + phi[1];
  switch (ijv) {
  case 0:
    switch (jjv) {
    case 0:
      factor = ratio * cdist;
      dQ[0]  = factor * cos(phi[0]);
      dQ[1]  = factor * sin(phi[0]);
      break;
    case 1:
      dQ[0]  = ratio * sin(phi[0]);
      dQ[1]  =-ratio * cos(phi[0]);
      break;
    case 2:
      break;
    }
  case 1:
    dcos  = cd * cos(20.0 * PI / 180.0);
    dcos  = dcos * dcos;
    denom = cdist * cdist - dcos;
    switch (jjv) {
    case 0:
      factor = cdist * cdist * (1.0 + ratio) / (cd * sqrt(denom));
      dQ[0]  = factor * cos(phi[0]) - sin(phi[0]);
      dQ[1]  =-factor * sin(phi[0]) + cos(phi[0]);
      break;
    case 1:
      factor = cdist * (cdist * cdist - 2.0 * dcos) / pow(denom, 1.5);
      dQ[0]  = factor * sin(phi[0]);
      dQ[1]  =-factor * cos(phi[0]);
      break;
    case 2:
      break;
    }
  case 2:
    factor = tan(helix) * (1.0 + ratio) / cd;
    switch (jjv) {
    case 0:
      factor = cdist * factor;
      dQ[0]  = factor * cos(phi[0]);
      dQ[1]  = factor * sin(phi[0]);
      break;
    case 1:
      dQ[0]  = factor * sin(phi[0]);
      dQ[1]  =-factor * cos(phi[0]);
      break;
    case 2:
      break;
    }
    break;
  }
  return;
}
