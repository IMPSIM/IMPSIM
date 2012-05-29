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
/* drevc-01 Jan 00:15 Sep 07
|    (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Form and store the transformation matrices from the global
|     coordinate system to the local coordinate systems for both sides
|     of a revolute (ZPIN) joint.  pt0 is the local origin, pt1 is a
|     point on the local w and w' axes, and pt2 and pt3 are points on
|     the local u and u' axes of the joint, respectively.
|
|     Access:
|       (void) drevc(Word name, Token pt0[3], Token pt1[3],
|         Token pt2[3], Token pt3[3]);
|     Word name,i-Name of the revolute (ZPIN) joint.
|     Token pt0[3],i-Global coordinate data for pt0, the local origins.
|     Token pt1[3],i-Global coordinate data for pt1 on local w and w'.
|     Token pt2[3],i-Global coordinate data for pt2 on local u axis.
|     Token pt3[3],i-Global coordinate data for pt3 on local u' axis.
|
|     Error Conditions:
|       System.nerror = 3 indicates an unrecognized or improper joint.
|       System.nerror = 4 indicates missing or faulty data.
|
|     Comments:
|       System.level <= 1 on successful completion.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void drevc(Word name, Token pt0[3], Token pt1[3], Token pt2[3],
    Token pt3[3])
#else
  void drevc(name, pt0, pt1, pt2, pt3)
  Word name;
  Token pt0[3], pt1[3], pt2[3], pt3[3];
#endif
{
  Axes  *axesB, *axesA;
  Joint *joint;

  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
    if (joint->jtype == ZPIN) {
      if (strcmp(joint->name, name) == 0) {
        if (joint->orient < 0) {
          axesB = joint->jntAxA;
          axesA = joint->jntAxB;
        } else {
          axesB = joint->jntAxB;
          axesA = joint->jntAxA;
        }
        dbodyc(axesB->axsBdy->name, joint->name, pt0, pt1, pt2);
        if (System.nerror) return;
        dbodyc(axesA->axsBdy->name, joint->name, pt0, pt1, pt3);
        return;
      }
    }
  }
  echoc();
  textc("*** There is no revolute or zpin joint named ", FALSE);
  textc(name, FALSE);
  textc(". ***", TRUE);
  System.nerror = 3;
  return;
}
