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
/* ddaldc-01 Jan 00:29 Jun 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Form the contribution of a specified joint variable to the der-
|     ivative of a specified D operator with respect to a generalized
|     coordinate.
|
|     Access:
|       (void) ddaldc(Jvar *jvar, real W[6], real dphi, real dD[6]);
|     Jvar *jvar,i-Pointer to the j joint variable record.
|     real W[6], i-W operator for this derivative.
|     real dphi, i-derivative of the generalized coordinate.
|     real dD[6],o-Resulting derivative operator increment.
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
  void ddaldc(Jvar *jvar, real W[6], real dphi, real dD[6])
#else
  void ddaldc(jvar, W, dphi, dD)
  Jvar *jvar;
  real  W[6], dphi, dD[6];
#endif
{
  Axes    *axbfr;
  Joint   *joint;
  Jvar    *jv;
  complex *coeff;
  int      i, n;
  real     ampy, dph, dq[6], dQ[6], du, dv, ddu, ddv, phi[7], phimax,
    phimin, u, v;

  dD[0] = W[4] * jvar->D[2] - jvar->D[4] * W[2]
        + W[1] * jvar->D[5] - jvar->D[1] * W[5];
  dD[1] = W[5] * jvar->D[0] - jvar->D[5] * W[0]
        + W[2] * jvar->D[3] - jvar->D[2] * W[3];
  dD[2] = W[3] * jvar->D[1] - jvar->D[3] * W[1]
        + W[0] * jvar->D[4] - jvar->D[0] * W[4];
  dD[3] = W[4] * jvar->D[5] - jvar->D[4] * W[5];
  dD[4] = W[5] * jvar->D[3] - jvar->D[5] * W[3];
  dD[5] = W[3] * jvar->D[4] - jvar->D[3] * W[4];
  if (dphi == 0.0) return;
  joint = jvar->jvrJnt;
  switch (joint->jtype) {
  case SPHERE:
    for (jv=joint->jntJvr; jv; jv=jv->nxtJvr) {
      dqsphc(jvar->jvrnoJ, jv->jvrnoJ, dq);
      ampy = jv->vel;
      if (ampy != 0.0) {
        for (i=0; i<6; i++) dQ[i] += dq[i] * ampy;
      }
    }
    break;
  case OPEN:
    for (jv=joint->jntJvr; jv; jv=jv->nxtJvr) {
      dqopnc(jvar->jvrnoJ, jv->jvrnoJ, dq);
      ampy = jv->vel;
      if (ampy != 0.0) {
        for (i=0; i<6; i++) dQ[i] += dq[i] * ampy;
      }
    }
    break;
  case GEAR:
    for (jv=joint->jntJvr; jv; jv=jv->nxtJvr) {phi[jv->jvrnoJ]=jv->pos;}
    for (jv=joint->jntJvr; jv; jv=jv->nxtJvr) {
      dqgerc(jvar->jvrnoJ, jv->jvrnoJ, phi, joint->param[0],
        joint->param[1], joint->param[2], dQ);
      ampy = jv->vel;
      if (ampy != 0.0) {
        for (i=0; i<6; i++) dQ[i] += dq[i] * ampy;
      }
    }
    break;
  case RACK:
    for (jv=joint->jntJvr; jv; jv=jv->nxtJvr) {
      dqrckc(jvar->jvrnoJ, jv->jvrnoJ, joint->param[0], joint->param[1],
        dQ);
      ampy = jv->vel;
      if (ampy != 0.0) {
        for (i=0; i<6; i++) dQ[i] += dq[i] * ampy;
      }
    }
    break;
  case BEVEL:
    for (jv=joint->jntJvr; jv; jv=jv->nxtJvr) {phi[jv->jvrnoJ]=jv->pos;}
    for (jv=joint->jntJvr; jv; jv=jv->nxtJvr) {
      dqbvlc(jvar->jvrnoJ, jv->jvrnoJ, phi, joint->param[0],
        joint->param[1], dQ);
      ampy = jv->vel;
      if (ampy != 0.0) {
        for (i=0; i<6; i++) dQ[i] += dq[i] * ampy;
      }
    }
    break;
  case CAM:
    for (jv=joint->jntJvr; jv; jv=jv->nxtJvr) {phi[jv->jvrnoJ]=jv->pos;}
    coeff  = (complex *) jvar->jvrVup->arg[1];
    n      = nint((real) coeff[0].r) / 2;
    phimin = (real) coeff[1].r;
    phimax = (real) coeff[1].i;
    fservc(phi[0], phimin, phimax, &coeff[2], n, &u, &du, &ddu);
    coeff  = (complex *) jvar->jvrVvp->arg[1];
    n      = nint((real) coeff[0].r) / 2;
    phimin = (real) coeff[1].r;
    phimax = (real) coeff[1].i;
    fservc(phi[0], phimin, phimax, &coeff[2], n, &v, &dv, &ddv);
    for (jv=joint->jntJvr; jv; jv=jv->nxtJvr) {
      dqcamc(jvar->jvrnoJ, jv->jvrnoJ, phi, u, v, du, dv, ddu, ddv, dq);
      ampy = jv->vel;
      if (ampy != 0.0) {
        for (i=0; i<6; i++) dQ[i] += dq[i] * ampy;
      }
    }
    break;
  case SLOT:
    jvar = joint->jntJvr;
    coeff  = (complex *) jvar->jvrVup->arg[1];
    n      = nint((real) coeff[0].r) / 2;
    phimin = (real) coeff[1].r;
    phimax = (real) coeff[1].i;
    fservc(jvar->pos, phimin, phimax, &coeff[2], n, &u, &du, &ddu);
    coeff  = (complex *) jvar->jvrVvp->arg[1];
    n      = nint((real) coeff[0].r) / 2;
    phimin = (real) coeff[1].r;
    phimax = (real) coeff[1].i;
    fservc(jvar->pos, phimin, phimax, &coeff[2], n, &v, &dv, &ddv);
    for (jv=joint->jntJvr; jv; jv=jv->nxtJvr) {
      dqsltc(jvar->jvrnoJ, jv->jvrnoJ, u, v, du, dv, ddu, ddv, dq);
      ampy = jv->vel;
      if (ampy != 0.0) {
        for (i=0; i<6; i++) dQ[i] += dq[i] * ampy;
      }
    }
    break;
  default:
    return;
  }
  if (joint->orient < 0) {
    dph = -dphi;
    xdxinc(joint->Phi, dQ, dQ);
  } else {
    dph = dphi;
  }
  axbfr = joint->jntAxB;
  xdxinc(axbfr->S, dQ, dQ);
  xdxinc(axbfr->axsBdy->T0j, dQ, dQ);
  for (i=0; i<6; i++) {
    dD[i] += dph * dQ[i];
  }
  return;
}
