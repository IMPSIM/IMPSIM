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
/* tgtojc-01 Jan 00:15 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Form the transformation matices from the global coordinate 
|     system to each body coordinate system.
|
|     Access:
|       (void) tgtojc();
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
void tgtojc()
{
  Axes  *axesa, *axesb;
  Body  *bodya, *bodyb;
  Joint *joint;
  int    change, done;

/* Mark all T0j matrices invalid except that for the ground body. */
  for (bodya=System.sysBdy; bodya; bodya=bodya->nxtBdy) {
    if (bodya != System.ground) ldnanc((void *) &bodya->T0j[0][0]);
  }

/* Form the new T0j matrices. */
  do {
    change = FALSE;
    done   = TRUE;
    for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
      axesa = joint->jntAxA;
      bodya = axesa->axsBdy;
      if (isnanc((void *) &bodya->T0j[0][0])) {
        axesb = joint->jntAxB;
        bodyb = axesb->axsBdy;
        if (isnanc((void *) &bodyb->T0j[0][0])) {
          done = FALSE;
        } else {
          invxc (axesa->S,   bodya->T0j);
          mpyxxc(joint->Phi, bodya->T0j, bodya->T0j);
          mpyxxc(axesb->S,   bodya->T0j, bodya->T0j);
          mpyxxc(bodyb->T0j, bodya->T0j, bodya->T0j);
          change = TRUE;
        }
      }
    }
  } while (change);
  if (!done) {
    textc("*** Missing transformations in tgtojc. ***", TRUE);
    abortc();
  }
  return;
}
