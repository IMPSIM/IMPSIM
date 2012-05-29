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
/* qbvlc-01 Jan 00:10 Mar 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Form the derivative operator for a bevel gear joint.
|
|     Access:
|       (void) qbvlc(real phi, real ratio, real radout, real Q[6]);
|     real phi,   i-Joint variable of the bevel gear joint.
|     real ratio, i-Gear ratio of the joint.
|     real radout,i-Pitch radius of the output gear of the joint.
|     real Q[6],  o-Derivative operator for the joint.
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
  void qbvlc(real phi, real ratio, real radout, real Q[6])
#else
  void qbvlc(phi, ratio, radout, Q)
  real phi, ratio, radout, Q[6];
#endif
{
  Q[3] = ratio * cos(phi);
  Q[4] = ratio * sin(phi);
  Q[5] = 1.0;
  Q[0] = radout * Q[4];
  Q[1] =-radout * Q[3];
  Q[2] = 0.0;
  return;
}
