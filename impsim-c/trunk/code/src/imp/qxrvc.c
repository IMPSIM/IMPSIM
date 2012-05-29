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
/* qxrvc-01 Jan 00:10 Mar09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Form the derivative operator for an X-revolute joint.
|
|     Access:
|       (void) qxrvc(real Q[6]);
|     real Q[6],o-Derivative operator for the joint.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void qxrvc(real Q[6])
#else
  void qxrvc(Q)
  real Q[6];
#endif
{
  int i;

  for (i=0; i<6; i++) {
    Q[i] = 0.0;
  }
  Q[3] = 1.0;
  return;
}
