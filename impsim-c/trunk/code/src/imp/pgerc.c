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
/* pgerc-01 Jan 00:19 Jun 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Form the transformation matrix for a gear joint.
|
|     Access:
|       (void) pgerc(real phi[3], real ratio, helix, real cd,
|         real Phi[3][4]);
|     real phi[3],   i-Joint variable values for the joint.
|     real ratio,    i-Gear ratio for the gear joint.
|     real helix,    i-Helix angle of the gear joint.
|     real cd,       i-Center to center distance for the gear joint.
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
  void pgerc(real phi[3], real ratio, real helix, real cd,
    real Phi[3][4])
#else
  void pgerc(phi, ratio, helix, cd, Phi)
  real phi[3], ratio, helix, cd, Phi[3][4];
#endif
{
  int  i, j;
  real alpha, calpha, cphi, ctheta, cdist, salpha, sphi, stheta, term,
    theta;
  
  for (i=0; i<3; i++){
    for (j=0; j<4; j++){
      Phi[i][j] = 0.0;
    }
  }
  cphi  = cos(phi[0]);
  sphi  = sin(phi[0]);
  alpha = 20.0 / System.ascale;
  calpha= cos(alpha);
  salpha= sin(alpha);
  cdist = cd + phi[1];
  term  = cdist / cd;
  term  = sqrt(term * term - calpha * calpha) - salpha;
  theta = (1.0 + ratio) * (phi[0] + term + tan(helix) * phi[2] / cd);
  ctheta= cos(theta);
  stheta= sin(theta);
  Phi[0][0] = ctheta;
  Phi[0][1] =-stheta;
  Phi[0][3] = cdist * cphi;
  Phi[1][0] = stheta;
  Phi[1][1] = ctheta;
  Phi[1][3] = cdist * sphi;
  Phi[2][2] = 1.0;
  Phi[2][3] = phi[2];
  return;
}
