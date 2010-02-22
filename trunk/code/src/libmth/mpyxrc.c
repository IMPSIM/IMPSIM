/* ------------------------------------------------------------------ */
/* mpyxrc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Multiply a homogeneous coordinate rigid body transformation
|     matrix x by a three-dimensional homogeneous coordinate absolute
|     position vector r, and store the result in the vector xr = x * r.
|
|     Access:
|       (void) mpyxrc(real x[3][4], real r[3], real xr[3])
|     real x[3][4],i-The premultiplying transformation matrix;
|       stored with the last row implied as [0.0, 0.0, 0.0, 1.0].
|     real r[3],i-The coordinates of the given position vector;
|       stored with the last coordinate implied as 1.0.
|     real xr[3],o-The coordinates of the transformed position vector
|       xr = x * r; stored with the last coordinate implied as 1.0.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       Note that matrix x is assumed stored in row-major (C) rather
|     than column-major (Fortran) order.
|       If desired, the transformed position vector xr may overwrite the
|     given position vector r as follows: mpyxrc(x, r, r).
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void mpyxrc(real x[3][4], real r[3], real xr[3])
#else
  void mpyxrc(x, r, xr)
  real x[3][4], r[3], xr[3];
#endif
{
  int  i, j;
  real temp[3];
 
  for (i=0; i<3; i++) {
    temp[i] = x[i][3];
    for (j=0; j<3; j++) {
      temp[i] += x[i][j] * r[j];
    }
  }
  for (i=0; i<3; i++) {
    xr[i] = temp[i];
  }
  return;
}
