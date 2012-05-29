/* ------------------------------------------------------------------ */
/* promtc-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Provide a prompt for keyboard input for the interactive user.
|
|     Access:
|       (void) promtc();
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       This routine also moves the alpha pen to the next available line
|     following an assumed alpha input.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
void promtc()
{
  if (intact && (lunrd <= 0)) textc("> ", FALSE);
  return;
}
