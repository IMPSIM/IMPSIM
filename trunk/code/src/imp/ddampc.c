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
/* ddampc-01 Jan 00:18 Mar 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Store the viscous damping coefficient for a previously defined
|     damper or the viscous damping coefficient(s) within a specified
|     joint.
|
|     Access:
|       (void) ddampc(Word name, Token coeff[]);
|     Word name,i-Name of the damper or joint to be set.
|     Token coeff[],i-Array of tokens with the damping value(s).
|
|     Error Conditions:
|       System.nerror = 3 indicates an undefined damper or joint name.
|       System.nerror = 4 indicates Euler parameter damping ignored.
|
|     Comments:
|       A warning message is printed when previous data are redefined.
*
*     History:
*     01 Jan 00:JJU-Original.
*     12 Mar 09:JJU-Implemented Euler parameters.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void ddampc(Word name, Token coeff[])
#else
  void ddampc(name, coeff)
  Word  name;
  Token coeff[];
#endif
{
  Damper *damper;
  Joint  *joint;
  Jvar   *jvar;
  int     i, lfound, lprint;

/* Search for a joint with the given name. */
  lfound = FALSE;
  lprint = FALSE;
  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
    if (strcmp(joint->name, name) == 0) {
      for (jvar=joint->jntJvr, i=0; jvar; jvar=jvar->nxtJvr, i++) {
        if (jvar->jvrtyp == JV_EULER) {
          echoc();
          textc("*** Damping data for '", FALSE);
          textc(name, FALSE);
          textc("' Euler jvars are ignored. ***", TRUE);
          System.nerror = 4;
          break;
        }
        if (jvar->jvrVc) {
          jvar->jvrVc = NULL;
          lprint = TRUE;
        }
        if ((!isnanc((void *) &jvar->c)) && (jvar->c)) {
          ldnanc((void *) &(jvar->c));
          lprint = TRUE;
        }
        if (coeff[i].kind == TK_REAL) {
          jvar->c = coeff[i].data.word;
        } else if (coeff[i].kind == TK_VALUE) {
          if (coeff[i].data.value) {
            jvar->jvrVc = coeff[i].data.value;
          } else {
            jvar->jvrVc = NULL;             /* This is case of "none" */
          }
        }
      }
      lfound = TRUE;
    }
  }

/* Otherwise search for a damper with the given name. */
  if (!lfound) {
    for (damper=System.sysDmp; damper; damper=damper->nxtDmp) {
      if (strcmp(damper->name, name) == 0) {
        if (damper->dmpVc) {
          damper->dmpVc = NULL;
          lprint = TRUE;
        }
        if ((!isnanc((void *) &damper->c)) && (damper->c)) {
          ldnanc((void *) &(damper->c));
          lprint = TRUE;
        }
        if (coeff[0].kind == TK_REAL) {
          damper->c = coeff[0].data.word;
        } else if (coeff[0].kind == TK_VALUE) {
          damper->dmpVc = coeff[0].data.value;
        }
        lfound = TRUE;
      }
    }
  }
  if (lprint) {
    echoc();
    textc("*** The damping data for '", FALSE);
    textc(name, FALSE);
    textc("' is redefined. ***", TRUE);
  }
  if (!lfound) {
    echoc();
    textc("*** There is no damper or joint named '", FALSE);
    textc(name, FALSE);
    textc("'. ***", TRUE);
    System.nerror = 3;
  }
  return;
}
