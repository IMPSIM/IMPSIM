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
/* adjstc-01 Jan 00:16 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Improve the joint variable estimates for the iterative position
|     analysis by using a first-order Taylor series.
|
|     Access:
|       (void) adjstc();
|
|     Error Conditions:
|       If first kinematic derivatives are not yet stored no action is
|     taken.  No message is printed.
|
|     Comments:
|       System.level = 5 on successful completion.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
void adjstc()
{
  Joint *jnt, *joint;
  Jvar  *jvar, *jvr;
  int    jgc;
  real   delta;

  if (System.d1) {;
    for (jnt=System.sysJnt; jnt; jnt=jnt->nxtJnt) {
      for (jvr=jnt->jntJvr; jvr; jvr=jvr->nxtJvr) {
        jgc = jvr->jvrnoS - System.ndep;
        if (jgc >= 0) {
          delta = jvr->pos - jvr->lastpos;
          for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
            for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
              if (jvar->jvrnoS < System.ndep) {
                jvar->pos += System.d1[jvar->jvrnoS][jgc] * delta;
              }
            }
          }
        }
      }
    }
    System.level = 5;
  }
  return;
}
