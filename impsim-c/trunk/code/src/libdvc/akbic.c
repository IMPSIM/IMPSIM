/* ------------------------------------------------------------------ */
/* akbic-01 Jan 00:19 Aug 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       This routine arms the host system to monitor all interactive
|     input for a keyboard interrupt character and sets the interrupt
|     flag to TRUE when such an interrupt occurs.
|
|     Access:
|       (void) akbic();
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       The value of the keyboard interrupt flag is undefined and the
|     interrupt handler is inactive until armed by a call to akbic().
|       The current value of the keyboard interrupt flag may be found at
|     any time by calling the function qkbic().  The flag may be cleared
|     at any time by calling ckbic().
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

#include "..\libcad\libcad.h"
void akbic()
{
  kbwtch = TRUE;
  if (qiactc()) {
    signal(SIGINT,   (PFV) kbic);
    signal(SIGBREAK, (PFV) kbic);
  }
  kbint = FALSE;
  return;
}
