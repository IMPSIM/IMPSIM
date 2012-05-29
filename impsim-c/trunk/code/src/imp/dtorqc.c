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
/* dtorqc-01 Jan 00:19 Mar 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Store the torque amplitude for a previously defined torque or
|     for applied force(s) or torque(s) within a specified joint.
|
|     Access:
|       (void) dtorqc(Word name, Token token[]);
|     Word name,i-Name of the torque or joint to be set.
|     Token token[],i-Array of tokens with the torque value(s).
|
|     Error Conditions:
|       System.nerror = 3 indicates an undefined torque or joint name.
|       System.nerror = 4 indicates torque data for Euler jvars ignored.
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
  void dtorqc(Word name, Token token[])
#else
  void dtorqc(name, token)
  Word  name;
  Token token[];
#endif
{
  Body   *body;
  Joint  *joint;
  Jvar   *jvar;
  Torque *torque;
  int     i, lfound, lprint;

/* Search for a joint with the given name. */
  lfound = FALSE;
  lprint = FALSE;
  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
    if (strcmp(joint->name, name) == 0) {
      for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
        if (jvar->jvrtyp == JV_EULER) {
          echoc();
          textc("*** Applied torque data for '", FALSE);
          textc(name, FALSE);
          textc("' is ignored. ***", TRUE);
          System.nerror = 4;
          break;
        }
        if (jvar->jvrVf) {
          jvar->jvrVf = NULL;
          lprint = TRUE;
        }
        if (jvar->force) {
          ldnanc((void *) &(jvar->force));
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

/* Otherwise search for a torque with the given name. */
  if (!lfound) {
    for (body=System.sysBdy; body; body=body->nxtBdy) {
      for (torque=body->bdyTrq; torque; torque=torque->nxtTrq) {
        if (strcmp(torque->name, name) == 0) {
          if (torque->trqVt) {
            torque->trqVt = NULL;
            lprint = TRUE;
          }
          if (torque->t) {
            ldnanc((void *) &(torque->t));
            lprint = TRUE;
          }
          if (token[0].kind == TK_REAL) {
            torque->t = token[0].data.word;
          } else if (token[0].kind == TK_VALUE) {
            torque->trqVt = token[0].data.value;
          }
          lfound = TRUE;
        }
      }
    }
  }
  if (lprint) {
    echoc();
    textc("*** The applied torque data for '", FALSE);
    textc(name, FALSE);
    textc("' is redefined. ***", TRUE);
  }
  if (!lfound) {
    echoc();
    textc("*** There is no torque or joint named '", FALSE);
    textc(name, FALSE);
    textc("'. ***", TRUE);
    System.nerror = 3;
  }
  return;
}
