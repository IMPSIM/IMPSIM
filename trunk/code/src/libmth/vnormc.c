/* ------------------------------------------------------------------ */
/* vnormc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Normalize an n-dimension real vector v.
|
|     Access:
|       (void) vnormc(int n, real v[])
|     int  n,   i  -The number of components in the vector.
|     real v[n],i/o-The array of components defining the vector.
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
  void vnormc(int n, real v[])
#else
  void vnormc(n, v)
  int  n;
  real v[];
#endif
{
  int  i;
  real temp;
 
  temp = vabsc(n, v);
  temp = sign(max(fabs(temp), ZERO), temp);
  for (i=0; i<n; i++) {
    v[i] /= temp;
  }
  return;
}
