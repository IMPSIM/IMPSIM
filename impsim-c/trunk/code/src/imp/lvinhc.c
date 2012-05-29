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
/* lvinhc-01 Jan 00:15 Jul 09
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Determine whether a specified point in the plane of a specified 
|     face is on the left of a specified half-edge in the face.
|
|     Access:
|       lflag = (int) lvinhc(real pnt[3], Hedge *hedge, Face *face);
|     real   pnt[3],i-Point to be tested.
|     Hedge *hedge, i-Half-edge record to be tested.
|     Face  *face,  i-Face record to be tested.
|     int    lflag, o-Flag set TRUE if point is on the left of hedge.
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
  int lvinhc(real pnt[3], Hedge *hedge, Face *face)
#else
  int lvinhc(pnt, hedge, face)
  real   pnt[3];
  Hedge *hedge;
  Face  *face;
#endif
{
  int     i, lflag;
  real    abxpb[3], vab[3], vpb[3];
  Vertex *vtxa, *vtxb;

  lflag = FALSE;
  if (hedge->hedPrm->prmFac == face) {   /* Test if hedge is in face. */
    if (hedge->hedEdg->edgHeL == hedge) {
      vtxa = hedge->hedEdg->edgHeR->hedCnr->cnrVtx;
      vtxb = hedge->hedEdg->edgHeL->hedCnr->cnrVtx;
    } else {
      vtxa = hedge->hedEdg->edgHeL->hedCnr->cnrVtx;
      vtxb = hedge->hedEdg->edgHeR->hedCnr->cnrVtx;
    }
    for (i=0; i<3; i++) {
      vab[i] = vtxa->coord[i] - vtxb->coord[i];
      vpb[i] = pnt[i] - vtxb->coord[i];
    }
    vcrosc(vab, vpb, abxpb);
    if (vdotc(3, abxpb, face->faceq) > -zrogeo) lflag = TRUE;
  }
  return (lflag);
}
