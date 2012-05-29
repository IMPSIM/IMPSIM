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
/* xjxtrc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Form the transformed inertia matrix xjxtr.
|
|     Access:
|       (void) xjxtrc(real x[3][4], real mass[10], real xjxtr[4][4])
|     real x[3][4],i-Transformation matrix to be used.
|     real mass[10],i-Untransformed inertia data.
|     real xjxtr[4][4],o-Transformed inertia matrix.
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
  void xjxtrc(real x[3][4], real mass[10], real xjxtr[4][4])
#else
  void xjxtrc(x, mass, xjxtr)
  real x[3][4], mass[10], xjxtr[4][4];
#endif
{
  int  i, j, k;
  real temp[3][4];

  for (i=0; i<3; i++){
    temp[i][0] = x[i][0] * mass[0] + x[i][1] * mass[1]
               + x[i][2] * mass[3] + x[i][3] * mass[6];
    temp[i][1] = x[i][0] * mass[1] + x[i][1] * mass[2]
               + x[i][2] * mass[4] + x[i][3] * mass[7];
    temp[i][2] = x[i][0] * mass[3] + x[i][1] * mass[4]
               + x[i][2] * mass[5] + x[i][3] * mass[8];
    temp[i][3] = x[i][0] * mass[6] + x[i][1] * mass[7]
               + x[i][2] * mass[8] + x[i][3] * mass[9];
  }
  for (i=0; i<3; i++){
    for (j=0; j<=i; j++){
      xjxtr[i][j] = 0.0;
      for (k=0; k<4; k++){
        xjxtr[i][j] += temp[i][k] * x[j][k];
      }
      xjxtr[j][i] = xjxtr[i][j];
    }
    xjxtr[i][3] = temp[i][3];
    xjxtr[3][i] = temp[i][3];
  }
  xjxtr[3][3] = mass[9];
  return;
}
