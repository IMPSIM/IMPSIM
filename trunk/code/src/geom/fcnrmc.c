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
/* fcnrmc-01 Jan 00:15 Jul 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Calculate the plane equation coefficients for a specified Face
|     record.
|
|     Access:
|       (void) fcnrmc(Face *face);
|     Face *face,i/o-Pointer to the Face record.
|
|     Error Conditions:
|       If *face does not point to a valid Face record, execution is
|     aborted.  A message is printed.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libgeo.h"
#ifdef ANSI
  void fcnrmc(Face *face)
#else
  void fcnrmc(face)
  Face *face;
#endif
{
  Hedge  *hedge;
  Perim  *outer, *perim;
  Vertex *vxA, *vxB;
  int    k, n;
  real   bigest, size, varea[3], vector[3], w;

/* Initialize. */
  if (face->type == FACE) {
    bigest= 0.0;
    perim = face->facPrm;
    if (perim) {
      face->area = 0.0;
      for (k=0; k<4; k++) face->faceq[k] = 0.0;

/* Find the vector area of each Perim of the Face. */
      while (perim) {
        for (k=0; k<3; k++) varea[k] = 0.0;
        hedge = perim->prmHed;
        do {
          vxB = hedge->hedCnr->cnrVtx;
          vxA = hedge->nxtHedPrm->hedCnr->cnrVtx;
          vcrosc(vxB->coord, vxA->coord, vector);
          for (k=0; k<3; k++) varea[k] += vector[k];
          hedge = hedge->nxtHedPrm;
        } while (hedge != perim->prmHed);
        for (k=0; k<3; k++) varea[k] *= 0.5;

/* Identify the largest Perim as the "outer" Perim. */
        size = vabsc(3, varea);
        if (fabs(size) > bigest) {
          bigest= fabs(size);
          for (k=0; k<3; k++) face->faceq[k] = varea[k];
          outer = perim;
        }
        if (vdotc(3, varea, face->faceq) < 0.0) size = -size;
        perim->area = size;
        face->area += size;
        perim = perim->nxtPrm;
      }
      vnormc(3, face->faceq);

/* Put the "outer" Perim first in the list of Perims on the Face. */
      if (face->facPrm != outer) {
        perim = face->facPrm;
        while (perim->nxtPrm !=outer) perim = perim->nxtPrm;
        perim->nxtPrm = outer->nxtPrm;
        outer->nxtPrm = face->facPrm;
        face->facPrm  = outer;    
      }

/* Calculate the constant for the Face equation. */
      n = 0;
      for (k=0; k<3; k++) vector[k] = 0.0;
      hedge = outer->prmHed;
      do {
        vxB = hedge->hedCnr->cnrVtx;
        w   = vxB->coord[3];
        for (k=0; k<3; k++) vector[k] += vxB->coord[k] / w;
        n++;
        hedge = hedge->nxtHedPrm;
      } while (hedge != outer->prmHed);
      face->faceq[3] = -vdotc(3, face->faceq, vector) / n;
    } else {           /* A Face with no Perim is a planar halfspace. */
      outer = NULL;
      face->area = 1.0 / zrogeo;
    }
  } else {
    echoc();
    textc("*** fcnrmc: Invalid Face record. ***", TRUE);
    abortc();
  }
  return;
}
