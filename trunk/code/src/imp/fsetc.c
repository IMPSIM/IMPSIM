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
/* fsetc-01 Jan 00:17 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Set the magnitudes of the applied forces controlled by Value
|     expressions.
|
|     Access:
|       (void) fsetc();
|
|     Error Conditions:
|       None.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
void fsetc()
{
  Body   *body;
  Force  *force;
  Joint  *joint;
  Jvar   *jvar;
  Torque *torque;
  Value  *value;
  real    val[3];

  vzeroc(F_FORCE);
  for (body=System.sysBdy; body; body=body->nxtBdy) {
    for (force=body->bdyFrc; force; force=force->nxtFrc) {
      value = force->frcVf;
      if (value) {
        vevalc(value, val);
        if (isnanc((void *) &val[0])) {
          force->f = 0.0;
        } else {
          force->f = val[0];
        }
      }
    }
    for (torque=body->bdyTrq; torque; torque=torque->nxtTrq) {
      value = torque->trqVt;
      if (value) {
        vevalc(value, val);
        if (isnanc((void *) &val[0])) {
          torque->t = 0.0;
        } else {
          torque->t = val[0];
        }
      }
    }
  }
  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
    for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
      value = jvar->jvrVf;
      if (value) {
        vevalc(value, val);
        if (isnanc((void *) &val[0])) {
          jvar->force = 0.0;
        } else {
          jvar->force = val[0];
        }
      }
    }
  }
  return;
}
