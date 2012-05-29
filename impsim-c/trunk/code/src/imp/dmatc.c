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
/* dmatc-01 Jan 00:20 Jun 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Form the derivative operators for all joint variables.
|
|     Access:
|       (void) dmatc();
|
|     Error Conditions:
|       None.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
*     10 Mar 09:JJU-Implemented Euler parameters.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
void dmatc()
{
  Joint   *joint;
  Jvar    *jvar;
  Value   *value;
  int      i, n;
  complex *coeff;
  real     ddu, ddv, du, dv, phi[7], phimin, phimax, Q[6], u, v;

/* Loop through the joints. */
  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {

/* Gather the joint variable values. */
    for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
      phi[jvar->jvrnoJ] = jvar->pos;
    }

/* Form the derivative operator for each joint variable. */
    for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
      switch (joint->jtype) {
      case XPIN:
        qxrvc(Q);
        break;
      case YPIN:
        qyrvc(Q);
        break;
      case ZPIN:
        qzrvc(Q);
        break;
      case XSLIDE:
        qxprc(Q);
        break;
      case YSLIDE:
        qyprc(Q);
        break;
      case ZSLIDE:
        qzprc(Q);
        break;
      case SCREW:
        qscrc(joint->param[0], Q);
        break;
      case GEAR:
        qgerc(jvar->jvrnoJ, phi, joint->param[0], joint->param[1],
          joint->param[2], Q);
        break;
      case RACK:
        qrckc(jvar->jvrnoJ, phi, joint->param[0], joint->param[1], Q);
        break;
      case BEVEL:
        qbvlc(phi[0], joint->param[0], joint->param[1], Q);
        break;
      case CYLINDER:
        qcylc(jvar->jvrnoJ, Q);
        break;
      case UJOINT:
        qujtc(jvar->jvrnoJ, phi, Q);
        break;
      case CAM:
        if (jvar->jvrnoJ == 0) {
          value  = jvar->jvrVup;
          coeff  = (complex *) value->arg[1];
          n      = nint((real) coeff[0].r) / 2;
          phimin = (real) coeff[1].r;
          phimax = (real) coeff[1].i;
          fservc(phi[0], phimin, phimax, &coeff[2], n, &u, &du, &ddu);
          value  = jvar->jvrVvp;
          coeff  = (complex *) value->arg[1];
          n      = nint((real) coeff[0].r) / 2;
          phimin = (real) coeff[1].r;
          phimax = (real) coeff[1].i;
          fservc(phi[0], phimin, phimax, &coeff[2], n, &v, &dv, &ddv);
        }
        qcamc(jvar->jvrnoJ, phi, u, v, du, dv, ddu, ddv, Q);
        break;
      case SLOT:
        if (jvar->jvrnoJ == 0) {
          value  = jvar->jvrVup;
          coeff  = (complex *) value->arg[1];
          n      = nint((real) coeff[0].r) / 2;
          phimin = (real) coeff[1].r;
          phimax = (real) coeff[1].i;
          fservc(phi[0], phimin, phimax, &coeff[2], n, &u, &du, &ddu);
          value  = jvar->jvrVvp;
          coeff  = (complex *) value->arg[1];
          n      = nint((real) coeff[0].r) / 2;
          phimin = (real) coeff[1].r;
          phimax = (real) coeff[1].i;
          fservc(phi[0], phimin, phimax, &coeff[2], n, &v, &dv, &ddv);
        }
        qsltc(jvar->jvrnoJ, phi, u, v, du, dv, Q);
        break;
      case FLAT:
        qfltc(jvar->jvrnoJ, phi, Q);
        break;
      case PLANE:
        qplnc(jvar->jvrnoJ, phi, Q);
        break;
      case SPHERE:
        qsphc(jvar->jvrnoJ, phi, Q);
        break;
      case OPEN:
        qopnc(jvar->jvrnoJ, phi, Q);
        break;
      }

/* Transform the operator for negatively oriented joints. */
      if (joint->orient < 0) {
        for (i=0; i<6; i++) {
          Q[i] = -Q[i];
        }
        xdxinc(joint->Phi, Q, Q);
      }

/* Transform the operator to the preceding body coordinate system. */
      xdxinc(joint->jntAxB->S, Q, Q);

/* Transform the operator to the absolute coordinate system. */
      xdxinc(joint->jntAxB->axsBdy->T0j, Q, Q);

/* Scale the length units for translational joint variables. */
      if (jvar->jvrtyp == JV_LINEAR) {
        for (i=0; i<6; i++) {
          Q[i] *= System.lscale;
        }
      }

/* Scale length units of translational elements of all operators. */
      for (i=0; i<3; i++) {
        Q[i] /= System.lscale;
      }

/* Copy the operator into the Jvar record. */
      for (i=0; i<6; i++) {
        jvar->D[i] = Q[i];
      }
    }
  }
  return;
}
