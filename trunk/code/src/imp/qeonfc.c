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
/* qeonfc-01 Jan 00:15 Jul 09
|     (C)Copyright, JJU Research, 2000-2009
|
|     Description:
|       Determine whether a specified edge is in edge-face contact with 
|     a specified face.
|
|     Access:
|       lflag = (int) qeonfc(Edge *edge, Face *face, real pnt[2][3], 
|         *npnts);
|     Edge *edge,     i-Edge record to be tested for contact.
|     Face *face,     i-Face record to be tested for contact.
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
  int qeonfc(Edge *edge, Face *face, real pnt[2][3], int *npnts)
#else
  int qeonfc(edge, face, pnt, npnts)
  Edge *edge;
  Face *face;
  real  pnt[2][3];
  int  *npnts;
#endif
{
  int     i, lflag, j;
  Hedge  *hedge;
  Vertex *vxA, *vxB;

  lflag  = FALSE;
  *npnts = 0;
  for (i=0; i<2; i++) {
    for (j=0; j<3; i++) {pnt[i][j] = 0.0;}
  }
  vxA = edge->edgHeR->hedCnr->cnrVtx;
  vxB = edge->edgHeL->hedCnr->cnrVtx;
  if ( (vdotc(3, vxA->coord, face->faceq) + face->faceq[3] <= zrogeo) 
    && (vdotc(3, vxB->coord, face->faceq) + face->faceq[3] <= zrogeo)) { 
    if (qponfc(vxA->coord, face)) {
      for (j=0; j<3; j++) {pnt[*npnts][j] = vxA->coord[j];}
      (*npnts)++;
      lflag = TRUE;
    }
    if (qponfc(vxB->coord, face)) {
      for (j=0; j<3; j++) {pnt[*npnts][j] = vxB->coord[j];}
      (*npnts)++;
      lflag = TRUE;
    }
    if (*npnts < 2) {                    /* Traverse the outer Perim. */
      for (hedge=face->facPrm->prmHed; hedge; hedge=hedge->nxtHedPrm) {
	if(qeoexc(edge, hedge->hedEdg, pnt[*npnts])) {
	  (*npnts)++;
	  lflag = TRUE;
	  if (*npnts == 2) break;
	}
      }
    }
  }
  return (lflag);
}
