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
/* icsetc-01 Jan 00:16 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Set the initial conditions controlled by Value expressions.
|
|     Access:
|       (void) icsetc();
|
|     Error Conditions:
|       If a Value expression returns an undefined result, a message is
|     printed.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
void icsetc()
{
  Ic     *ic;
  Joint  *joint;
  Jvar   *jvar;
  Value  *value;
  real    val[3];

  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
    for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
      ic = jvar->jvrIc;
      if (ic) {
        value = ic->icVpos;
        if (value) {
          vevalc(value, val);
          if (isnanc((void *) &val[0])) {
            textc("*** Value(", FALSE);
            textc(value->name, FALSE);
            textc(") is undefined for this position. ***", TRUE);
            ic->initpos = 0.0;
          } else {
            ic->initpos = val[0];
          }
          jvar->pos = ic->initpos;
        }
        value = ic->icVvel;
        if (value) {
          vevalc(value, val);
          if (isnanc((void *) &val[0])) {
            textc("*** Value(", FALSE);
            textc(value->name, FALSE);
            textc(") is undefined for this position. ***", TRUE);
            ic->initvel = 0.0;
          } else {
            ic->initvel = val[0];
          }
          jvar->vel = ic->initvel;
        }
      }
    }
  }
  return;
}
