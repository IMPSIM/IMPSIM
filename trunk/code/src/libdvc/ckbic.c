/* ------------------------------------------------------------------ */
/* ckbic-01 Jan 00:19 Aug 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       This routine clears the keyboard interrupt flag.
|
|     Access:
|       (void) ckbic();
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().  Otherwise, the keyboard interrupt will not be detected.
|       This routine sets the flag to FALSE without testing it.  It is
|     often useful to reinitialize the keyboard interrupt flag to FALSE
|     so that a new interrupt may be detected by routine qkbic() rather
|     than an older one.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

#include "..\libcad\libcad.h"
void ckbic()
{
  kbint = FALSE;
  return;
}
