/* ------------------------------------------------------------------ */
/* bellc-01 Jan 00:22 Apr 06
|     (C)Copyright, JJU Research, 2000-2006.
|
|     Description:
|       Sound the bell or other audible signal at the display terminal.
|
|     Access:
|       (void) bellc();
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       This routine is inoperative except in interactive execution.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
void bellc()
{
  if (intact) putc((int) '\a', streams[STDOUT]);
  return;
}
