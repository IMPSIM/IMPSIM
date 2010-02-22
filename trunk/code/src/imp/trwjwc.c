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
/* trwjwc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Return the trace of the matrix product (w * j * ww-transpose).
|
|     Access:
|       trwjw = (real) trwjwc(real w[6], real mass[4][4],real ww[3][4]);
|     real w[6],      i-Premultiplying derivative operator.
|     real mass[4][4],i-Global coordinate inertia matrix.
|     real ww[3][4],  i-Postmultiplying derivative matrix.
|     real trwjw,     o-Resulting trace of the matrix product.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       Note that the ww[3][4] matrix is not stored in derivative oper-
|     ator form since it may contain a product such as ww = w * w.
*
*     History:
*     01 Jan 96:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  real trwjwc(real w[6], real mass[4][4], real ww[3][4])
#else
  real trwjwc(w, mass, ww)
  real w[6], mass[4][4], ww[3][4];
#endif
{
  int  i, j;
  real temp[3], trwjw;

  trwjw = 0.0;
  for (j=0; j<4; j++) {
    vcrosc(w, &mass[j][0], temp);
    for (i=0; i<3; i++) {
      temp[i] += w[i+3] * mass[3][j];
    }
    for (i=0; i<3; i++){
      trwjw += temp[i] * ww[i][j];
    }
  }
  return(trwjw);
}
