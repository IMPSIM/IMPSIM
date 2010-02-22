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
/* gfptsc-01 Jan 00:17 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Add the effects of point springs to the current values of the
|     generalized forces.
|
|     Access:
|       (void) gfptsc(int nfgc, real G[]);
|     int  nfgc,     i-Number of free generalized coordinates.
|     real G[nfgc],i/o-Generalized forces on the system.
|
|     Error Conditions:
|       If the two points defining a spring axis are coincident, the
|     effect of that spring is ignored at that position.  A warning
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
  void gfptsc(int nfgc, real G[])
#else
  void gfptsc(nfgc, G);
  int  nfgc;
  real G[];
#endif
{
  Body   *bodya, *bodyb;
  Point  *pointa, *pointb;
  Spring *spring;
  int     i, k;
  real    ra[3], rab[3], rate, rb[3], size, vai[3], vbi[3], vi[3], W[6];

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
              if (rate != 0.0) {
                for (i=0; i<nfgc; i++) {
                  wmatc(bodya, i, W);
                  mpydrc(W, ra, vai);
                  wmatc(bodyb, i, W);
                  mpydrc(W, rb, vbi);
                  for (k=0; k<3; k++) {
                    vi[k] = vai[k] - vbi[k];
                  }
                  G[i] -= rate * vdotc(3, vi, rab);
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
