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
/* dsetc-01 Jan 00:17 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Set the damping coefficients controlled by Value expressions.
|
|     Access:
|       (void) dsetc();
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
void dsetc()
{
  Damper *damper;
  Joint  *joint;
  Jvar   *jvar;
  Value  *value;
  real    val[3];

  vzeroc(F_FORCE);
  for (damper=System.sysDmp; damper; damper=damper->nxtDmp) {
    value = damper->dmpVc;
    if (value) {
      vevalc(value, val);
      if (isnanc((void *) &val[0])) {
        damper->c = 0.0;
      } else {
        damper->c = val[0];
      }
    }
  }
  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
    for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
      value = jvar->jvrVc;
      if (value) {
        vevalc(value, val);
        if (isnanc((void *) &val[0])) {
          jvar->c = 0.0;
        } else {
          jvar->c = val[0];
        }
      }
    }
  }
  return;
}
