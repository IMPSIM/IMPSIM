/* ------------------------------------------------------------------ */
/* qorg3c-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Return the 2D coordinates of the origin of the 3D coordinate
|     system.
|
|     Access:
|       (void) qorg3c(real *x2, real *y2, real *z2);
|     real *x2,o-The 2D x-coordinate of the 3D origin.
|     real *y2,o-The 2D y-coordinate of the 3D origin.
|     real *z2,o-The 2D z-coordinate of the 3D origin.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       Realignment of the 3D axes relative to the 2D may take place
|     by calls to slid3c(), slidec(), turn3c(), turnc(), vreadc(),
|     multvc(), and/or perspc().
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void qorg3c(real *x2, real *y2, real *z2)
#else
  void qorg3c(x2, y2, z2)
  real *x2, *y2, *z2;
#endif
{
# define ZRO 0.0001
  real w2;
 
  x3to2c(0.0, 0.0, 0.0, 1.0, x2, y2, z2, &w2);
  if (fabs(w2) < ZRO) w2 = sign(ZRO, w2);
  *x2 /= w2;
  *y2 /= w2;
  *z2 /= w2;
  return;
# undef ZRO
}
