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
/* dacc-01 Jan 00:16 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Store the acceleration of an SGC and set System.mode to MD_KIN.
|
|     Access:
|       (void) dacc(Word name, real accel);
|     Word name,i-Name of the joint for the SGC to be set.
|     real accel,i-Value of the input acceleration.
|
|     Error Conditions:
|       System.nerror = 3 indicates an undefined SGC joint name.
|       System.nerror = 5 indicates a conflict in mode.
|
|     Comments:
|       A warning message is printed when previous data are replaced.
|       System.mode = MD_KIN on successful completion.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void dacc(Word name, real accel)
#else
  void dacc(name, accel)
  Word name;
  real accel;
#endif
{
  Joint *joint;
  Jvar  *jvar;
  Sgc   *sgc;

  if (System.mode > MD_KIN) {
    echoc();
    textc("*** Not allowed in static or dynamic mode. ***", TRUE);
    System.nerror = 5;
  } else {
    for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
      if (strcmp(joint->name, name) == 0) {
        for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
          sgc = jvar->jvrSgc;
          if (sgc) {
            if (sgc->acc != 0.0) {
              echoc();
              textc("*** The data for SGC in joint '", FALSE);
              textc(name, FALSE);
              textc("' are redefined. ***", TRUE);
            }
            sgc->acc = accel;
            System.mode = MD_KIN;
            return;
          }
        }
        echoc();
        textc("*** There is no SGC joint named '", FALSE);
        textc(name, FALSE);
        textc("'. ***", TRUE);
        System.nerror = 3;
        return;
      }
    }
    echoc();
    textc("*** There is no joint named '", FALSE);
    textc(name, FALSE);
    textc("'. ***", TRUE);
    System.nerror = 3;
  }
  return;
}
