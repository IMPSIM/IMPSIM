/* ------------------------------------------------------------------ */
/* qasp2c-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Return the current aspect ratio of a unit square in the 2D
|     coordinate system, as transformed onto the  2D screen of the
|     graphic display device.
|
|     Access:
|       aspect = (real) qasp2c();
|     real aspect,o-Aspect ratio (height/width) of a 2D unit square as
|       transformed to screen coordinates.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
real qasp2c()
{
  real aspct;

  aspct = aspect * y2scal /x2scal;
  return(aspct);
}
