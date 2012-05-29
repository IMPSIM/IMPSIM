/* ------------------------------------------------------------------ */
/* abortc-01 Jan 00:02 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Wrapup procedure for fatal errors in the JJU software library.
|
|     Access:
|       (void) abortc();
|
|     Error Conditions:
|       None.
|
|     Comments:
|       This routine halts execution of the calling program.
|       The applications programmer may wish to modify this routine in
|     order to print a traceback, flush any buffers, close and save
|     any files, etc.
*
*     History:
*     01 Jan 00:JJU-Original.
*     01 Jan 04:JJU-Change "RETURN" to "ENTER".
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
void abortc()
{
  int iostat;
 
  textc("", TRUE);
  textc("Fatal Error in the Software Library.",  TRUE);
  textc("Please save all printed results and",   TRUE);
  textc("Phone: (608) 262-0225 for assistance.", TRUE);
  if (qiactc()) {
    textc("Press ENTER when ready to abort: > ", FALSE);
    iostat = bfinc("?");
  }
  finplc();
  abort();
}
