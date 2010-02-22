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
/* mpyddc-01 Jan 00:15 Mar 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Multiply two homogeneous coordinate derivative operators, d1 by
|     d2, and store the result in the matrix dd = d1 * d2.
|
|     Access:
|       (void) mpyddc(real d1[6], real d2[6], real dd[3][4]);
|     real d1[6],   i-The  premultiplying derivative operator.
|     real d2[6],   i-The postmultiplying derivative operator.
|     real dd[3][4],o-The derivative operator product, stored in matrix
|       form with the last row implied as [0.0, 0.0, 0.0, 0.0].
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
  void mpyddc(real d1[6], real d2[6], real dd[3][4])
#else
  void mpyddc(d1, d2, dd)
  real d1[6], d2[6], dd[3][4];
#endif
{
  int  i, j;
  real sum, temp[3];

  sum = 0.0;
  for (i=0; i<3; i++) {
    sum += d1[i+3] * d2[i+3];
    for (j=0; j<3; j++) {
      dd[i][j] = d1[j+3] * d2[i+3];
    }
  }
  vcrosc(&d1[3], d2, temp);
  for (i=0; i<3; i++){
    dd[i][i] -= sum;
    dd[i][3]  = temp[i];
  }
  return;
}
