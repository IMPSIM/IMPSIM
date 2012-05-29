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
/* kbdtc-01 Jan 00:17 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Add the effects of body torques to the current values of the
|     stiffness matrix.
|
|     Access:
|       (void) kbdtc(int nfgc, real K[]);
|     int  nfgc,          i-Number of free generalized coordinates.
|     real K[nfgc,nfgc],i/o-Stiffness matrix of the system.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       This routine only adds incremental changes to the total stiff-
|     ness matrix.  It assumes that K[] is initialized before entry.
|       If the two points defining a torque axis are coincident, the
|     effect of that torque is ignored at that position.  A warning
|     message is printed.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void kbdtc(int nfgc, real K[])
#else
  void kbdtc(nfgc, K);
  int  nfgc;
  real K[];
#endif
{
  Body   *body, *bodya, *bodyb;
  Point  *pointa, *pointb;
  Torque *torque;
  int     i, j, k;
  real    ra[3], rab[3], rate, rb[3], size, t, v[3], va[3], vb[3], W[6];

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
              t = torque->t / size;
              for (i=0; i<nfgc; i++) {
                wmatc(body, i, W);
                for (k=0; k<3; k++) {
                  v[k] = W[k];
                }
                rate = t * vdotc(3, W, rab) / (size*size);
                for (j=0; j<=i; j++) {
                  accijc(body, j, i, W);
                  K[i*nfgc+j] -= t * vdotc(3, W, rab);
                  wmatc(bodya, j, W);
                  mpydrc(W, ra, va);
                  wmatc(bodyb, j, W);
                  mpydrc(W, rb, vb);
                  for (k=0; k<3; k++) {
                    vb[k] = va[k] - vb[k];
                  }
                  K[i*nfgc+j] += rate * vdotc(3, vb, rab)
                                  - t * vdotc(3, vb, v);
                }
              }
            }
          }
        }
      }
    }
  }
  return;
}
