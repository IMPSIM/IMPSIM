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
/* bsphrc-01 Jan 00:27 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Determine and store the bounding sphere of a specified Solid.
|
|     Access:
|       (void) bsphrc(Solid *solid);
|     Solid *solid,i-Solid for which bounding sphere is sought.
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
  void bsphrc(Solid *solid)
#else
  void bsphrc(solid)
  Solid *solid;
#endif
{
  Vertex *vmax, *vmin, *vtx, *vxmax, *vxmin, *vymax, *vymin, *vzmax,
    *vzmin;
  int     i;
  real    dr, span[3], spansz, xmax, xmin, ymax, ymin, zmax, zmin;
# define  BIG  1.0E12

/* Initialize. */
  for (i=0; i<3; i++) {
    solid->smax_coord[i] =-BIG;
    solid->smin_coord[i] = BIG;
  }
  xmax = ymax = zmax =-BIG;
  xmin = ymin = zmin = BIG;

/* Find the bounding box and the max and min vertex coordinates in the
     Solid x, y, z directions. */
  for (vtx=solid->sldVtx; vtx; vtx=vtx->nxtVtx) {
    for (i=0; i<3; i++) {
      if (vtx->coord[i] > solid->smax_coord[i])
        solid->smax_coord[i] = vtx->coord[i];
      if (vtx->coord[i] < solid->smin_coord[i])
        solid->smin_coord[i] = vtx->coord[i];
    }
    if (vtx->coord[0] > xmax) vxmax = vtx;
    if (vtx->coord[0] < xmin) vxmin = vtx;
    if (vtx->coord[1] > ymax) vymax = vtx;
    if (vtx->coord[1] < ymin) vymin = vtx;
    if (vtx->coord[2] > zmax) vzmax = vtx;
    if (vtx->coord[2] < zmin) vzmin = vtx;
  }

/* Determine major axis distances between max and min vertices. */
  for (i=0; i<3; i++) {
    span[i] = vxmax->coord[i] - vxmin->coord[i];
  }
  vmax = vxmax;
  vmin = vxmin;
  spansz = vabsc(3, span);
  for (i=0; i<3; i++) {
    span[i] = vymax->coord[i] - vymin->coord[i];
  }
  if (vabsc(3, span) > spansz) {
    vmax = vymax;
    vmin = vymin;
    spansz = vabsc(3, span);
  }
  for (i=0; i<3; i++) {
    span[i] = vzmax->coord[i] - vzmin->coord[i];
  }
  if (vabsc(3, span) > spansz) {
    vmax = vzmax;
    vmin = vzmin;
    spansz = vabsc(3, span);
  }

/* Calculate initial sphere from two major axis spanning vertices. */
  for (i=0; i<3; i++) {
    solid->bs_ctr[i] = 0.5 * (vmax->coord[i] - vmin->coord[i]);
  }
  solid->bs_rad = 0.5 * spansz;

/* Pass two; check each vertex and increment the bounding sphere. */
  for (vtx=solid->sldVtx; vtx; vtx=vtx->nxtVtx) {
    for (i=0; i<3; i++) {
      span[i] = vtx->coord[i] - solid->bs_ctr[i];
    }
    dr = 0.5 * (vabsc(3, span) - solid->bs_rad);
    if (dr > 0.0) {
      dr /= solid->bs_rad;
      for (i=0; i<3; i++) {
        solid->bs_ctr[i] += dr * span[i];
      }
      solid->bs_rad *= (1.0 + dr);
    }
  }
  return;
# undef  BIG
}
