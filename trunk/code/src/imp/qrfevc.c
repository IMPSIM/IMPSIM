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
/* qrfevc-01 Jan 00:15 Jul 09
|     (C)Copyright, JJU Research, 2000-2009
|
|     Description:
|       Search a specified solid for faces, edges, and vertices which 
|     are in contact with a specified pnt.
|
|     Access:
|       (void) qrfevc(Solid *solid, real pnt[3], Face *faceon[],
|         Edge *edgeon[], Vertex *vtxon[], int *nfacon, int *nedon,
|         int *nvxon);
|     Solid  *solid,   i-Record specifying solid to be investigated.
|     real    pnt[3],  i-Coordinates of the specified point.
|     Face   *faceon[],o-Array of pointers to faces in contact.
|     Edge   *edgeon[],o-Array of pointers to edges in contact.
|     Vertex *vtxon[], o-Array of pointers to vertices in contact.
|     int    *nfacon,  o-Number of face   records in faceon[] array.
|     int    *nedgon,  o-Number of edge   records in edgeon[] array.
|     int    *nvtxon,  o-Number of vertex records in vtxon[] array.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void qrfevc(Solid *solid, real pnt[3], Face *faceon[], Edge *edgeon[],
    Vertex *vtxon[], int *nfacon, int *nedgon, int *nvtxon)
#else
  void qrfevc(solid, pnt, faceon, edgeon, vtxon, nfacon, nedgon, nvtxon)
  Solid  *solid;
  real    pnt[3];
  Face   *faceon[];
  Edge   *edgeon[];
  Vertex *vtxon[];
  int    *nfacon, *nedgon, *nvtxon;
#endif
{
  Corner *corner;
  Edge   *edge;
  Face   *face;
  Vertex *vx;
  int     lfound;

/* Initialize. */
  *nfacon = 0;
  *nedgon = 0;
  *nvtxon = 0;
  lfound  = FALSE;

/* Loop through all vertices of the solid. */
  for (vx=solid->sldVtx; (vx!=NULL)&&(!lfound); vx=vx->nxtVtx) {
    lfound = qponvc(pnt, vx);
    if (lfound) {
      vtxon[(*nvtxon)++] = vx;

/* Include all edges and faces connected to this vertex. */
      for (corner=vx->vtxCnr; corner; corner=corner->nxtCnr) {
        for (edge=corner->cnrHed->hedEdg; edge;
            edge=edge->edgHeR->nxtHedCnr->hedEdg) {
          edgeon[(*nedgon)++] = edge;
          faceon[(*nfacon)++] = edge->edgHeL->hedPrm->prmFac;
	}
        for (edge=corner->cnrHed->hedEdg; edge;
            edge=edge->edgHeL->nxtHedCnr->hedEdg) {
          edgeon[(*nedgon)++] = edge;
          faceon[(*nfacon)++] = edge->edgHeL->hedPrm->prmFac;
	}
      }
    }
  }

/* Loop through all edges of the solid. */
  if (!lfound) {
    for (edge=solid->sldEdg; edge; edge=edge->nxtEdg) {
      lfound = qponec(pnt, edge);
      if (lfound) {
        edgeon[(*nedgon)++] = edge;

/* Include the faces connected to this edge. */
        faceon[(*nfacon)++] = edge->edgHeL->hedPrm->prmFac;
        faceon[(*nfacon)++] = edge->edgHeR->hedPrm->prmFac;
	break;
      }
    }
  }

/* Loop through all faces of the solid. */
  if (!lfound) {
    for (face=solid->sldFac; face; face=face->nxtFac) {
      lfound = qponfc(pnt, face);
      if (lfound) {
        faceon[(*nfacon)++] = face;
	break;
      }
    }
  }
  return;
}
