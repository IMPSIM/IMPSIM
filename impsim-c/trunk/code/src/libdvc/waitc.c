/* ------------------------------------------------------------------ */
/* waitc-01 Jan 00:24 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Produce an interactive wait for a keyboard input.
|
|     Access:
|       (void) waitc();
|
|     Error Conditions:
|       For non-interactive execution, no action is taken.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       A prompt message is printed for the user.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
void waitc()
{
  char response[4];
 
  if (intact) {
    textc("Press 'ENTER' to continue: > ", TRUE);
    scanf("%c", response);
/*  textc("Press 'ENTER' to continue: > ", FALSE);
    bfinc("?"); */
  }
  return;
}
