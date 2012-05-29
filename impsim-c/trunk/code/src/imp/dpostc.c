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
/* dpostc-01 Jan 00:15 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Define a specified single freedom joint as an SGC.  Store the
|     motion as specified by the initial position, increment size and
|     number of increments.
|
|     Access:
|       (void) dpostc(Word name, real psi, real dpsi, int nsteps);
|     Word name,i-Name of the joint for the SGC to be set.
|     real psi,i-Value for the initial position of the joint variable.
|     real dpsi,i-Value of the joint variable increment.
|     int nsteps,i-Number of times to increment this joint variable.
|
|     Error Conditions:
|       System.nerror = 3 indicates an undefined or improper joint name.
|       System.nerror = 5 indicates a conflict in mode.
|
|     Comments:
|       Any previous input motion data for this joint is deleted; a
|     warning message is printed.
|       System.mode = MD_KIN on successful completion.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void dpostc(Word name, real psi, real dpsi, int nsteps)
#else
  void dpostc(name, psi, dpsi, nsteps)
  Word name;
  real psi, dpsi;
  int  nsteps;
#endif
{
  Joint *joint;
  Jvar  *jvar;
  Sgc   *sgc;

  if (System.mode == MD_DYN) {
    echoc();
    textc("*** DATA POSITION is not allowed in dynamic mode. ***",
      TRUE);
    System.nerror = 5;
  } else {
    for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
      if (strcmp(joint->name, name) == 0) {
        if (joint->njvars == 1) {
          jvar = joint->jntJvr;
          if (jvar->jvrSgc) {
            echoc();
            textc("*** Input motion for joint ", FALSE);
            textc(name, FALSE);
            textc(" ", FALSE);
            itextc(jvar->jvrnoJ+1);
            textc(" is redefined. ***", TRUE);
            xsgc(jvar->jvrSgc);
          }
          sgc = (Sgc *) malloc(sizeof(Sgc));
          if (sgc) {
            jvar->jvrSgc = sgc;
            sgc->type    = SGC;
            sgc->sgcJvr  = jvar;
            sgc->sgcVal  = NULL;
            sgc->incrnum = nsteps;
            sgc->incrpos = dpsi;
            sgc->initpos = psi;
            sgc->scale   = 1.0;
            if (jvar->jvrtyp == JV_ANGULAR) {
              sgc->incrpos /= System.ascale;
              sgc->initpos /= System.ascale;
              sgc->scale   /= System.ascale;
            }
            ldnanc((void *) &(sgc->pos));
            sgc->vel = 0.0;
            sgc->acc = 0.0;
          }
          if (System.mode < MD_GEO) System.mode = MD_GEO;
          ldnanc((void *) &System.tfinal);
          return;
        } else {
          echoc();
          textc("*** DATA POSITION is not allowed for joint ", FALSE);
          textc(name, FALSE);
          textc(". ***", TRUE);
          System.nerror = 3;
          return;
        }
      }
    }
    echoc();
    textc("*** There is no joint named '", FALSE);
    textc(name, FALSE);
    textc("'. ***", TRUE);
    System.nerror = 3;
  }
  return;
}
