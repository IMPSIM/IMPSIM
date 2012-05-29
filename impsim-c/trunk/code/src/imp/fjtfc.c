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
/* fjtfc-01 Jan 00:16 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Add the effects of the joint forces to the current vector of
|     constraint forces and torques in a given joint.
|
|     Access:
|       (void) fjtfc(real f[6]);
|     real   f[6], i/o-Vector of constraint forces and torques.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       This routine only adds incremental changes to the total of all
|     constraint forces.  It assumes that f[] is initialized elsewhere.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void fjtfc(real f[6])
#else
  void fjtfc(f);
  real   f[6];
#endif
{
  Joint *joint;
  Jvar  *jvar;
  int    n, njvar;
  real   force;

/* Loop through all joint variables having applied force. */
  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
    for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
      if (!isnanc((void *) &jvar->force)) {
        force = jvar->force;
        if (force != 0.0) {
          njvar = jvar->jvrnoS;
          if (njvar < System.ndep) {

/* Add the effects to the constraint forces. */
            for (n=0; n<6; n++) {
              if (!isnanc((void *) &System.pd[0][n])) {
                f[n] += System.pd[njvar][n] * force;
              }
            }
          }
        }
      }
    }
  }
  return;
}
