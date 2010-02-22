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
/* tmptdc-01 Jan 00:17 Jul 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Add the point damping effects to the generalized forces for a 
|     motion input transfer function.
|
|     Access:
|       (void) tmptdc(int ngc, real G[]);
|     int  ngc,      i-number for the input motion coordinate.
|     real G[3*nfgc],o-Generalized force components formed.
|
|     Error Conditions:
|       If the two endpoints of a damper are coincident, the damper is
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
  void tmptdc(int ngc, real G[])
#else
  void tmptdc(ngc, G)
  int  ngc;
  real G[];
#endif
{
  Body   *bodyA, *bodyB;
  Damper *damper;
  Point  *point;
  int    i, j, nfgc;
  real   rate, RA[3], RB[3], RBA[3], size, VB[3], VA[3], VBA[3], W[6];

  nfgc = System.nfgc;
  for (damper=System.sysDmp; damper; damper=damper->nxtDmp) {
    if (abs(damper->c) >= System.zero) {
      point = damper->dmpPtA;
      bodyA = point->pntBdy;
      ptposc(point, RA);
      point = damper->dmpPtB;
      bodyB = point->pntBdy;
      ptposc(point, RB);
      if (bodyB != bodyA) {
        for (i=0; i<3; i++) {
          RBA[i] = RB[i] - RA[i];
        }
        size = vabsc(3, RBA);
        if (size >= System.ptoll) {
          wmatc(bodyA, ngc, W);
          mpydrc(W, RA, VA);
          wmatc(bodyB, ngc, W);
          mpydrc(W, RB, VB);
          for (i=0; i<3; i++) {
            VBA[i] = VB[i] - VA[i];
          }
          rate = -damper->c * vdotc(3, VBA, RBA) / (size * size);
          if (abs(rate) >= System.zero) {
            for (i=0; i<nfgc; i++) {
              wmatc(bodyA, i, W);
              mpydrc(W, RA, VA);
              wmatc(bodyB, i, W);
              mpydrc(W, RB, VB);
              for (j=0; j<3; j++) {
                VBA[j] = VB[j] - VA[j];
              }
              G[nfgc+i] += rate * vdotc(3, VBA, RBA);
            }
          }
        } else {
          textc("*** The endpoints of damper '", FALSE);
          textc(damper->name, FALSE);
          textc("' are coincident. ***", TRUE);
          textc("*** This damper ignored at this position. ***", TRUE);
        }
      }
    }
  }
  return;
}
