/* ------------------------------------------------------------------ */
/* ldx32c-01 Jan 00:10 Aug 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Load a given homogeneous coordinate transformation matrix into
|     the libcad imagec area to replace the current x3to2 matrix.
|
|     Access:
|       (void) ldx32c(real x32[4][4]);
|     real x32[4][4],i-Given transformation matrix.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       The rotation submatrix given must be orthonormal and right-
|     handed.  Also, there may no perspective or shear elements; i.e.,
|     x32[3][0] = x32[3][1] = x32[3][2] = 0.0.  x32[3][3] must contain
|     the 3D to 2D scale factor.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void ldx32c(real x32[4][4])
#else
  void ldx32c(x32)
  real x32[4][4];
#endif
{
  int i, j;
 
  for (i=0; i<4; i++) {
    for (j=0; j<4; j++) {
      x3to2[i][j] = x32[i][j];
    }
  }
  x2to3[3][3] = 1.0 / x3to2[3][3];
  for (i=0; i<3; i++) {
    x2to3[i][3] = 0.0;
    x2to3[3][i] = 0.0;
    for (j=0; j<3; j++){
      x2to3[i][j] = x3to2[j][i];
      x2to3[i][3] -= x2to3[i][j] * x3to2[j][3];
    }
    x2to3[i][3] *= x2to3[3][3];
  }
  lspen = FALSE;
  l3pen = FALSE;
  return;
}
