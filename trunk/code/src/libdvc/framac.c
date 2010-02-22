/* ------------------------------------------------------------------ */
/* framac-07 Aug 03
|     (C)Copyright, JJU Research, 2003.
|
|     Description:
|       Set the display device alpha window boundaries for subsequent
|     text commands.
|
|     Access:
|       (void) framac(int imx, int jmx);
|     int imx,i-Maximum text line   allowable on the alpha screen.
|     int jmx,i-Maximum text column allowable on the alpha screen.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       The alpha window boundaries may be changed at will by calling
|     framac().  Before the first call, the screen window boundaries are
|     coincident with the edges of the graphic display screen.
|       All of the calling parameters must have values between 1 and the
|     limits consistent with the screen and character sizes.
*
*     History:
*     07 Aug 03:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void framac(int imx, int jmx)
#else
  void framac(imx, jmx)
  int imx, jmx;
#endif
{
  imax = min(MXLINE, max(1, imx));
  jmax = min(MXIOBF, max(1, jmx));
  return;
}
