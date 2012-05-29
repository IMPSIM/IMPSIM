/* ------------------------------------------------------------------ */
/* finplc-01 Jan 00:16 Oct 06
|     (C)Copyright, JJU Research, 2000-2006.
|
|     Description:
|       Deactivate any currently active display device and properly
|     close the local i/o buffers and open files.
|
|     Access:
|       (void) finplc();
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       The application program should always call finplc() after all
|     i/o is completed to insure proper flushing of local output buffer
|     and proper closing of open files.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

#include "..\libcad\libcad.h"
void finplc()
{
# ifdef __WATCOMC__
#   include <graph.h>
# else
#   include "xglblc.h"
# endif
  static int finplc_initialized = FALSE;

  if (!finplc_initialized) {
    lunin  = lunitc("input");
    lunio  = lunitc("output");
    lunerr = lunio;
    luneco = 0;
    lunpr  = 0;
    lunrd  = 0;
    lunsmb = 0;
    lunwr  = 0;
    crlf   = FALSE;
    streams[lunio] = stdout;
    finplc_initialized = TRUE;
  }
  if (crlf) {
    ipen++;
    if (dspdvc == DT_GRAPHIC) ipen = min(ipen, imax - 1);
    jpen = 0;
    amodec();
  }
  clrplc();
  free(text_buff);
  text_buff = NULL;
  free(textq);
  textq = NULL;
  free(text_color);
  text_color = NULL;
  if (dspdvc == DT_GRAPHIC) {
#   ifdef __WATCOMC__
      _setvideomode( _DEFAULTMODE );
#   else
      if (X_Initialized) {
        xclosc(win);
        xendc();
      }
#   endif
  }
  dspdvc = DT_ALPHA;
  return;
}
