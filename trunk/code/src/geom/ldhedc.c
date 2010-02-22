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
/* ldhedc-01 Jan 00:15 Jul 09
|     (C)Copyright, JJU Research, 2000-2009
|
|     Description:
|       Create a new Halfedge for a specified Edge of a solid.
|
|     Access:
|       hedge = (Hedge *) ldhedc(Edge *edge);
|     Edge  *edge, i-Pointer to the Edge for this new Halfedge.
|     Hedge *hedge,o-Pointer to the Hedge record created.
|
|     Error Conditions:
|       If edge is not of type EDGE, then execution is aborted.
|
|     Comments:
|       The new Hedge is not connected to a Perim or Corner or mating
|     hedge, or as the right or left hedge of the edge.  This must be
|     done by the calling program.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libgeo.h"
#ifdef ANSI
  Hedge *ldhedc(Edge *edge)
#else
  Hedge *ldhedc(edge)
  Edge *edge;
#endif
{
  Hedge *hedge;

  if (edge->type != EDGE) abortc();
  hedge = (Hedge *) malloc(sizeof(Hedge));
  if (hedge) {
    hedge->type   = HEDGE;
    hedge->nxtHedPrm = hedge;
    hedge->nxtHedCnr = hedge;
    hedge->hedPrm = NULL;
    hedge->hedCnr = NULL;
    hedge->hedEdg = edge;
    hedge->hedMat = NULL;
  }
  return(hedge);
}
