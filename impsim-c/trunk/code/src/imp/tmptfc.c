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
/* tmptfc-01 Jan 00:17 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Add the point force effects to the generalized forces for a 
|     motion input transfer function.
|
|     Access:
|       (void) tmptfc(int ngc, real G[]);
|     int  ngc,      i-number for the input motion coordinate.
|     real G[3*nfgc],o-Generalized force components formed.
|
|     Error Conditions:
|       If the two direction points of a force are coincident, the force
|     is ignored for this position; a message is printed.
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
  void tmptfc(int ngc, real G[])
#else
  void tmptfc(ngc, G)
  int  ngc;
  real G[];
#endif
{
  Body   *body, *bodyA, *bodyB;
  Force  *force;
  Point  *point;
  int     i, nfgc;
  real    f, factor, R[3], RA[3], RB[3], RBA[3], size, VI[3], VJ[3], 
    VBJ[3], VAJ[3], VBAJ[3], W[6];

  nfgc = System.nfgc;
  for (body=System.sysBdy; body; body=body->nxtBdy) {
    for (force=body->bdyFrc; force; force=force->nxtFrc) {
      if (abs(force->f) >= System.zero) {
        point = force->frcPtA;
        bodyA = point->pntBdy;
        ptposc(point, RA);
        point = force->frcPtB;
        bodyB = point->pntBdy;
        ptposc(point, RB);
        if (bodyB != bodyA) {
          for (i=0; i<3; i++) {
            RBA[i] = RB[i] - RA[i];
          }
          size = vabsc(3, RBA);
          if (size >= System.ptoll) {
            ptposc(force->frcPtC, R);
            f = force->f / size;
            wmatc(body, ngc, W);
            mpydrc(W, R, VJ);
            wmatc(bodyA, ngc, W);
            mpydrc(W, RA, VAJ);
            wmatc(bodyB, ngc, W);
            mpydrc(W, RB, VBJ);
            for (i=0; i<3; i++) {
              VBAJ[i] = VBJ[i] - VAJ[i];
            }
            factor = -f * vdotc(3, VBAJ, RBA) / (size * size);
            for (i=0; i<nfgc; i++) {
              wmatc(body, i, W);
              mpydrc(W, R, VI);
              G[i] += f * vdotc(3, VI, VBAJ) + factor * vdotc(3,VI,RBA);
              vcrosc(W, VJ, VI);
              G[i] += f * vdotc(3, VI, RBA);
              accijc(body, i, ngc, W);
              mpydrc(W, R, VI);
              G[i] += f * vdotc(3, VI, RBA);
            }
          } else {
            textc("*** The direction points of force '", FALSE);
            textc(force->name, FALSE);
            textc("' are coincident. ***", TRUE);
            textc("*** This force ignored at this position. ***", TRUE);
          }
        }
      }
    }
  }
  return;
}
