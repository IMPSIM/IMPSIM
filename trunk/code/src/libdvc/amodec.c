/* ------------------------------------------------------------------ */
/* amodec-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Set the display device to alphanumeric mode.
|
|     Access:
|       (void) amodec();
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
void amodec()
{
  lsmode=FALSE;
  lspen =FALSE;
  return;
}
