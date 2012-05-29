/* ------------------------------------------------------------------ */
/* vabsc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Determine the absolute value (magnitude) of an n-dimensional
|     real vector v.
|
|     Access:
|       size = (real) vabsc(int n, real v[]);
|     int  n,   i-The number of components in vector v[].
|     real v[n],i-The components of vector v[].
|     real size,o-The absolute value of vector v[].
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
#if defined(ANSI)
  real vabsc(int n, real v[])
#else
  real vabsc(n, v)
  int  n;
  real v[];
#endif
{
  int  j;
  real vabs;
 
  vabs = 0.0;
  for (j=0; j<n; j++) {
    vabs += v[j] * v[j];
  }
  vabs = sqrt(vabs);
  return(vabs);
}
