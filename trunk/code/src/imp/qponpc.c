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
/* qponpc-01 Jan 00:16 Aug 09
|     (C)Copyright, JJU Research, 2000-2009
|
|     Description:
|       Check if a given point is inside or touching of a given Perim.
|
|     Access:
|       lflag = (int) qponpc(real pnt[3], Perim *perim, int *imax,
|         int *nvertx);
|     real   pnt[3],i-Coordinates of the specified point.
|     Perim *perim, i-Perim record to be tested.
|     int   *imax,  o-Index of the largest plane coordinate.
|     int   *nvertx,o-Vertex number if lflag = TRUE; (see Comments).
|     int    lflag, o-Flag set TRUE if found inside or touching Perim.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       If pnt[] lies at a vertex of Perim, lflag is set to 3 and 
|     *nvertx is set to the vertex number.  If pnt[] lies on an edge of 
|     Perim, lflag is set to 2 and *nvertx is set to the number of the
|     vertex preceding the touching halfedge.  If pnt[] is not on the
|     boundary of the Perim, lflag is set to 0 (FALSE) and nvertx is set
|     to -1.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  int qponpc(real pnt[3], Perim *perim, int *imax, int *nvertx)
#else
  int qponpc(pnt, perim, imax, nvertx)
  real   pnt[3];
  Perim *perim;
  int   *imax;
  int   *nvertx;
#endif
{
  int     i, kount, lflag, linsct;
  real    bigest, R[3], t1, t2;
  Face   *face;
  Hedge  *hed1, *hed2;
  Vertex *vxA, *vxB;

/* Check if the point lies on the plane of the perim. */
  *imax   = -1;
  *nvertx = -1;
  lflag   = FALSE;
  face    = perim->prmFac;
  if (fabs(vdotc(3, pnt, face->faceq) + face->faceq[3]) < zrogeo) {

/* Check if the point is on the boundary. */
    lflag = qpprmc(pnt, perim, nvertx);
    if (lflag > 0) return(lflag);
    hed1  = perim->prmHed;
    if ((hed1->nxtHedPrm==NULL) || (hed1->nxtHedPrm->nxtHedPrm==NULL)) {
      return(lflag);           /* Perim has only one or two vertices. */
    }
    lflag = FALSE;

/* Identify the largest Face normal coordinate. */
    bigest = 0.0;
    for (i=0; i<3; i++) {
      if (fabs(face->faceq[i]) > bigest) {
        *imax  = i;
        bigest = fabs(face->faceq[i]);
      }
    }

/* Check by ray casting if the point is inside of the perim. */
RETRY:
    vxA = hed1->hedEdg->edgHeR->hedCnr->cnrVtx;/*Cast ray at mid-he1. */
    vxB = hed1->hedEdg->edgHeL->hedCnr->cnrVtx;
    for (i=0; i<3; i++) {R[i] = 0.5 * (vxA->coord[i] + vxB->coord[i]);}
    kount = 0;
    hed2  = perim->prmHed;
    for (hed2=perim->prmHed; hed2; hed2=hed2->nxtHedPrm) {
      vxA = hed1->hedEdg->edgHeR->hedCnr->cnrVtx;
      vxB = hed1->hedEdg->edgHeL->hedCnr->cnrVtx;
      linsct = lnxlnc(pnt, R, vxA->coord, vxB->coord, *imax, &t1, &t2);
      if (linsct && (t1 > 0.0)) { /* Ray cuts the line of this hedge. */
        if (fabs(t2 < zrogeo) || (fabs(t2 - 1.0) < zrogeo)) {
          hed1=hed1->nxtHedPrm;/* Ray is through vertex of the perim. */
          goto RETRY;                      /* Choose a different ray. */
        }
        if ((t2 > 0.0) && (t2 < 1.0)) kount++;
      }
    }
    lflag = kount % 2;
  }
  return(lflag);
}
