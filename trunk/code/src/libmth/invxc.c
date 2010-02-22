/* ------------------------------------------------------------------ */
/* invxc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Invert a homogeneous coordinate rigid body transformation
|     matrix.
|
|     Access:
|       void invxc(real x[3][4], real xinv[3][4])
|     real x[3][4],i-The transformation matrix, stored with the last row
|       implied as [0.0, 0.0, 0.0, 1.0].
|     real xinv[3][4],o-The inverse transformation matrix, stored with
|       the last row implied as [0.0, 0.0, 0.0, 1.0].
|
|     Error Conditions:
|       None.
|
|     Comments:
|       Note that matrices x and xinv are stored in row-major (C) rather
|     than column-major (Fortran) order.
|       If desired, the transformation matrix may be inverted onto the
|     same memory space which it originally occupied as follows:
|         invxc(x, x).
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void invxc(real x[3][4], real xinv[3][4])
#else
  void invxc(x, xinv)
  real x[3][4], xinv[3][4];
#endif
{
  int  i, j;
  real temp[3][4];
 
  for (i=0; i<3; i++) {
    temp[i][3] = 0.0;
    for (j=0; j<3; j++) {
      temp[i][j]  = x[j][i];
      temp[i][3] -= x[j][i]*x[j][3];
    }
  }
  for (i=0; i<3; i++) {
    for (j=0; j<4; j++) {
      xinv[i][j] = temp[i][j];
    }
  }
  return;
}
