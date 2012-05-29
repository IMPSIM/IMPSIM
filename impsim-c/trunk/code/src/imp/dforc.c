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
/* dforc-01 Jan 00:18 Mar 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Store the force amplitude for a previously defined force or for
|     applied force(s) or torque(s) within a specified joint.
|
|     Access:
|       (void) dforc(Word name, Token token[]);
|     Word name,i-Name of the force or joint to be set.
|     Token token[],i-Array of tokens with the force value(s).
|
|     Error Conditions:
|       System.nerror = 3 indicates an undefined force or joint name.
|       System.nerror = 4 indicates force for Euler jvars ignored.
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
  void dforc(Word name, Token token[])
#else
  void dforc(name, token)
  Word  name;
  Token token[];
#endif
{
  Body  *body;
  Force *force;
  Joint *joint;
  Jvar  *jvar;
  int    i, lfound, lprint;

/* Search for a joint with the given name. */
  lfound = FALSE;
  lprint = FALSE;
  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
    if (strcmp(joint->name, name) == 0) {
      for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
        if (jvar->jvrtyp == JV_EULER) {
          echoc();
          textc("*** Applied force data for '", FALSE);
          textc(name, FALSE);
          textc("' Euler jvars are ignored. ***", TRUE);
          System.nerror = 4;
          break;
        }
        if (jvar->jvrVf) {
          jvar->jvrVf = NULL;
          lprint = TRUE;
        }
        if (!isnanc((void *) &jvar->force)) {
          ldnanc((void *) &jvar->force);
          lprint = TRUE;
        }
        i = jvar->jvrnoJ;
        if (token[i].kind == TK_REAL) {
          jvar->force = token[i].data.word;
        } else if (token[i].kind == TK_VALUE) {
          if (token[i].data.value) {
            jvar->jvrVf = token[i].data.value;
          } else {
            jvar->jvrVf = NULL;        /* This is the case of "none". */
          }
        }
      }
      lfound = TRUE;
    }
  }

/* Otherwise search for a force with the given name. */
  if (!lfound) {
    for (body=System.sysBdy; body; body=body->nxtBdy) {
      for (force=body->bdyFrc; force; force=force->nxtFrc) {
        if (strcmp(force->name, name) == 0) {
          if (force->frcVf) {
            force->frcVf = NULL;
            lprint = TRUE;
          }
          if (!isnanc((void *) &force->f)) {
            ldnanc((void *) &force->f);
            lprint = TRUE;
          }
          if (token[0].kind == TK_REAL) {
            force->f = token[0].data.word;
          } else if (token[0].kind == TK_VALUE) {
            force->frcVf = token[0].data.value;
          }
          lfound = TRUE;
        }
      }
    }
  }
  if (lprint) {
    echoc();
    textc("*** The applied force data for '", FALSE);
    textc(name, FALSE);
    textc("' is redefined. ***", TRUE);
  }
  if (!lfound) {
    echoc();
    textc("*** There is no force or joint named '", FALSE);
    textc(name, FALSE);
    textc("'. ***", TRUE);
    System.nerror = 3;
  }
  return;
}
