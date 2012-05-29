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
/* qeoexc-01 Jan 00:15 Jul 09
|     (C)Copyright, JJU Research, 2000-2009
|
|     Description:
|       Determine whether two specified edges are in contact at a point.
|
|     Access:
|       lflag = (int) qeoexc(Edge *edge1, Edge *edge2, real pnt[3]);
|     Edge *edge1, i-First  edge record to be tested for contact.
|     Edge *edge2, i-Second edge record to be tested for contact.
|     real  pnt[3],o-Point of contact, if found.
|     int   lflag, o-Flag set TRUE if contact is verified.
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
  int qeoexc(Edge *edge1, Edge *edge2, real pnt[3])
#else
  int qeoexc(edge1, edge2, pnt)
  Edge *edge1, *edge2;
  real  pnt[3];
#endif
{
  Vertex *vx1A, *vx1B, *vx2A, *vx2B;
  int     i, lflag;
  real    ABAB, ABBD, ABCD, BDCD, CDCD, det, diff[3], edg1[3], edg2[3], 
    edg12[3], eta1, eta2;

  lflag = FALSE;
  for (i=0; i<3; i++) {pnt[i] = 0.0;}
  vx1A = edge1->edgHeR->hedCnr->cnrVtx;
  if (qponec(vx1A->coord, edge2)) {
    lflag = TRUE;                         /* Vertex vx1A is on edge2. */
    for (i=0; i<3; i++) {pnt[i] = vx1A->coord[i];}
    goto DONE;
  }
  vx1B = edge1->edgHeL->hedCnr->cnrVtx;
  if (qponec(vx1B->coord, edge2)) {
    lflag = TRUE;                         /* Vertex vx1B is on edge2. */
    for (i=0; i<3; i++) {pnt[i] = vx1B->coord[i];}
    goto DONE;
  }
  vx2A = edge2->edgHeR->hedCnr->cnrVtx;
  if (qponec(vx2A->coord, edge1)) {
    lflag = TRUE;                         /* Vertex vx2A is on edge1. */
    for (i=0; i<3; i++) {pnt[i] = vx2A->coord[i];}
    goto DONE;
  }
  vx2B = edge2->edgHeL->hedCnr->cnrVtx;
  if (qponec(vx2B->coord, edge1)) {
    lflag = TRUE;                         /* Vertex vx2B is on edge1. */
    for (i=0; i<3; i++) {pnt[i] = vx2B->coord[i];}
    goto DONE;
  }
  for (i=0; i<3; i++) { edg1[i] = vx1A->coord[i] - vx1B->coord[i];}
  for (i=0; i<3; i++) { edg2[i] = vx2A->coord[i] - vx2B->coord[i];}
  for (i=0; i<3; i++) {edg12[i] = vx1B->coord[i] - vx2B->coord[i];}
  ABAB = vdotc(3, edg1, edg1); 
  ABCD = vdotc(3, edg1, edg2);
  CDCD = vdotc(3, edg2, edg2);
  det  = ABAB * CDCD - ABCD * ABCD;
  if (fabs(det) < System.zero) goto DONE;      /* Edges are parallel. */
  ABBD = vdotc(3, edg1, edg12);
  BDCD = vdotc(3, edg2, edg12);
  eta1 = (ABCD * BDCD - ABBD * CDCD) / det;
  if ((eta1 < 0.0) || (eta1 > 1.0)) goto DONE;   /* Outside of edge1. */
  eta2 = (ABAB * BDCD - ABBD * ABCD) / det;
  if ((eta2 < 0.0) || (eta2 > 1.0)) goto DONE;   /* Outside of edge2. */
  for (i=0; i<3; i++) {
    diff[i] = edg12[i] + eta1 * edg1[i] - eta2 * edg2[i];
  }
  if (vabsc(3, diff) < zrogeo) {
    lflag  = TRUE;
    pnt[i] = vx1B->coord[i] + eta1 * edg1[i];
  }
DONE: ;
  return (lflag);
}
