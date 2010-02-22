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
/* fptsc-01 Jan 00:17 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Add the effects of point springs to the current vector of 
|     constraint forces and torques in a given joint.
|
|     Access:
|       (void) fptsc(Joint *joint, real f[6]);
|     Joint *joint,i  -Pointer to the given joint record.
|     real   f[6], i/o-Vector of joint constraint forces and torques.
|
|     Error Conditions:
|       If the endpoints of a spring are coincident then its direction
|     is indeterminate.  In such a case, the spring is ignored for that
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
  void fptsc(Joint *joint, real f[6])
#else
  void fptsc(joint, f);
  Joint *joint;
  real   f[6];
#endif
{
  Body   *bodya,  *bodyb;
  Point  *pointa, *pointb;
  Spring *spring;
  int     i, n;
  real    ra[3], rab[3], rate, rb[3], size, va[3], vab[3], vb[3], W[6];

  for (spring=System.sysSpg; spring; spring=spring->nxtSpg) {
    if (!isnanc((void *) &spring->k)) {
      if (spring->k != 0.0) {
        pointa = spring->spgPtA;
        bodya  = pointa->pntBdy;
        pointb = spring->spgPtB;
        bodyb  = pointb->pntBdy;
        if (bodya != bodyb) {
          ptposc(pointa, ra);
          ptposc(pointb, rb);
          for (i=0; i<3; i++) {
            rab[i] = ra[i] - rb[i];
          }
          size = vabsc(3, rab);
          if (size < System.ptoll) {
            textc("*** Spring '", FALSE);
            textc(spring->name, FALSE);
            textc("' with coincident endpoints is ignored. ***", TRUE);
          } else {
            rate  = spring->k * (1.0 - spring->freel / size);
            for (n=0; n<6; n++) {
              if (!isnanc((void *) &System.pd[0][n])) {
                wdeltc(bodya, joint, n, W);
                mpydrc(W, ra, va);
                wdeltc(bodyb, joint, n, W);
                mpydrc(W, rb, vb);
                for (i=0; i<3; i++) {
                  vab[i] = va[i] - vb[i];
                }
                f[n] -= rate * vdotc(3, vab, rab);
              }
            }
          }
        }
      }
    }
  }
  return;
}
