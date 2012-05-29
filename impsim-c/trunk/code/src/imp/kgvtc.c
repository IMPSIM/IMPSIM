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
/* kgvtc-01 Jan 00:12 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Add the effects of gravity and body weights to the current 
|     values of the stiffness matrix.
|
|     Access:
|       (void) kgvtc(int nfgc, real K[]);
|     int nfgc,           i-Number of free generalized coordinates.
|     real K[nfgc,nfgc],i/o-Stiffness matrix of the system.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       This routine only adds incremental changes to the total stiff-
|     ness matrix.  It assumes that K[] is initialized before entry.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void kgvtc(int nfgc, real K[])
#else
  void kgvtc(nfgc, K);
  int  nfgc;
  real K[];
#endif
{
  Body *body;
  int   i, j;
  real  d2r[3], dri[3], D[6], mass, r[3];

  if (nfgc > 0) {
    if (!isnanc((void *) &System.gravty[0])) {
      for (body=System.sysBdy; body; body=body->nxtBdy) {
        if (body->bdyMas) {
          mass = body->bdyMas->I[9];
          if (fabs(mass) > System.dytol) {    /* Ignore small masses. */
            for (i=0; i<3; i++) {
              r[i] = body->bdyMas->I[6+i] / mass;
            }
            mpyxrc(body->T0j, r, r);
            for (i=0; i<nfgc; i++) {
              wmatc(body, i, D);
              mpydrc(D, r, dri);
              for (j=0; j<=i; j++) {             /* K[] is symmetric. */
                wmatc(body, j, D);
                vcrosc(D, dri, d2r);  /* Note that top of D[] is dwj. */
                K[i*nfgc+j] -= mass * vdotc(3, System.gravty, d2r);
                accijc(body, j, i, D);
                mpydrc(D, r, d2r);
                K[i*nfgc+j] -= mass * vdotc(3, System.gravty, d2r);
              }
            }
          }
        }
      }
    }
  }
  return;
}
