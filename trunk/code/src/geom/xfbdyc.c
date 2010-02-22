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
/* xfbdyc-29 Feb 04:08 Jul 07
|     (C)Copyright, JJU Research, 2004-2007.
|
|     Description:
|       Use a specified transformation matrix to transform all data of
|     a specified Body to a modified location and orientation with
|     respect to the Body coordinate system.
|
|     Access:
|       (void) xfbdyc(Body *body, real xform[3][4]);
|     Body *body,       i-Body to be transformed.
|     real  xform[3][4],i-Transformation to be applied.
|
|     Error Conditions:
|       If *body does not point to a valid Body record, execution is
|     aborted.
|
|     Comments:
|       None.
*
*     History:
*     29 Feb 04:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libgeo.h"
#ifdef ANSI
  void xfbdyc(Body *body, real xform[3][4])
#else
  void xfbdyc(body, xform)
  Body *body;
  real  xform[3][4];
#endif
{
  Axes   *axes;
  Face   *face;
  Point  *pnt;
  Solid  *solid;
  Vertex *vtx;

  if (body->type == BODY) {
    solid = body->bdySld;
    while (solid) {          /* Cycle through all Solids of the Body. */
      vtx = solid->sldVtx;
      while (vtx) {      /* Cycle through all Vertices of this Solid. */
        mpyxrc(xform, vtx->coord, vtx->coord);   /* Transform Vertex. */
        vtx = vtx->nxtVtx;
      }
      face = solid->sldFac;
      while (face) {        /* Cycle through all Faces of this Solid. */
        mpyxvc(xform, face->faceq, face->faceq);
        if (face->facPrm) {
          fcnrmc(face);              /* Transform data for this Face. */
        } else {           /*Transform an unbounded planar halfspace. */
          vtx = solid->sldVtx;
          if (vtx) face->faceq[3] = -vdotc(3, face->faceq, vtx->coord);
        }
        face = face->nxtFac;
      }
      solid = solid->nxtSld;
    }
    axes = body->bdyAxs;
    while (axes) {            /* Cycle through all Axes of this Body. */
      mpyxxc(xform, axes->S, axes->S);             /* Transform Axes. */
      axes = axes->nxtAxs;
    }
    pnt = body->bdyPnt;
    while (pnt) {           /* Cycle through all Points of this Body. */
      mpyxrc(xform, pnt->coord, pnt->coord);      /* Transform Point. */
      pnt = pnt->nxtPnt;
    }
    ldraw = TRUE;
  } else {                                 /* Abort for invalid Body. */
    echoc();
    textc("*** xfbdyc: Invalid Body pointer. ***", TRUE);
    abortc();
  }
  return;
}
