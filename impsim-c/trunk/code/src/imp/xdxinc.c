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
/* xdxinc-01 Jan 00:15 Mar 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Transform a given derivative operator to another coordinate
|     system through a given transformation matrix.
|
|     Access:
|       (void) xdxinc(real x[3][4], real d[6], real xdxinv[6]);
|     real x[3][4],  i-Transformation matrix to be used.
|     real d[6],     i-Untransformed derivative operator.
|     real xdxinv[6],o-Transformed derivative operator.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       If desired, the transformed operator xdxinv[] may overwrite the
|     original operator d[] as follows: xdxinc(x, d, d)
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void xdxinc(real x[3][4], real d[6], real xdxinv[6])
#else
  void xdxinc(x, d, xdxinv)
  real x[3][4], real d[6], real xdxinv[6];
#endif
{
  int  i, i1, i2, i3, j;
  real temp[6];

  for (i=0; i<3; i++) {
    i1 = (i + 1) % 3;
    i2 = (i + 2) % 3;
    i3 = (i + 3);
    temp[i]  = vdotc(3, &x[i][0], d);
    temp[i3] = vdotc(3, &x[i][0], &d[3]);
    for (j=0; j<3; j++) {
      temp[i] += (x[i2][j] * x[i1][3] - x[i1][j] * x[i2][3]) * d[j+3];
    }
  }
  for (i=0; i<6; i++) {
    xdxinv[i] = temp[i];
  }
  return;
}
