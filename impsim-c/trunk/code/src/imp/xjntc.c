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
/* xjntc-01 Jan 00:16 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Delete a specified joint record.
|
|     Access:
|       (void) xjntc(Joint *joint);
|     Joint *joint,i-Pointer to the joint record to be deleted.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       All records which are dependent on this joint are also deleted.
|       System.level = 0 on successful completion.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void xjntc(Joint *joint)
#else
  void xjntc(joint)
  Joint *joint;
#endif
{
  Joint *jnt;

  if (joint->type == JOINT) {
    if (System.sysJnt == joint) {
      System.sysJnt = joint->nxtJnt;
    } else {
      jnt = System.sysJnt;
      while (jnt) {
        if (jnt->nxtJnt == joint) {
          jnt->nxtJnt = joint->nxtJnt;
          break;
        }
        jnt = jnt->nxtJnt;
      }
    }
    if (joint->jntAxB) joint->jntAxB->axsJnt = NULL;
    if (joint->jntAxA) joint->jntAxA->axsJnt = NULL;
    while (joint->jntJvr) xjvarc(joint->jntJvr);
    for (jnt=joint; jnt; jnt=jnt->nxtJnt) (jnt->jntno)--;
    System.njnts--;
    System.level = 0;
    free(joint);
  }
  return;
}
