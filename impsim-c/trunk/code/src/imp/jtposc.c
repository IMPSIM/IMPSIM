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
/* jtposc-01 Jan 00:16 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Determine the current joint variable position values for a given
|     joint.
|
|     Access:
|       (void) jtposc(Joint *joint, real pos[], int *n);
|     Joint *joint,i-Pointer to the given joint record.
|     real pos[],  o-Array of joint variable position values.
|     int *n,      o-Number of position components in pos[].
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
  void jtposc(Joint *joint, real pos[], int *n)
#else
  void jtposc(joint, pos, n);
  Joint *joint;
  real   pos[];
  int   *n;
#endif
{
  Jvar *jvar;

  for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
    pos[jvar->jvrnoJ] = jvposc(jvar);
  }
  *n = joint->njvars;
  return;
}
