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
/* dyrvc-01 Jan 00:15 Sep 07
|    (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Form and store the transformation matrices from the global
|     coordinate system to the local coordinate systems for both sides
|     of a y-revolute (YPIN) joint.  pt0 is the local origin, and pt1
|     and pt2 are points on the local w and w' axes of the joint,
|     respectively.
|
|     Access:
|       (void) dyrvc(Word name, Token pt0[3], Token pt1[3],
|         Token pt2[3]);
|     Word name,i-Name of the revolute (YPIN) joint.
|     Token pt0[3],i-Global coordinate data for pt0, the local origins.
|     Token pt1[3],i-Global coordinate data for pt1 on local w axis.
|     Token pt2[3],i-Global coordinate data for pt2 on local w' axis.
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
*     20 Feb 07:JJU-Corrected logic error in testing axis size.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void dyrvc(Word name, Token pt0[3], Token pt1[3], Token pt2[3])
#else
  void dyrvc(name, pt0, pt1, pt2)
  Word name;
  Token pt0[3], pt1[3], pt2[3];
#endif
{
  Axes  *axesB, *axesA;
  Joint *joint;
  Token  ptY[3];
  int    i;
  real   dist, size1, size2;

  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
    if (joint->jtype == YPIN) {
      if (strcmp(joint->name, name) == 0) {
        if (joint->orient < 0) {
          axesB = joint->jntAxA;
          axesA = joint->jntAxB;
        } else {
          axesB = joint->jntAxB;
          axesA = joint->jntAxA;
        }
        size1 = 0.0;
        size2 = 0.0;
        for (i=0; i<3; i++) {
          dist = pt1[i].data.word - pt0[i].data.word;
          size1 += dist * dist;
          dist = pt1[i].data.word - pt0[i].data.word;
          size2 += dist * dist;
        }
        size1 = sqrt(size1);
        size2 = sqrt(size2);
        for (i=0; i<3; i++) {
          ptY[i].kind = pt0[i].kind;
          ptY[i].data.word = pt0[i].data.word;
          if (size1 < System.dtoll) pt1[i].data.word = pt0[i].data.word;
          if (size2 < System.dtoll) pt2[i].data.word = pt0[i].data.word;
        }
        ptY[1].data.word += 10.0;
        if (size1 < System.dtoll) pt1[2].data.word += 10.0;
        if (size2 < System.dtoll) pt2[2].data.word += 10.0;
        dbodyc(axesB->axsBdy->name, joint->name, pt0, ptY, pt1);
        if (System.nerror) return;
        dbodyc(axesA->axsBdy->name, joint->name, pt0, ptY, pt2);
        return;
      }
    }
  }
  echoc();
  textc("*** There is no ypin joint named ", FALSE);
  textc(name, FALSE);
  textc(". ***", TRUE);
  System.nerror = 3;
  return;
}
