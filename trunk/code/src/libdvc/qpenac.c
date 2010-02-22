/* ------------------------------------------------------------------ */
/* qpenac-01 Jan 00:03 Oct 06
|     (C)Copyright, JJU Research, 2000-2006.
|
|     Description:
|       Return the current alpha screen coordinates of the alpha pen.
|
|     Access:
|       (void) qpenac(int *i, int *j)
|     int *i,o-Line number down from the top of the alpha screen.
|     int *j,o-Character position within line i.
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
  void qpenac(int *i, int *j)
#else
  void qpenac(i, j)
  int *i, *j;
#endif
{
  *i = ipen - line0 + 1;
  *j = jpen + 1;
  return;
}
