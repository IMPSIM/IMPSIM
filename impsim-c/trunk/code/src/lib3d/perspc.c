/* ------------------------------------------------------------------ */
/* perspc-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Set the viewing distance for subsequent perspective views.
|
|     Access:
|       (void) perspc(real eyedst)
|     real eyedst,i-The distance of the eye from the center of the
|       screen, given in 2D length units.
|
|     Error Conditions:
|       A very large distance (eyedst > 10000.0)is treated as infinite,
|     thus producing an orthogonal view.
|       A very small distance (abs(eyedst) < 0.0001) is close to being
|     undefined, and is treated as eyedst = 0.0001.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       The picture plane is assumed to be the x-y plane of the 2D
|     coordinate system, with the eye located out by the specified dist-
|     ance from the center of the screen window.
|       3D clipping is performed by clip2c() for all 3D drawing opera-
|    tions; therefore, any graphic data behind the eye will not be
|    visible.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void perspc(real eyedst)
#else
  void perspc(eyedst)
  real eyedst;
#endif
{
# define ZRO 0.0001
 
  if (fabs(eyedst) > ZRO){
    eyeinv = 1.0 / eyedst;
  } else {
    eyeinv = 1.0 / ZRO;
  }
  if (fabs(eyeinv) < ZRO) eyeinv = 0.0;
  lspen=FALSE;
  l2pen=FALSE;
  l3pen=FALSE;
  return;
# undef ZRO
}
