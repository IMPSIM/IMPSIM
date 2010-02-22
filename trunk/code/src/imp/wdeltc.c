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
/* wdeltc-01 Jan 00:15 Mar 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Form the derivative operator for a given body with respect to
|     the n-th virtual deformation in a given joint.
|
|     Access:
|       (void) wdeltc(Body *body, Joint *joint, int n, real W[6]);
|     Body  *body, i-Pointer to the given Body record.
|     Joint *joint,i-Pointer to the given Joint record.
|     int    n,    i-Number of the virtual deformation component.
|     real   W[6], o-Derivative operator for this virtual deformation.
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
  void wdeltc(Body *body, Joint *joint, int n, real W[6])
#else
  void wdeltc(body, joint, n, W)
  Body  *body;
  Joint *joint;
  int    n;
  real   W[6];
#endif
{
  Body  *bdy;
  Joint *jnt;
  Jvar  *jvar;
  int    i;
  real   dphi, D[6];

  for (i=0; i<6; i++) {
    D[i] = 0.0;
    W[i] = 0.0;
  }
  D[n%6] = 1.0;
  xdxinc(joint->jntAxB->S, D, D);
  xdxinc(joint->jntAxB->axsBdy->T0j, D, D);
  if (!isnanc((void *) &System.pd[0][n])) {
    bdy  = body;
    while (bdy != System.ground) {
      jnt = bdy->bdyAxs->axsJnt;
      if (jnt == joint) {
        for (i=0; i<6; i++) {
          W[i] += D[i];
        }
      }
      for (jvar=jnt->jntJvr; jvar; jvar=jvar->nxtJvr) {
        if (jvar->jvrnoS < System.ndep) {
          dphi = System.pd[jvar->jvrnoS][n];
          if (dphi != 0.0) {
            for (i=0; i<6; i++) {
              W[i] += jvar->D[i] * dphi;
            }
          }
        }
      }
      bdy = jnt->jntAxB->axsBdy;
    }
  }
  return;
}
