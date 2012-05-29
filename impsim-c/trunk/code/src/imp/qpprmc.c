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
/* qpprmc-01 Jan 00:15 Jul 09
|     (C)Copyright, JJU Research, 2000-2009
|
|     Description:
|       Check if a given point is in contact with a specified perim. 
|
|     Access:
|       lflag = (int) qpprmc(real pnt[3], Perim *perim, int *nvertx);
|     real  pnt[3],i-Coordinates of the specified point.
|     Perim *perim, i-Perim record to be tested for contact.
|     int   *nvertx,o-Vertex number if lflag=TRUE; (see Comments).
|     int    lflag, o-Flag set FALSE for no contact with perim boundary;
|                      (See Comments below for other values).
|
|     Error Conditions:
|       None.
|
|     Comments:
|       If pnt[3] lies on a vertex of the perim, lflag is set to 3 and 
|     *nvertx is set to the vertex number.  If pnt[] lies on an edge of 
|     the perim, lflag is set to 2 and *nvertx is set to the number of 
|     the vertex preceding the halfedge in the perim.  If pnt[3] is not 
|     on the boundary of the perim, lflag is set to 0 (FALSE) and nvertx 
|     is set to -1.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  int qpprmc(real pnt[3], Perim *perim, int *nvertx)
#else
  int qpprmc(pnt, perim, nvertx)
  real   pnt[3];
  Perim *perim;
  int   *nvertx;
#endif
{
  int    lflag, lfound;
  Face  *face;
  Hedge *hedge;

/* Initialize. */
  lflag   = FALSE;
  *nvertx = -1;
  face    = perim->prmFac;
  if (fabs(face->faceq[3]+vdotc(3, pnt, face->faceq)) < zrogeo) {

/* Loop through and test all vertices of the perim. */
    for (hedge=perim->prmHed; hedge; hedge=hedge->nxtHedPrm) {
      lfound = qponvc(pnt, hedge->hedEdg->edgHeL->hedCnr->cnrVtx);
      if (lfound) {
        *nvertx = hedge->hedEdg->edgHeL->hedCnr->cnrVtx->vtxno;
        return(3);
      }
    }

/* Loop through and test all edges of the perim. */
    for (hedge=perim->prmHed; hedge; hedge=hedge->nxtHedPrm) {
      lfound = qponec(pnt, hedge->hedEdg);
      if (lfound) {
        *nvertx = hedge->hedEdg->edgHeL->hedCnr->cnrVtx->vtxno;
        return(2);
      }
    }
  }
  return (lflag);
}
