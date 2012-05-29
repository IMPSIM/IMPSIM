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
/* qcrgnc-01 Jan 00:16 Aug 09
|     (C)Copyright, JJU Research, 2000-2009
|
|     Description:
|       Find the type of contact and the contact region of two solids 
|     specified by a Contact for which the two solids touch each other.
|
|     Access:
|       lfound = (int) qcrgnc(Contact *cntact);
|     Contact *cntact,i-Record specifying Contact to be investigated.
|     int      lfound,o-Flag set TRUE if contact region is found.
|
|     Error Conditions:
|       If the two solids do not touch each other, exit is made with
|     lfound=FALSE.
|
|     Comments:
|       Assuming that the two solids touch, the integer types of contact 
|     and pointers to the specific components in contact and an array of  
|     points in the contact region are stored in the Contact record.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  int qcrgnc(Contact *cntact)
#else
  int qcrgnc(cntact)
  Contact *cntact;
#endif
{
# define  MXON     (32)      /* Max entities in contact with a Solid. */
  int     i, j, k, lfound, nedonA, nedonB, nfconA, nfconB, npnts, 
	    nvxonA, nvxonB;
  real    pnt[2][3];
  Edge   *edonA[MXON], *edonB[MXON];
  Face   *fconA[MXON], *fconB[MXON];
  Vertex *vxonA[MXON], *vxonB[MXON];

  lfound = FALSE;
  if (vabsc(3, cntact->pln_dir) < zrogeo) {

/* Search for the possible components in contact. */
    qrfevc(cntact->cnSldA, cntact->pln_pntA, fconA, edonA, vxonA, 
      &nfconA, &nedonA, &nvxonA);
    qrfevc(cntact->cnSldB, cntact->pln_pntB, fconB, edonB, vxonB,
      &nfconB, &nedonB, &nvxonB);

/* Check for each type of contact in order. */
    cntact->numcr = 0;

/* Check for Face on Face contact. */
    for (i=0; i<nfconA; i++) {
      for (j=0; j<nfconB; j++) {
	lfound = qfonfc(fconA[i], fconB[j], cntact->CR, &cntact->numcr);
	if (lfound) {
          cntact->ptrA   = (Face *) fconA[i];
          cntact->ptrB   = (Face *) fconB[j];
          cntact->cntypA = FACE;
          cntact->cntypB = FACE;
	  return(TRUE);
	}
      }
    }

/* Check for Edge on Edge (tangential) contact. */
    for (i=0; i<nedonA; i++) {
      for (j=0; j<nedonB; j++) {
	lfound = qeoetc(edonA[i], edonB[j], pnt, &npnts);
	if (lfound) {
	  for (k=0; k<npnts; k++) {
	    ptocrc(pnt[k], cntact->CR, &cntact->numcr);
	  }
          cntact->ptrA   = (Edge *) edonA[i];
          cntact->ptrB   = (Edge *) edonB[j];
          cntact->cntypA = EDGE;
          cntact->cntypB = EDGE;
	  return(TRUE);
	}
      }
    }

/* Check for Edge on Edge (cross) contact. */
    for (i=0; i<nedonA; i++) {
      for (j=0; j<nedonB; j++) {
	lfound = qeoexc(edonA[i], edonB[j], pnt[0]);
	if (lfound) {
	  ptocrc(pnt[0], cntact->CR, &cntact->numcr);
          cntact->ptrA   = (Edge *) edonA[i];
          cntact->ptrB   = (Edge *) edonB[j];
          cntact->cntypA = EDGE;
          cntact->cntypB = EDGE;
	  return(TRUE);
	}
      }
    }

/* Check for a Edge on Face contact. */
    for (i=0; i<nedonA; i++) {
      for (j=0; j<nfconB; j++) {
	lfound = qeonfc(edonA[i], fconB[j], pnt, &npnts);
	if (lfound) {
	  for (k=0; k<npnts; k++) {
	    ptocrc(pnt[k], cntact->CR, &cntact->numcr);
	  }
          cntact->ptrA   = (Edge *) edonA[i];
          cntact->ptrB   = (Face *) fconB[j];
          cntact->cntypA = EDGE;
          cntact->cntypB = FACE;
	  return(TRUE);
	}
      }
    }
    for (i=0; i<nfconA; i++) {
      for (j=0; j<nedonB; j++) {
	lfound = qeonfc(edonB[j], fconA[i], pnt, &npnts);
	if (lfound) {
	  for (k=0; k<npnts; k++) {
	    ptocrc(pnt[k], cntact->CR, &cntact->numcr);
	  }
          cntact->ptrA   = (Face *) fconA[i];
          cntact->ptrB   = (Edge *) edonB[j];
          cntact->cntypA = FACE;
          cntact->cntypB = EDGE;
	  return(TRUE);
	}
      }
    }

/* Check for a Vertex on Vertex contact. */
    for (i=0; i<nvxonA; i++) {
      for (j=0; j<nvxonB; j++) {
	lfound = qponvc(vxonB[j]->coord, vxonA[i]);
	if (lfound) {
	  ptocrc(vxonB[j]->coord, cntact->CR, &cntact->numcr);
          cntact->ptrA   = (Vertex *) vxonA[i];
          cntact->ptrB   = (Vertex *) vxonB[j];
          cntact->cntypA = VERTEX;
          cntact->cntypB = VERTEX;
	  return(TRUE);
	}
      }
    }

/* Check for an Edge on Vertex contact. */
    for (i=0; i<nedonA; i++) {
      for (j=0; j<nvxonB; j++) {
	lfound = qponec(vxonB[j]->coord, edonA[i]);
	if (lfound) {
	  ptocrc(vxonB[j]->coord, cntact->CR, &cntact->numcr);
          cntact->ptrA   = (Edge *)   edonA[i];
          cntact->ptrB   = (Vertex *) vxonB[j];
          cntact->cntypA = EDGE;
          cntact->cntypB = VERTEX;
	  return(TRUE);
	}
      }
    }
    for (i=0; i<nvxonA; i++) {
      for (j=0; j<nedonB; j++) {
	lfound = qponec(vxonA[i]->coord, edonB[j]);
	if (lfound) {
	  ptocrc(vxonA[i]->coord, cntact->CR, &cntact->numcr);
          cntact->ptrA   = (Vertex *) vxonA[i];
          cntact->ptrB   = (Edge *)   edonB[j];
          cntact->cntypA = VERTEX;
          cntact->cntypB = EDGE;
	  return(TRUE);
	}
      }
    }

/* Check for a Face on Vertex contact. */
    for (i=0; i<nfconA; i++) {
      for (j=0; j<nvxonB; j++) {
	lfound = qponfc(vxonB[j]->coord, fconA[i]);
	if (lfound) {
	  ptocrc(vxonB[j]->coord, cntact->CR, &cntact->numcr);
          cntact->ptrA   = (Face *)   fconA[i];
          cntact->ptrB   = (Vertex *) vxonB[j];
          cntact->cntypA = FACE;
          cntact->cntypB = VERTEX;
	  return(TRUE);
	}
      }
    }
    for (i=0; i<nvxonA; i++) {
      for (j=0; j<nfconB; j++) {
	lfound = qponfc(vxonA[i]->coord, fconB[j]);
	if (lfound) {
	  ptocrc(vxonA[i]->coord, cntact->CR, &cntact->numcr);
          cntact->ptrA   = (Vertex *) vxonA[i];
          cntact->ptrB   = (Face *)   fconB[j];
          cntact->cntypA = VERTEX;
          cntact->cntypB = FACE;
	  return(TRUE);
	}
      }
    }

/* Check for any other contact. */
    if ((nfconA+nedonA+nvxonA == 1) && (nfconB+nedonB+nvxonB == 1)) {
      if (nfconA == 1) {
        cntact->ptrA   = (Face *) fconA[0];
        cntact->cntypA = FACE;
      }
      if (nedonA == 1) {
        cntact->ptrA   = (Edge *) edonA[0];
        cntact->cntypA = EDGE;
      }
      if (nvxonA == 1) {
        cntact->ptrA   = (Vertex *) vxonA[0];
        cntact->cntypA = VERTEX;
      }
      if (nfconB == 1) {
        cntact->ptrB   = (Face *) fconB[0];
        cntact->cntypB = FACE;
      }
      if (nedonB == 1) {
        cntact->ptrB   = (Edge *) edonB[0];
        cntact->cntypB = EDGE;
      }
      if (nvxonB == 1) {
        cntact->ptrB   = (Vertex *) vxonB[0];
        cntact->cntypB = VERTEX;
      }
      cntact->numcr = 1;
      for (i=0; i<3; i++) {cntact->CR[0][i] = cntact->pln_pntA[i];}
      return(TRUE);
    }
  }
  return(lfound);
}
