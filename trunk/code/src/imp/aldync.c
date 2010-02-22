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
/* aldync-01 Jan 00:15 Jun 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Form the modified acceleration operator for a specified body for
|     calculating the generalized inertia forces.
|
|     Access:
|       (void) aldync(Body *body, real phi2dot[], real A[6]);
|     Body *body,          i-Pointer to the specified body record.
|     real phi2dot[njvars],i-Array of special jvar second derivatives.
|     real A[6],           o-Derivative operator found.
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
  void aldync(Body *body, real phi2dot[], real A[6])
#else
  void accijc(body, phi2dot, A)
  Body *body;
  real  phi2dot[], A[6];
#endif
{
  Body  *bdbfr, *bdy;
  Joint *joint;
  Jvar  *jvar;
  int    i, jv, njvar, noJ;
  real   ampy, dD[6], W[6];

  if (System.level < 8) velc();
  for (i=0; i<6; i++) {
    A[i] = 0.0;
  }
  for (bdy=body; bdy!=System.ground; bdy=bdbfr) {
    joint = bdy->bdyAxs->axsJnt;
    bdbfr = joint->jntAxB->axsBdy;
    for (i=0; i<6; i++) {
      W[i] = bdbfr->W[i];
    }
    for (jv=0; jv<joint->njvars; jv++) {
      jvar = joint->jntJvr;
      noJ  = (joint->orient < 0) ? (joint->njvars-1-jv) : jv;
      while (jvar->jvrnoJ != noJ) jvar = jvar->nxtJvr;
      njvar = jvar->jvrnoS;
      ampy = phi2dot[njvar];
      if (ampy != 0.0) {
        for (i=0; i<6; i++) {
          A[i] += jvar->D[i] * ampy;
        }
      }
      ampy = jvar->vel;
      if (ampy != 0.0) {
        ddaldc(jvar, W, ampy, dD);
        for (i=0; i<6; i++) {
          W[i] += jvar->D[i] * ampy;
          A[i] +=      dD[i] * ampy;
        }
      }
    }
  }
  return;
}
