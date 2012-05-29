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
/* jtforc-01 Jan 00:14 Jul 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Determine the current vector of constraint forces and torques in
|     a given joint.
|
|     Access:
|       (void) jtforc(Joint *joint, real f[6]);
|     Joint *joint,i-Pointer to the given joint record.
|     real   f[6], o-Vector of joint constraint forces and torques.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       Indeterminate force and torque components are currently returned
|     as zero.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void jtforc(Joint *joint, real f[6])
#else
  void jtforc(joint, f);
  Joint *joint;
  real   f[6];
#endif
{
  int  i;
  real Phiinv[3][4], r[3], torq[3];

/* Find the force and torque components in system coordinates. */
  for (i=0; i<6; i++) f[i] = 0.0;
  vdervc(joint);
  if (System.mode != MD_STAT) {
    fdync(joint, f);
    fjtdc(f);
    fptdc(joint, f);
  }
  fgvtc(joint, f);
  fjtsc(f);
  fptsc(joint, f);
  fjtfc(f);
  fptfc(joint, f);
  fbdtc(joint, f);

/* Transform results to user coordinates. */
  if(joint->orient < 0) {
    invxc(joint->Phi, Phiinv);
    mpyxvc(Phiinv, f, f);
    mpyxvc(Phiinv, &f[3], &f[3]);
    for (i=0; i<3; i++) r[i] = Phiinv[i][3];
    vcrosc(r, f, torq);
    for (i=0; i<3; i++) {
      f[i]   = - f[i];
      f[i+3] = - f[i+3] - torq[i];
    }
  }
  return;
}
