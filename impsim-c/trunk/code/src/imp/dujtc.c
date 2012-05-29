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
/* dujtc-01 Jan 00:15 Sep 07
|    (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Form and store the transformation matrices from the global
|     coordinate system to the local coordinate systems for both sides
|     of a universal (UJOINT) joint.  pt0 is the local origin, pt1 is
|     a point on the first local pin axis, and pt2 is a point on the
|     second local pin axis of the joint.
|
|     Access:
|       (void) dujtc(Word name, Token pt0[3],Token pt1[3],Token pt2[3]);
|     Word name,i-Name of the universal (UJOINT) joint.
|     Token pt0[3],i-Global coordinate data for pt0, the local origins.
|     Token pt1[3],i-Global coordinate data for pt1 on the w axis.
|     Token pt2[3],i-Global coordinate data for pt2 on the w' axis.
|
|     Error Conditions:
|       System.nerror = 3 indicates an unrecognized or improper joint.
|       System.nerror = 4 indicates missing or faulty data.
|
|     Comments:
|       A warning message is printed when previous data are replaced.
|       System.level <= 1 on successful completion.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void dujtc(Word name, Token pt0[3], Token pt1[3], Token pt2[3])
#else
  void dujtc(name, pt0, pt1, pt2)
  Word name;
  Token pt0[3], pt1[3], pt2[3];
#endif
{
  Axes  *axesB, *axesA;
  Joint *joint;
  Token  ptX[3];
  real   v10[3], v20[3], vec[3];
  int    i;

  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
    if (joint->jtype == UJOINT) {
      if (strcmp(joint->name, name) == 0) {
        if (joint->orient < 0) {
          axesB = joint->jntAxA;
          axesA = joint->jntAxB;
        } else {
          axesB = joint->jntAxB;
          axesA = joint->jntAxA;
        }
        for (i=0; i<3; i++) {
          v10[i] = pt1[i].data.word - pt0[i].data.word;
          v20[i] = pt2[i].data.word - pt0[i].data.word;
        }
        vcrosc(v10, v20, vec);
        for (i=0; i<3; i++) {
          ptX[i].kind = pt0[i].kind;
          ptX[i].data.word = pt0[i].data.word + vec[i];
        }
        dbodyc(axesB->axsBdy->name, joint->name, pt0, pt1, ptX);
        if (System.nerror) return;
        dbodyc(axesA->axsBdy->name, joint->name, pt0, pt2, ptX);
        return;
      }
    }
  }
  echoc();
  textc("*** There is no ujoint named ", FALSE);
  textc(name, FALSE);
  textc(". ***", TRUE);
  System.nerror = 3;
  return;
}
