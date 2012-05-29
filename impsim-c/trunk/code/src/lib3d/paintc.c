/* ------------------------------------------------------------------ */
/* paintc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       This is a dummy routine for applications not including paintc().
|
|     Access:
|       (void) paintc(int junk);
|     int junk,i-Single unused integer argument.
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
  void paintc(int junk)
#else
  void paintc(junk)
  int junk;
#endif
{
  printf("Dummy LIBCAD version of paintc(): parameter =%2i\n", junk);
  return;
}
