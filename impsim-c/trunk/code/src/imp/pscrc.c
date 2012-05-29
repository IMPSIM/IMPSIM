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
/* pscrc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Form the transformation matrix for a screw joint.
|
|     Access:
|       (void) pscrc(real phi, real advnc, real Phi[3][4]);
|     real phi,      i-Joint variable value for the joint, length units.
|     real advnc,    i-Lead of the screw, length units per radian.
|     real Phi[4][3],o-Transformation matrix for the joint.
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
  void pscrc(real phi, real advnc, real Phi[3][4])
#else
  void pscrc(phi, advnc, Phi)
  real phi, advnc, Phi[3][4];
#endif
{
  int  i, j;
  real ctheta, stheta, theta;
  
  for (i=0; i<3; i++){
    for (j=0; j<4; j++){
      Phi[i][j] = 0.0;
    }
  }
  theta  = phi / advnc;
  ctheta = cos(theta);
  stheta = sin(theta);
  Phi[0][0] = ctheta;
  Phi[0][1] =-stheta;
  Phi[1][0] = stheta;
  Phi[1][1] = ctheta;
  Phi[2][2] = 1.0;
  Phi[2][3] = phi;
  return;
}
