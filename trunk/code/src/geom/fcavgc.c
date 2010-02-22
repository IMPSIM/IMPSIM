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
/* fcavgc-21 Sep 03:15 Jul 09
|     (C)Copyright, JJU Research, 2003-2009.
|
|     Description:
|       This function calculates the average of the Vertex coordinates
|     of the outer Perim of a specified Face.
|
|     Access:
|       (void) fcavgc(Face *face, real *xavg, real *yavg, real *zavg);
|     Face *face, i - Pointer to the face.
|     real *xavg, o - Average x coordinate of the face.
|     real *yavg, o - Average y coordinate of the face.
|     real *zavg, o - Average z coordinate of the face.
|
|     Error Conditions:
|       I face does not point to a valid Face record, execution is
|     aborted.  A message is printed.
|
|     Comments:
|       Values are returned in local Body coordinates.
|       A Face with no Perim is assumed to be a planar halfspace.  Such
|     a Face returns coordinates of zero.
*
*     History:
*     21 Sep 03:JJU-Original.
*     07 Sep 07:JJU-Added error message.
* ------------------------------------------------------------------- */
 
#include "libgeo.h"
#ifdef ANSI
  void fcavgc(Face *face, real *xavg, real *yavg, real *zavg)
#else
  void fcavgc(face, xavg, yavg, zavg);
  Face *face;
  real *xavg, *yavg, *zavg;
#endif
{
  Hedge  *hedge;
  Perim  *perim;
  Vertex *vertex;
  int  n;
  real w, x, y, z;

  if (face->type == FACE) {
    x = 0.0;
    y = 0.0;
    z = 0.0;
    perim = face->facPrm;
    if (perim) {       /* A Face with no Perim is a planar halfspace. */
      n = 0;
      hedge = perim->prmHed;
      do {
        vertex = hedge->hedCnr->cnrVtx;
        w  = vertex->coord[3];
        x += vertex->coord[0] / w;
        y += vertex->coord[1] / w;
        z += vertex->coord[2] / w;
        n++;
        hedge = hedge->nxtHedPrm;
      } while (hedge != perim->prmHed);
      x /= n;
      y /= n;
      z /= n;
    }
    *xavg = x;
    *yavg = y;
    *zavg = z;
  } else {
    echoc();
    textc("*** fcavgc: Invalid Face record. ***", TRUE);
    abortc();
  }
  return;
}
