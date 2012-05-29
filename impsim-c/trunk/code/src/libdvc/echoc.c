/* ------------------------------------------------------------------ */
/* echoc-01 Jan 00:15 Aug 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Echo the last line of user input, if appropriate.
|
|     Access:
|       (void) echoc();
|
|     Error Conditions:
|       None.
|
|     Comments:
|       This routine produces an echo of the last input line under the
|     condition that it was not echoed either because of the user's
|     direct interactive input or because of the system echo settings.
*
*     History:
*     01 Jan 00:JJU-Original.
*     15 Aug 03:JJU-Adopted from IMP into LIBCAD
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
void echoc()
{
  int lunwr;

  if (lunitc("echo") != lunitc("output")){
    if ((lunitc("read") > 0) || !qiactc()){
      lunwr = lunitc("print") > 0;
      if (lunwr > 0) prntrc("off", "", "", "");
      textc(inbufr, TRUE);
      if (lunwr > 0) prntrc("on", "", "", "");
    }
  }
  return;
}
