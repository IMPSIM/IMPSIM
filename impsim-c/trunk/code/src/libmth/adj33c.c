/* ------------------------------------------------------------------ */
/* adj33c-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Form the adjoint of a real (3x3) matrix.
|
|     Access:
|       (void) adj33c(real a[3][3], real adj[3][3]);
|     real a[3][3],i-The matrix whose adjoint is desired.
|     real adj[3][3],o-The adjoint of matrix a.
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
  void adj33c(real a[3][3], real adj[3][3])
#else
  void adj33c(a, adj)
  real a[3][3], adj[3][3];
#endif
{
  adj[0][0] = a[1][1] * a[2][2] - a[1][2] * a[2][1];
  adj[0][1] = a[2][1] * a[0][2] - a[2][2] * a[0][1];
  adj[0][2] = a[0][1] * a[1][2] - a[0][2] * a[1][1];
  adj[1][0] = a[1][2] * a[2][0] - a[1][0] * a[2][2];
  adj[1][1] = a[2][2] * a[0][0] - a[2][0] * a[0][2];
  adj[1][2] = a[0][2] * a[1][0] - a[0][0] * a[1][2];
  adj[2][0] = a[1][0] * a[2][1] - a[1][1] * a[2][0];
  adj[2][1] = a[2][0] * a[0][1] - a[2][1] * a[0][0];
  adj[2][2] = a[0][0] * a[1][1] - a[0][1] * a[1][0];
  return;
}
