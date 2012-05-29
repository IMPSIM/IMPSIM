/* ------------------------------------------------------------------ */
/* qscl3c-01 Jan 00:23 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Return the current 3D to 2D scale factor.
|
|     Access:
|       factor = (real) qscl3c();
|     real factor,o-The current 3D to 2D scale factor.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       The scale factor returned gives 2D distance units per 3D dist-
|     ance unit.
|       The 3D to page scale factor may be changed at will by calling
|     scal3c().
|       The scale factor returned does not include the effect of per-
|     spective, i.e. it is a proper scale factor for a distance in the
|     plane of the 2D x-y coordinate system, but does not include the
|     effect of foreshortening for points not in that plane.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
real qscl3c()
{
  real d;
 
  d = x3to2[3][3];
  if (fabs(d) < ZERO) d = sign(ZERO, d);
  return(1.0 / d);
}
