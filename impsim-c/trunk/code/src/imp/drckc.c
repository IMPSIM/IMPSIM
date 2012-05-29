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
/* drckc-01 Jan 00:20 Jun 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Store the pinion pitch radius and the tooth helix angle for a
|     specified rack joint.
|
|     Access:
|       (void) drckc(Word name, real radius, real helix);
|     Word name,  i-Name of the rack joint to be set.
|     real radius,i-Value of the pinion pitch radius.
|     real helix, i-Value of the tooth helix angle in degrees.
|
|     Error Conditions:
|       System.nerror = 3 indicates an undefined rack joint name.
|       System.nerror = 4 indicates faulty data.
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
  void drckc(Word name, real radius, real helix)
#else
  void drckc(name, radius, helix)
  Word name;
  real radius, helix;
#endif
{
  Joint *joint;
  Jvar  *jvar;

/* Locate the appropriate rack joint. */
  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
    if (strcmp(joint->name, name) == 0) {
      if (joint->jtype == RACK) {

/* Check for degenerate data. */
        if (fabs(radius) < System.dtoll) {
          echoc();
          textc("*** Zero or negative pinion radius not allowed. ***",
            TRUE);
          System.nerror = 4;
          return;
        }

/* Store the values. */
        if (System.level > 1) System.level = 1;
        if (!isnanc((void *) &joint->param[0])) {
          echoc();
          textc("*** Joint ", FALSE);
          textc(name, FALSE);
          textc(" pinion pitch radius is redefined. ***", TRUE);
        }
        joint->param[0] = radius;
        if (!isnanc((void *) &joint->param[1])) {
          echoc();
          textc("*** Joint ", FALSE);
          textc(name, FALSE);
          textc(" pinion helix angle is redefined. ***", TRUE);
        }
        joint->param[1] = helix / System.ascale;
        for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
          ldnanc((void *) &(jvar->design));
        }
        return;
      }
    }
  }
  echoc();
  textc("*** There is no rack joint named '", FALSE);
  textc(name, FALSE);
  textc("'. ***", TRUE);
  System.nerror = 3;
  return;
}
