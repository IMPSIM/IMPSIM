/* ------------------------------------------------------------------ */
/* slid3c-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Translate the 3D coordinate system by (dx, dy, dz, w) 3D units
|     along its own axes relative to the page.
|
|     Access:
|       (void) slid3c(real dx, real dy, real dz, real w);
|     real dx,i-The relative 3D x-coordinate to slide through.
|     real dy,i-The relative 3D y-coordinate to slide through.
|     real dz,i-The relative 3D z-coordinate to slide through.
|     real w, i-The 3D homogeneous coordinate for this increment.
|
|     Error Conditions:
|       If fabs(w) is less than 0.0001, no action is taken.
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
  void slid3c(real dx, real dy, real dz, real w)
#else
  void slid3c(dx, dy, dz, w)
  real dx, dy, dz, w;
#endif
{
# define ZRO 0.0001
  int  i;
  real x, y, z;
 
  if (fabs(w) >= ZRO){
    x = dx / w;
    y = dy / w;
    z = dz / w;
    for (i=0; i<3; i++) {
      x3to2[i][3] += x3to2[i][0] * x + x3to2[i][1] * y + x3to2[i][2]* z;
    }
    x2to3[0][3] -= x2to3[3][3] * x;
    x2to3[1][3] -= x2to3[3][3] * y;
    x2to3[2][3] -= x2to3[3][3] * z;
    lspen = FALSE;
    l3pen = FALSE;
  }
  return;
# undef ZRO
}
