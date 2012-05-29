/* ------------------------------------------------------------------ */
/* mpyxxc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Multiply two homogeneous coordinate rigid body transformation
|     matrices, x1 by x2, and store the result in the transformation
|     matrix xx = x1 * x2.
|
|     Access:
|       (void) mpyxxc(real x1[3][4], real x2[3][4], real xx[3][4]);
|     real x1[3][4],i-The premultiplying transformation matrix, stored
|       with the last row implied as [0.0, 0.0, 0.0, 1.0].
|     real x2[3][4],i-The postmultiplying transformation matrix, stored
|       with the last row implied as [0.0, 0.0, 0.0, 1.0].
|     real xx[3][4],o-The product transformation matrix, stored with the
|       last row implied as [0.0, 0.0, 0.0, 1.0].
|
|     Error Conditions:
|       None.
|
|     Comments:
|       Note that the matrices x1, x2, and xx are stored in row-major
|     (C) rather than column-major (Fortran) order.
|       If desired, the product matrix xx may overwrite either of the
|     original matrices x1 or x2 as follows: mpyxxc(x1, x2, x1).
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void mpyxxc(real x1[3][4], real x2[3][4], real xx[3][4])
#else
  void mpyxxc(x1, x2, xx)
  real x1[3][4], x2[3][4], xx[3][4];
#endif
{
  int  i, ij, j;
  real temp[3][4];
 
  for (i=0; i<3; i++) {
    for (j=0; j<4; j++) {
      temp[i][j] = 0.0;
      for (ij=0; ij<3; ij++) {
        temp[i][j] += x1[i][ij] * x2[ij][j];
      }
    }
    temp[i][3] += x1[i][3];
  }
  for (i=0; i<3; i++) {
    for (j=0; j<4; j++){
      xx[i][j] = temp[i][j];
    }
  }
  return;
}
