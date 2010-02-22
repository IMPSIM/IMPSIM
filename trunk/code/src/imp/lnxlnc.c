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
/* lnxlnc-01 Jan 00:16 Aug 09
|     (C)Copyright, JJU Research, 2000-2009
|
|     Description:
|       Determine the intersection of the two lines defined by the two
|     pairs of point coordinates r1:r2 and r3:r4 on the assumption that
|     the four points lie in a common plane.
|
|     Access:
|       lflag = (int) lnxlnc(real r1[3], real r2[3], real r3[3],
|         real r4[3], int ignore, *t1, *t2);
|     real  r1[3], i-Coordinates of the first  point of the first  line.
|     real  r2[3], i-Coordinates of the second point of the first  line.
|     real  r3[3], i-Coordinates of the first  point of the second line.
|     real  r4[3], i-Coordinates of the second point of the second line.
|     int  *ignore,i-Index of the plane with the largest projection.
|     real *t1,    o-Parameter of intersection along first  line.
|     real *t2,    o-Parameter of intersection along second line.
|     int   lflag, o-Flag set TRUE if intersection is found; FALSE if 
|                      lines are parallel.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       Point of intersection is:  r = t1*r2+(1.0-t1)*r1 = r1+t1*(r2-r1)
|                                    = t2*r4+(1.0-t2)*r3 = r3+t2*(r4-r3)
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  int lnxlnc(real r1[3], real r2[3], real r3[3], real r4[3], 
    int ignore, real *t1, real *t2)
#else
  int lnxlnc(r1, r2, r3, r4, ignore, t1, t2)
  real  r1[3], r2[3], r3[3], r4[4];
  int   ignore;
  real *t1, *t2;
#endif
{
  int lflag;
  real a1, a2, b1, b2, c1, c2, denom;

  lflag = FALSE;
  *t1 = 0.0;
  *t2 = 0.0;
  switch (ignore) {
  case 0:               /* Ignore X coordinates; take Y-Z projection. */
    a1 = r2[1] - r1[1];
    a2 = r2[2] - r1[2];
    b1 = r3[1] - r4[1];
    b2 = r3[2] - r4[2];
    c1 = r1[1] - r3[1];
    c2 = r1[2] - r3[2];
    break;
  case 1:               /* Ignore Y coordinates; take Z-X projection. */
    a1 = r2[2] - r1[2];
    a2 = r2[0] - r1[0];
    b1 = r3[2] - r4[2];
    b2 = r3[0] - r4[0];
    c1 = r1[2] - r3[2];
    c2 = r1[0] - r3[0];
    break;
  case 2:               /* Ignore Z coordinates; take X-Y projection. */
    a1 = r2[0] - r1[0];
    a2 = r2[1] - r1[1];
    b1 = r3[0] - r4[0];
    b2 = r3[1] - r4[1];
    c1 = r1[0] - r3[0];
    c2 = r1[1] - r3[1];
  }
  denom = a1 * b2 - a2 * b1;
  if (fabs(denom) > zrogeo * zrogeo) {
    *t1 = (c2 * b1 - c1 * b2) / denom;
    *t2 = (a2 * c1 - a1 * c2) / denom;
    lflag = TRUE;
  }
  return(lflag);
}
