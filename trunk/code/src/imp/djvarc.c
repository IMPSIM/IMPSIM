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
/* djvarc-01 Jan 00:16 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Store the initial estimates of the positions of the joint
|     variables of a specified joint at the design position.
|
|     Access:
|       (void) djvarc(Word name, Token values[]);
|     Word name,i-Name of the joint for the jvar estimates to be set.
|     Token values[],i-Estimates of the joint variable values.
|
|     Error Conditions:
|       System.nerror = 3 indicates an undefined joint name.
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
  void djvarc(Word name, Token values[])
#else
  void djvarc(name, values)
  Word  name;
  Token values[];
#endif
{
  Joint *joint;
  Jvar  *jvar;
  int    flag;

  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
    if (strcmp(joint->name, name) == 0) {
      flag = FALSE;
      for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
        if (!isnanc((void *) &jvar->design)) {
          flag = TRUE;
        }
        jvar->design = values[jvar->jvrnoJ].data.word;
        if (jvar->jvrtyp == JV_ANGULAR) jvar->design /= System.ascale;
      }
      if (flag) {
        echoc();
        textc("*** The estimates for joint '", FALSE);
        textc(name, FALSE);
        textc("' variables are redefined. ***", TRUE);
      }
      if (System.level > 2) System.level = 2;
      return;
    }
  }
  echoc();
  textc("*** There is no joint named '", FALSE);
  textc(name, FALSE);
  textc("'. ***", TRUE);
  System.nerror = 3;
  return;
}
