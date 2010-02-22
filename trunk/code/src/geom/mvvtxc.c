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
/* mvvtxc-01 Jul 04:15 Jul 09
|     (C)Copyright, JJU Research, 2004-2009.
|
|     Description:
|       Modify the Body coordinates of a specified Vertex.
|
|     Access:
|       (void) mvvtxc(Vertex *vertex, real x, real y, real z);
|     Vertex *vertex,i-Pointer to the Vertex to be moved.
|     real    x,y,z, i-New Body coordinate data for Vertex.
|
|     Error Conditions:
|       If vertex does not point to a record of type VERTEX, execution
|     is aborted.  A message is printed.
|
|     Comments:
|       This function does not support modification of Vertices of 2-D
|     Solids.  If this is attempted, a message is printed and return is
|     made without change of Vertex coordinate data.
|       Since the new x,y,z coordinate data may not fit the plane equa-
|     tions of existing Faces, each Face touching the specified Vertex
|     is first triangulated, isolating the specified Vertex in its own
|     triangular facet.  Then the Vertex data is modified and all
|     affected Face data is recomputed.
|       If the specified x,y,z coordinate data cause a Face-Edge inter-
|     section, the change of the Vertex data is scaled back to avoid
|     intersection; a message is printed.
*
*     History:
*     01 Jul 04:JJU-Original.
*     08 Sep 07:JJU-Added error message.
* ------------------------------------------------------------------- */
 
#include "libgeo.h"
#ifdef ANSI
  void mvvtxc(Vertex *vertex, real x, real y, real z)
#else
  void mvvtxc(vertex, x, y, z)
  Vertex *vertex;
  real   x, y, z;
#endif
{
  Body   *body;
  Corner *corner;
  Edge   *edge, *newedg;
  Face   *face, *newfac;
  Hedge  *hedA, *hedB, *hedge;
  Perim  *perim;
  Solid  *solid;
  int     i;
  real    r[4], rba[4], sigma, tau, w;

/* Verify the Vertex record and locate the Solid and Body records. */
  if (vertex->type == VERTEX) {
    solid  = vertex->vtxSld;
    if (solid->kdimen == SPATIAL) {
      body = solid->sldBdy;
      w    = vertex->coord[3];

/* Test this change in position for intersection with any Face. */
      rba[0] = vertex->coord[0] / w - x;
      rba[1] = vertex->coord[1] / w - y;
      rba[2] = vertex->coord[2] / w - z;
      rba[3] = 1.0;
      tau    = 1.0;
      face   = solid->sldFac;
      while (face) {
        sigma= (vdotc(4, face->faceq, vertex->coord)) /
               (vdotc(4, face->faceq, rba));
        if ((sigma >= 0.0) && (sigma < tau)) {
          for (i=0; i<3; i++) {
            r[i] = vertex->coord[i] / w - sigma * rba[i];
          }
          perim = face->facPrm;
          while (perim) {
            if (lptprc(r, perim)) tau = sigma;
            perim = perim->nxtPrm;
          }
        }
        face = face->nxtFac;
      }

/* Modify the Vertex coordinate data. */
      for (i=0; i<3; i++) {
        r[i] = vertex->coord[i] / w - tau * rba[i];
        vertex->coord[i] = r[i];
      }
      vertex->coord[3] = 1.0;
      if (tau < 1.0) {
        echoc();
        textc("Warning: ", FALSE);
        ftextc(r[0]);
        textc(",", FALSE);
        ftextc(r[1]);
        textc(",", FALSE);
        ftextc(r[2]);
        textc(" used to avoid interference.", TRUE);
        waitc();
      }

/* Increment through Edges at this Vertex. */
      corner = vertex->vtxCnr;
      while (corner) {
        hedge  = corner->cnrHed;
        do {
          edge = hedge->hedEdg;
          edlngc(edge);
          hedA = hedge->hedMat->nxtHedPrm;
          if (hedA->hedPrm->nhedgs > 3) {
            hedB = hedge->hedMat;
            while (hedB->nxtHedPrm != hedge->hedMat) {
              hedB = hedB->nxtHedPrm;
            }
            newedg = mkefc(hedB, hedA);
            newfac = hedA->hedPrm->prmFac;
            fcnrmc(newfac);
            fcnrmc(hedB->hedPrm->prmFac);
          }
          hedge = hedA;
        } while (hedge != corner->cnrHed);
        corner = corner->nxtCnr;
      }
      lsaved = FALSE;
      ldraw  = TRUE;
    } else {
      echoc();
      textc(" *** mvvtxc: Solid is 2-D. ***", TRUE);
    }
  } else {
    echoc();
    textc("*** mvvtxc: Invalid Vertex record. ***", TRUE);
    abortc();
  }
  return;
}
