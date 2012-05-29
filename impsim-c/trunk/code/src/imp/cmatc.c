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
/* cmatc-01 Jan 00:17 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Form the second-order system viscous damping matrix.
|
|     Access:
|       (void) cmatc(int nfgc, real D[]);
|     int nfgc,         i-Number of free generalized coordinates.
|     real D[nfgc,nfgc],o-Viscous damping matrix of the system.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void cmatc(int nfgc, real D[])
#else
  void cmatc(nfgc, D)
  int  nfgc;
  real D[];
#endif
{
  Body   *bodya, *bodyb;
  Damper *damper;
  Joint  *joint;
  Jvar   *jvar;
  Point  *pnta, *pntb;
  int     i, j, k, njvar;
  real    dist, ra[3], rb[3], rab[3], rate, va[3], vb[3], vi[3], vj[3],
    w[6];

/* Initialize. */
  for (i=0; i<nfgc; i++) {
    for (j=0; j<=i; j++) {
      D[i*nfgc+j] = 0.0;
    }
  }

/* Add the effects of joint damping. */
  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
    for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
      if (!isnanc((void *) &jvar->c)) {
        if (jvar->c != 0.0) {
          njvar = jvar->jvrnoS;
          if (njvar >= System.ndep) {
            i = njvar - System.ndep;
            if (i < nfgc) D[i*nfgc+i] += jvar->c;
          } else {
            for (i=0; i<nfgc; i++) {
              rate = System.d1[njvar][i] * jvar->c;
              if (rate != 0.0) {
                for (j=0; j<=i; j++) {
                  D[i*nfgc+j] += rate * System.d1[njvar][j];
                }
              }
            }
          }
        }
      }
    }
  }

/* Add the effects of point dampers. */
  for (damper=System.sysDmp; damper; damper=damper->nxtDmp) {
    if (!isnanc((void *) &damper->c)) {
      if (damper->c != 0.0) {
        pnta  = damper->dmpPtA;
        bodya = pnta->pntBdy;
        pntb  = damper->dmpPtB;
        bodyb = pntb->pntBdy;
        if (bodyb != bodya) {
          ptposc(pnta, ra);
          ptposc(pntb, rb);
          for (k=0; k<3; k++) {
            rab[k] = ra[k] - rb[k];
          }
          dist = vabsc(3, rab);
          if (dist < System.ptoll) {
            textc("*** Damper '", FALSE);
            textc(damper->name, FALSE);
            textc("' having coincident endpoints is ignored. ***",
              TRUE);
          } else {
            dist = damper->c / (dist * dist);
            for (i=0; i<nfgc; i++) {
              wmatc(bodya, i, w);
              mpydrc(w, ra, va);
              wmatc(bodyb, i, w);
              mpydrc(w, rb, vb);
              for (k=0; k<3; k++) {
                vi[k] = va[k] - vb[k];
              }
              rate = dist * vdotc(3, vi, rab);
              if (rate != 0.0) {
                for (j=0; j<=i; j++) {
                  wmatc(bodya, j, w);
                  mpydrc(w, ra, va);
                  wmatc(bodyb, j, w);
                  mpydrc(w, rb, vb);
                  for (k=0; k<3; k++) {
                    vj[k] = va[k] - vb[k];
                  }
                  D[i*nfgc+j] += rate * vdotc(3, vj, rab);
                }
              }
            }
          }
        }
      }
    }
  }

/* Complete the symmetric entries. */
  for (i=0; i<nfgc; i++) {
    for (j=0; j<i; j++) {
      D[j*nfgc+i] = D[i*nfgc+j];
    }
  }
  return;
}
