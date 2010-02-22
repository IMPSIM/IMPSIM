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
/* qeoetc-01 Jan 00:15 Jul 09
|     (C)Copyright, JJU Research, 2000-2009
|
|     Description:
|       Determine whether two specified edges are in tangential contact. 
|
|     Access:
|       lflag = (int) qeoetc(Edge *edge1, Edge *edge2, real pnt[2][3], 
|         *npnts);
|     Edge *edge1,    i-First  edge record to be tested for contact.
|     Edge *edge2,    i-Second edge record to be tested for contact.
|     real  pnt[2][3],o-Point(s) of contact, if found.
|     int  *npnts,    o-Number of contact points found (*npnts <= 2).
|     int   lflag,    o-Flag set TRUE if contact is verified.
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
  int qeoetc(Edge *edge1, Edge *edge2, real pnt[2][3], int *npnts)
#else
  int qeoetc(edge1, edge2, pnt, npnts)
  Edge *edge1, *edge2;
  real  pnt[2][3];
  int  *npnts;
#endif
{
  int     i, lflag, j;
  Vertex *vx1A, *vx1B, *vx2A, *vx2B;

  lflag = FALSE;
  for (i=0; i<2; i++) {
    for (j=0; j<3; i++) {pnt[i][j] = 0.0;}
  }
  vx1A = edge1->edgHeR->hedCnr->cnrVtx;
  if(qponec(vx1A->coord, edge2)) {
    for (j=0; j<3; j++) {pnt[*npnts][j] = vx1A->coord[j];}
    (*npnts)++;
  }
  vx1B = edge1->edgHeL->hedCnr->cnrVtx;
  if(qponec(vx1A->coord, edge2)) {
    for (j=0; j<3; j++) {pnt[*npnts][j] = vx1B->coord[j];}
    (*npnts)++;
  }
  vx2A = edge2->edgHeR->hedCnr->cnrVtx;
  if(qponec(vx2A->coord, edge1)) {
    if (*npnts < 2) {
      for (j=0; j<3; j++) {pnt[*npnts][j] = vx2A->coord[j];}
      (*npnts)++;
    }
  }
  vx2B = edge2->edgHeL->hedCnr->cnrVtx;
  if(qponec(vx1A->coord, edge1)) {
    if (*npnts < 2) {
      for (j=0; j<3; j++) {pnt[*npnts][j] = vx2B->coord[j];}
      (*npnts)++;
    }
  }
  if (*npnts > 0) lflag = TRUE;
  return (lflag);
}
