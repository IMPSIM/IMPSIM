/* ------------------------------------------------------------------ */
/* turn3c-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Rotate the 3D image  by a specified angle about one of its own
|     axes with respect to the 2D coordinate system.
|
|     Access:
|       (void) turn3c(int naxis, real angle);
|     int naxis,i-A number specifying the axis of rotation:
|       naxis = 1 specifies the 3D x-axis.
|       naxis = 2 specifies the 3D y-axis.
|       naxis = 3 specifies the 3D z-axis.
|     real angle,i-Counterclockwise angle, in radians, for the turn.
|
|     Error Conditions:
|       An naxis of other than 1, 2, or 3 is treated modulo 3.
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
  void turn3c(int naxis, real angle)
#else
  void turn3c(naxis, angle)
  int  naxis;
  real angle;
#endif
{
  int  i, j1, j2;
  real a, b, costh, sinth;
 
  costh = cos(angle);
  sinth = sin(angle);
  j2 = naxis % 3;
  j1 = (j2 + 1) % 3;
  for (i=0; i<3; i++) {
    a = x3to2[i][j1] * costh - x3to2[i][j2] * sinth;
    b = x3to2[i][j1] * sinth + x3to2[i][j2] * costh;
    x3to2[i][j1] = a;
    x3to2[i][j2] = b;
    x2to3[j1][i] = a;
    x2to3[j2][i] = b;
  }
  x2to3[j1][3] = 0.0;
  x2to3[j2][3] = 0.0;
  for (i=0; i<3; i++){
    x2to3[j1][3] -= x2to3[j1][i] * x3to2[i][3] * x2to3[3][3];
    x2to3[j2][3] -= x2to3[j2][i] * x3to2[i][3] * x2to3[3][3];
  }
  lspen = FALSE;
  l3pen = FALSE;
  return;
}
