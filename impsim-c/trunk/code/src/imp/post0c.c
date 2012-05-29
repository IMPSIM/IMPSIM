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
/* post0c-01 Jan 00:17 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Reassemble the system at the design position.
|
|     Access:
|       (void) post0c();
|
|     Error Conditions:
|       System.nerror = 5 indicates that System.level < 3 on entry.
|       System.nerror = 10 indicates that the system will not assemble.
|
|     Comments:
|       System.level = 7 on successful completion.
*
*     History:
*     01 Jan 00:JJU-Original.
*     14 Apr 03:JJU-Implemented enum XQ_type for execution flags.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
void post0c()
{
  Body  *body;
  Joint *joint;
  Jvar  *jvar;
  Point *point;
  int    i;

/* Output the requested lists and plots. */
  for (i=0; i<3; i++) {
    if (lunfil[i] > 0) {
      fprintf(streams[lunfil[i]],
        " END  EXEC    0 %#19.10e %#19.10e %#19.10e\n", 0.0, 0.0, 0.0);
      rewind(streams[lunfil[i]]);
    }
  }
  if (qbitc(XQ_PAUSE, (void *) &System.xeqflags)) waitc();
  if (System.level >= 3) {
    wrlstc();
    wrpltc();
    ckbic();

/* Reset the joint variable estimates. */
    if (System.hold) {
      resetc();
      if (System.mode != MD_DYN) vzeroc(F_TIME);
    } else {
      for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
        for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
          jvar->pos = jvar->design;
        }
      }
      ldnanc((void *) &System.t);
      vzeroc(F_TIME);
    }
    System.level = 4;
    closec();
  }

/* Switch appropriate point data to global coordinates. */
  for (body=System.sysBdy; body; body=body->nxtBdy) {
    for (point=body->bdyPnt; point; point=point->nxtPnt) {
      if (point->local < 0) {
        mpyxrc(body->T0j, point->coord, point->coord);
        point->local = FALSE;
      }
    }
  }
  if (System.level < 3) {
    System.nerror = 5;
    return;
  }
  if (System.nerror) {
    System.level = 2;
    return;
  }

/* Reset the reference position for execute/hold. */
  pvsetc();
  vzeroc(F_ALL);
  if (System.hold) {
    System.hold = FALSE;
    for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
      for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
        jvar->design = jvar->pos;
      }
    }
    textc("*** The current position is set as reference. ***", TRUE);
  }
  return;
}
