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
/* prckc-01 Jan 00:22 Jun 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Form the transformation matrix for a rack joint.
|
|     Access:
|       (void) prckc(real phi[3], real radius, real helix,
|         real Phi[3][4]);
|     real phi[3],   i-Joint variable values for the joint.
|     real radius,   i-Pinion radius the joint.
|     real helix,    i-Helix angle of the pinion.
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
  void prckc(real phi[3], real radius, real helix, real Phi[3][4])
#else
  void prckc(phi, radius, helix, Phi)
  real phi[3], radius, helix, Phi[3][4];
#endif
{
  int  i, j;
  real ctheta, stheta, theta;
  
  for (i=0; i<3; i++){
    for (j=0; j<4; j++){
      Phi[i][j] = 0.0;
    }
  }
  theta  =-(phi[0] + phi[1] * tan(20.0 / System.ascale)
            - phi[2] * tan(helix)) / radius;
  ctheta = cos(theta);
  stheta = sin(theta);
  Phi[0][0] = ctheta;
  Phi[0][1] =-stheta;
  Phi[0][3] = phi[0];
  Phi[1][0] = stheta;
  Phi[1][1] = ctheta;
  Phi[1][3] = radius + phi[1];
  Phi[2][2] = phi[2];
  return;
}
