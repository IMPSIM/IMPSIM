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
/* pmatc-01 Jan 00:21 Jun 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Form the joint transformation matices from the joint variables.
|
|     Access:
|       (void) pmatc();
|
|     Error Conditions:
|       None.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
*     09 Mar 09:JJU-Implemented Euler parameters.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
void pmatc()
{
  Joint   *joint;
  Jvar    *jvar;
  Value   *value;
  int      n;
  complex *coeff;
  real     ddu, ddv, du, dv, phi[7], phimin, phimax, u, v;

/* Loop through the joints. */
  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {

/* Gather the joint variable values. */
    for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
      phi[jvar->jvrnoJ] = jvar->pos;
      if (jvar->jvrnoJ == 0) {
        if ((joint->jtype == CAM) || (joint->jtype == SLOT)) {
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
      }
    }

/* Form the joint transformation matrix. */
    switch (joint->jtype) {
    case RIGID:
      prgdc(joint->Phi);
      break;
    case XPIN:
      pxrvc(phi[0], joint->Phi);
      break;
    case YPIN:
      pyrvc(phi[0], joint->Phi);
      break;
    case ZPIN:
      pzrvc(phi[0], joint->Phi);
      break;
    case XSLIDE:
      pxprc(phi[0], joint->Phi);
      break;
    case YSLIDE:
      pyprc(phi[0], joint->Phi);
      break;
    case ZSLIDE:
      pzprc(phi[0], joint->Phi);
      break;
    case SCREW:
      pscrc(phi[0], joint->param[0], joint->Phi);
      break;
    case GEAR:
      pgerc(phi, joint->param[0], joint->param[1], joint->param[2],
        joint->Phi);
      break;
    case RACK:
      prckc(phi, joint->param[0], joint->param[1], joint->Phi);
      break;
    case BEVEL:
      pbvlc(phi, joint->param[0], joint->param[1], joint->Phi);
      break;
    case CYLINDER:
      pcylc(phi, joint->Phi);
      break;
    case UJOINT:
      pujtc(phi, joint->Phi);
      break;
    case CAM:
      pcamc(phi, u, v, du, dv, joint->Phi);
      break;
    case SLOT:
      psltc(phi, u, v, joint->Phi);
      break;
    case FLAT:
      pfltc(phi, joint->Phi);
      break;
    case PLANE:
      pplnc(phi, joint->Phi);
      break;
    case SPHERE:
      psphc(phi, joint->Phi);
      break;
    case OPEN:
      popnc(phi, joint->Phi);
      break;
    }
    if (joint->orient < 0) invxc(joint->Phi, joint->Phi);
  }
  return;
}
