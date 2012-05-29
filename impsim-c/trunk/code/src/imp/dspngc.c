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
/* dspngc-01 Jan 00:18 Mar 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Store the spring rate and free position for a previously defined
|     spring or the stiffness and free position value(s) within a speci-
|     fied joint.
|
|     Access:
|       (void) dspngc(Word name, Token token[]);
|     Word name,i-Name of the spring or joint to be set.
|     Token token[],i-Array of tokens with the spring rate and free pos-
|       ition value(s).
|
|     Error Conditions:
|       System.nerror = 3 indicates an undefined spring or joint name.
|       System.nerror = 4 indicates Euler jvars ignored.
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
  void dspngc(Word name, Token token[])
#else
  void dspngc(name, token)
  Word  name;
  Token token[];
#endif
{
  Joint  *joint;
  Jvar   *jvar;
  Spring *spring;
  int     i, lfound, lprint;

/* Search for a joint with the given name. */
  lfound = FALSE;
  lprint = FALSE;
  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
    if (strcmp(joint->name, name) == 0) {
      for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
        if (jvar->jvrtyp == JV_EULER) {
          echoc();
          textc("*** Stiffness data for '", FALSE);
          textc(name, FALSE);
          textc("' is ignored. ***", TRUE);
          System.nerror = 4;
          break;
        }
        if ((!isnanc((void *) &jvar->k)) && (jvar->k)) {
          ldnanc((void *) &(jvar->k));
          lprint = TRUE;
        }
        if (jvar->jvrVk) {
          jvar->jvrVk  = NULL;
          jvar->jvrVfp = NULL;
          lprint = TRUE;
        }
        if ((!isnanc((void *) &jvar->freepos)) && (jvar->freepos)) {
          ldnanc((void *) &(jvar->freepos));
          lprint = TRUE;
        }
        if (jvar->jvrVfp) {
          jvar->jvrVk  = NULL;
          jvar->jvrVfp = NULL;
          lprint = TRUE;
        }
        i = jvar->jvrnoJ;
        if (token[2*i].kind == TK_REAL) {
          jvar->k = token[2*i].data.word;
          if (jvar->jvrtyp == JV_ANGULAR) jvar->k *= System.ascale;
        } else if (token[2*i].kind == TK_VALUE) {
          if (token[2*i].data.value) {
            jvar->jvrVk = token[2*i].data.value;
          } else {
            jvar->jvrVk  = NULL;            /* This is case of "none" */
            jvar->jvrVfp = NULL;
          }
        }
        if (token[2*i+1].kind == TK_REAL) {
          jvar->freepos = token[2*i+1].data.word;
          if (jvar->jvrtyp == JV_ANGULAR)jvar->freepos /= System.ascale;
        } else if (token[2*i+1].kind == TK_VALUE) {
          if (token[2*i+1].data.value) {
            jvar->jvrVfp = token[2*i+1].data.value;
          } else {
            jvar->jvrVk  = NULL;            /* This is case of "none" */
            jvar->jvrVfp = NULL;
          }
        }
      }
      lfound = TRUE;
    }
  }

/* Otherwise search for a spring with the given name. */
  if (!lfound) {
    for (spring=System.sysSpg; spring; spring=spring->nxtSpg) {
      if (strcmp(spring->name, name) == 0) {
        if ((!isnanc((void *) &spring->k)) && (spring->k)) {
          ldnanc((void *) &(spring->k));
          lprint = TRUE;
        }
        if (spring->spgVk) {
          spring->spgVk = NULL;
          lprint = TRUE;
        }
        if ((!isnanc((void *) &spring->freel)) && (spring->freel)) {
          ldnanc((void *) &(spring->freel));
          lprint = TRUE;
        }
        if (spring->spgVfl) {
          spring->spgVfl = NULL;
          lprint = TRUE;
        }
        if (token[0].kind == TK_REAL) {
          spring->k = token[0].data.word;
        } else if (token[0].kind == TK_VALUE) {
          spring->spgVk = token[0].data.value;
        }
        if (token[1].kind == TK_REAL) {
          spring->freel = token[1].data.word;
        } else if (token[1].kind == TK_VALUE) {
          spring->spgVfl = token[1].data.value;
        }
        lfound = TRUE;
      }
    }
  }
  if (lprint) {
    echoc();
    textc("*** The spring data for '", FALSE);
    textc(name, FALSE);
    textc("' is redefined. ***", TRUE);
  }
  if (!lfound) {
    echoc();
    textc("*** There is no spring or joint named '", FALSE);
    textc(name, FALSE);
    textc("'. ***", TRUE);
    System.nerror = 3;
  }
  return;
}
