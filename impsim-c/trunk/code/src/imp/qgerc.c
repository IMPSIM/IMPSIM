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
/* qgerc-01 Jan 00:10 Mar 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Form the derivative operator for a spur gear joint.
|
|     Access:
|       (void) qgerc(int njvar, real phi, real ratio, real helix,
|         real cd, real Q[6]);
|     int  njvar, i-Number of the variable within the joint.
|     real phi[3],i-Joint variables of the joint.
|     real ratio, i-Gear ratio of the joint.
|     real helix, i-Helix angle of the gears.
|     real cd,    i-Nominal center to center distance of the joint.
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
  void qgerc(int njvar, real phi[3], real ratio, real helix, real cd,
    real Q[6])
#else
  void qgerc(njvar, phi, ratio, helix, cd, Q)
  int  njvar;
  real phi, ratio, helix, cd, Q[6];
#endif
{
  int  i;
  real cdist, factor;

  for (i=0; i<6; i++) {Q[i] = 0.0;}
  cdist = cd + phi[1];
  switch (njvar) {
  case 0:
    factor = ratio * cdist;
    Q[0]   = factor * sin(phi[0]);
    Q[1]   =-factor * cos(phi[0]);
    Q[5]   = 1.0 + ratio;
    break;
  case 1:
    factor = cos(20.0 / System.ascale);
    factor = sqrt(cdist * cdist - factor * factor);
    factor = cdist * (1.0 + ratio) / (cd * factor);
    Q[0]   = factor * cdist * sin(phi[0]) + cos(phi[0]);
    Q[1]   =-factor * cdist * cos(phi[0]) + sin(phi[0]);
    Q[5]   = factor;
    break;
  case 2:
    factor = tan(helix) * (1.0 + ratio) / cd;
    Q[0]   = factor * cdist * sin(phi[0]);
    Q[1]   =-factor * cdist * cos(phi[0]);
    Q[2]   = 1.0;
    Q[5]   = factor;
    break;
  }
  return;
}
