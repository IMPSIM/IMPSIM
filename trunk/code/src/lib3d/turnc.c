/* ------------------------------------------------------------------ */
/* turnc-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Rotate the 3D coordinate system by a specified counterclockwise
|     angle about one of the 2D axes.
|
|     Access:
|       (void) turnc(int naxis, real angle);
|     int naxis,i-A number specifying the axis of rotation:
|       naxis = 1 specifies the 2D x-axis.
|       naxis = 2 specifies the 2D y-axis.
|       naxis = 3 specifies an axis perpendicular to the screen.
|     real angle,i-The counterclockwise angle, in radians, by which the
|       3D axes should be rotated with respect to the 2D.
|
|     Error Conditions:
|       A naxis of other than 1, 2, or 3 is treated modulo 3.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       The rotation takes place about a stationary point in the middle
|     of the screen.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void turnc(int naxis, real angle)
#else
  void turnc(naxis, angle)
  int  naxis;
  real angle;
#endif
{
  int  j, j1, j2;
  real a, b, costh, sinth, r[3];
 
  r[0] = 0.5 * (x2max + x2min);
  r[1] = 0.5 * (y2max + y2min);
  r[2] = 0.0;
  costh = cos(angle);
  sinth = sin(angle);
  j1 = naxis % 3;
  j2 = (j1 + 1) % 3;
  for (j=0; j<3; j++) {
    a = x3to2[j1][j] * costh - x3to2[j2][j] * sinth;
    b = x3to2[j1][j] * sinth + x3to2[j2][j] * costh;
    x3to2[j1][j] = a;
    x3to2[j2][j] = b;
    x2to3[j][j1] = a;
    x2to3[j][j2] = b;
  }
  x3to2[j1][3] = x3to2[3][3] * r[j1];
  x3to2[j2][3] = x3to2[3][3] * r[j2];
  x2to3[j1][3] = x2to3[3][3] * r[j1];
  x2to3[j2][3] = x2to3[3][3] * r[j2];
  for (j=j1; j<3; j++) {
    x3to2[j1][3] -= x3to2[j1][j] * r[j];
    x3to2[j2][3] -= x3to2[j2][j] * r[j];
    x2to3[j1][3] -= x2to3[j1][j] * r[j];
    x2to3[j2][3] -= x2to3[j2][j] * r[j];
  }
  lspen = FALSE;
  l3pen = FALSE;
  return;
}
