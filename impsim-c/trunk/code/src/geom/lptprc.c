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
/* lptprc-07 Mar 04:15 Jul 09
|     (C)Copyright, JJU Research, 2004-2009.
|
|     Description:
|       Test a specified point against a specified Perim and determine
|     if the projection of the Perim boundary onto the "best" principal
|     plane surrounds the same projection of the point, i.e., test if
|     the point is inside of the Perim as seen in the "best" principal
|     projection.
|
|     Access:
|       lflag = (int) lptprc(real pt[3], Perim *perim);
|     real  pt[3], i-Coordinates of the point to be tested.
|     Perim *perim,i-Pointer to the specified Perim record.
|     int   lflag, o-Flag returns TRUE if pt is inside of perim.
|
|     Error Conditions:
|       if *perim does not point to a valid Perim record, execution is
|     aborted.  A message is printed.
|
|     Comments:
|       It is assumed that pt and perim have been transformed to the
|     same coordinate system before entry.
|       The semi-infinite ray-trace technique is used along one axis of
|     the coordinate system.
|       A point "on" an edge is considered inside.
*
*     History:
*     07 Mar 04:JJU-Original.
*     07 Sep 07:JJU-Added error message.
* ------------------------------------------------------------------- */
 
#include "libgeo.h"
#ifdef ANSI
  int lptprc(real pt[3], Perim *perim)
#else
  int lptprc(pt, perim)
  real  pt[3];
  Perim *perim;
#endif
{
  Face   *face;
  Hedge  *hedge;
  Vertex *vxA, *vxB;
  int    i, icross, index0, index1, index2, lflag;
  real   area, areamx, denom, dist, sigma, wA, wB;

  if (perim->type == PERIM) {
    if (perim->prmHed) {
      areamx = 0.0;
      index0 = 0;
      face   = perim->prmFac;
      for (i=0; i<3; i++) {    /* Find the best axis for projections. */
        area = fabs(face->faceq[i]);
        if (area > areamx) {
          areamx = area;
          index0 = i;
        }
      }
      index1 = (index0 + 1) % 3;
      index2 = (index1 + 1) % 3;
      icross = 0;
      hedge  = perim->prmHed;
      do {                   /* Step through the Hedges of the Perim. */
        vxB = hedge->hedCnr->cnrVtx;
        wB  = vxB->coord[3];
        vxA = hedge->nxtHedPrm->hedCnr->cnrVtx;
        wA  = vxA->coord[3];
        denom = vxA->coord[index2] / wA - vxB->coord[index2] / wB;
        if (fabs(denom) >= zrogeo) { /* Parametric line intersection. */
          sigma  = (pt[index2] - vxB->coord[index2] / wB) / denom;
          if ((sigma > 0.0) && (sigma < 1.0)) {
            dist   = sigma  * vxA->coord[index1] / wA +
              (1.0 - sigma) * vxB->coord[index1] / wB - pt[index1];
            if (dist >= 0.0) icross++;        /* Count intersections. */
          }
        } else {
          sigma  =              pt[index1] - vxB->coord[index1] / wB;
          dist   = vxA->coord[index1] / wA - vxB->coord[index1] / wB;
          if ((sigma * dist) >= 0.0) {
            if (fabs(sigma) < fabs(dist)) {
              if (fabs(pt[index2] - vxB->coord[index2] / wB)
                < fabs(denom)) icross++;      /* Count intersections. */
            }
          }
        }
        hedge = hedge->nxtHedPrm;
      } while (hedge != perim->prmHed);
      lflag = (icross % 2) != 0;/* Test if intersection count is odd. */
    }
  } else {
    echoc();
    textc("*** lptprc: Invalid Perim record. ***", TRUE);
    abortc();
  }
  return(lflag);
}
