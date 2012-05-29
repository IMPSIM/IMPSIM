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
/* qfonfc-01 Jan 00:15 Jul 09
|     (C)Copyright, JJU Research, 2000-2009
|
|     Description:
|       Determine whether a specified face is in face-face contact with 
|     another specified face.
|
|     Access:
|       lflag = (int) qfonfc(Face *face1, Face *face2, real pnt[][3], 
|         *npnts);
|     Face *face1,   i-First  face record to be tested for contact.
|     Face *face2,   i-Second face record to be tested for contact.
|     real  pnt[][3],o-Point(s) of contact, if found.
|     int  *npnts,   o-Number of contact points found.
|     int   lflag,   o-Flag set TRUE if contact is verified.
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
  int qfonfc(Face *face1, Face *face2, real pnt[][3], int *npnts)
#else
  int qfonfc(face1, face2, pnt, npnts)
  Face *face1;
  Face *face2;
  real  pnt[][3];
  int  *npnts;
#endif
{
  enum {Unknown, Pin, Qin} inflag;
  int     i, lflag, l1ain2, l2bin1, nedge1, nedge2;
  real    a[3], b[3], axb[3], pt[3], sum[3];
  Hedge  *hed,  *hed1, *hed2;
  Vertex *vx1a, *vx1b, *vx2a, *vx2b;

/* Initialize. */
  lflag  = FALSE;
  *npnts = 0;

