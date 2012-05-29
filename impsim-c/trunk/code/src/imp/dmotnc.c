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
/* dmotnc-01 Jan 00:18 Mar 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Define one or more specified joint variables as SGC(s) and
|     store the specified descriptions of their input motion(s).
|
|     Access:
|       (void) dmotnc(Word name, Token token[]);
|     Word name,    i-Name of the joint for the SGC(s) to be set.
|     Token token[],i-Array of tokens giving SGC motion description(s).
|
|     Error Conditions:
|       System.nerror = 3 indicates an undefined joint name.
|       System.nerror = 4 indicates Euler parameter jvars ignored.
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
  void dmotnc(Word name, Token token[])
#else
  void dpostc(name, token)
  Word  name;
  Token token[];
#endif
{
  Joint *joint;
  Jvar  *jvar;
  Sgc   *sgc;
  int    i;

/* Locate the appropriate joint. */
  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
    if (strcmp(joint->name, name) == 0) {
      for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
        if (jvar->jvrSgc) {
          echoc();
          textc("*** Input motion for joint ", FALSE);
          textc(name, FALSE);
          textc(" ", FALSE);
          itextc(jvar->jvrnoJ+1);
          textc(" is redefined. ***", TRUE);
          free(jvar->jvrSgc);
          jvar->jvrSgc = NULL;
        }
        if (jvar->jvrIc) {
          echoc();
          textc("*** DATA IC for joint ", FALSE);
          textc(name, FALSE);
          textc(" is deleted. ***", TRUE);
          free(jvar->jvrIc);
          jvar->jvrIc = NULL;
        }
        if (jvar->jvrtyp == JV_EULER) {
          echoc();
          textc("*** Input motions for joint ", FALSE);
          textc(name, FALSE);
          textc(" ", FALSE);
          itextc(jvar->jvrnoJ+1);
          textc(" etc. are ignored. ***", TRUE);
          System.nerror = 4;
          break;
        }
        i = jvar->jvrnoJ;
        if (token[i].kind == TK_VALUE) {
          if (token[i].data.value) {
            sgc = (Sgc *) malloc(sizeof(Sgc));
            if (sgc) {
              jvar->jvrSgc = sgc;
              sgc->type    = SGC;
              sgc->sgcJvr  = jvar;
              sgc->sgcVal  = token[i].data.value;
              ldnanc((void *) &(sgc->incrnum));
              ldnanc((void *) &(sgc->incrpos));
              ldnanc((void *) &(sgc->initpos));
              sgc->scale   = 1.0;
              if (jvar->jvrtyp == JV_ANGULAR) 
                sgc->scale /= System.ascale;
              ldnanc((void *) &(sgc->pos));
              sgc->vel = 0.0;
              sgc->acc = 0.0;
            }
          } else {
            jvar->jvrSgc = NULL;       /* This is the case of "none". */
          }
        } else if (token[i].kind == TK_REAL) {
          sgc = (Sgc *) malloc(sizeof(Sgc));
          if (sgc) {
            jvar->jvrSgc = sgc;
            sgc->type    = SGC;
            sgc->sgcJvr  = jvar;
            sgc->sgcVal  = NULL;
            sgc->incrnum = 0;
            sgc->incrpos = 0.0;
            sgc->initpos = token[i].data.word;
            sgc->scale   = 1.0;
            if (jvar->jvrtyp == JV_ANGULAR) {
              sgc->initpos /= System.ascale;
              sgc->scale   /= System.ascale;
            }
            ldnanc((void *) &(sgc->pos));
            sgc->vel = 0.0;
            sgc->acc = 0.0;
          }
        }
        if (System.mode < MD_GEO) System.mode = MD_GEO;
        if (isnanc((void *) &System.dtmin)) {
          ldnanc((void *) &System.tfinal);
        }
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
