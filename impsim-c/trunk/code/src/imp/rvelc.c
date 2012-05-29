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
/* rvelc-01 Jan 00:16 Aug 09
|     (C)Copyright, JJU Research, 2000-2009
|
|     Description:
|       Determine the relative velocity tangent to the surface at a 
|     specified contact.
|
|     Access:
|       (real) rvelc(Contact *contct, fgcvel[]);
|     Contact *contct, i-Contact record specified for impact.
|     real    fgcvel[],i-Array of FGC velocities.
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
  real rvelc(Contact *cntact, real fgcvel[])
#else
  void rvelc(cntact, fgcvel)
  Contact *cntact;
  real    fgcvel[];
#endif
{
  Joint *joint;
  Jvar  *jvar;
  int    i, j;
  real   phivel, rvel, V[3], WA[6], WAB[6], WB[6];

  rvel = 0.0;
  for (i=0; i<System.ndof; i++) {
    wmatc(cntact->cnSldA->sldBdy, i, WA);
    wmatc(cntact->cnSldB->sldBdy, i, WB);
    for (j=0; j<6; j++) WAB[j] = WA[j] - WB[j];
    mpydrc(WAB, cntact->cnpoint, V);
    if (i < System.nfgc) {
      phivel = fgcvel[i];
    } else {
      for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
        for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
          j = jvar->jvrnoS - System.ndep;
          if (j == i) phivel = jvar->vel;
        }
      }
    }
    rvel += vdotc(3, V, cntact->cntangnt) * phivel;
  }
  return(rvel);
}
