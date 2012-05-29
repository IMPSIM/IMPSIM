/* ------------------------------------------------------------------ */
/* echonc-01 Jan 00:24 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Set the logical unit number for echo of input through the
|     echoc() routine.
|
|     Access:
|       (void) echonc(int lun)
|     int lun,i-Logical unit (stream) number of the file for echo.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       This routine causes the echo printing of routine echoc() to
|     become active or (if lun is negative or zero) can be used to
|     suspend its activity.  It does not cause other actions in its own
|     right.  Description of the actions of routine echoc() are listed
|     within that routine.
|       If lun is given as positive, it is assumed that it is associated
|     with a file which is already opened.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void echonc(int lun)
#else
  void echonc(lun)
  int lun;
#endif
{
  luneco = lun;
  return;
}