/* First check if the two faces are coplanar and oppositely directed. */
  for (i=0; i<3; i++) {sum[i] = face2->faceq[i] + face1->faceq[i];}
  if ((vabsc(3, sum) < System.zero) && 
    (fabs(face2->faceq[3] + face1->faceq[3]) < zrogeo)) {
    
/* Find the intersection of the two faces by the O'Rourke algorithm. */
    inflag = Unknown;
    hed1 = face1->facPrm->prmHed;   /* Get the outer Perim of Face 1. */
    if (hed1->hedEdg->edgHeL == hed1) {
      vx1a = hed1->hedEdg->edgHeR->hedCnr->cnrVtx;
      vx1b = hed1->hedEdg->edgHeL->hedCnr->cnrVtx;
    } else {
      vx1a = hed1->hedEdg->edgHeL->hedCnr->cnrVtx;
      vx1b = hed1->hedEdg->edgHeR->hedCnr->cnrVtx;
    }
    hed2 = face2->facPrm->prmHed;   /* Get the outer Perim of Face 2. */
    if (hed2->hedEdg->edgHeL == hed2) {
      vx2a = hed2->hedEdg->edgHeR->hedCnr->cnrVtx;
      vx2b = hed2->hedEdg->edgHeL->hedCnr->cnrVtx;
    } else {
      vx2a = hed2->hedEdg->edgHeL->hedCnr->cnrVtx;
      vx2b = hed2->hedEdg->edgHeR->hedCnr->cnrVtx;
    }
    nedge1 = 0;
    nedge2 = 0;
    do {                             /* Traverse edges of both faces. */
      l1ain2 = lvinhc(vx1a->coord, hed2, face2);
      l2bin1 = lvinhc(vx2b->coord, hed1, face1);
      if (qeoexc(hed1->hedEdg, hed2->hedEdg, pt)) {
	inflag = l1ain2 ? (l2bin1 ? Unknown : Pin) : Qin;
	ptocrc(pt, pnt, npnts);
      }
      if (inflag == Unknown) {  /* If starting out by parallel edges. */
	if (qponec(vx2b->coord, hed1->hedEdg)) {
	  inflag = Pin;
	} else if (qponec(vx1a->coord, hed2->hedEdg)) {
	  inflag = Qin;
	}
      }
      for (i=0; i<3; i++) {
	a[i] = vx1a->coord[i] - vx1b->coord[i];
	b[i] = vx2b->coord[i] - vx2a->coord[i];
      }
      vcrosc(a, b, axb);
      if (vdotc(3, axb, face1->faceq) >= 0.0) {
	if (l2bin1) {
	  if (inflag == Pin) ptocrc(vx1a->coord, pnt, npnts);
          hed1 = hed1->nxtHedPrm;
	  if (hed1->hedEdg->edgHeL == hed1) {
            vx1a = hed1->hedEdg->edgHeR->hedCnr->cnrVtx;
            vx1b = hed1->hedEdg->edgHeL->hedCnr->cnrVtx;
	  } else {
            vx1a = hed1->hedEdg->edgHeL->hedCnr->cnrVtx;
            vx1b = hed1->hedEdg->edgHeR->hedCnr->cnrVtx;
	  }
	  nedge1++;
	} else {
	  if (inflag == Qin) ptocrc(vx2b->coord, pnt, npnts);
          hed = hed2->hedPrm->prmHed;
          while (hed->nxtHedPrm != hed2) hed=hed->nxtHedPrm;
	  hed2 = hed;
	  if (hed2->hedEdg->edgHeL == hed2) {
            vx2a = hed2->hedEdg->edgHeR->hedCnr->cnrVtx;
            vx2b = hed2->hedEdg->edgHeL->hedCnr->cnrVtx;
	  } else {
            vx2a = hed2->hedEdg->edgHeL->hedCnr->cnrVtx;
            vx2b = hed2->hedEdg->edgHeR->hedCnr->cnrVtx;
	  }
	  nedge2++;
	}
      } else {
	if (l1ain2) {
	  if (inflag == Qin) ptocrc(vx2b->coord, pnt, npnts);
          hed = hed2->hedPrm->prmHed;
          while (hed->nxtHedPrm != hed2) hed=hed->nxtHedPrm;
	  hed2 = hed;
	  if (hed2->hedEdg->edgHeL == hed2) {
            vx2a = hed2->hedEdg->edgHeR->hedCnr->cnrVtx;
            vx2b = hed2->hedEdg->edgHeL->hedCnr->cnrVtx;
	  } else {
            vx2a = hed2->hedEdg->edgHeL->hedCnr->cnrVtx;
            vx2b = hed2->hedEdg->edgHeR->hedCnr->cnrVtx;
	  }
	  nedge2++;
	} else {
	  if (inflag == Pin) ptocrc(vx1a->coord, pnt, npnts);
          hed1 = hed1->nxtHedPrm;
	  if (hed1->hedEdg->edgHeL == hed1) {
            vx1a = hed1->hedEdg->edgHeR->hedCnr->cnrVtx;
            vx1b = hed1->hedEdg->edgHeL->hedCnr->cnrVtx;
	  } else {
            vx1a = hed1->hedEdg->edgHeL->hedCnr->cnrVtx;
            vx1b = hed1->hedEdg->edgHeR->hedCnr->cnrVtx;
	  }
	  nedge1++;
	}
      }
    } while ((nedge1 <= face1->facPrm->nhedgs)  /* Do for all edges   */
          || (nedge2 <= face2->facPrm->nhedgs));/*   of outer Perims. */
    if (*npnts == 0) {          /* No edges are crossing or touching. */
      if (qponfc(hed1->hedEdg->edgHeL->hedCnr->cnrVtx->coord, face2)) {
				    /* Face1 is totally inside face2. */
        for (hed=face1->facPrm->prmHed; hed; hed=hed->nxtHedPrm) {
          ptocrc(hed->hedEdg->edgHeL->hedCnr->cnrVtx->coord, pnt,npnts);
	}
	lflag = TRUE;
      } else if (qponfc(hed2->hedEdg->edgHeL->hedCnr->cnrVtx->coord,
          face1)) {
				    /* Face2 is totally inside face1. */
        for (hed=face2->facPrm->prmHed; hed; hed=hed->nxtHedPrm) {
          ptocrc(hed->hedEdg->edgHeL->hedCnr->cnrVtx->coord, pnt,npnts);
	}
	lflag = TRUE;
      }
    } else if (*npnts % 2 == 0) {
      lflag = TRUE;
    } else {
      *npnts = 0;                                 /* Degenerate case. */
    }
  }
  return (lflag);
}
