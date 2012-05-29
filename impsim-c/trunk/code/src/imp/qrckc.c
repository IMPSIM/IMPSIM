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
/* qrckc-01 Jan 00:20 Jun 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Form the derivative operators for a rack and pinion joint.
|
|     Access:
|       (void) qrckc(int njvar, real phi[3], real radius, real helix,
|         real Q[6]);
|     int  njvar, i-Number of the joint variable within the joint.
|     real phi[3],i-Joint variables of the rack and pinion joint.
|     real radius,i-Pitch radius of the pinion gear of the joint.
|     real helix, i-Helix angle of the pinion gear of the joint.
|     real Q[6],  o-Derivative operator for this joint variable.
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
  void qrckc(int njvar, real phi[3], real radius, real helix, real Q[6])
#else
  void qrckc(njvar, phi, radius, helix, Q)
  int  njvar;
  real phi[3], radius, helix, Q[6];
#endif
{
  int i;
  real factor;

  for (i=0; i<6; i++) Q[i] = 0.0;
  switch (njvar) {
  case 0:
    Q[0] =-phi[1] / radius;
    Q[1] = phi[0] / radius;
    Q[5] =-1.0 / radius;
    break;
  case 1:
    factor = tan(20.0 / System.ascale) / radius;
    Q[0]   =-(radius + phi[1]) * factor;
    Q[1]   = 1.0 + phi[0] * factor;
    Q[5]   =-factor;
    break;
  case 2:
    factor = tan(helix) / radius;
    Q[0]   = (radius + phi[1]) * factor;
    Q[1]   =-phi[0] * factor;
    Q[2]   = 1.0;
    Q[5]   = factor;
    break;
  }
  return;
}
