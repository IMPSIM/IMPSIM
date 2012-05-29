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
/* pbvlc-01 Jan 00:21 Jun 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Form the transformation matrix for a bevel gear joint.
|
|     Access:
|       (void) pbvlc(real phi[2], real conei,real coneo,real Phi[3][4]);
|     real phi[2],   i-Joint variable values for the bevel gear joint.
|     real conei,    i-Cone half-angle of the first gear.
|     real coneo,    i-Cone half-angle of the second gear.
|     real Phi[3][4],o-Transformation matrix for the joint.
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
  void pbvlc(real phi[2], real conei, real coneo, real Phi[3][4])
#else
  void pbvlc(phi, conei, coneo, Phi)
  real phi[2], conei, coneo, Phi[3][4];
#endif
{
  real cosphi, cospsi, costh, psi, sinphi, sinpsi, sinth, theta;

  sinphi = sin(phi[0]);
  cosphi = cos(phi[0]);
  psi    = (tan(conei) / tan(coneo)) * phi[0];
  sinpsi = sin(psi);
  cospsi = cos(psi);
  theta  = conei + coneo + phi[1];
  sinth  = sin(theta);
  costh  = cos(theta);
  Phi[0][0] = cosphi * cospsi - sinphi * costh * sinpsi;
  Phi[0][1] =-cosphi * sinpsi + sinphi * costh * cospsi;
  Phi[0][2] =                 - sinphi * sinth;
  Phi[0][3] = 0.0;
  Phi[1][0] =-sinphi * cospsi + cosphi * costh * sinpsi;
  Phi[1][1] = sinphi * sinpsi + cosphi * costh * cospsi;
  Phi[1][2] =                 - cosphi * sinth;
  Phi[1][3] = 0.0;
  Phi[2][0] =                            sinth * sinpsi;
  Phi[2][1] =                            sinth * cospsi;
  Phi[2][2] =                            costh;
  Phi[2][3] = 0.0;
  return;
}
