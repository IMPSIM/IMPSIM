/* ------------------------------------------------------------------ */
/* slidec-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Translate the 3D image along one of the 2D axes by a specified
|     2D increment.
|
|     Access:
|       (void) slidec(int naxis, real delta);
|     int naxis,i-A number specifying the 2D axis to slide along:
|       naxis = 1 for the 2D u-axis.
|       naxis = 2 for the 2D v-axis.
|       naxis = 3 for an axis perpendicular to the screen (pos. out).
|     real delta,i-The relative 2D increment for the translation.
|
|     Error Conditions:
|       A naxis of other than 1, 2, or 3 is treated modulo 3.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void slidec(int naxis, real delta)
#else
  void slidec(naxis, delta)
  int  naxis;
  real delta;
#endif
{
  int i, n;
 
  n = (naxis - 1) % 3;
  x3to2[n][3] += x3to2[3][3] * delta;
  for (i=0; i<3; i++) {
    x2to3[i][3] -= x2to3[i][n] * delta;
  }
  lspen = FALSE;
  l3pen = FALSE;
  return;
}
