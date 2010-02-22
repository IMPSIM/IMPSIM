/* ------------------------------------------------------------------ */
/* clrplc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Set the display device to alphanumeric mode and flush any
|     remaining characters from the local output buffer.
|
|     Access:
|       (void) clrplc();
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
void clrplc()
{
  amodec();
  bflshc();
  return;
}
