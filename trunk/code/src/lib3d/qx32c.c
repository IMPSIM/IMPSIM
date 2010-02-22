/* ------------------------------------------------------------------ */
/* qx32c-01 Jan 00:23 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|     Description:
|       Return the current 3D to 2D transformation matrix from the
|     libcad imagec area.
|
|     Access:
|       (void) qx32c(real x32[4][4]);
|     real x32[4][4],o-Transformation matrix.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       The rotation submatrix returned will be orthonormal and right-
|     handed.  Also, there will be no perspective or shear elements;
|     i.e., x32[0][3] = x32[1][3] =x32[2][3] = 0.0; x32[3][3] contains
|     the 3D to 2D scale factor.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void qx32c(real x32[4][4])
#else
  void qx32c(x32)
  real x32[4][4];
#endif
{
  int i, j;
 
  for (i=0; i<4; i++) {
    for (j=0; j<4; j++) {
      x32[i][j] = x3to2[i][j];
    }
  }
  return;
}
