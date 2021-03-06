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
/* popnc-01 Jan 00:09 Mar 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Form the transformation matrix for an open joint.
|
|     Access:
|       (void) popnc(real phi[7], real Phi[3][4]);
|     real phi[7],   i-Joint variable values for the joint.
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
*     09 Mar 09:JJU-Implemented Euler parameters.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void popnc(real phi[7], real Phi[3][4])
#else
  void popnc(phi, Phi)
  real phi[7], Phi[3][4];
#endif
{
  Phi[0][0] = phi[3]*phi[3]-phi[4]*phi[4]-phi[5]*phi[5]+phi[6]*phi[6];
  Phi[0][1] = 2.0 * (phi[3] * phi[4] - phi[5] * phi[6]);
  Phi[0][2] = 2.0 * (phi[3] * phi[5] + phi[4] * phi[6]);
  Phi[0][3] = phi[0];
  Phi[1][0] = 2.0 * (phi[3] * phi[4] + phi[5] * phi[6]);
  Phi[1][1] =-phi[3]*phi[3]+phi[4]*phi[4]-phi[5]*phi[5]+phi[6]*phi[6];
  Phi[1][2] = 2.0 * (phi[4] * phi[5] - phi[3] * phi[6]);
  Phi[1][3] = phi[1];
  Phi[2][0] = 2.0 * (phi[3] * phi[5] - phi[4] * phi[6]);
  Phi[2][1] = 2.0 * (phi[4] * phi[5] + phi[3] * phi[6]);
  Phi[2][2] =-phi[3]*phi[3]-phi[4]*phi[4]+phi[5]*phi[5]+phi[6]*phi[6];
  Phi[2][3] = phi[2];
  return;
}
