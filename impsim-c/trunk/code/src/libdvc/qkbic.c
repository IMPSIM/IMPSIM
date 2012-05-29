/* ------------------------------------------------------------------ */
/* qkbic-01 Jan 00:19 Aug 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       This function returns the current value of the keyboard inter-
|     rupt flag.
|
|     Access:
|       lflag = (int) qkbic();
|     int flag,o-Current setting of interrupt flag:
|       lflag = TRUE if an interrupt has occurred, otherwise FALSE.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The value of the keyboard interrupt flag is undefined and the
|     interrupt handler is inactive until armed by a call to akbic().
|       The current value of the keyboard interrupt flag may be found
|     at any time by calling the function qkbic().  The flag may be
|     cleared at any time by calling ckbic().
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

#include "..\libcad\libcad.h"
int qkbic()
{
# ifdef __WATCOMC__
    char string[12];

    datec(string);  /* Detecting a signal requires a DOS system call. */
# endif
  return(kbint);
}
