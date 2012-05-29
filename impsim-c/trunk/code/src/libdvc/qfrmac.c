/* ------------------------------------------------------------------ */
/* qfrmac-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Return the row and column limits of the alpha screen.
|
|     Access:
|       (void) qfrmac(int *imx, int *jmx)
|     int *imx,o-Maximum number of text lines  on the alpha screen.
|     int *jmx,o-Maximum characters for a line on the alpha screen.
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
#ifdef ANSI
  void qfrmac(int *imx, int *jmx)
#else
  void qfrmac(imx, jmx)
  int *imx, *jmx;
#endif
{
  *imx = imax;
  *jmx = jmax;
  return;
}
