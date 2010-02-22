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
/* qntbc-01 Jan 00:16 Aug 09
|     (C)Copyright, JJU Research, 2000-2009
|
|     Description:
|       Determine the normal, tangential, and binormal direction vectors 
|     for a specified contact.
|
|     Access:
|       lflag = (int) qntbc(Contact *cntact);
|     Contact *cntact,i/o-Contact record to be modified.
|     int      lflag,   o-Flag set TRUE when computation is completed.
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
  int qntbc(Contact *cntact)
#else
  int qntbc(cntact)
  Contact *cntact;
#endif
{
  Body   *bodyA, *bodyB;
  Edge   *edgeA, *edgeB;
  Hedge  *hedge;
  int     i, j, lflag;
  real    area, ax2, R[3], vdotn, v0[3], v1[3], v2[3];

/* Find the centroid of the contact region. */
  lflag = FALSE;
  if (cntact->numcr == 1) {             /* Only one point of contact. */
    for (j=0; j<3; j++) {cntact->cnpoint[j] = cntact->CR[0][j];}
  } else if (cntact->numcr == 2) {              /* A line of contact. */
    for (j=0; j<3; j++) {
      cntact->cnpoint[j] = 0.5 * cntact->CR[0][j] + cntact->CR[1][j];
    }
  } else {                                         /* A contact area. */
    area = 0.0;
    for(j=0; j<3; j++) {cntact->cnpoint[j] = 0.0;}
    for (i=1; i<cntact->numcr; i++) {
      for (j=0; j<3; j++) {   /* Triangulate the region from point 0. */
	v1[j] = cntact->CR[i-1][j] - cntact->CR[0][j];
	v2[j] = cntact->CR[i][j]   - cntact->CR[0][j];
      }
      vcrosc(v1, v2, v0);
      ax2 = vabsc(3, v0);
      area += ax2;          /* Sum twice area of each small triangle. */
      for (j=0; j<3; j++) {
	v0[j] = cntact->CR[i-1][j]+cntact->CR[i][j]+cntact->CR[0][j];
        cntact->cnpoint[j] += ax2 * v0[j];   /* Sum moments of areas. */
      }
    }
    area *= 3.0;
    for (j=0; j<3; j++) {
      cntact->cnpoint[j] /= area;
    }
  }

/* Branch on different contact types. */
  if        ((cntact->cntypA==CN_VERTEX)&&(cntact->cntypB==CN_VERTEX)) {
    goto DONE;
  } else if ((cntact->cntypA==CN_VERTEX)&&(cntact->cntypB==CN_EDGE))   {
    goto DONE;
  } else if ((cntact->cntypA==CN_EDGE)  &&(cntact->cntypB==CN_VERTEX)) {
    goto DONE;
  } else if ((cntact->cntypA==CN_EDGE)  &&(cntact->cntypB==CN_EDGE)
					&& (cntact->numcr==2))         {
    goto DONE;
  } else {

/* Find global coordinate contact normal vector. */
    bodyA = cntact->cnSldA->sldBdy;
    bodyB = cntact->cnSldB->sldBdy;
    if (cntact->cntypA == CN_FACE) {
      mpyxvc(bodyA->T0j,((Face *)cntact->ptrA)->faceq,cntact->cnnormal);
    } else if (cntact->cntypB == CN_FACE) {
      mpyxvc(bodyB->T0j,((Face *)cntact->ptrB)->faceq,cntact->cnnormal);
      for (j=0; j<3; j++) {cntact->cnnormal[j] = - cntact->cnnormal[j];}
    } else {                       /* Edge-Edge crossed type contact. */
      edgeA = (Edge *) cntact->ptrA;
      edgeB = (Edge *) cntact->ptrB;
      for (j=0; j<3; j++) {
        v1[j] = edgeA->edgHeR->hedCnr->cnrVtx->coord[j]
              - edgeA->edgHeL->hedCnr->cnrVtx->coord[j];
        v2[j] = edgeB->edgHeR->hedCnr->cnrVtx->coord[j]
              - edgeB->edgHeL->hedCnr->cnrVtx->coord[j];
      }
      mpyxvc(bodyA->T0j, v1, v1);
      mpyxvc(bodyB->T0j, v2, v2);
      vcrosc(v1, v2, cntact->cnnormal);
      vnormc(3, cntact->cnnormal);
      for (j=0; j<3; j++) {cntact->cnplane[j] = cntact->cnnormal[j];}
      cntact->cnplane[3] = -vdotc(3, cntact->cnnormal, cntact->cnpoint);
      for(hedge = edgeA->edgHeL->hedPrm->prmHed; hedge;
          hedge = hedge->nxtHedPrm) {
        mpyxrc(bodyA->T0j, hedge->hedEdg->edgHeL->hedCnr->cnrVtx->coord,
          R);
        if (cntact->cnplane[3] + vdotc(3,cntact->cnplane,R) > zrogeo) {
          for (j=0;j<3;j++){cntact->cnnormal[j] = -cntact->cnnormal[j];}
	  break;
	}
      }
    }

/* Find the velocities of the two points. */
    mpydrc(bodyA->W, cntact->cnpoint, v1);
    mpydrc(bodyB->W, cntact->cnpoint, v2);
    for (j=0; j<3; j++) {v0[j] = v1[j] - v2[j];}
    vdotn = vdotc(3, v0, cntact->cnnormal);
    if (vdotn > zrogeo) {                          /* Impact occured. */
      vcrosc(v0, cntact->cnnormal, v1);
      if (vabsc(3, v1) > zrogeo) {/* Velocity and normal nonparallel. */
	for (j=0; j<3; j++) {
          cntact->cntangnt[j] = v0[j] - vdotn * cntact->cnnormal[j];
	}
      } else {    /* Relative velocity is parallel to contact normal. */
        for (j=0; j<3; j++) {cntact->cntangnt[j] = 0.0;}
        cntact->cntangnt[2] = 1.0; /* Select arbitrary tangent direc. */
        vcrosc(cntact->cnnormal, cntact->cntangnt, v1);
	if (vabsc(3, v1) < zrogeo) {
          for (j=0; j<3; j++) {cntact->cntangnt[j] = 0.0;}
          cntact->cntangnt[1] = 1.0; /* Select another tangent direc. */
	}
        vcrosc(cntact->cnnormal, cntact->cntangnt, cntact->cntangnt);
        vcrosc(cntact->cntangnt, cntact->cnnormal, cntact->cntangnt);
      }
      vcrosc(cntact->cnnormal, cntact->cntangnt, cntact->cnbinorm);
      vcrosc(cntact->cntangnt, cntact->cnbinorm, cntact->cnnormal);
      vnormc(3, cntact->cntangnt);
      vnormc(3, cntact->cnbinorm);
    }
  }
  lflag = TRUE;
DONE: ;
  return (lflag);
}
