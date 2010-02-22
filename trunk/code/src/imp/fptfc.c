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
/* fptfc-01 Jan 00:17 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Add the effects of point forces to the current vector of 
|     constraint forces and torques in a given joint.
|
|     Access:
|       (void) fptfc(Joint *joint, real f[6]);
|     Joint *joint,i  -Pointer to the given joint record.
|     real   f[6], i/o-Vector of joint constraint forces and torques.
|
|     Error Conditions:
|       If the points defining a force axis are coincident then its 
|     directionis indeterminate.  In such a case, the force is ignored 
|     for that position; a message is printed.
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
  void fptfc(Joint *joint, real f[6])
#else
  void fptfc(joint, f);
  Joint *joint;
  real   f[6];
#endif
{
  Body  *body,  *bodya,  *bodyb;
  Point *point, *pointa, *pointb;
  Force *force;
  int    i, n;
  real   dr[3], r[3], ra[3], rab[3], rb[3], size, W[6];

  for (body=System.sysBdy; body; body=body->nxtBdy) {
    for (force=body->bdyFrc; force; force=force->nxtFrc) {
      if (!isnanc((void *) &force->f)) {
        if (force->f != 0.0) {
          point = force->frcPtC;
          ptposc(point, r);
          pointa = force->frcPtA;
          bodya  = pointa->pntBdy;
          ptposc(pointa, ra);
          pointb = force->frcPtB;
          bodyb  = pointb->pntBdy;
          ptposc(pointb, rb);
          for (i=0; i<3; i++) {
            rab[i] = ra[i] - rb[i];
          }
          size = vabsc(3, rab);
          if (size < System.ptoll) {
            textc("*** Force '", FALSE);
            textc(force->name, FALSE);
            textc("' with coincident axis points is ignored. ***",TRUE);
          } else {
            size = force->f / size;
            for (n=0; n<6; n++) {
              if (!isnanc((void *) &System.pd[0][n])) {
                wdeltc(body, joint, n, W);
                mpydrc(W, r, dr);
                f[n] += size * vdotc(3, dr, rab);
              }
            }
          }
        }
      }
    }
  }
  return;
}
