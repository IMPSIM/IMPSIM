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
/* xedgc-23 Jul 03:09 Sep 07
|     (C)Copyright, JJU Research, 2003-2007.
|
|     Description:
|       Delete a specified Edge record from a solid model.
|
|     Access:
|       (void) xedgc(Edge *edg);
|     Edge *edg, i-Pointer to the Edge record to be deleted.
|
|     Error Conditions:
|       If edg does not point to a valid Edge record then execution is
|     aborted.  A message is printed.
|
|     Comments:
|       None.
*
*     History:
*     20 Jul 03:JJU-Original.
*     09 Sep 07:JJU-Printed error message.
* ------------------------------------------------------------------- */
 
#include "libgeo.h"
#ifdef ANSI
  void xedgc(Edge *edg)
#else
  void xedgc(edg)
  Edge  *edg;
#endif
{
  Edge   *edge;
  Hedge  *hedge;

  if (edg->type == EDGE) {
    edge = edg->edgSld->sldEdg;
    if (edge == edg) {                /* Bypass edg in list of Edges. */
      edg->edgSld->sldEdg = edg->nxtEdg;
    } else {
      while (edge->nxtEdg != edg) {edge = edge->nxtEdg;}
      edge->nxtEdg = edg->nxtEdg;       
    }
    hedge = edg->edgHeL;
    if (hedge) {
      hedge->hedEdg = NULL;         /* Remove Hedge on left from edg. */
    }
    edg->edgHeL = NULL;
    hedge = edg->edgHeR;
    if (hedge) {
      hedge->hedEdg = NULL;        /* Remove Hedge on right from edg. */
    }
    edg->edgHeR = NULL;
    edg->edgSld->nedges--;
    free(edg);
  } else {
    echoc();
    textc("*** xedgc:  Invalid Edge record. ***", TRUE);
    abortc();
  }
  return;
}
