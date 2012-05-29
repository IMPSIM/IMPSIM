/* ------------------------------------------------------------------ */
/* vlessc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Subtract an n-dimensional real vector u from vector v to form a
|     vector difference w = v - u.
|
|     Access:
|       (void) vlessc(int n, real v[], real u[], real w[]);
|     int  n,   i-The number of components in the vectors.
|     real v[n],i-The components of the vector v.
|     real u[n],i-The components of the vector u.
|     real w[n],o-The components of the difference vector, w = v - u.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       If desired, the resulting vector w may overwrite either of the
|     vectors, v or u, as follows: (void) vlessc(n, v, u, v).
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void vlessc(int n, real v[], real u[], real w[])
#else
  void vlessc(n, v, u, w)
  int  n;
  real v[], u[], w[];
#endif
{
  int j;
 
  for (j=0; j<n; j++){
    w[j] = v[j] - u[j];
  }
  return;
}
