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
/* msetc-01 Jan 00:16 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Set the motions for the SGC inputs.
|
|     Access:
|       (void) msetc();
|
|     Error Conditions:
|       A warning message is printed if a Value expression returns an
|     undefined result.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
void msetc()
{
  Joint *joint;
  Jvar  * jvar;
  Sgc   *sgc;
  Value *value;
  int    i, lprint;
  real   time, val[3];

  if (isnanc((void *) &System.t)) {
    time = 0.0;
  } else {
    time = System.t / System.dtio;
  }
  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
    for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
      sgc = jvar->jvrSgc;
      if (sgc) {
        value = sgc->sgcVal;
        if (value) {
          vevalc(value, val);
          lprint = TRUE;
          for (i=0; i<3; i++) {
            if (isnanc((void *) &val[i])) {
              if (lprint) {
                textc("*** The ", FALSE);
                switch (i) {
                case 0:
                  textc("value", FALSE);
                  break;
                case 1:
                  textc("1st derivative", FALSE);
                  break;
                case 2:
                  textc("2nd derivative", FALSE);
                }
                textc(" of '", FALSE);
                textc(value->name, FALSE);
                textc("' is undefined. ***", TRUE);
                lprint = FALSE;
              }
              System.nerror = 0;
            } else {
              switch (i) {
              case 0:
                sgc->pos = val[0];
                break;
              case 1:
                sgc->vel = val[1];
                break;
              case 2:
                sgc->acc = val[2];
              }
            }
          }
        } else {
          sgc->pos = sgc->initpos + sgc->incrpos * time;
        }
        if (!isnanc((void *) &sgc->pos)) jvar->pos = sgc->pos;
        if (System.mode < MD_STAT) {
          if (!isnanc((void *) &sgc->vel)) jvar->vel = sgc->vel;
          if (!isnanc((void *) &sgc->acc)) jvar->acc = sgc->acc;
        }
      }
    }
  }
  return;
}
