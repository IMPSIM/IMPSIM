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
/* xcnrc-23 Jul 03:09 Sep 07
|     (C)Copyright, JJU Research, 2003-2007.
|
|     Description:
|       Delete a specified Corner record and any dependent Edge records
|     from a solid model.
|
|     Access:
|       (void) xcnrc(Corner *cnr);
|     Corner *cnr, i-Pointer to the Corner record to be deleted.
|
|     Error Conditions:
|       If cnr does not point to a valid Corner record then execution is
|     aborted.  A message is printed.
|
|     Comments:
|       None.
*
*     History:
*     23 Jul 03:JJU-Original.
*     09 Sep 07:JJU-Added a message.
* ------------------------------------------------------------------- */
 
#include "libgeo.h"
#ifdef ANSI
  void xcnrc(Corner *cnr)
#else
  void xcnrc(cnr)
  Corner *cnr;
#endif
{
  Corner *corner;
  Edge   *edge;
  Hedge  *hedge;
  Solid  *solid;
  Vertex *vertex;

  if (cnr->type == CORNER) {
    vertex = cnr->cnrVtx;
    corner = vertex->vtxCnr;
    if (corner == cnr) {
      vertex->vtxCnr = cnr->nxtCnr;
    } else {
      while (corner) {
        if (corner->nxtCnr == cnr) corner->nxtCnr = cnr->nxtCnr;
        corner = corner->nxtCnr;
      }
    }
    solid = vertex->vtxSld;
    edge  = solid->sldEdg;
    while (edge) {
      hedge = edge->edgHeL;
      if (hedge->hedCnr == cnr) xhedc(hedge);
      hedge = edge->edgHeR;
      if (hedge->hedCnr == cnr) xhedc(hedge);
      edge = edge->nxtEdg;
    }
    vertex->ncnrs--;
    solid->ncnrs--;
    free(cnr);
  } else {
    echoc();
    textc("*** xcnrc:  Invalid Corner record. ***", TRUE);
    abortc();
  }
  return;
}
