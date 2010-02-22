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
/* dsltc-01 Jan 00:25 Jun 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Store a pointer to the pitch curve for a specified SLOT joint.
|
|     Access:
|       (void) dsltc(Word name, Token curveu, Token curvev);
|     Word name,i-Name of the SLOT joint to be set.
|     Token curveu,i-Token pointing to the pitch curve u Value record.
|     Token curvev,i-Token pointing to the pitch curve v Value record.
|
|     Error Conditions:
|       System.nerror = 3 indicates an undefined SLOT joint name.
|       System.nerror = 4 indicates missing or faulty data.
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
  void dsltc(Word name, Token curveu, Token curvev)
#else
  void dsltc(name, curveu, curvev)
  Word  name;
  Token curve, curvev;
#endif
{
  Joint *joint;
  Jvar  *jvar;

/* Locate the appropriate SLOT joint. */
  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
    if (joint->jtype == SLOT) {
      if (strcmp(joint->name, name) == 0) {
        jvar = joint->jntJvr;

/* Check the Value functions. */
        if (curveu.kind == TK_VALUE) {
          if (curvev.kind == TK_VALUE) {

/* Store the data. */
            if (System.level > 1) System.level = 1;
            if (jvar->jvrVup) {
              echoc();
              textc("*** Joint ", FALSE);
              textc(name, FALSE);
              textc(" slot shape is redefined. ***", TRUE);
            }
            jvar->jvrVup = curveu.data.value;
            jvar->jvrVvp = curvev.data.value;
            ldnanc((void *) &(jvar->design));

/* Print error messages. */
          } else {
            echoc();
            textc("*** This statement must reference VALUe names. ***",
              TRUE);
            System.nerror = 4;
          }
        } else {
          echoc();
          textc("*** This statement must reference VALUe names. ***",
            TRUE);
          System.nerror = 4;
        }
        return;
      }
    }
  }
  echoc();
  textc("*** There is no SLOT joint named '", FALSE);
  textc(name, FALSE);
  textc("'. ***", TRUE);
  System.nerror = 3;
  return;
}
