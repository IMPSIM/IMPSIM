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
/* kptfc-01 Jan 00:17 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Add the effects of point forces to the current values of the
|     stiffness matrix.
|
|     Access:
|       (void) kptfc(int nfgc, real K[]);
|     int  nfgc,          i-Number of free generalized coordinates.
|     real K[nfgc,nfgc],i/o-Stiffness matrix of the system.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       This routine only adds incremental changes to the total stiff-
|     ness matrix.  It assumes that K[] is initialized before entry.
|       If the two points defining a force axis are coincident, the
|     effect of that force is ignored at that position.  A warning
|     message is printed.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void kptfc(int nfgc, real K[])
#else
  void kptfc(nfgc, K);
  int  nfgc;
  real K[];
#endif
{
  Body  *body,  *bodya,  *bodyb, *bodyf;
  Point *point, *pointa, *pointb;
  Force *force;
  int    i, j, k;
  real   f, r[3], ra[3], rab[3], rate, rb[3], size, v[3], va[3], vab[3],
    vb[3], W[6];

  if (nfgc > 0) {
    for (body=System.sysBdy; body; body=body->nxtBdy) {
      for (force=body->bdyFrc; force; force=force->nxtFrc) {
        if (!isnanc((void *) &force->f)) {
          if (force->f != 0.0) {
            point = force->frcPtC;
            bodyf = point->pntBdy;
            ptposc(point, r);
            pointa = force->frcPtA;
            bodya  = pointa->pntBdy;
            ptposc(pointa, ra);
            pointb = force->frcPtB;
            bodyb  = pointb->pntBdy;
            ptposc(pointb, rb);
            for (k=0; k<3; k++) {
              rab[k] = ra[k] - rb[k];
            }
            size = vabsc(3, rab);
            if (size < System.ptoll) {
              textc("*** Force '", FALSE);
              textc(force->name, FALSE);
              textc("' with coincident axis points is ignored. ***",
                TRUE);
            } else {
              f = force->f / size;
              for (i=0; i<nfgc; i++) {
                wmatc(bodyf, i, W);
                mpydrc(W, r, v);
                rate = f * vdotc(3, v, rab) / (size * size);
                for (j=0; j<=i; j++) {
                  wmatc(bodyf, j, W);
                  vcrosc(W, v, vab);
                  K[i*nfgc+j] -= f * vdotc(3, vab, rab);
                  accijc(bodyf, j, i, W);
                  mpydrc(W, r, vab);
                  K[i*nfgc+j] -= f * vdotc(3, vab, rab);
                  wmatc(bodya, j, W);
                  mpydrc(W, ra, va);
                  wmatc(bodyb, j, W);
                  mpydrc(W, rb, vb);
                  for (k=0; k<3; k++) {
                    vab[k] = va[k] - vb[k];
                  }
                  K[i*nfgc+j] -= f * vdotc(3, vab, v);
                  K[i*nfgc+j] += rate * vdotc(3, vab, rab);
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
