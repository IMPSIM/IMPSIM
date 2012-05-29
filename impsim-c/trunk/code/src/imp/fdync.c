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
/* fdync-01 Jan 00:12 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Add the effects of the moving masses to the current vector of
|     constraint forces and torques in a given joint.
|
|     Access:
|       (void) fdync(Joint *joint, real f[6]);
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
  void fdync(Joint *joint, real f[6])
#else
  void fdync(joint, f);
  Joint *joint;
  real   f[6];
#endif
{
  Body *body;
  Mass *mass;
  int   n;
  real  W[6], WW[3][4], xjx[4][4];

  if (System.mode != MD_STAT) {
    if (System.level < 10) acc();
    if (System.nerror == 0) {
      for (body=System.sysBdy; body; body=body->nxtBdy) {
        mass = body->bdyMas;
        if (mass) {
          xjxtrc(body->T0j, mass->I, xjx);
          mpyddc(body->W, body->W, WW);
          WW[0][1] -= body->A[2];
          WW[0][2] += body->A[1];
          WW[0][3] += body->A[3];
          WW[1][0] += body->A[2];
          WW[1][2] -= body->A[0];
          WW[1][3] += body->A[4];
          WW[2][0] -= body->A[1];
          WW[2][1] += body->A[0];
          WW[2][3] += body->A[5];
          for (n=0; n<6; n++) {
            if (!isnanc((void *) &System.pd[0][n])) {
              wdeltc(body, joint, n, W);
              f[n] -= trwjwc(W, xjx, WW);
            }
          }
        }
      }
    }
  }
  return;
}
