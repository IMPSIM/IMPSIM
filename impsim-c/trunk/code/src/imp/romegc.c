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
/* romegc-01 Jan 00:16 Aug 09
|     (C)Copyright, JJU Research, 2000-2009
|
|     Description:
|       Determine the relative rotational velocity normal to the surface 
|     at a specified contact.
|
|     Access:
|       (real) romegc(Contact *contct, fgcvel[]);
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
  real romegc(Contact *cntact, real fgcvel[])
#else
  void romegc(cntact, fgcvel)
  Contact *cntact;
  real    fgcvel[];
#endif
{
  Joint *joint;
  Jvar  *jvar;
  int    i, j;
  real   D[3], romega, phivel, WA[6], WB[6];

  romega = 0.0;
  for (i=0; i<System.ndof; i++) {
    wmatc(cntact->cnSldA->sldBdy, i, WA);
    wmatc(cntact->cnSldB->sldBdy, i, WB);
    D[0] = cntact->cnSldB->sldBdy->T0j[1][1] * WB[3]
         - cntact->cnSldB->sldBdy->T0j[0][1] * WB[4]
         - cntact->cnSldA->sldBdy->T0j[1][1] * WA[3]
         + cntact->cnSldA->sldBdy->T0j[0][1] * WA[4];
    D[1] = cntact->cnSldB->sldBdy->T0j[2][2] * WB[4]
         - cntact->cnSldB->sldBdy->T0j[1][2] * WB[5]
         - cntact->cnSldA->sldBdy->T0j[2][2] * WA[4]
         + cntact->cnSldA->sldBdy->T0j[1][2] * WA[5];
    D[2] = cntact->cnSldB->sldBdy->T0j[0][0] * WB[5]
         - cntact->cnSldB->sldBdy->T0j[2][0] * WB[3]
         - cntact->cnSldA->sldBdy->T0j[0][0] * WA[5]
         + cntact->cnSldA->sldBdy->T0j[2][0] * WA[3];
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
    romega += vdotc(3, &D[3], cntact->cnnormal) * phivel;
  }
  return(romega);
}
