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
/* prmarc-01 Jan 00:15 Jul 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Compute the signed scalar area of a specified Perim.
|
|     Access:
|       area = (real) prmarc(Perim *perim);
|     Perim *perim,i-Pointer to the specified Perim record.
|     real  area,  o-Signed area found for this perim.
|
|     Error Conditions:
|       If *perim is not a valid Perim record, execution is aborted.  A
|     message is printed.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
*     08 Sep 07:JJU-Added error message.
* ------------------------------------------------------------------- */
 
#include "libgeo.h"
#ifdef ANSI
  real prmarc(Perim *perim)
#else
  real prmarc(perim)
  Perim *perim;
#endif
{
  Hedge  *hedge;
  Vertex *vxB, *vxA;
  int     k;
  real    area, rA[3], rB[3], varea[3], vector[3], wA, wB;

  if (perim->type == PERIM) {
    for (k=0; k<3; k++) {
      varea[k] = 0.0;
    }
    hedge = perim->prmHed;
    do {
      vxB = hedge->hedCnr->cnrVtx;
      wB  = vxB->coord[3];
      vxA = hedge->nxtHedPrm->hedCnr->cnrVtx;
      wA  = vxA->coord[3];
      for (k=0; k<3; k++) {
        rA[k] = vxA->coord[k] / wA;
        rB[k] = vxB->coord[k] / wB;
      }
      vcrosc(rB, rA, vector);
      for (k=0; k<3; k++) varea[k] += vector[k];
      hedge = hedge->nxtHedPrm;
    } while (hedge != perim->prmHed);
    area = vabsc(3, varea);
    if (vdotc(3, perim->prmFac->faceq, varea) < 0.0) area = -area;
    perim->area = area;
  } else {
    echoc();
    textc("*** prmarc:  Invalid Perim record. ***", TRUE);
    abortc();
  }
  return(area);
}
