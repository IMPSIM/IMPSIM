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
/* xdync-01 Jan 00:16 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Delete all motion inputs and ic's, unset all time parameters,
|     and set the System.mode flag to MD_UNDEF.
|
|     Access:
|       (void) xdync();
|
|     Error Conditions:
|       System.nerror = 5 indicates that the System.mode flag is not
|     currently set to MD_DYN.  A message is printed.
|
|     Comments:
|       System.mode = MD_UNDEF and System.level <= 3 on successful
|     completion.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
void xdync()
{
  Joint *joint;
  Jvar  *jvar;

  if (System.mode == MD_DYN) {
    for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
      for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
        if (jvar->jvrSgc) xsgc(jvar->jvrSgc);
        if (jvar->jvrIc) xic(jvar->jvrIc);
      }
    }
    ldnanc((void *) &(System.tprev));
    ldnanc((void *) &(System.t));
    ldnanc((void *) &(System.tnxtio));
    ldnanc((void *) &(System.tfinal));
    ldnanc((void *) &(System.dt));
    ldnanc((void *) &(System.dtmin));
    ldnanc((void *) &(System.dtmax));
    ldnanc((void *) &(System.dtio));
    System.mode = MD_UNDEF;
    if (System.level > 3) System.level = 3;
  } else {
    echoc();
    textc("*** Dynamic mode is not defined. ***", TRUE);
    System.nerror = 5;
  }
  return;
}
