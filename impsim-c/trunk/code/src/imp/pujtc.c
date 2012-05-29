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
/* pujtc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Form the transformation matrix for an uninversal joint.
|
|     Access:
|       (void) pujtc(real phi[2], real Phi[3][4]);
|     real phi[2],   i-Joint variable values for the joint.
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
  void pujtc(real phi[2], real Phi[3][4])
#else
  void pujtc(phi, Phi)
  real phi[2], Phi[3][4];
#endif
{
  real cphi0, cphi1, sphi0, sphi1;
  
  cphi0 = cos(phi[0]);
  sphi0 = sin(phi[0]);
  cphi1 = cos(phi[1]);
  sphi1 = sin(phi[1]);
  Phi[0][0] = cphi0 * cphi1;
  Phi[0][1] =-cphi0 * sphi1;
  Phi[0][2] = sphi0;
  Phi[0][3] = 0.0;
  Phi[1][0] = sphi0 * cphi1;
  Phi[1][1] =-sphi0 * sphi1;
  Phi[1][2] =-cphi0;
  Phi[1][3] = 0.0;
  Phi[2][0] =         sphi1;
  Phi[2][1] =         cphi1;
  Phi[2][2] = 0.0;
  Phi[2][3] = 0.0;
  return;
}
