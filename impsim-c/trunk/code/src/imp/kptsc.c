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
/* kptsc-01 Jan 00:17 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Add the effects of point springs to the current values of the
|     stiffness matrix.
|
|     Access:
|       (void) kptsc(int nfgc, real K[]);
|     int nfgc,           i-Number of free generalized coordinates.
|     real K[nfgc,nfgc],i/o-Stiffness matrix of the system.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       This routine only adds incremental changes to the total stiff-
|     ness matrix.  It assumes that K[] is initialized before entry.
|       If the two points defining a spring axis are coincident, the
|     effect of the spring is ignored at this position.  A warning
|     message is printed.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void kptsc(int nfgc, real K[])
#else
  void kptsc(nfgc, K);
  int  nfgc;
  real K[];
#endif
{
  Body   *bodya, *bodyb;
  Point  *pointa, *pointb;
  Spring *spring;
  int     i, j, k;
  real    ra[3], rab[3], rate, rat2, rat3, rb[3], size, vai[3], vaj[3],
    vbi[3], vbj[3], vi[3], vj[3], W[6];

  if (nfgc > 0) {
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
            for (k=0; k<3; k++) {
              rab[k] = ra[k] - rb[k];
            }
            size = vabsc(3, rab);
            if (size < System.ptoll) {
              textc("*** Spring '", FALSE);
              textc(spring->name, FALSE);
              textc("' with coincident endpoints is ignored. ***",TRUE);
            } else {
              rate = spring->k * (size - spring->freel) / size;
              rat2 = spring->k * spring->freel / (size * size * size);
              for (i=0; i<nfgc; i++) {
                wmatc(bodya, i, W);
                mpydrc(W, ra, vai);
                wmatc(bodyb, i, W);
                mpydrc(W, rb, vbi);
                for (k=0; k<3; k++) {
                  vi[k] = vai[k] - vbi[k];
                }
                rat3 = rat2 * vdotc(3, vi, rab);
                for (j=0; j<=i; j++) {
                  wmatc(bodya, j, W);
                  vcrosc(W, vai, vaj);
                  K[i*nfgc+j] += rate * vdotc(3, vaj, rab);
                  mpydrc(W, ra, vaj);
                  wmatc(bodyb, j, W);
                  vcrosc(W, vbi, vbj);
                  K[i*nfgc+j] -= rate * vdotc(3, vbj, rab);
                  mpydrc(W, rb, vbj);
                  for (k=0; k<3; k++) {
                    vj[k] = vaj[k] - vbj[k];
                  }
                  K[i*nfgc+j] += rate * vdotc(3, vi, vj)
                               + rat3 * vdotc(3, vj, rab);
                  accijc(bodya, j, i, W);
                  mpydrc(W, ra, vaj);
                  accijc(bodyb, j, i, W);
                  mpydrc(W, rb, vbj);
                  for (k=0; k<3; k++) {
                    vj[k] = vaj[k] - vbj[k];
                  }
                  K[i*nfgc+j] += rate * vdotc(3, vj, rab);
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
