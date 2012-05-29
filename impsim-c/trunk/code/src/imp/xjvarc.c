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
/* xjvarc-01 Jan 00:16 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Delete a specified jvar record.
|
|     Access:
|       (void) xjvarc(Jvar *jvar);
|     Jvar *jvar,i-Pointer to the jvar record to be deleted.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       System.level = 0 on successful completion.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void xjvarc(Jvar *jvar)
#else
  void xjvarc(jvar)
  Jvar *jvar;
#endif
{
  Joint *joint;
  Jvar  *jvr;

  if (jvar->type == JVAR) {
    joint = jvar->jvrJnt;
    if (joint->jntJvr == jvar) {
      joint->jntJvr = jvar->nxtJvr;
    } else {
      jvr = joint->jntJvr;
      while (jvr) {
        if (jvr->nxtJvr == jvar) {
          jvr->nxtJvr = jvar->nxtJvr;
          break;
        }
        jvr = jvr->nxtJvr;
      }
    }
    while (jvar->jvrSgc) xsgc(jvar->jvrSgc);
    while (jvar->jvrIc)  xic(jvar->jvrIc);
    joint->njvars--;
    for (jvr=joint->jntJvr; jvr; jvr=jvr->nxtJvr) {
      if(jvr->jvrnoJ > jvar->jvrnoJ) jvr->jvrnoJ--;
    }
    if (System.njvars) {
      System.njvars--;
      for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
        for (jvr=joint->jntJvr; jvr; jvr=jvr->nxtJvr) {
          if(jvr->jvrnoS > jvar->jvrnoS) jvr->jvrnoS--;
        }
      }
    }
    System.level = 0;
    free(jvar);
  }
  return;
}
