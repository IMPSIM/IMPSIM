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
/* qponec-01 Jan 00:15 Jul 09
|     (C)Copyright, JJU Research, 2000-2009
|
|     Description:
|       Determine whether a specified point is in contact with a 
|     specified edge.
|
|     Access:
|       lflag = (int) qponec(real pnt[3], Edge *edge);
|     real  pnt[3],i-Point to be tested for contact.
|     Edge *edge,  i-Edge record to be tested for contact.
|     int   lflag, o-Flag set TRUE if contact is verified.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       If pnt is in contact with an end vertex of the edge, then 
|     return is made with the value lflag = 2.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  int qponec(real pnt[3], Edge *edge)
#else
  int qponec(pnt, edge)
  real  pnt[3];
  Edge *edge;
#endif
{
  int     i, lflag;
  real    diffAB[3], diffPB[3], diffXP[3], distAB, eta;
  Vertex *VxA, *VxB;

  VxA = edge->edgHeR->hedCnr->cnrVtx;
  VxB = edge->edgHeL->hedCnr->cnrVtx;
  lflag = FALSE;
  if (qponvc(pnt, VxA) || qponvc(pnt, VxB)) {
    lflag = 2;             /* Point is in contact with an end vertex. */
  } else {
    for (i=0; i<3; i++) {diffAB[i] = VxA->coord[i] - VxB->coord[i];}
    distAB = vabsc(3, diffAB);
    if (distAB > zrogeo) {
      for (i=0; i<3; i++) {diffPB[i] = pnt[i] - VxB->coord[i];}
      eta = vdotc(3, diffPB, diffAB) / (distAB * distAB);
      if ((eta >= 0.0) && (eta <= 1.0)) {
        for (i=0; i<3; i++) {diffXP[i] = eta * diffAB[i] - diffPB[i];}
        lflag = vabsc(3, diffXP) < zrogeo;
      }
    }
  }
  return (lflag);
}
