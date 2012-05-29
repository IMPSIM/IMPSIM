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
/* tmbdtc-01 Jan 00:17 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Add the body torque effects to the generalized forces for a 
|     motion input transfer function.
|
|     Access:
|       (void) tmbdtc(int ngc, real G[]);
|     int  ngc,      i-number for the input motion coordinate.
|     real G[3*nfgc],o-Generalized force components formed.
|
|     Error Conditions:
|       If the two axis points of a torque are coincident, the torque is 
|     ignored for this position; a message is printed.
|
|     Comments:
|       This function assumes that the G[] array has been initialized 
|     before entry and that other effects are added elsewhere.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void tmbdtc(int ngc, real G[])
#else
  void tmbdtc(ngc, G)
  int  ngc;
  real G[];
#endif
{
  Body   *body, *bodyA, *bodyB;
  Torque *torque;
  Point  *point;
  int     i, nfgc;
  real    factor, RA[3], RB[3], RBA[3], size, t, VBJ[3], VAJ[3],VBAJ[3], 
    W[6];

  nfgc = System.nfgc;
  for (body=System.sysBdy; body; body=body->nxtBdy) {
    for (torque=body->bdyTrq; torque; torque=torque->nxtTrq) {
      if (abs(torque->t) >= System.zero) {
        point = torque->trqPtA;
        bodyA = point->pntBdy;
        ptposc(point, RA);
        point = torque->trqPtB;
        bodyB = point->pntBdy;
        ptposc(point, RB);
        for (i=0; i<3; i++) {
          RBA[i] = RB[i] - RA[i];
        }
        size = vabsc(3, RBA);
        if (size >= System.ptoll) {
          t = torque->t / size;
          wmatc(bodyA, ngc, W);
          mpydrc(W, RA, VAJ);
          wmatc(bodyB, ngc, W);
          mpydrc(W, RB, VBJ);
          for (i=0; i<3; i++) {
            VBAJ[i] = VBJ[i] - VAJ[i];
          }
          factor = -t * vdotc(3, VBAJ, RBA) / (size * size);
          for (i=0; i<nfgc; i++) {
            wmatc(body, i, W);
            G[i] += t * vdotc(3, W, VBAJ) + factor * vdotc(3, W, RBA);
            accijc(body, i, ngc, W);
            G[i] += t * vdotc(3, W, RBA);
          }
        } else {
          textc("*** The axis points of torque '", FALSE);
          textc(torque->name, FALSE);
          textc("' are coincident. ***", TRUE);
          textc("*** This torque ignored at this position. ***", TRUE);
        }
      }
    }
  }
  return;
}
