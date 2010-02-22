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
/* fptdc-01 Jan 00:17 Jul 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Add the effects of point dampers to the current vector of 
|     constraint forces and torques in a given joint.
|
|     Access:
|       (void) fptdc(Joint *joint, real f[6]);
|     Joint *joint,i  -Pointer to the given joint record.
|     real   f[6], i/o-Vector of joint constraint forces and torques.
|
|     Error Conditions:
|       If the endpoints of a damper are coincident then its direction
|     is indeterminate.  In such a case, the damper is ignored for that
|     position; a message is printed.
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
  void fptdc(Joint *joint, real f[6])
#else
  void fptdc(joint, f);
  Joint *joint;
  real   f[6];
#endif
{
  Body   *bodya,  *bodyb;
  Damper *damper;
  Point  *pointa, *pointb;
  int     i, n;
  real    ra[3], rab[3], rb[3], size, va[3], vab[3], vb[3], W[6];

  if (System.mode == MD_STAT) return;
  for (damper=System.sysDmp; damper; damper=damper->nxtDmp) {
    if (!isnanc((void *) &damper->c)) {
      if (damper->c != 0.0) {
        pointa = damper->dmpPtA;
        bodya  = pointa->pntBdy;
        pointb = damper->dmpPtB;
        bodyb  = pointb->pntBdy;
        if (bodya != bodyb) {
          ptvelc(pointa, ra, va);
          if (System.nerror) return;
          ptvelc(pointb, rb, vb);
          for (i=0; i<3; i++) {
            rab[i] = ra[i] - rb[i];
            vab[i] = va[i] - vb[i];
          }
          size = vabsc(3, rab);
          if (size < System.ptoll) {
            textc("*** Damper '", FALSE);
            textc(damper->name, FALSE);
            textc("' with coincident endpoints is ignored. ***", TRUE);
          } else {
            size = damper->c / (size * size);
            size = size * vdotc(3, vab, rab);
            for (n=0; n<6; n++) {
              if (!isnanc((void *) &System.pd[0][n])) {
                wdeltc(bodya, joint, n, W);
                mpydrc(W, ra, va);
                wdeltc(bodyb, joint, n, W);
                mpydrc(W, rb, vb);
                for (i=0; i<3; i++) {
                  vab[i] = va[i] - vb[i];
                }
                f[n] -= size * vdotc(3, vab, rab);
              }
            }
          }
        }
      }
    }
  }
  return;
}
