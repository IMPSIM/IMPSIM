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
/* qsphc-01 Jan 00:10 Mar 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Form the derivative operator for one joint variable of a spheric
|     joint.
|
|     Access:
|       (void) qsphc(int njvar, real phi[4], real Q[6]);
|     int  njvar, i-Number of the variable within the joint.
|     real phi[4],i-Values of the joint variables of the joint.
|     real Q[6],  o-Derivative operator for that joint variable.
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
  void qsphc(int njvar, real phi[4], real Q[6])
#else
  void qsphc(njvar, phi, Q)
  int  njvar;
  real phi[4], Q[6];
#endif
{
  int  i;

  for (i=0; i<6; i++) {
    Q[i] = 0.0;
  }
  switch (njvar) {
  case 0:
    Q[3] =  phi[3];
    Q[4] =  phi[2];
    Q[5] = -phi[1];
    break;
  case 1:
    Q[3] = -phi[2];
    Q[4] =  phi[3];
    Q[5] =  phi[0];
    break;
    break;
  case 2:
    Q[3] =  phi[1];
    Q[4] = -phi[0];
    Q[5] =  phi[3];
    break;
    break;
  case 3:
    Q[3] = -phi[0];
    Q[4] = -phi[1];
    Q[5] = -phi[2];
    break;
  }
  for (i=0; i<6; i++) {
    Q[i] = Q[i] + Q[i];
  }
  return;
}
