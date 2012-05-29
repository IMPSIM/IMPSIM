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
/* wmatc-01 Jan 00:16 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Form the derivative operator for a specified body with respect
|     to a designated generalized coordinate.
|
|     Access:
|       (void) wmatc(Body *body, int kgc, real wmat[6]);
|     Body *body,  i-Pointer to the specified body record.
|     int kgc,     i-Number of the generalized coordinate specified.
|     real wmat[6],o-Derivative operator found.
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
  void wmatc(Body *body, int kgc, real wmat[6])
#else
  void wmatc(body, kgc, wmat)
  Body *body;
  int   kgc;
  real  wmat[6];
#endif
{
  Body  *bdy;
  Joint *joint;
  Jvar  *jvar;
  int    i;
  real   deriv;

  for (i=0; i<6; i++) {
    wmat[i] = 0.0;
  }
  for (bdy=body; bdy!=System.ground; bdy=joint->jntAxB->axsBdy) {
    joint = bdy->bdyAxs->axsJnt;
    for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
      if (jvar->jvrnoS < System.ndep) {
        deriv = System.d1[jvar->jvrnoS][kgc];
        if (deriv != 0.0) {
          for (i=0; i<6; i++) {
            wmat[i] += deriv * jvar->D[i];
          }
        }
      } else if (jvar->jvrnoS == System.ndep + kgc) {
        for (i=0; i<6; i++) {
          wmat[i] += jvar->D[i];
        }
      }
    }
  }
  return;
}
