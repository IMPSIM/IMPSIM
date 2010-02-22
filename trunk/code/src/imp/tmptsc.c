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
/* tmptsc-01 Jan 00:17 Jul 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Add the point spring effects to the generalized forces for a 
|     motion input transfer function.
|
|     Access:
|       (void) tmptsc(int ngc, real G[]);
|     int  ngc,      i-number for the input motion coordinate.
|     real G[3*nfgc],o-Generalized force components formed.
|
|     Error Conditions:
|       If the two endpoints of a spring are coincident, the spring is
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
  void tmptsc(int ngc, real G[])
#else
  void tmptsc(ngc, G)
  int  ngc;
  real G[];
#endif
{
  Body   *bodyA, *bodyB;
  Point  *point;
  Spring *spring;
  int    i, j, nfgc;
  real   rate1, rate2, RA[3], RB[3], RBA[3], size, VBI[3], VAI[3], 
    VBAI[3], VBJ[3], VAJ[3], VBAJ[3], VBIJ[3], VAIJ[3], VBAIJ[3], W[6];

  nfgc = System.nfgc;
  for (spring=System.sysSpg; spring; spring=spring->nxtSpg) {
    if (abs(spring->k) >= System.zero) {
      point = spring->spgPtA;
      bodyA = point->pntBdy;
      ptposc(point, RA);
      point = spring->spgPtB;
      bodyB = point->pntBdy;
      ptposc(point, RB);
      if (bodyB != bodyA) {
        for (i=0; i<3; i++) {
          RBA[i] = RB[i] - RA[i];
        }
        size = vabsc(3, RBA);
        if (size >= System.ptoll) {
          rate1 = spring->k * (spring->freel - size) / size;
          rate2 = -spring->k * spring->freel / (size * size * size);
          wmatc(bodyA, ngc, W);
          mpydrc(W, RA, VAJ);
          wmatc(bodyB, ngc, W);
          mpydrc(W, RB, VBJ);
          for (i=0; i<3; i++) {
            VBAJ[i] = VBJ[i] - VAJ[i];
          }
          rate2 *= vdotc(3, VBAJ, RBA);
          for (i=0; i<nfgc; i++) {
            wmatc(bodyA, i, W);
            mpydrc(W, RA, VAI);
            wmatc(bodyB, i, W);
            mpydrc(W, RB, VBI);
            for (j=0; j<3; j++) {
              VBAI[j] = VBI[j] - VAI[j];
            }
            accijc(bodyA, i, ngc, W);
            mpydrc(W, RA, VAIJ);
            accijc(bodyB, i, ngc, W);
            mpydrc(W, RB, VBIJ);
            G[i] += rate1 * (vdotc(3, VBAIJ, RBA) + vdotc(3,VBAI,VBAJ))
                  + rate2 *  vdotc(3, VBAI,  RBA);
          }
        } else {
          textc("*** The endpoints of spring '", FALSE);
          textc(spring->name, FALSE);
          textc("' are coincident. ***", TRUE);
          textc("*** This spring ignored at this position. ***", TRUE);
        }
      }
    }
  }
  return;
}
