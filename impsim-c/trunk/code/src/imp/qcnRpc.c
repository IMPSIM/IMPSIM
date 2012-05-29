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
/* qcnRpc-01 Jan 00:16 Feb 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Find and return a radius Rp of the contact area, which is used 
|     to find torsional impulse.
|
|     Access:
|       rad = (real) qcnRpc(real pnt[][3], int npnts, real center[3]);
|     real  pnt[][3], i-Array  of points of contact region.
|     int  *npnts,    i-Number of points in contact region array.
|     real  center[3],i-Coordinates of center of contact region.
|     real  rad,      o-Radius of contact used for torsional impulse.
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
  real qcnRpc(real pnt[][3], int npnts, real center[3])
#else
  real qcnRpc(pnt, npnts, center)
  real pnt[][3];
  int  npnts;
  real center[3];
#endif
{
  int     i, ip1, j;
  real    da, r, Rp, sumda, sumrda, v1[3], v2[3], v12[3];

/* Initialize. */
  Rp = 0.0;
  if (npnts > 2) {
    sumrda = 0.0;
    sumda  = 0.0;
    for (i=0; i<npnts; i++) {
      if (i < npnts - 1) {
	ip1 = i + 1;
      } else {
	ip1 = 0;
      }
      for (j=0; j<3; j++)  v1[j] =   pnt[i][j] - center[j];
      for (j=0; j<3; j++)  v2[j] = pnt[ip1][j] - center[j];
      for (j=0; j<3; j++) v12[j] = v1[j] + v2[j];
      r = vabsc(3, v12) / 3.0;
      vcrosc(v1, v2, v12);
      da = vabsc(3, v12) / 2.0;
      sumrda += (r * da);
      sumda  += da;
    }
    if (fabs(sumda) > 0.0) Rp = sumrda / sumda;
  }
  return (Rp);
}
