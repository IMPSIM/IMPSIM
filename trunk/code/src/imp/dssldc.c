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
/* dssldc-01 Jan 00:14 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Evaluate the support function and find the contact vertex for a
|     specified solid in a specified direction.
|
|     Access:
|       distnc = (real) dssldc(Solid *solid, real direc[3], real R[3], 
|         Vertex **vtx);
|     Solid   *solid,   i-Solid specified to be tested.
|     real     direc[3],i-Specified direction to be tested.
|     real     R[3],    o-Global position coordinates found.
|     Vertex **vtx,     o-Vertex found with largest directed distance.
|     real     distnc,  o-Distance found in the specified direction.
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
  real dssldc(Solid *solid, real direc[3], real R[3], Vertex **vtx)
#else
  real dssldc(solid, direc, R, vtx)
  Solid  *solid;
  real   direc[3], R[3];
  Vertex **vtx;
#endif
{
  Body   *body;
  Vertex *vx;
  int     i;
  real    dst, dstmax, r[3];

/* Initialize with the first vertex of the solid. */
  body   = solid->sldBdy;
  (*vtx) = solid->sldVtx;
  mpyxrc(body->T0j, (*vtx)->coord, R);
  dstmax = vdotc(3, R, direc);

/* Cycle through other vertices looking for larger directed distance. */
  for (vx=(*vtx)->nxtVtx; vx; vx=vx->nxtVtx) {
    mpyxrc(body->T0j, vx->coord, r);
    dst = vdotc(3, r, direc);
    if (dst > dstmax) {
      dstmax = dst;
      (*vtx) = vx;
      for (i=0; i<3; i++) {R[i] = r[i];}
    }
  }
  return(dstmax);
}
