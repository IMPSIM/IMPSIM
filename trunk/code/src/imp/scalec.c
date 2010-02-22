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
/* scalec-01 Jan 00:15 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Set the internal length scale factor such that the length of the
|     longest body scales to the order of unity, as do angular values.
|
|     Access:
|       (void) scalec();
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The purpose of this internal scaling is to control convergence
|     of the iterative position analysis and to make it less sensitive
|     to the length units used or the size of the system modeled or to
|     the internal accuracy of the host computer system.
|       Internal length unit scaling is only in effect until convergence
|     has been achieved for the iterative position analysis.  The final
|     iteration sets length units back to user dimensional units.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
void scalec()
{
  Axes  *axesA, *axesB;
  Joint *joint;
  int    i;
  real   sizea, sizeb;

  System.lscale = System.dtoll;
  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
    axesB = joint->jntAxB;
    sizeb = 0.0;
    axesA = joint->jntAxA;
    sizea = 0.0;
    for (i=0; i<3; i++) {
      sizeb += axesB->S[i][3] * axesB->S[i][3];
      sizea += axesA->S[i][3] * axesA->S[i][3];
    }
    sizeb = sqrt(sizeb);
    System.lscale = max(System.lscale, sizeb);
    sizea = sqrt(sizea);
    System.lscale = max(System.lscale, sizea);
  }
  return;
}
