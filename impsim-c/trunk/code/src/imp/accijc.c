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
/* accijc-01 Jan 00:14 Jun 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Form the second derivative operator for a specified body with
|     respect to a specified pair of generalized coordinates.
|
|     Access:
|       (void) accijc(Body *body, int kgc1, int kgc2, real A[6]);
|     Body *body,i-Pointer to the specified body record.
|     int   kgc1,i-Number of first  specified generalized coordinate.
|     int   kgc2,i-Number of second specified generalized coordinate.
|     real  A[6],o-Second derivative operator found.
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
  void accijc(Body *body, int kgc1, int kgc2, real A[6])
#else
  void accijc(body, kgc1, kgc2, A)
  Body *body;
  int   kgc1, kgc2;
  real  A[6];
#endif
{
  Body  *bdy;
  Joint *joint;
  Jvar  *jvar;
  int    i, jv, njvar, noJ;
  real   ampy0, ampy1, ampy2, dD[6], W[6];

  if (System.level < 9) sdervc();
  for (i=0; i<6; i++) {
    A[i] = 0.0;
  }
  for (bdy=body; bdy!=System.ground; bdy=joint->jntAxB->axsBdy) {
    wmatc(bdy, kgc2, W);
    joint = bdy->bdyAxs->axsJnt;
    for (jv=0; jv<joint->njvars; jv++) {
      jvar = joint->jntJvr;
      noJ  = (joint->orient < 0) ? (joint->njvars-1-jv) : jv;
      while (jvar->jvrnoJ != noJ) jvar = jvar->nxtJvr;
      njvar = jvar->jvrnoS;
      if (njvar < System.ndep) {
        ampy0 = System.d2[njvar][kgc1][kgc2];
        if (ampy0 != 0.0) {
          for (i=0; i<6; i++) {
            A[i] += jvar->D[i] * ampy0;
          }
        }
        ampy1 = System.d1[njvar][kgc1];
        ampy2 = System.d1[njvar][kgc2];
      } else if (njvar == System.ndep + kgc1) {
        ampy1 = 1.0;
        ampy2 = 0.0;
      } else if (njvar == System.ndep + kgc2) {
        ampy1 = 0.0;
        ampy2 = 1.0;
      } else {
        ampy1 = 0.0;
        ampy2 = 0.0;
      }
      if (ampy1 != 0.0) {
        ddmatc(jvar, W, kgc2, dD);
        for (i=0; i<6; i++) {
          A[i] += dD[i] * ampy1;
        }
      }
      if (ampy2 != 0.0) {
        for (i=0; i<6; i++) {
          W[i] += jvar->D[i] * ampy2;
        }
      }
    }
  }
  return;
}
