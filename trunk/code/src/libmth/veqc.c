/* ------------------------------------------------------------------ */
/* veqc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Copy the n-dimensional real vector u to vector v = u.
|
|     Access:
|       (void) veqc(int n, real u[], real v[])
|     int  n,   i-The number of components in the two vectors.
|     real u[n],i-The components of the given vector, u.
|     real v[n],o-The components of the returned vector, v = u.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void veqc(int n, real u[], real v[])
#else
  void  veqc(n, u, v)
  int  n;
  real u[], v[];
#endif
{
  int j;
 
  for (j=0; j<n; j++) {
    v[j] = u[j];
  }
  return;
}
