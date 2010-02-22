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
/* gfgvtc-01 Jan 00:12 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Add the effects of gravity and body weights to the current 
|     values of the generalized forces.
|
|     Access:
|       (void) gfgvtc(int nfgc, real G[]);
|     int nfgc,      i-Number of free generalized coordinates.
|     real G[nfgc],i/o-Generalized force vector on the system.
|
|     Error Conditions:
|       None.
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
  void gfgvtc(int nfgc, real G[])
#else
  void gfgvtc(nfgc, G);
  int  nfgc;
  real G[];
#endif
{
  Body *body;
  int   i;
  real  dri[3], mass, r[3], W[6];

  if (nfgc > 0) {
    if (!isnanc((void *) &System.gravty[0])) {
      for (body=System.sysBdy; body; body=body->nxtBdy) {
        if (body->bdyMas) {
          mass = body->bdyMas->I[9];
          if (fabs(mass) > System.dytol) {
            for (i=0; i<3; i++) {
              r[i] = body->bdyMas->I[6+i] / mass;
            }
            mpyxrc(body->T0j, r, r);
            for (i=0; i<nfgc; i++) {
              wmatc(body, i, W);
              mpydrc(W, r, dri);
              G[i] += mass * vdotc(3, System.gravty, dri);
            }
          }
        }
      }
    }
  }
  return;
}
