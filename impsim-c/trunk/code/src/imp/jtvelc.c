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
/* jtvelc-01 Jan 00:16 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Determine the current joint variable velocity values for a given
|     joint.
|
|     Access:
|       (void) jtvelc(Joint *joint, real vel[], int *n);
|     Joint *joint,i-Pointer to the given joint record.
|     real vel[],  o-Array of joint variable velocity values.
|     int *n,      o-Number of velocity components in vel[].
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
  void jtvelc(Joint *joint, real vel[], int *n)
#else
  void jtvelc(joint, vel, n);
  Joint *joint;
  real   vel[];
  int   *n;
#endif
{
  Jvar *jvar;

  for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
    vel[jvar->jvrnoJ] = jvvelc(jvar);
  }
  *n = joint->njvars;
  return;
}
