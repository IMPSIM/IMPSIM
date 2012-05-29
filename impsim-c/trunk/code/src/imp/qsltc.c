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
/* qsltc-01 Jan 00:25 Jun 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Form the derivative operator for one joint variable of a pin in
|     slot joint.
|
|     Access:
|       (void) qsltc(int njvar, real phi[3], real u, real v, real du,
|         real dv, real Q[6]);
|     int  njvar, i-Number of the variable within the joint.
|     real phi[3],i-Values of the joint variables of the joint.
|     real u,     i-Value of the slot u profile function.
|     real v,     i-Value of the slot v profile function.
|     real du,    i-Value of slot u profile function first derivative.
|     real dv,    i-Value of slot v profile function first derivative.
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
  void qsltc(int njvar, real phi[3], real u, real v, real du, real dv,
    real Q[6])
#else
  void qsltc(njvar, phi, u, v, du, dv, Q)
  int  njvar;
  real phi[3], u,v, du, dv, Q[6];
#endif
{
  int i;

  for (i=0; i<6; i++) {
    Q[i] = 0.0;
  }
  switch (njvar) {
  case 0:
    Q[0] = du;
    Q[1] = dv;
    break;
  case 1:
    Q[0] = v;
    Q[1] =-u;
    Q[5] = 1.0;
    break;
  case 2:
    Q[2] = 1.0;
  }
  return;
}
