/* ------------------------------------------------------------------ */
/* dvuec-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Define the view transformation matrix between 3D and 2D.
|
|     Access:
|       (void) dvuec(real out[3], real vert[3]);
|     real out[3], i-3D vector normal to the viewing plane.
|     real vert[3],i-3D vector to appear vertical on the screen.
|
|     Error Conditions:
|       If the absolute value of either the out[] or vert[] vectors is
|     less than the size of a single pixel, then the identity transform-
|     ation matrix is used for the view transformation.
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
  void dvuec(real out[3], real vert[3])
#else
  void dvuec(out, vert)
  real out[3], vert[3];
#endif
{
  int  i, j;
  real zero;
 
/* Set the identity transformation. */
  for (i=0; i<4; i++) {
    for (j=0; j<4; j++) {
      x2to3[j][i] = 0.0;
    }
    x2to3[i][i] = 1.0;
  }
 
/* Set the user defined view parameters into x2to3. */
  zero = qscl3c() * qzro2c();
  if ((vabsc(3, out) > zero) && (vabsc(3, vert) > zero)) {
    for (j=0; j<3; j++) {
      x2to3[1][j] = vert[j];
      x2to3[2][j] = out[j];
    }
    vcrosc(vert, out, x2to3);
    vcrosc(out, x2to3, &(x2to3[1][0]));
    for (j=0; j<3; j++) {
      vnormc(3, &(x2to3[j][0]));
    }
  }
 
/* Recompute the updated x3to2 transformation. */
  for (i=0; i<3; i++) {
    for (j=i; j<3; j++) {
      x3to2[j][i] = x2to3[i][j];
    }
    x3to2[3][i] = 0.0;
    x3to2[i][3] = 0.0;
  }
  x3to2[3][3] = 1.0;
  l3pen = FALSE;
  return;
}
