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
/* edsrtc-01 Jan 00:15 Jul 09
|     (C)Copyright, JJU Research, 2000-2009
|
|     Description:
|       Sort and reorder the Hedge records of a specified Face.
|
|     Access:
|       (void) edsrtc(Face *face);
|     Face *face,i-Pointer to the specified Face record.
|
|     Error Conditions:
|       If face does not point to a valid Face record, execution is
|     aborted.
|
|     Comments:
|       If multiple-closed boundaries are discovered, new Perims are
|     created to accomodate them.
|       The Face equation and bounding box limits are also calculated
|     for the Face after Perims are sorted.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void edsrtc(Face *face)
#else
  void edsrtc(face)
  Face *face;
#endif
{
  Edge   *edge;
  Hedge  *hed, *hedge, *hedque;
  Perim  *perim;
  Vertex *vertex, *vertex0;
  int     nogo1, nogo2, nogo3;

/* Initialize. */
  if (face->type != FACE) {
    textc("*** edsrtc: Face pointer is invalid. ***", TRUE);
    abortc();
  }
  nogo1 = 0;
  nogo2 = 0;
  nogo3 = 0;

/* Loop through and check all current Perims of the face. */
  hedque = NULL;
  for (perim=face->facPrm; perim; perim=perim->nxtPrm) {

/* Identify the initial Hedge and Vertex in the Perim. */
    hedge = perim->prmHed;
    edge = hedge->hedEdg;
    if (edge->edgHeL == hedge) {
      vertex0 = edge->edgHeL->hedCnr->cnrVtx;
    } else if (edge->edgHeR == hedge) {
      vertex0 = edge->edgHeR->hedCnr->cnrVtx;
    } else {
      abortc();
    }
    vertex = vertex0;

/* Sequence through the Hedges and check consecutive connections. */
    while (hedge) {
      edge = hedge->hedEdg;
      if (edge->edgHeL == hedge) {
        if (edge->edgHeL->hedCnr->cnrVtx == vertex) {
          vertex = edge->edgHeR->hedCnr->cnrVtx;
        } else {               /* Save any improper Hedge on a queue. */
          hed = perim->prmHed;
          while (hed) {
            if (hed->nxtHedPrm == hedge) {
              hed->nxtHedPrm = hedge->nxtHedPrm;
              if (hedque != NULL) hedge->nxtHedPrm = hedque->nxtHedPrm;
              hedge->hedPrm = NULL;
              hedque = hedge;
              hedge = hed;
              break;
            } else {
              hed = hed->nxtHedPrm;
            }
          }
        }
      } else if (edge->edgHeR == hedge) {
        if (edge->edgHeR->hedCnr->cnrVtx == vertex) {
          vertex = edge->edgHeL->hedCnr->cnrVtx;
        } else {               /* Save any improper Hedge on a queue. */
          hed = perim->prmHed;
          while (hed) {
            if (hed->nxtHedPrm == hedge) {
              hed->nxtHedPrm = hedge->nxtHedPrm;
              if (hedque != NULL) hedge->nxtHedPrm = hedque->nxtHedPrm;
              hedge->hedPrm = NULL;
              hedque = hedge;
              hedge  = hed;
              break;
            } else {
              hed = hed->nxtHedPrm;
            }
          }
        }
      } else {
        abortc();
      }
      if (vertex == vertex0) {
        while (hedge->nxtHedPrm) {     /* Save extra Hedges on queue. */
          if (hedque) hedge->nxtHedPrm->nxtHedPrm = hedque->nxtHedPrm;
          hedque = hedge->nxtHedPrm;
          hedge->nxtHedPrm = hedge->nxtHedPrm->nxtHedPrm;
          hedge->hedPrm = NULL;
        }
      }
      hedge = hedge->nxtHedPrm;
    }
  }

/* Form a new Perim for any Hedges left on the queue. */
  while (hedque) {
    hedge  = hedque;
    hedque = hedge->nxtHedPrm;
    hedge->nxtHedPrm = NULL;
    edge   = hedge->hedEdg;
    if (edge->edgHeL == hedge) {
      vertex  = edge->edgHeL->hedCnr->cnrVtx;
      vertex0 = edge->edgHeR->hedCnr->cnrVtx;
    } else if(edge->edgHeR == hedge) {
      vertex  = edge->edgHeR->hedCnr->cnrVtx;
      vertex0 = edge->edgHeL->hedCnr->cnrVtx;
    } else {
      abortc();
    }
    if (vertex0 == vertex) {
      nogo1++;
      xhedc(hedge);
    } else {
      perim = mkprmc(face);

/* Insert the initial Hedge into the Perim. */
      hedge->hedPrm = perim;
      perim->prmHed = hedge;
      perim->nhedgs++;

/* Search the Hedges on the queue for the previous Hedge of Perim. */
      while (hedque) {
        for (hedge=hedque; hedge; hedge=hedge->nxtHedPrm) {
          edge = hedge->hedEdg;
          if ((edge->edgHeL == hedge)
            && (edge->edgHeR->hedCnr->cnrVtx == vertex)) {
            if (hedge == hedque) {
              hedque = hedge->nxtHedPrm;
            } else {
              hed = hedque;
              while (hed->nxtHedPrm != hedge) hed = hed->nxtHedPrm;
              hed->nxtHedPrm = hedge->nxtHedPrm;
            }
            hedge->nxtHedPrm = perim->prmHed;
            perim->prmHed = hedge;
            perim->nhedgs++;
            vertex = edge->edgHeL->hedCnr->cnrVtx;
            break;
          } else if ((edge->edgHeR == hedge)
            && (edge->edgHeL->hedCnr->cnrVtx == vertex)) {
            if (hedge == hedque) {
              hedque = hedge->nxtHedPrm;
            } else {
              hed = hedque;
              while (hed->nxtHedPrm != hedge) hed = hed->nxtHedPrm;
              hed->nxtHedPrm = hedge->nxtHedPrm;
            }
            hedge->nxtHedPrm = perim->prmHed;
            perim->prmHed = hedge;
            perim->nhedgs++;
            vertex = edge->edgHeR->hedCnr->cnrVtx;
            break;
          } else {
            abortc();
          }
        }
        if (vertex == vertex0) {
          if (perim->nhedgs <= 2) {
            nogo2++;
            xprmc(perim);
          }
          break;
        }
      }
      if (vertex != vertex0) {
        nogo3++;
        xprmc(perim);
      }
    }
  }
  if (nogo1 > 0) {
    echoc();
    textc("*** Notice: ", FALSE);
    itextc(nogo1);
    textc(" zero length edges are deleted. ***", TRUE);
  }
  if (nogo2 > 0) {
    echoc();
    textc("*** Notice: ", FALSE);
    itextc(nogo2);
    textc(" dangling edges are deleted. ***", TRUE);
  }
  if (nogo3 > 0) {
    echoc();
    textc("*** Notice: ", FALSE);
    itextc(nogo3);
    textc(" faces are not closed. ***", TRUE);
  }
  if ((nogo1 + nogo2 + nogo3) > 0) waitc();
  fcnrmc(face);
  return;
}
