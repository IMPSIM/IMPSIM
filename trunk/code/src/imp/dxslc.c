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
/* dxslc-01 Jan 00:15 Sep 07
|    (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Form and store the transformation matrices from the global
|     coordinate system to the local coordinate systems for both sides
|     of an XSLIDE joint.  pt0 is the local origin.
|
|     Access:
|       (void) dxslc(Word name, Token pt0[3]);
|     Word name,i-Name of the XSLIDE joint.
|     Token pt0[3],i-Global coordinate data for pt0, the local origins.
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
  void dxslc(Word name, Token pt0[3])
#else
  void dxslc(name, pt0)
  Word name;
  Token pt0[3];
#endif
{
  Axes  *axesB, *axesA;
  Joint *joint;
  Token  ptX[3], ptY[3];
  int    i;

  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
    if (joint->jtype == XSLIDE) {
      if (strcmp(joint->name, name) == 0) {
        if (joint->orient < 0) {
          axesB = joint->jntAxA;
          axesA = joint->jntAxB;
        } else {
          axesB = joint->jntAxB;
          axesA = joint->jntAxA;
        }
        for (i=0; i<3; i++) {
          ptX[i].kind = pt0[i].kind;
          ptX[i].data.word = pt0[i].data.word;
          ptY[i].kind = pt0[i].kind;
          ptY[i].data.word = pt0[i].data.word;
        }
        ptX[0].data.word += 10.0;
        ptY[1].data.word += 10.0;
        dbodyc(axesB->axsBdy->name, joint->name, pt0, ptX, ptY);
        if (System.nerror) return;
        dbodyc(axesA->axsBdy->name, joint->name, pt0, ptX, ptY);
        return;
      }
    }
  }
  echoc();
  textc("*** There is no xslide joint named ", FALSE);
  textc(name, FALSE);
  textc(". ***", TRUE);
  System.nerror = 3;
  return;
}
