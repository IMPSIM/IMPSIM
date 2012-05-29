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
/* fjtdc-01 Jan 00:16 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Add the effects of the joint damping to the current vector of
|     constraint forces and torques in a given joint.
|
|     Access:
|       (void) fjtdc(real f[6]);
|     real f[6], i/o-Vector of constraint forces and torques.
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
  void fjtdc(real f[6])
#else
  void fjtdc(f);
  real   f[6];
#endif
{
  Joint *joint;
  Jvar  *jvar;
  int    i, njvar;
  real   fdamp;

/* Initialize. */
  if (System.mode == MD_STAT) return;
  if (System.level < 8) velc();
  if (System.nerror) return;

/* Loop through all joint variables having damping. */
  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
    for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
      if (!isnanc((void *) &jvar->c)) {
        fdamp = - jvar->c * jvar->vel;
        if (fdamp != 0.0) {
          njvar = jvar->jvrnoS;
          if (njvar < System.ndep) {

/* Add the effects to the constraint forces. */
            for (i=0; i<6; i++) {
              if (!isnanc((void *) &System.pd[0][i])) {
                f[i] += System.pd[njvar][i] * fdamp;
              }
            }
          }
        }
      }
    }
  }
  return;
}
