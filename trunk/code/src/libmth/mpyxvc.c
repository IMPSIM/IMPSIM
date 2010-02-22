/* ------------------------------------------------------------------ */
/* mpyxvc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Multiply a homogeneous coordinate rigid body transformation
|     matrix x by a three-dimensional vector v, and store the result in
|     the vector xv = x * v.
|
|     Access:
|       (void) mpyxvc(real x[3][4], real v[3], real xv[3])
|     real x[3][4],i-The premultiplying transformation matrix, stored
|       with the last row implied as [0.0, 0.0, 0.0, 1.0].
|     real v[3],i-The components of the given vector, stored with the
|       last component implied as 0.0.
|     real xv[3],o-The components of the transformed vector xv = x * v,
|       stored with the last component implied as 0.0.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       Note that matrix x is assumed stored in row-major (C) rather
|     than column-major (Fortran) format.
|       The transformed vector xv may overwrite the given vector v if
|     desired as follows: mpyxvc(x, v, v).
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void mpyxvc(real x[3][4], real v[3], real xv[3])
#else
  void mpyxvc(x, v, xv)
  real x[3][4], v[3], xv[3];
#endif
{
  int  i, j;
  real temp[3];
 
  for (i=0; i<3; i++) {
    temp[i] = 0.0;
    for (j=0; j<3; j++) {
      temp[i] += x[i][j] * v[j];
    }
  }
  for (i=0; i<3; i++) {
    xv[i] = temp[i];
  }
  return;
}
