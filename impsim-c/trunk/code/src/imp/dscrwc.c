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
/* dscrwc-01 Jan 00:15 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Store the lead of the thread for a specified screw joint.
|
|     Access:
|       (void) dscrwc(Word name, real advnc);
|     Word name,i-Name of the spur gear joint to be set.
|     real advnc,i-Value of the lead of the screw thread.
|
|     Error Conditions:
|       System.nerror = 3 indicates an undefined screw joint name.
|       System.nerror = 4 indicates a zero lead.
|
|     Comments:
|       A warning message is printed when previous data are redefined.
|       System.level <= 2 on successful completion.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void dscrwc(Word name, real advnc)
#else
  void dscrwc(name, advnc)
  Word name;
  real advnc;
#endif
{
  Joint *joint;
  Jvar  *jvar;

/* Locate the appropriate screw joint. */
  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
    if (strcmp(joint->name, name) == 0) {
      if (joint->jtype == SCREW) {

/* Validate and store the data. */
        if (advnc > System.dtoll) {
          if (!isnanc((void *) &joint->param[0])) {
            echoc();
            textc("*** The lead for screw joint ", FALSE);
            textc(name, FALSE);
            textc(" is redefined. ***", TRUE);
          }
          joint->param[0] = advnc / (2.0 * PI);
          jvar = joint->jntJvr;
          ldnanc((void *) &(jvar->design));
          if (System.level > 2) System.level = 2;
        } else {
          echoc();
          textc("*** Zero lead is not allowed for a screw joint. ***",
            TRUE);
          System.nerror = 4;
        }
        return;
      }
    }
  }
  echoc();
  textc("*** There is no screw joint named '", FALSE);
  textc(name, FALSE);
  textc("'. ***", TRUE);
  System.nerror = 3;
  return;
}
