/* ------------------------------------------------------------------ */
/* xendc-01 Jan 00:01 Jan 04
|     (C)Copyright, JJU Research, 2000-2004.
|
|     Description:
|       This function ends this X window session.
|
|     Access:
|       (void) xendc();
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The X library must have been initialized by a previous call to
|     function xinitc().
|       All windows must be closed using xclosc() before xendc() is
|     called.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

#include "..\libcad\libcad.h"
void xendc()
{
# ifndef __WATCOMC__
#   include "xglblc.h"

/* Free GCs. */
    XFreeGC(dsp, text_gc);
    XFreeGC(dsp, gtext_gc);
    XFreeGC(dsp, line_gc);
    XFreeGC(dsp, fill_gc);
    XFreeGC(dsp, bkgnd_gc);
    XFreeCursor(dsp, arrow_cursor);
    XFreeCursor(dsp, watch_cursor);
    XCloseDisplay(dsp);
    X_Initialized = FALSE;
# endif
  return;
}
