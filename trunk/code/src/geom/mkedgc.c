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
/* mkedgc-20 Jul 03:08 Sep 07
|     (C)Copyright, JJU Research, 2003-2007.
|
|     Description:
|       Form a data structure for a new Edge record and form it as the
|     child of a designated Solid.
|
|     Access:
|       edge = (Edge *) mkedgc(Solid *solid);
|     Solid *solid, i-Pointer to the parent Solid record.
|     Edge  *edge,  o-Pointer to the new Edge record.
|
|     Error Conditions:
|       If solid does not point to a valid Solid record then execution 
|     is aborted.  A message is printed.
|
|     Comments:
|       The new Edge record is formed as a child of the designated
|     Solid.  There are not any Hedges on either the right or the left
|     of the new Edge; these are set to NULL.
*
*     History:
*     20 Jul 03:JJU-Original.
*     08 Sep 07:JJU-Added error message.
* ------------------------------------------------------------------- */
 
#include "libgeo.h"
#ifdef ANSI
  Edge *mkedgc(Solid *solid)
#else
  Edge *mkedgc(solid)
  Solid *solid;
#endif
{
  Edge *edge, *edgptr;

  if (solid->type == SOLID) {
    edge = (Edge *) malloc(sizeof(Edge));
    edge->type   = EDGE;
    edge->nxtEdg = NULL;
    edgptr = solid->sldEdg;
    if (edgptr) {
      while (edgptr->nxtEdg) edgptr = edgptr->nxtEdg;
      edgptr->nxtEdg = edge;
    } else {
      solid->sldEdg  = edge;
    }
    edge->edgSld = solid;
    edge->edgHeL = NULL;
    edge->edgHeR = NULL;
    ++solid->nedges;                     /* Solid->nedges = 1, 2, ... */
    ldnanc((void *) &(edge->length));
    edge->coeff = 1.0;
  } else {
    echoc();
    textc("*** mkedgc: Invalid Solid record. ***", TRUE);
    abortc();
  }
  return(edge);
}
