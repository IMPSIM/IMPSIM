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
/* pcamc-01 Jan 00:28 Jun 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Form the transformation matrix for a cam joint.
|
|     Access:
|       (void) pcamc(real phi[3], real u, real v, real du, real dv,
|         real Phi[3][4]);
|     real phi[3],   i-Joint variable values for the joint.
|     real u,v,      i-Pitch curve function values for the cam.
|     real du,dv,    i-Pitch curve derivative values for the cam.
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
  void pcamc(real phi[3], real u, real v, real du, real dv,
    real Phi[3][4])
#else
  void pcamc(phi, u, v, du, dv, Phi)
  real phi[3], u, v, du, dv, Phi[3][4];
#endif
{
  int  i, j;
  real ctheta, stheta, theta;
  
  for (i=0; i<3; i++){
    for (j=0; j<4; j++){
      Phi[i][j] = 0.0;
    }
  }
  theta  = atan2(du, dv);;
  ctheta = cos(theta);
  stheta = sin(theta);
  Phi[0][0] = ctheta;
  Phi[0][1] =-stheta;
  Phi[0][3] = u - phi[1] * ctheta;
  Phi[1][0] = stheta;
  Phi[1][1] = ctheta;
  Phi[1][3] = v - phi[1] * stheta;
  Phi[2][2] = 1.0;
  Phi[2][3] = phi[2];
  return;
}
