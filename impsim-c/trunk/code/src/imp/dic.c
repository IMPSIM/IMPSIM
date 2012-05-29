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
/* dic-01 Jan 00:18 Mar 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Define one or more specified joint variables as IC(s) and
|     store the specified descriptions of their initial condition(s).
|
|     Access:
|       (void) dic(Word name, Token token[]);
|     Word name,i-Name of the joint for the IC(s) to be set.
|     Token token[],i-Array of tokens giving IC description(s).
|
|     Error Conditions:
|       System.nerror = 3 indicates an undefined joint name.
|       System.nerror = 4 indicates data ignored for Euler parameters.
|       System.nerror = 5 indicates a conflict in mode.
|
|     Comments:
|       Any previous input motion or IC data for this joint is deleted;
|     a warning message is printed.
*
*     History:
*     01 Jan 00:JJU-Original.
*     12 Mar 09:JJU-Implemented Euler parameters.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void dic(Word name, Token token[])
#else
  void dic(name, token)
  Word  name;
  Token token[];
#endif
{
  Joint *joint;
  Jvar  *jvar;
  Ic    *ic;
  int    i;

/* Check for dynamic mode. */
  if (System.mode != MD_DYN) {
    echoc();
    textc("*** The FIND DYNAMICS statement is missing. ***", TRUE);
    System.nerror = 5;
    return;
  }

/* Locate the appropriate joint. */
  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
    if (strcmp(joint->name, name) == 0) {
      for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
        if (jvar->jvrtyp == JV_EULER) {
          echoc();
          textc("*** DATA IC for joint ", FALSE);
          textc(name, FALSE);
          textc(" are ignored. ***", TRUE);
          System.nerror = 4;
          break;
        }
        if (jvar->jvrSgc) {
          echoc();
          textc("*** Input motion data for joint ", FALSE);
          textc(name, FALSE);
          textc(" are deleted. ***", TRUE);
          free(jvar->jvrSgc);
          jvar->jvrSgc = NULL;
        }
        if (jvar->jvrIc) {
          echoc();
          textc("*** DATA IC for joint ", FALSE);
          textc(name, FALSE);
          textc(" are redefined. ***", TRUE);
          free(jvar->jvrIc);
          jvar->jvrIc = NULL;
        }
        i = jvar->jvrnoJ;
        if (token[2*i].kind == TK_VALUE || token[2*i].kind == TK_REAL) {
          ic = (Ic *) malloc(sizeof(Ic));
          if (ic) {
            jvar->jvrIc = ic;
            ic->type    = IC;
            ic->icJvr   = jvar;
            ic->scale   = 1.0;
            if (jvar->jvrtyp == JV_ANGULAR) ic->scale /= System.ascale;
            ic->icVpos  = NULL;
            ldnanc((void *) &(ic->initpos));
            ic->icVvel  = NULL;
            ldnanc((void *) &(ic->initvel));
          }
        }
        if (token[2*i].kind == TK_VALUE) {
          if (token[2*i].data.value) {/* Test for the case of "none". */
            ic->icVpos = token[2*i].data.value;
          }
        } else if (token[2*i].kind == TK_REAL) {
          ic->initpos  = token[2*i].data.word * ic->scale;
        }
        if (token[2*i+1].kind == TK_VALUE) {
          if (token[2*i+1].data.value) {  /* Test for case of "none". */
            ic->icVvel = token[2*i+1].data.value;
          }
        } else if (token[2*i+1].kind == TK_REAL) {
          ic->initvel = token[2*i+1].data.word;
        }
      }
      if (isnanc((void *) &System.dtmin)) {
        ldnanc((void *) &System.tfinal);
      }
      return;
    }
  }
  echoc();
  textc("*** There is no joint named '", FALSE);
  textc(name, FALSE);
  textc("'. ***", TRUE);
  System.nerror = 3;
  return;
}
