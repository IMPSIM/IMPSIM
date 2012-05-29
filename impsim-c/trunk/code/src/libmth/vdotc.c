/* ------------------------------------------------------------------ */
/* vdotc-01 JAN 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Form the dot product of two n-dimensional real vectors v and u.
|
|     Access:
|       vdot = (real) vdotc(int n, real v[], real u[]);
|     int  n,   i-The number of components in vectors v and u.
|     real v[n],i-The components of the premultiplying vector v.
|     real u[n],i-The components of the postmultiplying vector u.
|     real vdot,o-The resulting dot product value, vu = v . u.
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
  real vdotc(int n, real v[], real u[])
#else
  real vdotc(n, v, u)
  int  n;
  real v[], u[];
#endif
{
  int  j;
  real vdot;
 
  vdot = 0.0;
  for (j=0; j<n; j++) {
    vdot += v[j] * u[j];
  }
  return(vdot);
}
