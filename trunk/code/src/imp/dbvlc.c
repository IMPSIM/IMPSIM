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
/* dbvlc-01 Jan 00:16 Sep 07:21 Jun 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Store the two cone half-angles for a specified bevel gear joint.
|
|     Access:
|       (void) dbvlc(Word name, real conei, real coneo);
|     Word name, i-Name of the bevel gear joint to be set.
|     real conei,i-Value of the first  gear cone half-angle in degrees.
|     real coneo,i-Value of the second gear cone half-angle in degrees.
|
|     Error Conditions:
|       System.nerror = 3 indicates an undefined bevel gear joint name.
|       System.nerror = 4 indicates a cone half-angle of zero.
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
  void dbvlc(Word name, real conei, real coneo)
#else
  void dbvlc(name, conei, coneo)
  Word name;
  real conei, coneo;
#endif
{
  Joint *joint;
  Jvar  *jvar;

/* Locate the appropriate bevel gear joint. */
  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
    if (strcmp(joint->name, name) == 0) {
      if (joint->jtype == BEVEL) {

/* Test and store the values. */
        if (System.level > 1) System.level = 1;
        if (fabs(conei) < System.dtola) {
          echoc();
          textc("*** First cone-angle of zero is ignored. ***", TRUE);
          System.nerror = 4;
        } else {
          if (!isnanc((void *) &joint->param[0])) {
            echoc();
            textc("*** Joint ", FALSE);
            textc(name, FALSE);
            textc(" first cone half-angle is redefined. ***", TRUE);
          }
          joint->param[0] = conei / System.ascale;
          if (fabs(coneo) < System.dtola) {
            echoc();
            textc("*** Second cone-angle of zero is ignored. ***", TRUE);
            System.nerror = 4;
          } else {
            if (!isnanc((void *) &joint->param[1])) {
              echoc();
              textc("*** Joint ", FALSE);
              textc(name, FALSE);
              textc(" second cone half-angle is redefined. ***", TRUE);
            }
            joint->param[1] = coneo / System.ascale;
          }
          for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
            ldnanc((void *) &(jvar->design));
          }
        }
        return;
      }
    }
  }
  echoc();
  textc("*** There is no bevel gear joint named '", FALSE);
  textc(name, FALSE);
  textc("'. ***", TRUE);
  System.nerror = 3;
  return;
}
