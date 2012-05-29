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
/* sclbdc-28 Jun 04:15 Jul 09
|     (C)Copyright, JJU Research, 2004-2009.
|
|     Description:
|       Modify the scale of a specified Body about its origin by a given
|     factor.
|
|     Access:
|       (void) sclbdc(Body *body, real factor);
|     Body *body,  i-Pointer to the Body to be scaled.
|     real  factor,i-Specified scale factor.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       None.
*
*     History:
*     28 Jun 04:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libgeo.h"
#ifdef ANSI
  void sclbdc(Body *body, real factor)
#else
  void sclbdc(body, factor)
  Body *body;
  real  factor;
#endif
{
  Axes   *axes;
  Edge   *edge;
  Face   *face;
  Perim  *perim;
  Point  *point;
  Solid  *solid;
  Vertex *vertex;
  int    i;
  real   cube, square;

/* Loop through all Solids of the Body. */
  square = factor * factor;
  cube   = square * factor;
  solid  = body->bdySld;
  while (solid) {
    for (i=0; i<3; i++) solid->screw[i+3] *= factor;
    solid->area   *= square;
    solid->volume *= cube;
    for (i=0; i<3; i++) solid->cg[i]         *= factor;
    for (i=0; i<3; i++) solid->smin_coord[i] *= factor;
    for (i=0; i<3; i++) solid->smax_coord[i] *= factor;
    for (i=0; i<3; i++) solid->bs_ctr[i]     *= factor;

/* Loop through all Vertices of this Solid. */
    vertex = solid->sldVtx;
    while (vertex) {
      for (i=0; i<3; i++) vertex->coord[i] *= factor;
      vertex = vertex->nxtVtx;
    }

/* Loop through all Edges of this Solid. */
    edge = solid->sldEdg;
    while (edge) {
      edge->length *= factor;
      edge = edge->nxtEdg;
    }

/* Loop through all Faces of this Solid. */
    face = solid->sldFac;
    while (face) {
      face->faceq[3] *= factor;
      face->area     *= square;

/* Loop through all Perims of this Face. */
      perim = face->facPrm;
      while (perim) {
        perim->area *= square;
        perim = perim->nxtPrm;
      }
      face = face->nxtFac;
    }
    solid = solid->nxtSld;
  }

/* Loop through all Axes of the Body. */
  axes = body->bdyAxs;
  while (axes) {
    for (i=0; i<3; i++) axes->S[i][3] *= factor;
    axes = axes->nxtAxs;
  }

/* Loop through all Points of the Body. */
  point = body->bdyPnt;
  while (point) {
    for (i=0; i<3; i++) point->coord[i] *= factor;
    point = point->nxtPnt;
  }
  lsaved = lsaved && (factor == 1.0);
  ldraw  = TRUE;
  return;
}
