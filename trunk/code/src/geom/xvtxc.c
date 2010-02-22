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
/* xvtxc-23 Jul 03:09 Sep 07
|     (C)Copyright, JJU Research, 2003-2007.
|
|     Description:
|       Delete a specified Vertex record and any dependent Corner
|     records from a solid model.
|
|     Access:
|       (void) xvtxc(Vertex *vtx);
|     Vertex *vtx, i-Pointer to the Vertex record to be deleted.
|
|     Error Conditions:
|       If vtx does not point to a valid Vertex record then execution is
|     aborted.  A message is printed.
|
|     Comments:
|       None.
*
*     History:
*     23 Jul 03:JJU-Original.
*     09 Sep 07:JJU-Added error message.
* ------------------------------------------------------------------- */
 
#include "libgeo.h"
#ifdef ANSI
  void xvtxc(Vertex *vtx)
#else
  void xvtxc(vtx)
  Vertex *vtx;
#endif
{
  Vertex *vertex;

  if (vtx->type == VERTEX) {
    vertex = vtx->vtxSld->sldVtx;
    if (vertex == vtx) {
      vtx->vtxSld->sldVtx = vtx->nxtVtx;
    } else {
      while (vertex->nxtVtx != vtx) {
        if (vertex->nxtVtx == NULL) {
          echoc();
          textc("*** xvtxc:  NULL Vertex record. ***", TRUE);
          abortc();
        }
        vertex = vertex->nxtVtx;
      }
      vertex->nxtVtx = vtx->nxtVtx;
    }
    while (vtx->vtxCnr) xcnrc(vtx->vtxCnr);
    vtx->vtxSld->nvrtxs--;
    free(vtx);
  } else {
    echoc();
    textc("*** xvtxc:  Invalid Vertex record. ***", TRUE);
    abortc();
  }
  return;
}
