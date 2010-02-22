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
/* fgvtc-01 Jan 00:12 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Add the effects of gravity and body weights to the current 
|     vector of constraint forces and torques in a given joint.
|
|     Access:
|       (void) fgvtc(Joint *joint, real f[6]);
|     Joint *joint,i  -Pointer to the given joint record.
|     real   f[6], i/o-Vector of joint constraint forces and torques.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       This routine only adds incremental changes to the total of all
|     constraint forces.  It assumes that f[] is initialized elsewhere.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void fgvtc(Joint *joint, real f[6])
#else
  void fgvtc(joint, f);
  Joint *joint;
  real   f[6];
#endif
{
  Body *body;
  int   i;
  real  mass, R[3], v[3], W[6];

  if (!isnanc((void *) &System.gravty[0])) {
    for (body=System.sysBdy; body; body=body->nxtBdy) {
      if (body->bdyMas) {
        mass = body->bdyMas->I[9];
        if (fabs(mass) > System.dytol) {
          for (i=0; i<3; i++) {
            R[i] = body->bdyMas->I[i+6] / mass;
          }
          mpyxrc(body->T0j, R, R);
          for (i=0; i<6; i++) {
            wdeltc(body, joint, i, W);
            mpydrc(W, R, v);
            f[i] += mass * vdotc(3, System.gravty, v);
          }
        }
      }
    }
  }
  return;
}
