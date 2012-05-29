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
/* mkevc-25 Jul 03:08 Sep 07
|     (C)Copyright, JJU Research, 2003-2007.
|
|     Description:
|       Modify a Solid by adding a new Edge and a new Vertex.
|
|     Access:
|       edge = (Edge *) mkevc(Hedge *hedB, Hedge *hedA, real x,
|                 real y, real z);
|     Hedge *hedB, i-Pointer to first Hedge before new Edge/Vertex.
|     Hedge *hedA, i-Pointer to first Hedge after  new Edge/Vertex.
|     real   x,    i-Coordinate of new Vertex relative to Body axes.
|     real   y,    i-Coordinate of new Vertex relative to Body axes.
|     real   z,    i-Coordinate of new Vertex relative to Body axes.
|     Edge  *edge, o-Pointer to new Edge record created.
|
|     Error Conditions:
|       If hedB and hedA are not both valid Hedge records, or do not
|     share the same Corner and Vertex on entry, then execution is
|     aborted.  A message is printed.
|
|     Comments:
|       This is an Euler operator for geometry creation.
|       The shared Vertex is augmented in series by a new following Edge
|     (edge) ending at a new Vertex with location (x,y,z).  A new Corner
|     is formed at the new Vertex.  Two new Hedges are also formed on
|     either side of the new "edge".  The new Hedge on the left of
|     "edge" is inserted into the existing Corner, immediately preceding
|     Hedge hedB.  The new Hedge on the right of "edge" is inserted into
|     the new Corner.
|       If hedB and hedA both point to the same Hedge and hedB is the 
|     mate of hedA, then the new "edge" ending at the new Vertex are
|     formed starting in that Corner and Perim of that hedge.  That
|     hedge becomes the Hedge on the left of the new "edge" and only one
|     new Hedge is formed.
|       If hedA and hedB both point to the same hedge and hedB is not 
|     the mate of hedA, then a new "strut" edge is formed in that Perim
|     preceding hedB and hedA and ending at the new Vertex.
|       In the case where hedB and hedA share the same Corner then the
|     new edge and Vertex are inserted following that Corner and all 
|     Hedges starting with hedA up to but not including hedA are moved
|     to the new Corner at the new Vertex.
*
*     History:
*     25 Jul 03:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libgeo.h"
#ifdef ANSI
  Edge *mkevc(Hedge *hedB, Hedge *hedA, real x, real y, real z)
#else
  Edge  *mkevc(hedB, hedA, x, y, z)
  Hedge *hedB, hedA;
  real  x, y, z;
#endif
{
  Corner *cnrA, *cnrB;
  Edge   *edge;
  Hedge  *hedge, *hedL, *hedR;
  Perim  *prmL, *prmR;
  Solid  *solid;
  Vertex *vertex;

  if (hedB == NULL || hedA == NULL) {
    textc("*** mkevc:  Invalid Hedge records. ***", TRUE);
    abortc();
  }
  cnrB = hedA->hedCnr;                /* Find the Corner before hedA. */
  if (hedB->hedCnr == cnrB) {  /* See that Corner before hedB agrees. */
    solid = cnrB->cnrVtx->vtxSld;                  /* Find the Solid. */
    if (solid == NULL) {
      echoc();
      textc("*** mkevc:  Invalid Solid record. ***", TRUE);
      abortc();
    }
    vertex = mkvtxc(solid, x, y, z);  /* Locate or create new Vertex. */
    cnrA   = mkcnrc(vertex);                /* Create the new Corner. */
    hedge  = hedA;    /* For Hedges of cnrB from hedA to before hedB. */
    while (hedge != hedB) {
      hedge->hedCnr = cnrA;   /* Move the Hedge to start at new cnrA. */
      cnrB->nhedgs--;    /* Decrease count of Hedges moved from cnrB. */
      cnrA->nhedgs++;    /* Increase count of Hedges moved to   cnrA. */
      if (hedge->hedEdg != NULL) {
        edlngc(hedge->hedEdg);      /* Update lengths of moved Edges. */
      }
      hedge= hedge->nxtHedCnr;    /* Get next outgoing Hedge of cnrB. */
    }
    edge   = mkedgc(solid);                   /* Create the new Edge. */
    prmL   = hedA->hedPrm; /* Find the Perim on left of the new Edge. */
    if (hedB->hedMat == hedB) { 
      hedL = hedB;    /* Get or create Hedge on left of the new Edge. */
    } else {
      hedL = mkhedc(prmL, cnrB);
    }
    ringbc(prmL, hedL, hedA);       /* Move hedL before hedA in prmL. */
    hedL->hedEdg = edge;  /* Make this the Hedge on left of new Edge. */
    edge->edgHeL = hedL;
    prmR = hedA->hedPrm;      /* Find Perim on right of the new Edge. */
    hedR = mkhedc(prmR, cnrA); /* Create Hedge for right of new Edge. */
    ringbc(prmR, hedR, hedB);       /* Move hedR before hedB in prmR. */
    hedR->hedEdg = edge;  /*Make this the Hedge on right of new Edge. */
    edge->edgHeR = hedR;
    hedR->hedMat = hedL;
    hedL->hedMat = hedR;
    edlngc(edge);                 /* Find the length of the new Edge. */
  } else {
    echoc();
    textc("*** mkevc: HedB and HedA do not share the same Corner. ***",
      TRUE);
    abortc();
  }
  return(edge);
}
