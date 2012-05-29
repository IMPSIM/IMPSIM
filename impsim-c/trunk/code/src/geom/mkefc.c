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
/* mkefc-21 Aug 03:07 Mar 09
|     (C)Copyright, JJU Research, 2003-2009.
|
|     Description:
|       Modify a Solid by adding a new Edge and a new Face.
|
|     Access:
|       edge = (Edge *) mkefc(Hedge *hedB, Hedge *hedA);
|     Hedge *hedB, i-Pointer to the Hedge before the new Edge.
|     Hedge *hedA, i-Pointer to the Hedge after  the new Edge.
|     Edge  *edge, o-Pointer to address of new Edge record added.
|
|     Error Conditions:
|       If hedB and hedA do not point to valid Hedge records shared in a
|     common Perim, then execution is aborted.  A message is printed.
|
|     Comments:
|       This is an Euler operator for geometry creation.
|       The Vertex before hedB becomes the starting Vertex for a new 
|     Edge (edge) which terminates at the Vertex before hedA.  Two new
|     Hedges are formed on the two sides of the new edge.  The new Hedge
|     on the left of the new edge is inserted in a new Perim. The Hedges
|     starting with hedA up to but not including hedA are then removed 
|     from their old Perim and inserted into this new Perim in sequence.
|     A new Hedge on the right of the new edge is then inserted into the
|     old Perim preceding hedB.  Any further Hedges remain in the old
|     Perim. The new Perim becomes the boundary of a new Face.
*
*     History:
*     21 Aug 03:JJU-Original.
*     08 Sep 07:JJU-Added error message.
* ------------------------------------------------------------------- */
 
#include "libgeo.h"
#ifdef ANSI
  Edge   *mkefc(Hedge *hedB, Hedge *hedA)
#else
  Edge   *mkefc(hedB, hedA)
  Hedge  *hedB, *hedA;
#endif
{
  Corner *cnrA, *cnrB;
  Edge   *edge;
  Face   *facL, *facR;
  Hedge  *hed, *hedL, *hedR;
  Perim  *prmL, *prmR;
  Solid  *solid;
  Vertex *vtxA, *vtxB;
  int     k;

  prmR = hedB->hedPrm;                    /* Find the old Perim prmR. */
  if (hedA->hedPrm == prmR) {         /* Assure both Hedges share it. */
    facR = prmR->prmFac;                  /* Find the old Face  facR. */
    solid= facR->facSld;                     /* Find the Solid solid. */
    cnrB = hedB->hedCnr;                     /* Find old Corner cnrB. */
    vtxB = cnrB->cnrVtx;                     /* Find old Vertex vtxB. */
    cnrA = hedA->hedCnr;                     /* Find old Corner cnrA. */
    vtxA = cnrA->cnrVtx;                     /* Find old Vertex vtxA. */
    facL = mkfac(solid);                   /* Create new Face   facL. */
    facL->kcolor = facR->kcolor;
    for (k=0; k<4; k++) facL->faceq[k] = facR->faceq[k];
    facL->coeff  = facR->coeff;
    prmL = mkprmc(facL);                   /* Create new Perim  prmL. */
    edge = mkedgc(solid);                  /* Create new Edge   edge. */
    hedL = mkhedc(prmL, cnrB);             /* Create new Hedge  hedL. */
    hedL->hedEdg = edge;                /* Set hedL to point to edge. */
    edge->edgHeL = hedL;
    hedR = mkhedc(prmR, cnrA);             /* Create new Hedge  hedR. */
    hedR->hedEdg = edge;                /* Set hedR to point to edge. */
    edge->edgHeR = hedR;
    hedL->hedMat = hedR;
    hedR->hedMat = hedL;
    hed = hedB;                      /* Set hed as Hedge before hedA. */
    while (hed->nxtHedPrm != hedA) hed = hed->nxtHedPrm;
    hed->nxtHedPrm  = hedR;          /* Set hedR as Hedge after hed.  */
    hedL->nxtHedPrm = hedA;          /* Set hedA as Hedge after hedL. */
    hedR->nxtHedPrm = hedB;          /* Set hedB as Hedge after hedR. */
    hed = hedA;
    while (hed != hedL) {
      if (hed->nxtHedPrm == hedB) hed->nxtHedPrm = hedL;
      hed->hedPrm = prmL;       /* Set moved Hedges to point to prmL. */
      prmL->nhedgs++;            /* Increase count of Hedges in prmL. */
      prmR->nhedgs--;            /* Decrease count of Hedges in prmR. */
      hed = hed->nxtHedPrm;
    }
    edlngc(edge);                 /* Find the length of the new edge. */
    prmarc(prmL);                  /* Find the area of the  new prmL. */
    prmarc(prmR);               /* Updated the area of modified prmR. */
  } else {
    echoc();
    textc("*** mkefc: Invalid Hedge records. ***", TRUE);
    abortc();
  }
  return(edge);
}
