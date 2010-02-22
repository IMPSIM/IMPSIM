/* ------------------------------------------------------------------ */
/* vplusc-01 JAN 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Add two n-dimensional real vectors v and u to form the vector
|     sum, w = v + u.
|
|     Access:
|       (void) vplusc(int n, real v[], real u[], real w[]);
|     int  n,   i-The number of components in each vector.
|     real v[n],i-The components of the first vector, v.
|     real u[n],i-The components of the second vector, u.
|     real w[n],o-The components of the sum vector, w = v + u.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       If desired, the resulting sum vector w may overwrite either of
|     the given vectors, v or u, as follows: (void) vplusc(n, v, u, v).
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void vplusc(int n, real v[], real u[], real w[])
#else
  void vplusc(n, v, u, w)
  int  n;
  real v[], u[], w[];
#endif
{
  int j;
 
  for (j=0; j<n; j++) {
    w[j] = v[j] + u[j];
  }
  return;
}
