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
/* gfbdtc-01 Jan 00:17 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Add the effects of body torques to the current values of the
|     generalized forces.
|
|     Access:
|       (void) gfbdtc(int nfgc, real G[]);
|     int  nfgc,     i-Number of free generalized coordinates.
|     real G[nfgc],i/o-Generalized forces on the system.
|
|     Error Conditions:
|       If the two points defining a torque axis are coincident, the
|     effect of that torque is ignored at that position.  A warning
|     message is printed.
|
|     Comments:
|       This routine only adds incremental changes to the total general-
|     ized forces.  It assumes that G[] is initialized before entry.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void gfbdtc(int nfgc, real G[])
#else
  void gfbdtc(nfgc, G);
  int  nfgc;
  real G[];
#endif
{
  Body   *body, *bodya, *bodyb;
  Point  *pointa, *pointb;
  Torque *torque;
  int     i, k;
  real    ra[3], rab[3], rb[3], size, W[6];

  if (nfgc > 0) {
    for (body=System.sysBdy; body; body=body->nxtBdy) {
      for (torque=body->bdyTrq; torque; torque=torque->nxtTrq) {
        if (!isnanc((void *) &torque->t)) {
          if (torque->t != 0.0) {
            pointa = torque->trqPtA;
            bodya  = pointa->pntBdy;
            ptposc(pointa, ra);
            pointb = torque->trqPtB;
            bodyb  = pointb->pntBdy;
            ptposc(pointb, rb);
            for (k=0; k<3; k++) {
              rab[k] = ra[k] - rb[k];
            }
            size = vabsc(3, rab);
            if (size < System.ptoll) {
              textc("*** Torque '", FALSE);
              textc(torque->name, FALSE);
              textc("' with coincident axis points is ignored. ***",
                TRUE);
            } else {
              for (i=0; i<nfgc; i++) {
                wmatc(body, i, W);
                G[i] += torque->t * vdotc(3, W, rab) / size;
              }
            }
          }
        }
      }
    }
  }
  return;
}
