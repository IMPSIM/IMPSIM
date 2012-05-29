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
/* post1c-01 Jan 00:17 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Check the IMP data structure.  Reference global point data to
|     bodies.  Reassign joint variable numbers to reflect the SGC's and
|     IC's.  Assemble the system at the design position with the
|     proper generalized coordinates.
|
|     Access:
|       (void) post1c();
|
|     Error Conditions:
|       System.nerror = 3 indicates a critical undefined model element.
|       System.nerror = 4 indicates missing or faulty data.
|       System.nerror = 5-7 indicates faulty system topology.
|       System.nerror = 10 indicates that the system will not assemble.
|       An appropriate message is printed in each case.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
void post1c()
{
  Body  *body;
  Joint *joint;
  Jvar  *jvar;
  Point *point;
  Sgc   *sgc;
  real   Tj0[3][4];

/* Check for missing data. */
  vzeroc(F_ALL);
  if (System.level < 4) checkc();
  if (System.nerror) return;
  resetc();
  if (isnanc((void *) &System.dtmin)  ||
      isnanc((void *) &System.tfinal) ||
      isnanc((void *) &System.dtio)) {
    if (System.mode == MD_DYN) {                     /* Dynamic mode. */
      textc("*** The 'DATA TIME' statement is missing. ***", TRUE);
      System.nerror = 4;
      return;
    } else {                             /* Kinematic or static mode. */
      if (isnanc((void *) &System.dtmin)) System.dtmin = 0.0;
      if (isnanc((void *) &System.dtio )) System.dtio = 1.0;
      if (isnanc((void *) &System.tfinal)) {
        System.tfinal = 0.0;
        for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
          for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
            sgc = jvar->jvrSgc;
            if (sgc) {
              if (!isnanc((void *) &sgc->incrnum)) {
                System.tfinal = max(System.tfinal, (real) sgc->incrnum);
              }
            }
          }
        }
        textc("*** 'DATA TIME = ", FALSE);
        gtextc(System.tfinal);
        textc(", ", FALSE);
        gtextc(System.dtmin);
        textc(", ", FALSE);
        gtextc(System.dtio);
        textc("' is assumed. ***", TRUE);
      }
    }
  }

/* Assign numbers to the Jvars keeping IC's and SGC's highest. */
  System.nsgc = 0;
  System.nfgc = 0;                  /* Use temporarily to count IC's. */
  System.ndep = 0;
  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
    for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
      if (jvar->jvrSgc) {
        System.nsgc++;
        jvar->jvrnoS = System.njvars - System.nsgc;
      } else if (jvar->jvrIc) {
        if ((System.mode == MD_DYN) && (isnanc((void *) &System.t))) {
          System.nfgc++;
          jvar->jvrnoS = - System.nfgc;
        }
      } else {
        jvar->jvrnoS = System.ndep;
        System.ndep++;
      }
    }
  }
  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
    for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
      if (jvar->jvrnoS < 0) jvar->jvrnoS += System.njvars - System.nsgc;
    }
  }
  System.ndof  = System.nsgc + System.nfgc;
  System.nfree = System.njvars - System.ndof;
  pvsetc();

/* Reassemble the system with these generalized coordinates. */
  closec();
  if (System.nerror) return;
  if (isnanc((void *) &System.t)) {
    for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
      for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
        jvar->vel = 0.0;
        jvar->acc = 0.0;
      }
    }
  }
  pvsetc();

/* Switch global point data to local. */
  for (body=System.sysBdy; body; body=body->nxtBdy) {
    invxc(body->T0j, Tj0);
    for (point=body->bdyPnt; point; point=point->nxtPnt) {
      if (point->local == FALSE) {
        mpyxrc(Tj0, point->coord, point->coord);
        point->local = -TRUE;
      }
    }
  }
  return;
}
