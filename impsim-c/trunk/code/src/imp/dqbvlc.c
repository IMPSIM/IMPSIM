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
/* dqbvlc-01 Jan 00:22 Jun 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Form the derivative of the Q operator for a bevel gear joint.
|
|     Access:
|       (void) dqbvlc(int ijv, int jjv, real phi[2], real conei,
|         real coneo, real dQ[6]);
|     int  ijv,   i-Number of the joint variable of the Q operator.
|     int  jjv,   i-Number of the joint variable of the derivative.
|     real phi[2],i-Joint variables of the bevel gear joint.
|     real conei, i-First  cone half-angle of the bevel gear joint.
|     real coneo, i-Second cone half-angle of the bevel gear joint.
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
  void dqbvlc(int ijv, int jjv, real phi[2], real conei, real coneo,
    real dQ[6])
#else
  void dqbvlc(ijv, jjv, phi, conei, coneo, dQ)
  int  ijv, jjv;
  real phi[2], conei, coneo, dQ[6];
#endif
{
  int  i;
  real cosphi, costh, factor, sinphi, sinth, theta;

  for (i=0; i<6; i++) {dQ[i] = 0.0;}
  sinphi = sin(phi[0]);
  cosphi = cos(phi[0]);
  switch (ijv) {
  case 0:
    theta  = conei + coneo + phi[1];
    sinth  = sin(theta);
    costh  = cos(theta);
    factor = tan(conei) / tan(coneo);
    switch (jjv) {
    case 0:
      dQ[3] = -factor * cosphi * sinth;
      dQ[4] =  factor * sinphi * sinth;
      break;
    case 1:
      dQ[3] = -factor * sinphi * costh;
      dQ[4] = -factor * cosphi * costh;
      break;
    }
    break;
  case 1:
    switch (jjv) {
    case 0:
      dQ[3] = -sinphi;
      dQ[4] = -cosphi;
      break;
    }
  }
  return;
}
