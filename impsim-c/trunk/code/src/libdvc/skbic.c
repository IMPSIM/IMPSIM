/* ------------------------------------------------------------------ */
/* skbic-01 Jan 00:19 Aug 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       This subroutine sets the keyboard interrupt flag.
|
|     Access:
|       (void) skbic();
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().  Otherwise, the keyboard interrupt will not be detected.
|       This routine sets the flag to TRUE without testing it.  It is
|     often useful to reinitialize the keyboard interrupt flag to TRUE
|     so that a new interrupt will be detected by routine qkbic().
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

#include "..\libcad\libcad.h"
void skbic()
{
  kbint = TRUE;
  return;
}
