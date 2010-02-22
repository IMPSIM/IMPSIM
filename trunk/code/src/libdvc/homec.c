/* ------------------------------------------------------------------ */
/* homec-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Place the graphic pen at the top left corner of the graphic
|     screen.
|
|     Access:
|       (void) homec();
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The graphic display device must have been defined by a previous
|     call to devic().
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

#include "..\libcad\libcad.h"
void homec()
{
  movasc(smin, tmax);
  return;
}
