/* ------------------------------------------------------------------ */
/* rgtvuc-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Set up the 3D to 2D coordinate transformation to produce a
|     true view of a shape, given the unit outward normal vector for
|     the new view in the coordinate system of the shape.
|
|     Access:
|       (void) rgtvuc(real vnorm[3]);
|     real vnorm[3],i-Unit outward normal vector for the new view.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       The given outward normal vector becomes perpendicular to the 2D
|     viewing plane and is directed toward the viewer in the new view.
|     The scale factor and 2D location of the 3D origin are not modified.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void rgtvuc(real vnorm[3])
#else
  void rgtvuc(vnorm)
  real vnorm[3];
#endif
{
  int  i, j, jlast, jmin, jnext;
  real denom, vmin;
 
/* Set in the normal vector and find the smallest component. */
  vmin = 2.0;
  for (j=0; j<3; j++) {
    x3to2[2][j] = vnorm[j];
    if (vmin > fabs(vnorm[j])) {
      vmin = fabs(vnorm[j]);
      jmin = j;
    }
  }
  jnext = (jmin  + 1) % 3;
  jlast = (jnext + 1) % 3;
 
/* Complete the rotation submatrix column vectors. */
  denom = sqrt(1.0 - vmin * vmin);
  x3to2[0][jmin ] = denom;
  x3to2[1][jmin ] = 0.0;
  x3to2[0][jnext] =-x3to2[2][jmin] * x3to2[2][jnext] / denom;
  x3to2[1][jnext] =                  x3to2[2][jlast] / denom;
  x3to2[0][jlast] =-x3to2[2][jmin] * x3to2[2][jlast] / denom;
  x3to2[1][jlast] =                 -x3to2[2][jnext] / denom;
 
/* Form the inverse transformation. */
  for (i=0; i<3; i++) {
    for (j=0; j<3; j++) {
      x2to3[i][j] = x3to2[j][i];
    }
  }
  x2to3[3][3] = 1.0 / x3to2[3][3];
  for (i=0; i<3; i++) {
    x2to3[i][3] = 0.0;
    for (j=0; j<3; j++) {
      x2to3[i][3] -= x2to3[i][j] * x3to2[j][3] * x2to3[3][3];
    }
  }
  lspen = FALSE;
  l3pen = FALSE;
  return;
}
