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
/* dgearc-01 Jan 00:19 Jun 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Store the gear ratio and the center distance for a specified
|     spur gear joint.
|
|     Access:
|       (void) dgearc(Word name, real ratio, real helix, real ctrdist);
|     Word name,i-Name of the spur gear joint to be set.
|     real ratio,i-Value of the gear ratio.
|     real helix,i-Value of the helix angle in degrees.
|     real ctrdist,i-Value of the center to center distance.
|
|     Error Conditions:
|       System.nerror = 3 indicates an undefined spur gear joint name.
|
|     Comments:
|       A warning message is printed when previous data are redefined.
|       System.level <= 1 on successful completion.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void dgearc(Word name, real ratio, real helix, real ctrdist)
#else
  void dgearc(name, ratio, helix, ctrdist)
  Word name;
  real ratio, helix, ctrdist;
#endif
{
  Joint *joint;
  Jvar  *jvar;

/* Locate the appropriate spur gear joint. */
  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
    if (strcmp(joint->name, name) == 0) {
      if (joint->jtype == GEAR) {

/* Store the values. */
        if (System.level > 1) System.level = 1;
        if (!isnanc((void *) &joint->param[0])) {
          echoc();
          textc("*** Joint ", FALSE);
          textc(name, FALSE);
          textc(" gear ratio is redefined. ***", TRUE);
        }
        joint->param[0] = ratio;
        if (!isnanc((void *) &joint->param[1])) {
          echoc();
          textc("*** Joint ", FALSE);
          textc(name, FALSE);
          textc(" helix angle is redefined. ***", TRUE);
        }
        joint->param[1] = helix / System.ascale;
        if (!isnanc((void *) &ctrdist)) {
          if (!isnanc((void *) &joint->param[2])) {
            echoc();
            textc("*** Joint ", FALSE);
            textc(name, FALSE);
            textc(" center distance is redefined. ***", TRUE);
          }
          joint->param[2] = ctrdist;
        }
        for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
          ldnanc((void *) &(jvar->design));
        }
        return;
      }
    }
  }
  echoc();
  textc("*** There is no spur gear joint named '", FALSE);
  textc(name, FALSE);
  textc("'. ***", TRUE);
  System.nerror = 3;
  return;
}
