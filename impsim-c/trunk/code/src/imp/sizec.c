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
/* sizec-01 Jan 00:17 Aug 09
|     (C)Copyright, JJU Research, 2000-2007
|
|     Description:
|       Find the maximum and minimum dimensions of the system.
|
|     Access:
|       (void) sizec(real xmin, real ymin, real zmin, real xmax,
|         real ymax, real zmax);
|     real *xmin,o-Minimum global X coordinate of the system.
|     real *ymin,o-Minimum global Y coordinate of the system.
|     real *zmin,o-Minimum global Z coordinate of the system.
|     real *xmax,o-Maximum global X coordinate of the system.
|     real *ymax,o-Maximum global Y coordinate of the system.
|     real *zmax,o-Maximum global Z coordinate of the system.
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
  void sizec(real *xmin, real *ymin, real *zmin, real *xmax, real *ymax,
    real *zmax)
#else
  void sizec(xmin, ymin, zmin, xmax, ymax, zmax)
  real *xmin, *ymin, *zmin, *xmax, *ymax, *zmax;
#endif
{
  Axes   *axes;
  Body   *body;
  Point  *point;
  Solid  *solid;
  Vertex *vertex;
  real outside, r[3];

/* Set impossible initial limits. */
  outside = 1.0 / System.zero;
  *xmin =  outside;
  *ymin =  outside;
  *zmin =  outside;
  *xmax = -outside;
  *ymax = -outside;
  *zmax = -outside;

/* Loop through all body origins, Axes, Points, and Solid Vertices. */
  for (body=System.sysBdy; body; body=body->nxtBdy) {
    if (!isnanc((void *) &body->T0j[0][0])) {
      *xmin = min(*xmin, body->T0j[0][3]);
      *ymin = min(*ymin, body->T0j[1][3]);
      *zmin = min(*zmin, body->T0j[2][3]);
      *xmax = max(*xmax, body->T0j[0][3]);
      *ymax = max(*ymax, body->T0j[1][3]);
      *zmax = max(*zmax, body->T0j[2][3]);
      for (axes=body->bdyAxs; axes; axes=axes->nxtAxs) {
        mpyxrc(body->T0j, &(axes->S[0][3]), r);
        *xmin = min(*xmin, r[0]);
        *ymin = min(*ymin, r[1]);
        *zmin = min(*zmin, r[2]);
        *xmax = max(*xmax, r[0]);
        *ymax = max(*ymax, r[1]);
        *zmax = max(*zmax, r[2]);
      }
      for (point=body->bdyPnt; point; point=point->nxtPnt) {
        ptposc(point, r);
        *xmin = min(*xmin, r[0]);
        *ymin = min(*ymin, r[1]);
        *zmin = min(*zmin, r[2]);
        *xmax = max(*xmax, r[0]);
        *ymax = max(*ymax, r[1]);
        *zmax = max(*zmax, r[2]);
      }
      for (solid=body->bdySld; solid; solid=solid->nxtSld) {
        for (vertex=solid->sldVtx; vertex; vertex=vertex->nxtVtx) {
          mpyxrc(body->T0j, vertex->coord, r);
          *xmin = min(*xmin, r[0]);
          *ymin = min(*ymin, r[1]);
          *zmin = min(*zmin, r[2]);
          *xmax = max(*xmax, r[0]);
          *ymax = max(*ymax, r[1]);
          *zmax = max(*zmax, r[2]);
        }
      }
    }
  }

/* Loop through any orphan solids. */
  for (solid=System.sysSld; solid; solid=solid->nxtSld) {
    for (vertex=solid->sldVtx; vertex; vertex=vertex->nxtVtx) {
      mpyxrc(body->T0j, vertex->coord, r);
      *xmin = min(*xmin, r[0]);
      *ymin = min(*ymin, r[1]);
      *zmin = min(*zmin, r[2]);
      *xmax = max(*xmax, r[0]);
      *ymax = max(*ymax, r[1]);
      *zmax = max(*zmax, r[2]);
    }
  }
  return;
}
