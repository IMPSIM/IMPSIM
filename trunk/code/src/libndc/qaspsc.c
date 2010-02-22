/* ------------------------------------------------------------------ */
/* qaspsc-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Return the current aspect ratio of the screen of the graphic
|     display device.
|
|     Access:
|       aspect = (real) qaspsc();
|     real aspect,o-Aspect (height/width) ratio of the graphic screen.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       Aspect is the ratio of height to width of the full screen of the
|     graphic display device, and does not change when the usable screen
|     window is redefined by calling framsc().
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
real qaspsc()
{
  return(aspect);
}
