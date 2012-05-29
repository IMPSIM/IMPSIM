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
/* phopnc-01 Jan 00:09 Mar 09
|     (C)Copyright, JJU Research, 2009.
|
|     Description:
|       Find the joint variable values for an open joint from the
|     transformation matrix.
|
|     Access:
|       (void) phopnc(real Phi[3][4], real phi[7]);
|     real Phi[3][4],i-Transformation matrix for the joint.
|     real phi[7],   o-Joint variable values for the open joint.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
*     09 Mar 09:JJU-Implemented Euler parameters.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void phopnc(real Phi[3][4], real phi[7])
#else
  void phopnc(Phi, phi)
  real Phi[3][4], phi[7];
#endif
{
  real f00, f11, f22, tr;

  phi[0] = Phi[0][3];
  phi[1] = Phi[1][3];
  phi[2] = Phi[2][3];
  tr = Phi[0][0] + Phi[1][1] + Phi[2][2];
  phi[6] = 0.5 * sqrt(tr + 1.0);
  if (fabs(phi[6]) > System.zero) {
    phi[3] = sign(0.5 * sqrt(1.0 + 2.0 * Phi[0][0] - tr),
             (Phi[2][1] - Phi[1][2]));
    phi[4] = sign(0.5 * sqrt(1.0 + 2.0 * Phi[1][1] - tr),
             (Phi[0][2] - Phi[2][0]));
    phi[5] = sign(0.5 * sqrt(1.0 + 2.0 * Phi[2][2] - tr),
             (Phi[1][0] - Phi[0][1]));
  } else {
    f00 = fabs(Phi[0][0] + 1.0);
    f11 = fabs(Phi[1][1] + 1.0);
    f22 = fabs(Phi[2][2] + 1.0);
    if ((f00 >= f11) && (f00 >= f22)) {
      phi[3] = sqrt(0.5 * (Phi[0][0] + 1.0));
      phi[4] = (Phi[0][1] + Phi[1][0]) / (4.0 * phi[3]);
      phi[5] = (Phi[0][2] + Phi[2][0]) / (4.0 * phi[3]);
    } else if (f11 >= f22) {
      phi[4] = sqrt(0.5 * (Phi[1][1] + 1.0));
      phi[3] = (Phi[1][0] + Phi[0][1]) / (4.0 * phi[4]);
      phi[5] = (Phi[1][2] + Phi[2][1]) / (4.0 * phi[4]);
    } else {
      phi[5] = sqrt(0.5 * (Phi[2][2] + 1.0));
      phi[3] = (Phi[2][0] + Phi[0][2]) / (4.0 * phi[5]);
      phi[4] = (Phi[2][1] + Phi[1][2]) / (4.0 * phi[5]);
    }
  }
  return;
}
