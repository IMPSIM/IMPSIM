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
/* edlngc-01 Jan 00:15 Jul 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Compute and store the length of a specified Edge.
|
|     Access:
|       edlong = (real) edlngc(Edge *edge);
|     Edge *edge, i -Pointer to the Edge record.
|     real edlong,o -Length found for the edge.
|
|     Error Conditions:
|       If *edge is not a valid Edge record, execution is aborted.  A
|     message is printed.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libgeo.h"
#ifdef ANSI
  real edlngc(Edge *edge)
#else
  real edlngc(edge)
  Edge *edge;
#endif
{
  Vertex *vxB, *vxA;
  int     k;
  real    edlong, vector[3], wA, wB;

  if (edge->type == EDGE) {
    vxB = edge->edgHeL->hedCnr->cnrVtx;
    wB  = vxB->coord[3];
    vxA = edge->edgHeL->nxtHedPrm->hedCnr->cnrVtx;
    wA  = vxA->coord[3];
    for (k=0; k<3; k++) vector[k] = vxA->coord[k]/wA - vxB->coord[k]/wB;
    edlong = vabsc(3, vector);
    edge->length = edlong;
  } else {
    echoc();
    textc("*** edlngc: Invalid Edge record. ***", TRUE);
    abortc();
  }
  return(edlong);
}
