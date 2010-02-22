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
/* gfptdc-01 Jan 00:17 Jul 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Add the effects of point dampers to the current vector of gener-
|     alized forces.
|
|     Access:
|       (void) gfptdc(int nfgc, real G[]);
|     int nfgc,      i-Number of free generalized coordinates.
|     real G[nfgc],i/o-Generalized forces on the system.
|
|     Error Conditions:
|       If the endpoints of a damper are coincident then its direction
|     is indeterminate.  In such a case, the damper is ignored for that
|     position; a message is printed.
|
|     Comments:
|       This routine only adds incremental changes to the total of all
|     generalized forces.  It assumes that G[] is initialized elsewhere.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void gfptdc(int nfgc, real G[])
#else
  void gfptdc(nfgc, G);
  int  nfgc;
  real G[];
#endif
{
  Body   *bodya, *bodyb;
  Damper *damper;
  Joint  *joint;
  Jvar   *jvar;
  Point  *pointa, *pointb;
  int     i, j, k;
  real    ra[3], rab[3], rate, rb[3], size, va[3], vab[3], vb[3], W[6];

  if (System.mode == MD_STAT) return;
  if (nfgc > 0) {
    for (damper=System.sysDmp; damper; damper=damper->nxtDmp) {
      if (!isnanc((void *) &damper->c)) {
        if (damper->c != 0.0) {
          pointa = damper->dmpPtA;
          bodya  = pointa->pntBdy;
          pointb = damper->dmpPtB;
          bodyb  = pointb->pntBdy;
          if (bodya != bodyb) {
            ptvelc(pointa, ra, va);
            if (System.nerror) return;
            ptvelc(pointb, rb, vb);
            for (k=0; k<3; k++) {
              rab[k] = ra[k] - rb[k];
              vab[k] = va[k] - vb[k];
            }
            size = vabsc(3, rab);
            if (size < System.ptoll) {
              textc("*** Damper '", FALSE);
              textc(damper->name, FALSE);
              textc("' with coincident endpoints is ignored. ***",TRUE);
            } else {
              size = damper->c / (size * size);
              for (i=0; i<nfgc; i++) {
                wmatc(bodya, i, W);
                mpydrc(W, ra, va);
                wmatc(bodyb, i, W);
                mpydrc(W, rb, vb);
                for (k=0; k<3; k++) {
                  vab[k] = va[k] - vb[k];
                }
                rate = size * vdotc(3, vab, rab);
                if (rate != 0.0) {
                  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
                    for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
                      j = jvar->jvrnoS - System.ndep;
                      if (j >= nfgc) {
                        wmatc(bodya, j, W);
                        mpydrc(W, ra, va);
                        wmatc(bodyb, j, W);
                        mpydrc(W, rb, vb);
                        for (k=0; k<3; k++) {
                          vab[k] = va[k] - vb[k];
                        }
                        G[i] -= rate * vdotc(3, vab, rab) * jvar->vel;
                      }
                    }
                  }
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
