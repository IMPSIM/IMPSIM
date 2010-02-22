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
/* mkcnrc-20 Jul 03:08 Sep 07
|     (C)Copyright, JJU Research, 2003-2007.
|
|     Description:
|       Form a data structure for a new Corner record and form it as
|     the child of a designated Vertex.
|
|     Access:
|       corner = (Corner *) mkcnrc(Vertex *vertex);
|     Vertex * vertex, i-Pointer to the parent Vertex record.
|     Corner * corner, o-Pointer to the newly formed Corner record.
|
|     Error Conditions:
|       If vertex does not point to a valid Vertex record then execution 
|     is aborted.  A message is printed.
|
|     Comments:
|       The new Corner is added to the end of the list of corners at the
|     designated Vertex.  There is not yet a Hedge in this Corner.
*
*     History:
*     20 Jul 03:JJU-Original.
*     08 Sep 07:jju-Added error message.
* ------------------------------------------------------------------- */
 
#include "libgeo.h"
#ifdef ANSI
  Corner *mkcnrc(Vertex *vertex)
#else
  Corner *mkcnrc(vertex)
  Vertex *vertex;
#endif
{
  Corner *corner, *cnrptr;

  if (vertex->type == VERTEX) {
    corner = (Corner *) malloc(sizeof(Corner));
    corner->type = CORNER;
    cnrptr = vertex->vtxCnr;
    if (cnrptr) {
      while (cnrptr->nxtCnr) cnrptr = cnrptr->nxtCnr;
      cnrptr->nxtCnr = corner;
    } else {
      vertex->vtxCnr = corner;
    }
    corner->nxtCnr = NULL;
    corner->cnrVtx = vertex;
    corner->cnrHed = NULL;
    corner->nhedgs = 0;
    ldnanc((void *) &(corner->sldang));
    ++vertex->vtxSld->ncnrs;             /* Solid->ncnrs  = 1, 2, ... */
    ++vertex->ncnrs;                     /* Vertex->ncnrs = 1, 2, ... */
  } else {
    echoc();
    textc("*** mkcnrc: Invalid Vertex record. ***", TRUE);
    abortc();
  }
  return(corner);
}
