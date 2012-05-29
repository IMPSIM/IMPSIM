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
/* mkvtxc-20 Jul 03:15 Jul 09
|     (C)Copyright, JJU Research, 2003-2009.
|
|     Description:
|       Locate or form a new Vertex record with specified coordinates
|     with respect to Body axes as the child of a designated Solid.
|
|     Access:
|       vertex = (Vertex *) mkvtxc(Solid *solid, real x, real y,real z);
|     Solid  *solid, i-Pointer to the parent Solid record.
|     real    x,     i-Coordinate of the point relative to Body axes.
|     real    y,     i-Coordinate of the point relative to Body axes.
|     real    z,     i-Coordinate of the point relative to Body axes.
|     Vertex *vertex,o-Pointer to the newly formed Vertex record.
|
|     Error Conditions:
|       If *solid does not point to a valid Solid record then execution 
|     is aborted.  A message is printed.
|
|     Comments:
|       If a Vertex exists on the specified Solid with the specified
|     coordinates with respect to the Body, within a tolerance of zrogeo
|     then a pointer to that Vertex is returned.  If not, then a new
|     Vertex is created.
|       A new Vertex is added to the end of the list of vertices of the
|     designated Solid.
*
*     History:
*     20 Jul 03:JJU-Original.
*     08 Sep 07:JJU-Added error message.
* ------------------------------------------------------------------- */
 
#include "libgeo.h"
#ifdef ANSI
  Vertex *mkvtxc(Solid *solid, real x, real y, real z)
#else
  Vertex *mkvtxc(solid, x, y, z)
  Solid *solid;
  real   x, y, z;
#endif
{
  Vertex *vertex, *vtxptr;
  real w;

  if (solid->type == SOLID) {
    for (vertex=solid->sldVtx; vertex; vertex=vertex->nxtVtx) {
      w = vertex->coord[3];
      if (fabs(x - vertex->coord[0] / w) <= zrogeo) {
        if (fabs(y - vertex->coord[1] / w) <= zrogeo) {
          if (fabs(z - vertex->coord[2] / w) <= zrogeo) {
            goto _RETURN;     /* Vertex with these coordinates found. */
          }
        }
      }
    }
  } else {
    echoc();
    textc("*** mkvtxc:  Invalid Solid record. ***", TRUE);
    abortc();
  }
  vertex = (Vertex *) malloc(sizeof(Vertex));
  vertex->type   = VERTEX;
  vtxptr = solid->sldVtx;
  if (vtxptr) {
    while (vtxptr->nxtVtx) vtxptr = vtxptr->nxtVtx;
    vtxptr->nxtVtx = vertex;
  } else {
    solid->sldVtx = vertex;
  }
  vertex->nxtVtx = NULL;
  vertex->vtxSld = solid;
  vertex->vtxCnr = NULL;
  vertex->ncnrs  = 0;
  vertex->vtxno  = ++solid->nvrtxs;  /* vtxno = 1,2,...,Solid->nvrtxs */
  vertex->kcolor = kdfgeo;
  ldnanc((void *) &(vertex->sldang));
  vertex->coord[0] = x;
  vertex->coord[1] = y;
  vertex->coord[2] = z;
  vertex->coord[3] = 1.0;
  vertex->coeff = 1.0;
_RETURN:
  return(vertex);
}
